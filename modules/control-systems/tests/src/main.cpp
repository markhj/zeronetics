#include <bbunit/bbunit.hpp>
#include <bbunit/utilities/printer.hpp>

#include "cases/control-systems-test.h"

using namespace BBUnit;
using namespace ZEN::Tests;

int main() {
    TestResults results = TestRunner::run({
            std::make_shared<ControlSystemsTest>(ControlSystemsTest()),
    });

    BBUnit::Utilities::Printer::print(results, {});
}