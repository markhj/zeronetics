#include <zeronetics/core/io.h>

#include "io-test.h"

void ZEN::Tests::FileSystemTest::test() {
    pathExists();
}

void ZEN::Tests::FileSystemTest::pathExists() {
    it("Checks whether a path exists", [&]() {
        assertFalse(ZEN::Path("does-not-exist.txt").exists());
    });
}
