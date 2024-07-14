#include "opengl-renderer/opengl.hpp"

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
}

void ZEN::OpenGL::Renderer::render() {
    if (!renderManager) {
        ZEN_WARN("No render manager provided", ZEN::LogCategory::Rendering);
        return;
    } else if (!renderManager->camera3d) {
        ZEN_WARN("No camera on render manager", ZEN::LogCategory::Rendering);
        return;
    }

    glEnable(GL_DEPTH_TEST);

    while (!renderManager->requests.empty()) {
        processRequest(renderManager->requests.begin()->get());
        renderManager->requests.erase(renderManager->requests.begin());
    }

    MVP mvp = renderManager->camera3d->getModelViewProjection();

    for (const auto &group: renderManager->renderGroups3d) {
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
                glDrawArrays(GL_TRIANGLES, first, count);
            }
        });
    }
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
    vbo->setData({});

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
    for (const auto &group: renderManager->renderGroups3d) {
        for (auto &renderable3d: group->renderables3d) {
            if (renderable3d.second->gpuAlloc.has_value()) {
                continue;
            }
            std::optional<ZEN::GPUAllocation> allocation = vbo->allocate(18);
            if (!allocation.has_value()) {
                ZEN_INFO("Resize required", ZEN::LogCategory::RendererInternals);
                vbo->resize(vbo->getCurrentSize() * 2);
                renderManager->resetAllocations();
                handleReallocations();
                return;
            }
            renderable3d.second->gpuAlloc = allocation;
            std::vector<GLfloat> vertices;
            for (const Vertex3D &v: renderable3d.second->getVertices()) {
                appendFloatsFromVertex(vertices, v);
            }
            vbo->updateData(renderable3d.second->gpuAlloc.value(), vertices);
            ZEN_INFO(std::format("Re-allocated: [Index: {}, Size: {}]", allocation->index, allocation->size),
                     ZEN::LogCategory::RendererInternals);
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
        case RenderManagerRequest::Deallocate:
            break;
        case RenderManagerRequest::Update:
            break;
    }
}
