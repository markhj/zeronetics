@page timer Timer

The ZEN::Timer class makes it easy to measure one or several time intervals.

## 🕑 Basic usage

Once instantiated, you need to explicitly start the timer.

````cpp
ZEN::Timer timer;

timer.start();
````

Whenever needed, you can now grab the duration since the timer was started.
The return value is provided as ``ZEN::Result<ZEN::TimeMeasurement>``.

````cpp
Result<TimeMeasurement> interval = timer.getTime();

if (interval.isError()) {
    // Handle error
} else {
    std::cout << "Elapsed microseconds: " << interval.result().microsecs << std::endl;
}
````

@warning You will get an error if the timer hasn't been started prior to
requesting the time with ``getTime``.
