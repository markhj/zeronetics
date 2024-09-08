#pragma once

#include "zeronetics/core/tensors.h"

#include <memory>

namespace ZEN {
    struct EntityRegistration {
        const char *typeName;
        const char *name;
    };

    /**
     * Base entity class.
     *
     * @ref entity-system
     */
    class Entity {
    public:
        void registerEntity();

        virtual EntityRegistration getRegistration() = 0;
    };

    /**
     * Entity Registry
     */
    class EntityRegistry {
    public:
        static void add(const std::shared_ptr<EntityRegistration> &registration);

        static std::unordered_map<const char *, std::shared_ptr<ZEN::EntityRegistration>> getEntities();

    private:
        static std::unordered_map<const char *, std::shared_ptr<ZEN::EntityRegistration>> entities;
    };

    /**
     * 3D entity
     *
     * @note Whether a 3D entity has 3D transform properties (position,
     *      scale, rotation, etc.) is up to child classes to determine.
     *      Keep in mind that ZEN::ITransforms3D is also provided by
     *      ZEN::IRenderable3D.
     *
     * @ref entity-system
     */
    class Entity3D : public Entity {
//    public:
//        EntityRegistration getRegistration() override = 0;
    };
}
