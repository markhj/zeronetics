#pragma once

#include <bbunit/bbunit.hpp>

namespace ZEN::Tests {
    class FileSystemTest : public BBUnit::TestCase {
    public:
        void test() override;

    private:
        void pathExists();

        void directoryOrFolder();

        void getData();

        void setData();

        void append();

        void load();

        void loadOrCreate();

        void createIfNotExists();

        /**
         * @note This test may cause unexpected errors when running
         *      in coverage mode.
         */
        void deleteFile();
    };
}
