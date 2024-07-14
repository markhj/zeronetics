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
    std::shared_ptr<ZEN::VAO> vao;
    std::shared_ptr<ZEN::VBO> vbo;
}

void ZEN::OpenGLRenderer::render() {
    if (!renderManager) {
        ZEN_WARN("No render manager provided", ZEN::LogCategory::Rendering);
        return;
    } else if (!renderManager->camera3d) {
        ZEN_WARN("No camera on render manager", ZEN::LogCategory::Rendering);
        return;
    }

    glEnable(GL_DEPTH_TEST);

    handleAllocations();


    // @todo: Don't allocate on every frame -- Allocate when objects without
    //      allocation data are discovered
    int drawVertices = 0;
    std::vector<GLfloat> vertices;
    for (const auto &group: renderManager->renderGroups3d) {
        for (const auto &renderable3d: group->renderables3d) {
            auto rVertices = renderable3d.second->getVertices();
            for (const Vertex3D &v: rVertices) {
                vertices.emplace_back(v.position.x);
                vertices.emplace_back(v.position.y);
                vertices.emplace_back(v.position.z);
                vertices.emplace_back(v.color->r);
                vertices.emplace_back(v.color->g);
                vertices.emplace_back(v.color->b);
                ++drawVertices;
            }
        }
    }
    vbo->setData(vertices);

    MVP mvp = renderManager->camera3d->getModelViewProjection();

    for (const auto &group: renderManager->renderGroups3d) {
        group->shader->set("model", mvp.model);
        group->shader->set("view", mvp.view);
        group->shader->set("projection", mvp.projection);

        group->shader->use();

        vao->with([&]() {
            glDrawArrays(GL_TRIANGLES, 0, drawVertices);
        });
    }
}

void ZEN::OpenGLRenderer::initialize() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    m_initialized = true;

    vbo = std::make_shared<VBO>(VBO());
    vbo->initialize();
    vbo->resize(10);
    vbo->setData({});

    vao = std::make_shared<VAO>(VAO());
    vao->initialize();
    vao->attachVBO(vbo, {VertexAttribute::Position3D, VertexAttribute::ColorRGB});
}

bool ZEN::OpenGLRenderer::isInitialized() const noexcept {
    return m_initialized;
}

void ZEN::OpenGLRenderer::clear() noexcept {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ZEN::OpenGLRenderer::handleAllocations() {
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
                handleAllocations();
                return;
            }
            renderable3d.second->gpuAlloc = allocation;
            ZEN_INFO(std::format("ALLOC: [Index: {}, Size: {}]", allocation->index, allocation->size),
                     ZEN::LogCategory::RendererInternals);
        }
    }
}
