#pragma once

#include <memory>
#include <unordered_map>

namespace ZEN {
    /**
     * Registration of an entity. Used, among other places, in editors.
     */
    struct EntityRegistration {
        /**
         * The name of the type. Usually matches the class name.
         */
        const char *typeName;

        /**
         * "Friendly" (human-readable) name.
         * E.g. forming "3D Mesh" from "Mesh3D."
         */
        const char *name;
    };

    /**
     * Base entity class.
     *
     * @ref entity-system
     */
    class Entity {
    public:
        /**
         * Carry out the registration of the entity.
         */
        void registerEntity();

        /**
         * Retrieve information for the entity registry.
         * Must be implemented individually for every entity.
         *
         * @return
         */
        virtual EntityRegistration getRegistration() = 0;
    };

    /**
     * Entity Registry
     */
    class EntityRegistry {
    public:
        /**
         * Add an entity to the registry.
         *
         * @param registration
         */
        static void add(const std::shared_ptr<EntityRegistration> &registration);

        /**
         * Get all currently registered entities.
         *
         * @return
         */
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
    class Entity3D : public Entity {};
}
