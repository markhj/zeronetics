@page log-configuration Configuring the log system

In this article we will review how to:

- Configure behavior of log levels
- Decide which categories you log to files

Let's go!

## 🔇 Log level behavior

There are three primary log levels:

- Info
- Warning
- Critical

And they all behave in one of the following ways:

- Silence
- Console log
- Console log as error
- Throw exception (``std::runtime_error``)

You can combine them how you see fit for your project
and personal preferences.

You can modify the behavior upon request, or at the beginning
of your code.

### Example

Changing the behavior of the critical level to just output
an error in the console.

````cpp
Log::behaviors[LogLevel::Critical].takeAction = LogAction::ConsoleErr;
````

## ✂️ Blacklisting categories

By default, all categories are submitted to the log file. But
most would want to reduce that output.

You do so, simply by adding from the ``ZEN::LogCategory``
enumerator, like this:

````cpp
Log::blacklistCategories.emplace_back(LogCategory::RendererInternals);
````

In this example, you'll no longer see any message related
to "Render Internals." You can add many more categories, of course.

@note _Why is it not a whitelisting system?_
This decision was made on a "rather too much than too little"
principe. We found it safer &mdash; especially considering the
high likelihood of future additions to the list &mdash;
that game developers must explicitly and in full consciousness
blacklist categories.
