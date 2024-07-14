#include <fstream>
#include <utility>

#include "zeronetics/core/io.h"

ZEN::Path::Path(const std::string &path) : m_path(fs::path(path)) {
}

bool ZEN::Path::exists() const noexcept {
    return fs::exists(m_path);
}

bool ZEN::Path::isDirectory() const noexcept {
    return fs::is_directory(m_path);
}

bool ZEN::Path::isFile() const noexcept {
    return fs::is_regular_file(m_path);
}

std::string ZEN::Path::getAbsolute() const noexcept {
    return fs::absolute(m_path).generic_string();
}

ZEN::File::File(ZEN::Path path) : m_path(std::move(path)) {
}

std::optional<ZEN::File> ZEN::File::load(const ZEN::Path &path) {
    if (!path.exists()) {
        return std::nullopt;
    }
    return File(path);
}

ZEN::File ZEN::File::loadOrCreate(const ZEN::Path &path) {
    if (path.exists()) {
        return File(path);
    }
    File file(path);
    file.createIfNotExists();
    return file;
}

void ZEN::File::createIfNotExists() {
    if (m_path.exists()) {
        return;
    }
    std::ofstream ofs(m_path.getAbsolute());
}

void ZEN::File::append(const std::string &text) {
    std::ofstream ofs(m_path.getAbsolute(), std::ios::app);
    ofs << text;
}
