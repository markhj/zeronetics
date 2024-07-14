#include "zeronetics/traits/has-unique-id.h"

ZEN::unique_id ZEN::HasUniqueId::currentId = 1;

ZEN::unique_id ZEN::HasUniqueId::getUniqueId() noexcept {
    if (!m_uniqueId.has_value()) {
        m_uniqueId = currentId;
        ++currentId;
    }
    return m_uniqueId.value();
}
