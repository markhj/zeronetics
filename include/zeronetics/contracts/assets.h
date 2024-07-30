#pragma once

#include "zeronetics/core/typedefs.h"
#include <memory>
#include <optional>

namespace ZEN {
    /**
     * Information about an asset when it has been registered
     * on a renderer.
     */
    class IRegisteredAsset {
    public:
        virtual std::optional<registered_asset_id> getId() const noexcept = 0;

        virtual void setId(registered_asset_id id) = 0;

    };

    /**
     * Contract for Asset
     */
    class IAsset {
    public:
        virtual std::optional<IRegisteredAsset *> getRegistration() const noexcept = 0;

        virtual void setRegistration(const IRegisteredAsset &registration) = 0;

    };

    /**
     * Contract for Asset Manager
     */
    class IAssetManager {
    public:


    };
}
