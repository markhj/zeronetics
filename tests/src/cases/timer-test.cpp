#include "timer-test.h"
#include "zeronetics/core/timer.h"

#include <thread>

void ZEN::Tests::TimerTest::test() {
    it("Tests the life-time of a timer.", [&]() {
        ZEN::Timer timer;

        timer.start();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        assertTrue(timer.getTime().result().microsecs >= 1000 * 100);
    });

    it ("Cannot get time when timer is not running.", [&]() {
        assertEquals<std::string>("Timer not started.",
                     ZEN::Timer().getTime().error().errorMessage.value());
    });
}
