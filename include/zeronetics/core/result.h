#pragma once

#include <variant>
#include <optional>

namespace ZEN {
    /**
     * When a function which produces a result encounters an error,
     * an instance of this struct should be returned.
     *
     * @ref result
     */
    struct ResultError {
        /**
         * Optional error code.
         */
        std::optional<int> errorCode;

        /**
         * Optional message.
         */
        std::optional<const char*> errorMessage;
    };

    /**
     * Result-type, inspired by Rust's equivalent.
     *
     * @ref result
     */
    template<typename T>
    class Result : public std::variant<ResultError, T> {
    public:
        using std::variant<ResultError, T>::variant;

        /**
         * Returns true, if the result contains an error.
         * @return
         */
        bool isError();

        /**
         * Retrieve the result.
         *
         * @warning Will cause an error, if the object doesn't contain
         *      a result. Make sure to check in advance using ``isError``.
         *
         * @return
         */
        [[nodiscard]] T result() const;

        /**
         * Retrieve the error.
         *
         * @warning Will cause an error, if the object doesn't contain
         *      an instance of ZEN::ResultError.
         *      Make sure to check in advance using ``isError``.
         *
         * @return
         */
        ResultError error();

    };

    template<typename T>
    ResultError Result<T>::error() {
        return std::get<ResultError>(*this);
    }

    template<typename T>
    T Result<T>::result() const {
        return std::get<T>(*this);
    }

    template<typename T>
    bool Result<T>::isError() {
        return std::holds_alternative<ResultError>(*this);
    }
}
