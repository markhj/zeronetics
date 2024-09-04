#pragma once

#include <glad/glad.h>

#include <memory>

#include <GLFW/glfw3.h>

#include "control-systems/free-camera.h"
#include "utilities/editor-config.h"
#include "utilities/main-menu.h"
#include "utilities/project/project.h"
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

        void openProject(const Path &path);

        void openScene(const Scene &scene);

        void closeScene();

    private:
        GLFWwindow *m_window = nullptr;

        bool m_showProjectScreen = true;

        EditorConfig m_editorConfig;

        std::shared_ptr<Project> m_project;

        std::shared_ptr<OpenGL::Renderer> m_renderer;

        std::shared_ptr<RenderManager> m_renderManager;

        std::shared_ptr<Camera3D> m_camera;

        std::shared_ptr<FreeCamera> m_freeCameraAssist;

        std::shared_ptr<InputMapping> m_inputMapping;

        std::shared_ptr<SignalHandler> m_signalHandler;

        std::shared_ptr<RenderLayer> m_mainLayer,
                m_gridLayer;

        float m_delta;

        bool m_freeCameraActive = false;

        bool m_showAbout = false,
             m_showNewProject = false,
             m_showProjectSettings = false,
             m_showLoadProject = false,
             m_showExtensionList = false;

        MainMenu createMainMenu();

        MainMenu createProjectScreenMainMenu();

        uint16_t m_nextObjectId = 1;

        std::vector<VertexAttribute> m_defaultAttribs = {VertexAttribute::Position3D,
                                                         VertexAttribute::ColorRGB,
                                                         VertexAttribute::Normal3D};

        static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

        static void mouseMoveCallback(GLFWwindow *window, double x, double y);

        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

        static void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);

        void addCube();

        void setUpMainLayer();

        void setUpGrid();

        void configureControls();

        void setUpFreeCamera();

        void saveFile();

        void configureStyle();

        void refreshViewport();

        void createEntity(const std::string &entityName);
    };
}
