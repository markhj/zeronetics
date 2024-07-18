#include <zeronetics/core/io.h>

#include "io-test.h"

void ZEN::Tests::FileSystemTest::test() {
    pathExists();
    directoryOrFolder();
    getData();
    setData();
    append();
    deleteFile();
    load();
    loadOrCreate();
    createIfNotExists();
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

void ZEN::Tests::FileSystemTest::getData() {
    it("Loads a file with content.", [&]() {
        assertEquals<std::string>("Line 1\nLine 2\nLine 3",
                                  ZEN::File(ZEN::Path("payloads/io/existing-file.txt")).getData().result());
    });

    it("Attempts to load a file that doesn't exist.", [&]() {
        auto res = ZEN::File(ZEN::Path("non-existing-file.txt")).getData();
        assertTrue(res.isError());
    });
}

void ZEN::Tests::FileSystemTest::setData() {
    it("Replaces data in a file.", [&]() {
        ZEN::File file(ZEN::Path("payloads/io/set-data.txt"));
        file.setData("Hello");
        assertEquals<std::string>("Hello", file.getData().result());
        file.setData("World");
        assertEquals<std::string>("World", file.getData().result());
    });

    it("Checks that it fails to write to a non-existing file.", [&]() {
        assertException<std::exception>([&]() {
            ZEN::File(ZEN::Path("io/non-existing-file.txt")).setData("Hello");
        });
    });
}

void ZEN::Tests::FileSystemTest::append() {
    it("Appends data to a file.", [&]() {
        ZEN::File file(ZEN::Path("payloads/io/append.txt"));
        size_t currentLength = file.getData().result().length();
        file.append("More data");
        assertEquals<size_t>(currentLength + 9, file.getData().result().length());
    });
}

void ZEN::Tests::FileSystemTest::deleteFile() {
    // @note: This test may behave unexpectedly when executed in
    //      environment with code coverage.

    it("Deletes a file.", [&]() {
        ZEN::Path path = ZEN::Path("payloads/io/delete-me.txt");
        ZEN::File file = ZEN::File(path);
        file.createIfNotExists();
        assertTrue(path.exists());
        file.deleteFile();
        assertFalse(path.exists());
    });
}

void ZEN::Tests::FileSystemTest::load() {
    it("Loads an existing file.", [&]() {
        auto file = ZEN::File::load(ZEN::Path("payloads/io/existing-file.txt"));
        assertTrue(file.has_value());
    });

    it("Attempts to load non-existing file.", [&]() {
        auto file = ZEN::File::load(ZEN::Path("payloads/io/non-existing-file.txt"));
        assertFalse(file.has_value());
    });
}

void ZEN::Tests::FileSystemTest::loadOrCreate() {
    it("Loads an existing file with loadOrCreate.", [&]() {
        ZEN::Path path = ZEN::Path("payloads/io/existing-file.txt");
        // Integrity check: Ensure the test doesn't pass for the wrong reason
        assertTrue(path.exists());
        auto file = ZEN::File::loadOrCreate(path);
        assertEquals<std::string>("Line 1\nLine 2\nLine 3", file.getData().result());
    });

    it("Creates a file with loadOrCreate.", [&]() {
        ZEN::Path path = ZEN::Path("payloads/io/file-to-create.txt");

        // Integrity check: Ensure the test doesn't pass for the wrong reason
        if (path.exists()) {
            ZEN::File::loadOrCreate(path).deleteFile();
        }
        assertFalse(path.exists());

        auto file = ZEN::File::loadOrCreate(path);
        assertTrue(path.exists());
    });
}

void ZEN::Tests::FileSystemTest::createIfNotExists() {
    it("Creates a file if it does not exist.", [&]() {
        ZEN::Path path = ZEN::Path("payloads/io/create-if-not-exists.txt");
        ZEN::File file = ZEN::File(path);
        if (path.exists()) {
            file.deleteFile();
        }

        // Integrity test: Ensure the file doesn't exist from previous
        // test runs, and thereby produces the right result for the wrong reason.
        assertFalse(path.exists());

        file.createIfNotExists();
        assertTrue(path.exists());
    });
}
