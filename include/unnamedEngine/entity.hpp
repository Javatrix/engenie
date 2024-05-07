#pragma once

#include "glm/glm.hpp"
#include "unnamedEngine/component/component.hpp"
#include <algorithm>
#include <memory>
#include <unordered_set>

class World;

class Entity {
private:
  World *world;
  std::unordered_set<std::shared_ptr<IEntityComponent>> components;
  glm::vec3 lastPosition, lastRotation, lastScale;

public:
  glm::vec3 position, rotation, scale;
  void update();
  void addComponent(std::shared_ptr<IEntityComponent> component);
  void removeComponent(std::shared_ptr<IEntityComponent> component);
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          bool>::type
  hasComponent() {
    for (const auto &component : components) {
      if (dynamic_cast<T *>(component.get()) != nullptr) {
        return true;
      }
    }
    return false;
  }
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          T *>::type
  getComponent() {
    for (const auto &component : components) {
      if (dynamic_cast<T *>(component.get()) != nullptr) {
        return dynamic_cast<T *>(component.get());
      }
    }
    return nullptr;
  }
};
