#include <iostream>

#include <glad/glad.h>

#include <gizmos/3d-grid.h>
#include <glsl-shader-builder/glsl-shader-builder.h>
#include <opengl-renderer/opengl.h>
#include <zeronetics/zeronetics.h>

#include <control-systems/control-assist.h>
#include <control-systems/free-camera.h>

#include <GLFW/glfw3.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

using namespace ZEN;
using namespace ZEN::ControlSystems;

std::shared_ptr<ControlManager> controlManager = std::make_shared<ControlManager>(ControlManager());
std::optional<ZEN::MousePosition> s_lastPosition;

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action > 1) {
        return;
    }

    std::optional<ZEN::Key> inputKey = ZEN::KeyMap::toKey(key);
    if (!inputKey.has_value()) {
        return;
    }

    controlManager->onKeyStateChanged({
            .keyState = action == 1 ? ZEN::KeyState::JustPressed : ZEN::KeyState::JustReleased,
            .key = inputKey.value(),
    });
}

void mouseMoveCallback(GLFWwindow *window, double x, double y) {
    auto mx = static_cast<ZEN::mouse_pos_axis>(x);
    auto my = static_cast<ZEN::mouse_pos_axis>(y);

    if (!s_lastPosition.has_value()) {
        s_lastPosition = {mx, my};
        return;
    }

    ZEN::MousePosition lastPos = s_lastPosition.value();

    controlManager->onMouseMoved({
            {mx, my},
            {static_cast<ZEN::mouse_pos_axis>(mx - lastPos.x),
             static_cast<ZEN::mouse_pos_axis>(my - lastPos.y)},
    });

    s_lastPosition = {mx, my};
}

int main() {
    Globals::viewportSize = ViewportSize(1280, 720);

    if (!glfwInit()) {
        throw std::runtime_error("Cannot initialize GLFW.");
    }

    GLFWwindow *window = glfwCreateWindow(Globals::viewportSize.w,
                                          Globals::viewportSize.h,
                                          "ZenEdit",
                                          nullptr,
                                          nullptr);

    if (window == nullptr) {
        throw std::runtime_error("Failed to initialize editor window.");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    std::shared_ptr<Camera3D> camera = std::make_shared<Camera3D>(Camera3D());
    std::vector<VertexAttribute> defaultAttribs = {VertexAttribute::Position3D,
                                                   VertexAttribute::ColorRGB,
                                                   VertexAttribute::Normal3D};

    auto box = std::make_shared<Cube>(Cube(0.5));
    auto triangle2 = std::make_shared<Mesh3D>(Mesh3D(box));

    ZEN::GLSLShaderBuilder shaderBuilder;
    ZEN::ShaderBlueprint blueprint{
            .attributes = defaultAttribs,
            .projection = Projection::Perspective,
    };
    std::string vertex = shaderBuilder.make(blueprint, ShaderStage::Vertex).value();
    std::string frag = shaderBuilder.make(blueprint, ShaderStage::Fragment).value();
    std::shared_ptr<ZEN::OpenGL::Shader> shader;
    shader = std::make_shared<ZEN::OpenGL::Shader>(ZEN::OpenGL::Shader());
    shader->create();
    shader->setSource(ShaderStage::Vertex, vertex);
    shader->setSource(ShaderStage::Fragment, frag);
    shader->compile();

    auto layer = std::make_shared<RenderLayer>(RenderLayer(defaultAttribs));
    std::shared_ptr<RenderManager> renderManager = std::make_shared<RenderManager>(RenderManager());
    auto renderGroup = std::make_shared<RenderGroup3D>(RenderGroup3D());
    renderGroup->shader = shader;
    renderGroup->renderables3d["Cube"] = triangle2;
    std::shared_ptr<OpenGL::Renderer> renderer = std::make_shared<OpenGL::Renderer>(OpenGL::Renderer());
    layer->camera3d = camera;
    camera->position = Vec3(2.0);
    camera->target = Vec3(0.0);
    renderManager->attachLayer(layer);

    renderManager->request(RendererRequest{
            RenderManagerRequest::Allocate,
            renderGroup->renderables3d["Cube"],
            layer,
    });

    layer->renderGroups3d.emplace_back(renderGroup);

    // Control Manager
    std::shared_ptr<InputMapping> inputMapping = std::make_shared<InputMapping>(InputMapping());
    std::shared_ptr<SignalHandler> signalHandler = std::make_shared<SignalHandler>(SignalHandler());
    inputMapping->keyDown(Key::W, "forward");
    inputMapping->keyDown(Key::S, "back");
    inputMapping->keyDown(Key::A, "left");
    inputMapping->keyDown(Key::D, "right");
    controlManager->setInputMapping(inputMapping);
    controlManager->setSignalHandler(signalHandler);

    // Free Camera
    auto freeCamera = std::make_shared<FreeCamera>(FreeCamera());
    freeCamera->camera3d = camera;
    freeCamera->signals = {"forward", "left", "back", "right"};
    controlManager->attachAssist(freeCamera);

    // Grid
    auto grid3d = ZEN::Gizmos::Grid3D();
    auto grid = std::make_shared<RenderLayer>(grid3d.generate());
    std::shared_ptr<ZEN::OpenGL::Shader> gridShader;
    renderManager->attachLayer(grid);
    std::string gridVertex = shaderBuilder.make(grid3d.getShaderBlueprint(), ShaderStage::Vertex).value();
    std::string gridFrag = shaderBuilder.make(grid3d.getShaderBlueprint(), ShaderStage::Fragment).value();
    gridShader = std::make_shared<ZEN::OpenGL::Shader>(ZEN::OpenGL::Shader());
    gridShader->create();
    gridShader->setSource(ShaderStage::Vertex, gridVertex);
    gridShader->setSource(ShaderStage::Fragment, gridFrag);
    gridShader->compile();
    grid->renderGroups3d[0]->shader = gridShader;
    grid->camera3d = camera;
    renderManager->request(RendererRequest{
            RenderManagerRequest::Allocate,
            grid->renderGroups3d[0]->renderables3d["Lines"],
            grid,
    });

    // Set up rendering
    renderer->setRenderManager(renderManager);
    renderer->initialize();

    float delta;

    while (!glfwWindowShouldClose(window)) {
        renderer->clear();

        delta = 1.0f / io.Framerate;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");

        ImGui::Text("This is some useful text.");

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        controlManager->process(delta);

        renderer->render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
