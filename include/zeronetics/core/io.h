#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace fs = std::filesystem;

namespace ZEN {
    class Path {
    public:
        explicit Path(const std::string &path);

        [[nodiscard]] bool exists() const noexcept;

        [[nodiscard]] bool isDirectory() const noexcept;

        [[nodiscard]] bool isFile() const noexcept;

        [[nodiscard]] std::string getAbsolute() const noexcept;

    private:
        fs::path m_path;
    };

    class File {
    public:
        explicit File(Path path);

        static std::optional<File> load(const Path &path);

        static File loadOrCreate(const Path &path);

        void createIfNotExists();

        void append(const std::string &text);

    private:
        Path m_path;
    };
}
