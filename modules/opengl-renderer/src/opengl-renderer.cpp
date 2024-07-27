#include "opengl-renderer/opengl.h"

#include "objects/vao.h"
#include "objects/vbo.h"

#include "zeronetics/core/tensors.h"
#include "zeronetics/core/vertices.h"
#include "zeronetics/helpers/vertices.h"
#include "zeronetics/logging/logging.h"

#include <glad/glad.h>
// Keep space between glad and GLFW, otherwise clang-format
// will re-arrange their order, which causes inclusion conflicts.
#include <GLFW/glfw3.h>

#include <format>
#include <stdexcept>

namespace {
    struct VaoVboPair {
        std::shared_ptr<ZEN::OpenGL::VAO> vao;
        std::shared_ptr<ZEN::OpenGL::VBO> vbo;
    };

    std::unordered_map<ZEN::unique_id, VaoVboPair> layerVaoVbos;

    GLenum getPrimitive(ZEN::DrawPrimitive drawPrimitive) {
        switch (drawPrimitive) {
            case ZEN::DrawPrimitive::Points:
                return GL_POINTS;
            case ZEN::DrawPrimitive::Lines:
                return GL_LINES;
            case ZEN::DrawPrimitive::Triangles:
                return GL_TRIANGLES;
            default:
                ZEN_LIB_ERROR("Missing case in drawPrimitive.");
                return GL_TRIANGLES;
        }
    }

    /**
     * A quick-hand method to avoid a large amount of if/else statements.
     */
    inline void setEnum(GLenum key, bool value) {
        if (value) {
            glEnable(key);
        } else {
            glDisable(key);
        }
    }

    void processSettings(const ZEN::RenderSettings &settings) {
        setEnum(GL_DEPTH_TEST, settings.depthTesting);
    }
}

void ZEN::OpenGL::Renderer::render() {
    if (!m_renderManager) {
        ZEN_WARN("No render manager provided", ZEN::LogCategory::Rendering);
        return;
    }

    while (!m_renderManager->requests.empty()) {
        processRequest(m_renderManager->requests.begin()->get());
        m_renderManager->requests.erase(m_renderManager->requests.begin());
    }

    for (const auto &layer: m_renderManager->layers) {
        if (!layer->camera3d) {
            ZEN_WARN("No camera on render layer.", ZEN::LogCategory::Rendering);
            continue;
        }

        processSettings(layer->settings);

        MVP mvp = layer->camera3d->getModelViewProjection();

        for (const auto &group: layer->renderGroups3d) {
            if (!group->shader) {
                ZEN_WARN("A render group is missing shader.", LogCategory::ShaderUse);
                continue;
            }

            group->shader->set("model", mvp.model);
            group->shader->set("view", mvp.view);
            group->shader->set("projection", mvp.projection);

            group->shader->use();

            uint8_t vertexSize = VertexAttrSize::getSize(layer->getAttributes());

            // @todo: https://github.com/markhj/zeronetics/issues/5
            //      This part will eventually be optimized.
            layerVaoVbos[layer->getLayerId()].vao->with([&]() {
                for (const auto &renderable: group->renderables3d) {
                    std::optional<GPUAllocation> alloc = renderable.second->gpuAlloc;
                    if (!alloc.has_value()) {
                        continue;
                    }
                    gpu_alloc_int first = alloc->index / vertexSize;
                    gpu_alloc_int count = alloc->size / vertexSize;
                    glDrawArrays(getPrimitive(layer->settings.draw), first, count);
                }
            });
        }
    }
}

void ZEN::OpenGL::Renderer::setRenderManager(const std::shared_ptr<IRenderManager> &renderManager) noexcept(false) {
    if (m_renderManager) {
        ZEN_CRITICAL("Swapping render managers on-the-fly is not supported.");
        return;
    }

    m_renderManager = renderManager;
}

