#include "opengl-renderer/opengl.h"

#include "objects/vao.h"
#include "objects/vbo.h"

#include "zeronetics/core/tensors.h"
#include "zeronetics/core/vertices.h"
#include "zeronetics/logging/logging.h"

#include <glad/glad.h>
// Keep space between glad and GLFW, otherwise clang-format
// will re-arrange their order, which causes inclusion conflicts.
#include <GLFW/glfw3.h>

#include <format>
#include <stdexcept>

namespace {
    std::shared_ptr<ZEN::OpenGL::VAO> vao;
    std::shared_ptr<ZEN::OpenGL::VBO> vbo;

    int defaultColorPos = 0;
    std::vector<ZEN::ColorRGB> defaultColors = {
            {0.0, 0.2, 1.0},
            {1.0, 1.0, 1.0},
            {0.6, 0.2, 0.6},
    };

    // @todo: Will be removed, once the more flexible implementation of
    //      VBO is added.
    unsigned int assumedVertexSize = 6;

    inline void appendFloatsFromVertex(std::vector<ZEN::OpenGL::gl_float> &vertices, const ZEN::Vertex3D &v) {
        // @todo: Will be rewritten to be more flexible,
        //      when more vertex attributes are implemented
        vertices.emplace_back(v.position.x);
        vertices.emplace_back(v.position.y);
        vertices.emplace_back(v.position.z);
        if (v.color.has_value()) {
            vertices.emplace_back(v.color->r);
            vertices.emplace_back(v.color->g);
            vertices.emplace_back(v.color->b);
        } else {
            ++defaultColorPos;
            if (defaultColorPos >= defaultColors.size()) {
                defaultColorPos = 0;
            }
            vertices.emplace_back(defaultColors[defaultColorPos].r);
            vertices.emplace_back(defaultColors[defaultColorPos].g);
            vertices.emplace_back(defaultColors[defaultColorPos].b);
        }
    }

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
            ZEN_WARN("No camera on render manager", ZEN::LogCategory::Rendering);
            continue;
        }

        glEnable(GL_DEPTH_TEST);

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

            // @todo: https://github.com/markhj/zeronetics/issues/5
            //      This part will eventually be optimized.
            vao->with([&]() {
                for (const auto &renderable: group->renderables3d) {
                    std::optional<GPUAllocation> alloc = renderable.second->gpuAlloc;
                    if (!alloc.has_value()) {
                        continue;
                    }
                    gpu_alloc_int first = alloc->index / assumedVertexSize;
                    gpu_alloc_int count = alloc->size / assumedVertexSize;
                    glDrawArrays(getPrimitive(layer->drawPrimitive), first, count);
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

    m_initialized = true;

    vbo = std::make_shared<VBO>(VBO());
    vbo->initialize();
    vbo->resize(1000);

    vao = std::make_shared<VAO>(VAO());
    vao->initialize();
    vao->attachVBO(vbo, {VertexAttribute::Position3D, VertexAttribute::ColorRGB});
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
                    appendFloatsFromVertex(vertices, v);
                }
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
    switch (request->request) {
        case RenderManagerRequest::Allocate: {
            std::vector<GLfloat> vertices;
            for (const Vertex3D &v: request->renderable3d->getVertices()) {
                appendFloatsFromVertex(vertices, v);
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
                appendFloatsFromVertex(vertices, v);
            }
            vbo->updateData(request->renderable3d->gpuAlloc.value(), vertices);
            break;
        }
        case RenderManagerRequest::Deallocate:
            // @todo: Implement de-allocation requests to OpenGL renderer
            break;
    }
}
