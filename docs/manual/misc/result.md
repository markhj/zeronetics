@page result Result

The ZEN::Result is inspired by Rust's namesake equivalent.

The ``Result`` object is a container, which holds either the desired
result, or an error detailing what happened. It's a dynamic, but streamlined,
way of handling results, in cases where you maybe don't want to throw
exceptions, or have another reason to treat it more lightly.

## 🔑 Basic usage

Your function must return ``Result<T>`` where ``T`` is the data type
you expect when everything goes well.

If an error occurs, you return ZEN::ResultError.

Example:

````cpp
Result<CarKey> getCarKeys(unsigned int driverAge) {
    if (driverAge < 18) {
        return ZEN::ResultError{.errorCode = 268};
    }
    return CarKey();
}
````

To read this example, we will do the following:

````cpp
Result<CarKey> carKeys = getCarKeys(23);

if (carKeys.isError()) {
    // Explain the driver that they are too young
} else {
    // Get in and start the car
}
````

You can interact with the error and result, using
ZEN::Result::error and ZEN::Result::result.
