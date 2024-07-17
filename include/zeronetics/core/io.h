#pragma once

#include "result.h"
#include <filesystem>
#include <optional>
#include <string>

namespace fs = std::filesystem;

namespace ZEN {
    /**
     * Path to a file or directory on the system.
     *
     * @note The file or path doesn't have to physically exist
     *      for the object to be created
     *
     * @ref file-system
     */
    class Path {
    public:
        /**
         * Create object from a relative or absolute path.
         *
         * @param path
         */
        explicit Path(const std::string &path);

        /**
         * Returns true, if whatever the path points to, exists.
         * @return
         */
        [[nodiscard]] bool exists() const noexcept;

        /**
         * Return true, if the path points to a directory.
         *
         * @return
         */
        [[nodiscard]] bool isDirectory() const noexcept;

        /**
         * Returns true, if the path points to a file.
         *
         * @return
         */
        [[nodiscard]] bool isFile() const noexcept;

        /**
         * Returns the absolute path to the file, regardless of
         * whether relative or absolute path was provided in the
         * constructor.
         *
         * @return
         */
        [[nodiscard]] std::string getAbsolute() const noexcept;

    private:
        /**
         * C++ Standard Library path object
         */
        fs::path m_path;
    };

    /**
     * A file on the system.
     *
     * @note File doesn't have to exist for the object
     *      to be created.
     *
     * @ref file-system
     */
    class File {
    public:
        /**
         * Create object from a ZEN::Path.
         *
         * @param path
         */
        explicit File(Path path);

        /**
         * Attempt to load a file.
         *
         * @note Returns ``std::nullopt`` if the file doesn't exist.
         *
         * @note Returns ``std::nullopt`` if the path is a directory.
         *
         * @param path
         * @return
         */
        static std::optional<File> load(const Path &path);

        /**
         * Load a file. If it doesn't exist, it will be created.
         *
         * @note Critical level message is raised, if the path is a directory.
         *
         * @param path
         * @return
         */
        static File loadOrCreate(const Path &path);

        /**
         * Create the file if it doesn't exist.
         *
         * @note The file will be empty.
         */
        void createIfNotExists();

        /**
         * Append to the end of the file.
         *
         * @note You will have to manage line-breaks on your own.
         *
         * @param text
         */
        void append(const std::string &text);

        /**
         * Get the entire data from the file as a string.
         *
         * An ZEN::ResultError is returned for a number of reasons,
         * but typically because the file doesn't exist.
         *
         * @return
         */
        [[nodiscard]] Result<std::string> getData() const;

        /**
         * Replace all the contents of the file with ``data``
         */
        void setData(const std::string &data) const;

    private:
        /**
         * Path instance.
         */
        Path m_path;
    };
}
