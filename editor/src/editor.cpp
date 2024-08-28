#include "editor.h"
#include "box.h"
#include "ui-elements/button.h"
#include "utilities/editor-layout.h"
#include "utilities/editor-ui.h"
#include "utilities/font-manager.h"
#include "utilities/modals/about.h"
#include "utilities/modals/load-project.h"
#include "utilities/modals/new-project.h"
#include "utilities/modals/project-screen.h"
#include "utilities/modals/project-settings.h"
#include "utilities/side-panel.h"

#include <gizmos/3d-grid.h>
#include <glsl-shader-builder/glsl-shader-builder.h>
#include <zeronetics/zeronetics.h>

#include <control-systems/free-camera.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

using namespace ZEN;
using namespace ZEN::ControlSystems;

std::shared_ptr<ControlManager> m_controlManager = std::make_shared<ControlManager>(ControlManager());

std::optional<ZEN::MousePosition> s_lastPosition;

ZenEdit::Editor::Editor() : m_renderer(std::make_shared<OpenGL::Renderer>(OpenGL::Renderer())),
                            m_renderManager(std::make_shared<RenderManager>(RenderManager())),
                            m_camera(std::make_shared<Camera3D>(Camera3D())),
                            m_project(std::make_shared<Project>(Project())),
                            m_delta(0.0) {
    m_camera->position = Vec3(4.0);
    m_camera->target = Vec3(0.0);
}

