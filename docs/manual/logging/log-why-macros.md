@page log-why-macros Why are log functions macros?

A good question, indeed!

Logging is great. But logging is (usually) done with high frequency,
and therefore plays a role in performance optimization.

While we work on a game, we love logging. It's great. But when you
build the code you want to ship, we want to get rid of most of these
log points. Not all, but most.

Macros make for an efficient way to achieve exactly this, as we can specify
what the pre-processor outputs depending on the build type (see @ref build-info).

When we're in debugging mode, we instruct the pre-processor to output
the ZEN::Log functions. Otherwise, we output, well, nothing.
