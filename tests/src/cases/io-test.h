#pragma once

#include <bbunit/bbunit.hpp>

namespace ZEN::Tests {
    class FileSystemTest : public BBUnit::TestCase {
    public:
        void test() override;

    private:
        void pathExists();
    };
}
