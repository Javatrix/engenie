#include "unnamedEngine/entity.hpp"

void Entity::update() {
  lastPosition = position;
  lastRotation = rotation;
  lastScale = scale;

  for (IEntityComponent *component : components) {
    component->updateParent(*this);
  }
}

void Entity::addComponent(IEntityComponent *component) {
  components.insert(component);
}

void Entity::removeComponent(IEntityComponent *component) {
  components.erase(component);
}
