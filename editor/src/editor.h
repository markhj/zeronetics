#pragma once

#include <glad/glad.h>

#include <memory>

#include <GLFW/glfw3.h>

#include "control-systems/free-camera.h"
#include "zeronetics/entities/3d/camera-3d.h"
#include "zeronetics/render/render-manager.h"

#include <control-systems/control-assist.h>
#include <opengl-renderer/opengl.h>

using namespace ZEN;
using namespace ZEN::ControlSystems;

namespace ZenEdit {
    class Editor {
    public:
        Editor();

        void initialize() noexcept(false);

        void run();

    private:
        GLFWwindow *m_window = nullptr;

        std::shared_ptr<OpenGL::Renderer> m_renderer;

        std::shared_ptr<RenderManager> m_renderManager;

        std::shared_ptr<Camera3D> m_camera;

        std::shared_ptr<FreeCamera> m_freeCameraAssist;

        std::shared_ptr<InputMapping> m_inputMapping;

        std::shared_ptr<SignalHandler> m_signalHandler;

        std::shared_ptr<RenderLayer> m_mainLayer,
                m_gridLayer;

        float m_delta;

        std::vector<VertexAttribute> m_defaultAttribs = {VertexAttribute::Position3D,
                                                         VertexAttribute::ColorRGB,
                                                         VertexAttribute::Normal3D};

        static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

        static void mouseMoveCallback(GLFWwindow *window, double x, double y);

        void setUpMainLayer();

        void setUpGrid();

        void configureControls();

        void setUpFreeCamera();
    };
}
