@page callbacks Callbacks

This page details how to design function signatures for, and store,
callbacks.

It furthermore discusses the decision to use ``std::optional``
over ``std::shared_ptr``.

## How to make callbacks "a la Zeronetics"

> We start by emphasizing that you're not _required_ to make callbacks
> in this fashion. If you have a good reason to choose another way,
> then that's fine.

In Zeronetics, we strive to use ``std::optional`` to store callbacks
This was chosen over ``std::shared_ptr``. The "why?" you can read
in the chapter below.

This means that a callback is typically made on this form:

Member in your class:

````cpp
std::optional<std::function<void()>> m_myCallback;
````

Function signature:

````cpp
void setMyCallback(std::function<void()> m_myCallback);
````

Usage:

````cpp
myAwesomeClass.setMyCallback([]() {
    // ...
});
````

## Examination of choices

Below, different ways to designing callbacks are examined.

### Using ``std::optional``

Stored as:

````cpp
std::optional<std::function<void()>> m_myCallback;
````

Function signature:

````cpp
void setMyCallback(std::function<void()> callback);
````

- **Pro**: "Nullable" (empty state) by nature
- **Pro**: Simple code for end-user
- **Pro**: Explicitly shown that callback is optional - more readable
- **Pro**: Light-weight (limited overhead)
- **Pro**: Retains ownership until class destructor is called
- **Con**: Requires copy of the function*

*) Callbacks aren't really set often, so this issue is somewhat limited.

````cpp
window->onClose([]() {
    std::exit(0);
});
````

### Smart pointers

Stored as:

````cpp
std::shared_ptr<std::function<void()>> m_myCallback;
````

Function signature:

````cpp
void setMyCallback(std::shared_ptr<std::function<void()>> callback);
````

- **Pro**: "Nullable" (empty state) by nature
- **Pro**: Callback function is easily shared with other parts of the game
- **Pro**: Retains a reference (partial owner) to the callback function
- **Con**: More verbose declaration than ``std::optional``
- **Con**: While nullability is implied/understood, it's not _as_ clear
  as ``std::optional``.
- **Con**: Reference counter overhead*

*) But, again, due to limited number of times callbacks are set,
this is probably a non-issue.

````cpp
window->onClose(std::make_shared<std::function<void()>>([]() {
    std::exit(0);
}));
````
