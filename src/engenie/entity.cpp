#include "engenie/entity.hpp"
#include <memory>

void Entity::update() {
  transform.update();
  for (std::shared_ptr<IEntityComponent> component : m_components) {
    component->updateParent(this);
  }
}

void Entity::addComponent(std::shared_ptr<IEntityComponent> component) {
  m_components.insert(component);
}

void Entity::removeComponent(std::shared_ptr<IEntityComponent> component) {
  m_components.erase(component);
}
