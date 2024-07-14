@page log-reporting Log reports

The regular @ref logging "log system" will &mdash;
depending on @ref build-info "build configuration" &mdash;
strip logging functionality from the code, when you build it for
release.

However, what about the case where a player of your game experiences
an error, and wants to send you a bug report? Well, if we stripped
all the log points that's not possible.

## ✏️ What is reporting?

This is where this special **reporting level** of the log system comes in.
It remains in the release build, and writes valuable information to
the log file, including &mdash; but definitely not limited to &mdash;
system information, graphics driver, and events you've actively decided
to log at this level.

## 📋 Usage

Early in your game code, you should start the reporting.

````cpp
ZEN_REPORT_START();
````

This function writes very basic information, such as the system
information, to the log file.

To log something on-the-fly you use the ``ZEN_REPORT(entry)`` macro,
where ``entry`` is an instance of ZEN::LogFileEntry.

````cpp
ZEN_REPORT({"The player well off the edge."});
````

You can add more detailed information by filling out the full
ZEN::LogFileEntry.
