#pragma once

#include "zeronetics/core/typedefs.h"

#include <cstdint>
#include <optional>

namespace ZEN {
    /**
     * This trait manages generation and returning of unique IDs across
     * objects and class types.
     */
    class HasUniqueId {
    public:
        /**
         * Returns the object's unique ID.
         *
         * @note The ID isn't generated until requested. Meaning that if
         *      objects A and B are generated in that order, but B requests
         *      a unique ID before A, then B will have the lower ID.
         *
         * @return
         */
        [[nodiscard]] unique_id getUniqueId() noexcept;

    private:
        /**
         * Is ``std::nullopt`` to indicate that no ID has been generated.
         * Otherwise, it contains the ID.
         */
        std::optional<unique_id> m_uniqueId;

        /**
         * Universal incrementor used to ensure ID uniqueness.
         */
        static unique_id currentId;

    };
}
