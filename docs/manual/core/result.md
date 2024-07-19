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
    // You can use carKeys.error() to extract the error.
} else {
    // Get in and start the car
    // You can use carKeys.result() to extract the result
}
````

@warning You must check whether the ``Result`` contains an error
or not prior to calling ``error`` and ``result``, otherwise you 
risk a critical-level error.

You can interact with the error and result, using
ZEN::Result::error and ZEN::Result::result.

## When to use ``Result``

We use ``Result`` when we desire the behavior of ``std::optional``
but with the possibility to explain the end-user or implementor
what has gone wrong.

The alternative is to use exceptions, which should be done when
the error is recoverable or critical.
