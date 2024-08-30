#include "zeronetics/entities/entity.h"

std::unordered_map<const char *, std::shared_ptr<ZEN::EntityRegistration>> ZEN::EntityRegistry::entities;

void ZEN::Entity::registerEntity() {
    EntityRegistry::add(std::make_shared<EntityRegistration>(getRegistration()));
}

void ZEN::EntityRegistry::add(const std::shared_ptr<ZEN::EntityRegistration> &registration) {
    entities[registration->name] = registration;
}

std::unordered_map<const char *, std::shared_ptr<ZEN::EntityRegistration>> ZEN::EntityRegistry::getEntities() {
    return entities;
}