void ZenEdit::Editor::initialize() noexcept(false) {
    Log::blacklistCategories = {
            LogCategory::ShaderCompilation,
            LogCategory::RendererInternals,
            LogCategory::RendererInit,
    };

    m_editorConfig.load();

    Globals::viewportSize = ViewportSize(1280, 720);

    if (!glfwInit()) {
        throw std::runtime_error("Cannot initialize GLFW.");
    }

    m_window = glfwCreateWindow(Globals::viewportSize.w,
                                Globals::viewportSize.h,
                                "ZenEdit",
                                nullptr,
                                nullptr);

    if (m_window == nullptr) {
        throw std::runtime_error("Failed to initialize editor window.");
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(m_window, keyboardCallback);
    glfwSetCursorPosCallback(m_window, mouseMoveCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    configureControls();
    configureStyle();

    setUpMainLayer();
    setUpGrid();
    setUpFreeCamera();

    m_renderer->setRenderManager(m_renderManager);
    m_renderer->initialize();

    refreshViewport();
}

void ZenEdit::Editor::run() {
    ImGuiIO &io = ImGui::GetIO();

    Container mainContainer{
            .title = "Objects"};

    Button btnAddCube;
    btnAddCube.text = "Cube";
    btnAddCube.onClick = [&]() { addCube(); };

    mainContainer.elements.push_back(std::make_shared<Button>(btnAddCube));

    EditorUI editorUi;
    editorUi.containers.push_back(&mainContainer);

    MainMenu mainMenu = createMainMenu();
    MainMenu projectScreenMainMenu = createProjectScreenMainMenu();

    About about(&m_showAbout);
    NewProject newProject(&m_showNewProject);
    LoadProject loadProject(&m_showLoadProject);
    ProjectSettings projectSettings(&m_showProjectSettings, m_project);
    SidePanel sidePanel(m_project);
    ProjectScreen projectScreen(&m_editorConfig, &m_showNewProject, &m_showLoadProject);

    newProject.onCreate = [&](const Path &path) { openProject(path); };
    loadProject.onLoad = [&](const Path &path) { openProject(path); };
    projectScreen.onOpenProject = [&](const std::string &path) {  openProject(Path(path)); };
    sidePanel.onOpenScene = [&](Scene &scene) { openScene(scene); };

    FontManager::initialize();

    while (!glfwWindowShouldClose(m_window)) {
        m_delta = 1.0f / io.Framerate;

        m_renderer->backgroundColor = m_showProjectScreen ? ColorRGB(0.1, 0.115, 0.14) : ColorRGB(0.0, 0.02, 0.1);
        m_renderer->clear();
        m_controlManager->process(m_delta);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        FontManager::start();

        if (m_showProjectScreen) {
            projectScreenMainMenu.render();
            projectScreen.render();
        } else {
            mainMenu.render();
            editorUi.render();
            sidePanel.render();
        }

        if (m_showAbout) {
            about.render();
        }

        if (m_showNewProject) {
            newProject.render();
        }

        if (m_showProjectSettings) {
            projectSettings.render();
        }

        if (m_showLoadProject) {
            loadProject.render();
        }

        FontManager::end();

        ImGui::Render();

        if (!m_showProjectScreen) {
            m_renderer->render();
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void ZenEdit::Editor::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action > 1) {
        return;
    }

    std::optional<ZEN::Key> inputKey = ZEN::KeyMap::toKey(key);
    if (!inputKey.has_value()) {
        return;
    }

    m_controlManager->onKeyStateChanged({
            .keyState = action == 1 ? ZEN::KeyState::JustPressed : ZEN::KeyState::JustReleased,
            .key = inputKey.value(),
    });
}

void ZenEdit::Editor::mouseMoveCallback(GLFWwindow *window, double x, double y) {
    auto mx = static_cast<ZEN::mouse_pos_axis>(x);
    auto my = static_cast<ZEN::mouse_pos_axis>(y);

    if (!s_lastPosition.has_value()) {
        s_lastPosition = {mx, my};
        return;
    }

    ZEN::MousePosition lastPos = s_lastPosition.value();

    m_controlManager->onMouseMoved({
            {mx, my},
            {static_cast<ZEN::mouse_pos_axis>(mx - lastPos.x),
             static_cast<ZEN::mouse_pos_axis>(my - lastPos.y)},
    });

    s_lastPosition = {mx, my};
}

void ZenEdit::Editor::addCube() {
    auto box = std::make_shared<Cube>(Cube(0.5));
    auto renderable = std::make_shared<Mesh3D>(Mesh3D(box));

    ++m_nextObjectId;

    renderable->position = Vec3(-static_cast<gw_float>(m_nextObjectId), 0.0, 1.0);

    std::string objId = "Obj" + std::to_string(m_nextObjectId);

    m_mainLayer->renderGroups3d[0]->renderables3d[objId] = renderable;

    m_renderManager->request(RendererRequest{
            RenderManagerRequest::Allocate,
            m_mainLayer->renderGroups3d[0]->renderables3d[objId],
            m_mainLayer,
    });
}

void ZenEdit::Editor::setUpMainLayer() {
    ZEN::ShaderBlueprint blueprint{
            .attributes = m_defaultAttribs,
            .projection = Projection::Perspective,
    };

    ZEN::GLSLShaderBuilder shaderBuilder;
    std::string vertex = shaderBuilder.make(blueprint, ShaderStage::Vertex).value();
    std::string frag = shaderBuilder.make(blueprint, ShaderStage::Fragment).value();

    std::shared_ptr<ZEN::OpenGL::Shader> shader = std::make_shared<ZEN::OpenGL::Shader>(ZEN::OpenGL::Shader());
    shader->create();
    shader->setSource(ShaderStage::Vertex, vertex);
    shader->setSource(ShaderStage::Fragment, frag);
    shader->compile();

    m_mainLayer = std::make_shared<RenderLayer>(RenderLayer(m_defaultAttribs));
    std::shared_ptr<RenderGroup3D> renderGroup = std::make_shared<RenderGroup3D>(RenderGroup3D());
    renderGroup->shader = shader;

    m_mainLayer->camera3d = m_camera;
    m_mainLayer->renderGroups3d.emplace_back(renderGroup);
    m_renderManager->attachLayer(m_mainLayer);
}

void ZenEdit::Editor::setUpGrid() {
    auto grid3d = ZEN::Gizmos::Grid3D();
    grid3d.lines = 30;

    m_gridLayer = std::make_shared<RenderLayer>(grid3d.generate());

    m_renderManager->attachLayer(m_gridLayer);

    std::shared_ptr<ZEN::OpenGL::Shader> gridShader;
    ZEN::GLSLShaderBuilder shaderBuilder;
    std::string gridVertex = shaderBuilder.make(grid3d.getShaderBlueprint(), ShaderStage::Vertex).value();
    std::string gridFrag = shaderBuilder.make(grid3d.getShaderBlueprint(), ShaderStage::Fragment).value();

    gridShader = std::make_shared<ZEN::OpenGL::Shader>(ZEN::OpenGL::Shader());
    gridShader->create();
    gridShader->setSource(ShaderStage::Vertex, gridVertex);
    gridShader->setSource(ShaderStage::Fragment, gridFrag);
    gridShader->compile();

    m_gridLayer->renderGroups3d[0]->shader = gridShader;
    m_gridLayer->camera3d = m_camera;

    m_renderManager->request(RendererRequest{
            RenderManagerRequest::Allocate,
            m_gridLayer->renderGroups3d[0]->renderables3d["Lines"],
            m_gridLayer,
    });
}

void ZenEdit::Editor::configureControls() {
    m_inputMapping = std::make_shared<InputMapping>(InputMapping());
    m_signalHandler = std::make_shared<SignalHandler>(SignalHandler());

    m_inputMapping->keyDown(Key::W, "forward");
    m_inputMapping->keyDown(Key::S, "back");
    m_inputMapping->keyDown(Key::A, "left");
    m_inputMapping->keyDown(Key::D, "right");
    m_inputMapping->keyJustPressed(Key::F, "toggle_free_camera");

    m_signalHandler->on("toggle_free_camera", [&]() {
        m_freeCameraAssist->enabled = !m_freeCameraAssist->enabled;
    });

    m_controlManager->setInputMapping(m_inputMapping);
    m_controlManager->setSignalHandler(m_signalHandler);
}

void ZenEdit::Editor::setUpFreeCamera() {
    m_freeCameraAssist = std::make_shared<FreeCamera>(FreeCamera());
    m_freeCameraAssist->camera3d = m_camera;
    m_freeCameraAssist->signals = {"forward", "left", "back", "right"};
    m_freeCameraAssist->enabled = false;
    m_controlManager->attachAssist(m_freeCameraAssist);
}

void ZenEdit::Editor::saveFile() {
    m_project->save();
}

ZenEdit::MainMenu ZenEdit::Editor::createProjectScreenMainMenu() {
    MainMenuItem fileMenu{};
    fileMenu.title = "File";
    fileMenu.items.emplace_back(MainMenuItem{MainMenuType::Item, "Exit", "", {}, [&]() { std::exit(0); }});

    MainMenuItem helpMenu{};
    helpMenu.title = "Help";
    helpMenu.items.emplace_back(MainMenuItem{MainMenuType::Item, "About...", "", {}, [&]() { m_showAbout = true; }});

    MainMenu mainMenu;
    mainMenu.mainMenuItems.emplace_back(fileMenu);
    mainMenu.mainMenuItems.emplace_back(helpMenu);

    return mainMenu;
}

ZenEdit::MainMenu ZenEdit::Editor::createMainMenu() {
    MainMenuItem fileMenu{};
    fileMenu.title = "File";
    fileMenu.items.emplace_back(MainMenuItem{MainMenuType::Item, "Save", "", {}, [&]() { saveFile(); }});
    fileMenu.items.emplace_back(MainMenuItem{MainMenuType::Separator});
    fileMenu.items.emplace_back(MainMenuItem{MainMenuType::Item, "To Project Selection", "", {}, [&]() { m_showProjectScreen = true; }});
    fileMenu.items.emplace_back(MainMenuItem{MainMenuType::Separator});
    fileMenu.items.emplace_back(MainMenuItem{MainMenuType::Item, "Exit", "", {}, [&]() { std::exit(0); }});

    MainMenuItem projectMenu{};
    projectMenu.title = "Project";
    projectMenu.items.emplace_back(MainMenuItem{MainMenuType::Item, "Settings...", "", {}, [&]() { m_showProjectSettings = true; }});

    MainMenuItem helpMenu{};
    helpMenu.title = "Help";
    helpMenu.items.emplace_back(MainMenuItem{MainMenuType::Item, "About...", "", {}, [&]() { m_showAbout = true; }});

    MainMenu mainMenu;
    mainMenu.mainMenuItems.emplace_back(fileMenu);
    mainMenu.mainMenuItems.emplace_back(projectMenu);
    mainMenu.mainMenuItems.emplace_back(helpMenu);

    return mainMenu;
}

void ZenEdit::Editor::configureStyle() {
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.99f);

    style.WindowPadding = ImVec2(20, 20);
    style.FramePadding = ImVec2(10, 10);
    style.ItemSpacing = ImVec2(12, 8);
}

void ZenEdit::Editor::openProject(const Path &path) {
    m_project->load(path);
    m_showProjectScreen = false;

    auto absolutePath = path.getAbsolute();
    auto it = std::find_if(m_editorConfig.projects.begin(),
                           m_editorConfig.projects.end(),
                           [&](const auto &item) -> bool {
                               return item == absolutePath;
                           });

    if (it == m_editorConfig.projects.end()) {
        m_editorConfig.projects.emplace_back(absolutePath);
    }

    m_editorConfig.save();
    m_editorConfig.load();
}

void ZenEdit::Editor::openScene(const ZenEdit::Scene &scene) {
    if (m_project->activeScene && m_project->activeScene->hasChanged) {
        std::cerr << "Cannot change from an un-saved scene." << std::endl;
        return;
    }

    m_project->activeScene = std::make_shared<ZenEdit::Scene>(scene);
    m_project->activeScene->load();
}

void ZenEdit::Editor::refreshViewport() {
    m_renderer->setViewport(Viewport{
            .position = {EditorLayout::sidePanelWidth, 0},
            .size = {static_cast<uint16_t>(Globals::viewportSize.w - EditorLayout::sidePanelWidth), Globals::viewportSize.h},
    });
}
