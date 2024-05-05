#include "unnamedEngine/entity.hpp"

#include <algorithm>

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

template <typename T>
typename std::enable_if<std::is_base_of<IEntityComponent, T>::value, bool>::type
Entity::hasComponent() {
  return std::find_if(components.begin(), components.end(),
                      [](IEntityComponent *component) {
                        return dynamic_cast<T *>(component) != nullptr;
                      }) != components.end();
}

template <typename T>
typename std::enable_if<std::is_base_of<IEntityComponent, T>::value, T *>::type
Entity::getComponent() {
  auto it = std::find_if(components.begin(), components.end(),
                         [](IEntityComponent *component) {
                           return dynamic_cast<T *>(component) != nullptr;
                         });
  if (it == components.end()) {
    return nullptr;
  }
  return dynamic_cast<T *>(*it);
}
