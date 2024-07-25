#include <bbunit/bbunit.hpp>
#include <bbunit/utilities/printer.hpp>

#include "cases/glsl-shader-builder-test.h"

using namespace BBUnit;
using namespace ZEN::Tests;

int main() {
    TestResults results = TestRunner::run({
            std::make_shared<GLSLShaderBuilderTest>(GLSLShaderBuilderTest()),
    });

    BBUnit::Utilities::Printer::print(results, {});
}