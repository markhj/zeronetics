
#include <bbunit/bbunit.hpp>
#include <bbunit/utilities/printer.hpp>

#include "cases/io-test.h"

using namespace BBUnit;
using namespace ZEN::Tests;

int main() {
    TestResults results = TestRunner::run({
            std::make_shared<FileSystemTest>(FileSystemTest())
    });

    BBUnit::Utilities::Printer::print(results, {});
}