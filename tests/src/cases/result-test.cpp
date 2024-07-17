#include "result-test.h"

#include "zeronetics/core/result.h"

void ZEN::Tests::ResultTest::test() {
    it("Contains an error", [&]() {
        Result<int> subject = ResultError{13};

        assertTrue(subject.isError());
        assertEquals<int>(13, subject.error().errorCode.value());
    });

    it("Contains a result", [&]() {
        Result<int> subject = 50;

        assertFalse(subject.isError());
        assertEquals(50, subject.result());
    });
}
