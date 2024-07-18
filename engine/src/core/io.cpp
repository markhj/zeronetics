#include <format>
#include <fstream>
#include <utility>

#include "zeronetics/core/io.h"
#include "zeronetics/logging/log.h"
#include "zeronetics/logging/logging.h"

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

ZEN::File::File(Path path) : m_path(std::move(path)) {
}

std::optional<ZEN::File> ZEN::File::load(const ZEN::Path &path) {
    if (!path.exists() || path.isDirectory()) {
        return std::nullopt;
    }
    return File(path);
}

ZEN::File ZEN::File::loadOrCreate(const ZEN::Path &path) {
    if (path.exists()) {
        if (path.isDirectory()) {
            ZEN_CRITICAL(std::format("Loading directory as file: {}", path.getAbsolute()));
        }
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
    if (!m_path.exists()) {
        ZEN_WARN(std::format("Attempting to append data to non-existing file: {}", m_path.getAbsolute()),
                 ZEN::LogCategory::FileSystem);
        return;
    } else if (m_path.isDirectory()) {
        ZEN_WARN(std::format("Cannot append data to directory: {}", m_path.getAbsolute()),
                 ZEN::LogCategory::FileSystem);
        return;
    }
    std::ofstream ofs(m_path.getAbsolute(), std::ios::app);
    ofs << text;
}

ZEN::Result<std::string> ZEN::File::getData() const {
    if (!m_path.exists()) {
        return ResultError{
            .errorMessage = std::format("Cannot load data from non-existing file: {}",
                                        m_path.getAbsolute()).c_str()
        };
    }

    std::ifstream fileStream(m_path.getAbsolute());

    if (!fileStream.is_open()) {
        return ResultError{
                .errorMessage = std::format("Could not open file: {}",
                                            m_path.getAbsolute()).c_str()
        };
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();

    fileStream.close();

    return buffer.str();
}

void ZEN::File::setData(const std::string &data) const {
    if (!m_path.exists()) {
        throw std::runtime_error("File does not exist.");
    }

    std::ofstream outFile(m_path.getAbsolute());

    if (!outFile.is_open()) {
        throw std::runtime_error("Could not open file " + m_path.getAbsolute());
    }

    outFile << data;
    outFile.close();
}

void ZEN::File::deleteFile() {
    if (!m_path.exists() || !m_path.isFile()) {
        ZEN_WARN(std::format("Attempting to delete something that is not a file: {}", m_path.getAbsolute()),
                 ZEN::LogCategory::FileSystem);
        return;
    }

    auto status = std::remove(m_path.getAbsolute().c_str());
    if (status != 0) {
        ZEN_WARN(std::format("Failed to delete file: {}", m_path.getAbsolute()), ZEN::LogCategory::FileSystem);
    }
}
