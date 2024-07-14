@page logging Logging

On this page, we'll explore basic logging techniques.

## 👋 A simple message

The simplest type of logging is an info-level message.
It looks like this:

````cpp
ZEN_INFO("Hello, World!", ZEN::LogCategory::Info);
````

There are several categories available, which can be explored
in the ZEN::LogCategory enumerator.

## 📢 Log levels

You can log at four different levels, each with
@ref log-configuration "different behaviors".

Below, we're examining the first three, but you should
also have a look at @ref log-reporting "the reporting level".

### ℹ️ Info

We already examined the info level, which can be helpful in debugging,
especially things which aren't visible or easy to find.
But they don't in and of themselves convey information, which
is believed to be serious in nature.

### ⚠️ Warning

The ``ZEN_WARN`` macro is similar to ``ZEN_INFO``, but contains
information about implementation details which:

- Has low risk of crashing the application
- But may cause unintended behaviors

An example would be a renderer which skips rendering a ZEN::Mesh3D
because the mesh is missing some details.
This won't crash the application, but it's good for the end-user to know,
and can save the developer lots of time.

Example:

````cpp
ZEN_WARN("Missing shader material.", ZEN::LogCategory::ShaderUse);
````

### ⛔ Critical

The ``ZEN_CRITICAL`` level is for code which is certain to,
or carry high risk of, crashing the application.

Example:

````cpp
ZEN_CRITICAL("Attempting to use a pointer which is not set.");
````

@note ``ZEN_CRITICAL`` does not require a category.

@note Furthermore, critical levels are always logged to file.

## Notes

It's possible to use the ZEN::Log functionality directly, and you're welcome
to do so. But it's not the approach we recommend, and therefore not covered
in any further detail in this documentation.

When a message is sent to the console many times within a short timeframe,
it will be silenced for a few seconds.

## See also

@ref log-configuration

@ref log-reporting

@ref log-engine-dev

@ref log-why-macros
