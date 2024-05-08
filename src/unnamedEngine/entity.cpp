#include "unnamedEngine/entity.hpp"
#include <memory>

void Entity::update() {
  transform.update();
  for (std::shared_ptr<IEntityComponent> component : components) {
    component->updateParent(this);
  }
}

void Entity::addComponent(std::shared_ptr<IEntityComponent> component) {
  components.insert(component);
}

void Entity::removeComponent(std::shared_ptr<IEntityComponent> component) {
  components.erase(component);
}
