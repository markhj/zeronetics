#include <zeronetics/core/io.h>

#include "io-test.h"

void ZEN::Tests::FileSystemTest::test() {
    pathExists();
    directoryOrFolder();
}

void ZEN::Tests::FileSystemTest::pathExists() {
    it("Checks whether a path exists", [&]() {
        assertFalse(ZEN::Path("does-not-exist.txt").exists());
        assertTrue(ZEN::Path("payloads/io/existing-file.txt").exists());
    });
}

void ZEN::Tests::FileSystemTest::directoryOrFolder() {
    it("Checks if a path is directory or folder", [&]() {
        auto file = ZEN::Path("payloads/io/existing-file.txt");
        auto dir = ZEN::Path("payloads/io");
        auto doesNotExist = ZEN::Path("does-not-exist.txt");

        assertTrue(dir.isDirectory());
        assertFalse(file.isDirectory());

        assertFalse(dir.isFile());
        assertTrue(file.isFile());

        assertFalse(doesNotExist.isFile());
        assertFalse(doesNotExist.isDirectory());
    });
}
