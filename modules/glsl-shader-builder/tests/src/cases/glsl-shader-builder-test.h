#pragma once

#include <bbunit/bbunit.hpp>

namespace ZEN::Tests {
    class GLSLShaderBuilderTest : public BBUnit::TestCase {
    public:
        void test() override;

    private:
        void assertSource(const std::string &pathToExpected,
                          const std::string &actual);

        void simpleOrthographic();

        void simplePerspective();

        void attributes();

    };
}