void ZEN::OpenGL::Renderer::initialize() {
    // @todo: https://github.com/markhj/zeronetics/issues/6
    //      Fix this point of tight coupling to GLFW.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    if (!m_renderManager) {
        ZEN_CRITICAL("Cannot initialize renderer without a render manager.");
        return;
    }

    if (m_renderManager->layers.empty()) {
        ZEN_CRITICAL("There are no layers on the render manager.");
        return;
    }

    m_initialized = true;

    for (const std::shared_ptr<IRenderLayer> &layer: m_renderManager->layers) {
        unique_id id = layer->getLayerId();
        layerVaoVbos[id] = VaoVboPair{
                .vao = std::make_shared<VAO>(VAO()),
                .vbo = std::make_shared<VBO>(VBO()),
        };

        layerVaoVbos[id].vbo->initialize();
        layerVaoVbos[id].vbo->resize(1000);

        layerVaoVbos[id].vao->initialize();
        layerVaoVbos[id].vao->attachVBO(layerVaoVbos[id].vbo, layer->getAttributes());
    }
}

bool ZEN::OpenGL::Renderer::isInitialized() const noexcept {
    return m_initialized;
}

void ZEN::OpenGL::Renderer::clear() noexcept {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ZEN::OpenGL::Renderer::handleReallocations() {
    for (const auto &layer: m_renderManager->layers) {
        for (const auto &group: layer->renderGroups3d) {
            for (auto &renderable3d: group->renderables3d) {
                if (renderable3d.second->gpuAlloc.has_value()) {
                    continue;
                }
                std::vector<GLfloat> vertices;
                for (const Vertex3D &v: renderable3d.second->getVertices()) {
                    auto asFloats = Vertices::flattenVertex3D(v, layer->getAttributes());
                    vertices.insert(vertices.end(), asFloats.begin(), asFloats.end());
                }
                auto vbo = layerVaoVbos[layer->getLayerId()].vbo;
                std::optional<ZEN::GPUAllocation> allocation = vbo->allocate(vertices.size());
                if (!allocation.has_value()) {
                    ZEN_INFO("Resize required", ZEN::LogCategory::RendererInternals);
                    vbo->resize(vbo->getCurrentSize() * 2);
                    m_renderManager->resetAllocations();
                    handleReallocations();
                    return;
                }
                renderable3d.second->gpuAlloc = allocation;
                vbo->updateData(renderable3d.second->gpuAlloc.value(), vertices);
                ZEN_INFO(std::format("Re-allocated: [Index: {}, Size: {}]", allocation->index, allocation->size),
                         ZEN::LogCategory::RendererInternals);
            }
        }
    }
}

void ZEN::OpenGL::Renderer::processRequest(ZEN::IRendererRequest *request) {
    auto vbo = layerVaoVbos[request->renderLayer->getLayerId()].vbo;

    switch (request->request) {
        case RenderManagerRequest::Allocate: {
            std::vector<GLfloat> vertices;
            for (const Vertex3D &v: request->renderable3d->getVertices()) {
                auto asFloats = Vertices::flattenVertex3D(v, request->renderLayer->getAttributes());
                vertices.insert(vertices.end(), asFloats.begin(), asFloats.end());
            }

            std::optional<GPUAllocation> allocation = vbo->allocate(vertices.size());
            if (allocation.has_value()) {
                request->renderable3d->gpuAlloc = allocation;
                vbo->updateData(request->renderable3d->gpuAlloc.value(), vertices);
                ZEN_INFO(std::format("Allocated: [Index: {}, Size: {}]", allocation->index, allocation->size),
                         ZEN::LogCategory::RendererInternals);
            } else {
                handleReallocations();
            }
            break;
        }
        case RenderManagerRequest::Update: {
            if (!request->renderable3d->gpuAlloc.has_value()) {
                ZEN_WARN("Attempting to update renderable which isn't allocated.",
                         LogCategory::Rendering);
                return;
            }
            std::vector<GLfloat> vertices;
            for (const Vertex3D &v: request->renderable3d->getVertices()) {
                auto asFloats = Vertices::flattenVertex3D(v, request->renderLayer->getAttributes());
                vertices.insert(vertices.end(), asFloats.begin(), asFloats.end());
            }
            vbo->updateData(request->renderable3d->gpuAlloc.value(), vertices);
            break;
        }
        case RenderManagerRequest::Deallocate:
            std::optional<GPUAllocation> alloc = request->renderable3d->gpuAlloc;
            if (!alloc.has_value()) {
                return;
            }
            vbo->deallocate(alloc->index, alloc->size);
            request->renderable3d->gpuAlloc.reset();
            break;
    }
}
