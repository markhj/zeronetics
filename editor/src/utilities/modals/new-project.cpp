#include "new-project.h"
#include "box.h"
#include "button.h"
#include "label.h"
#include "separator.h"
#include "zeronetics/core/io.h"
#include <format>
#include <io.h>
#include <iostream>
#include <regex>

namespace {
    std::string projectName, projectLocation;
}

ZenEdit::NewProject::NewProject(bool *showBox) : m_showBox(showBox) {
    m_createButton.text = "Create Project";
    m_createButton.onClick = [&]() { createProject(); };
    m_location.label = "Location";
    m_location.value = &projectLocation;
    m_projectName.label = "Project Name";
    m_projectName.value = &projectName;
}

void ZenEdit::NewProject::render() {
    if (m_location.value->empty()) {
        m_basePath.reset();
    } else {
        m_basePath = Path(*m_location.value);
    }

    Box box("New Project");
    box.resizable = false;
    box.collapsible = false;
    box.size = Vec2(500, 300);
    box.contains([&]() {
        Label("Create a new project.").render();

        m_location.render();
        m_projectName.render();

        if (m_createError.has_value() && !m_createError->empty()) {
            Label(m_createError.value().c_str()).render();
        }

        m_createButton.disabled = !m_basePath.has_value() || !m_basePath->exists() || !std::regex_match(*m_projectName.value, m_regexProjectName);
        m_createButton.render();

        Button closeButton;
        closeButton.text = "Cancel";
        closeButton.onClick = [&]() { *m_showBox = false; };
        closeButton.render();
    });
    box.render();
}

void ZenEdit::NewProject::createProject() {
    std::string loc = *m_location.value;
    if (loc[loc.length() - 1] != '\\') {
        loc += '\\';
    }

    std::string fullPath = loc + *m_projectName.value;
    Path rootFolder(fullPath);

    if (rootFolder.exists()) {
        m_createError = "Folder already exists.";
        return;
    }

    // Create the project root and src folders
    mkdir(fullPath.c_str());
    mkdir(std::string(fullPath + "/src").c_str());
    mkdir(std::string(fullPath + "/hxl-data").c_str());

    // Create the main project HXL file
    std::string hxlProjectSource = std::format("<Project> Project\n\tname: \"{}\"\n\n", *m_projectName.value);
    hxlProjectSource += "<Scene> Scene1\n\tpath: \"Scene1.hxl\"\n";
    Path hxlProjectPath(fullPath + "/project.hxl");
    File hxlProject(hxlProjectPath);
    hxlProject.createIfNotExists();
    hxlProject.setData(hxlProjectSource);

    copyStub(rootFolder, "CMakeLists.txt");
    copyStub(rootFolder, "src/main.cpp");

    m_projectName.value->clear();
    m_location.value->clear();
    *m_showBox = false;

    onCreate(rootFolder);
}

void ZenEdit::NewProject::copyStub(const Path &root, const char *file) {
    Path stubLocation(std::string("./stub/project/") + file + ".stub");
    Path target(root.getAbsolute() + "/" + file);

    fs::copy(stubLocation.getAbsolute(), target.getAbsolute());
}
