#pragma once

#include "glm/detail/type_vec.hpp"
#include "glm/glm.hpp"
#include "unnamedEngine/component/component.hpp"
#include <memory>
#include <unordered_set>

class World;

class Entity {
private:
  World *world;
  std::unordered_set<std::shared_ptr<IEntityComponent>> components;
  glm::vec3 lastPosition = glm::vec3(), lastRotation = glm::vec3(),
            lastScale = glm::vec3();

public:
  glm::vec3 position = glm::vec3(), rotation = glm::vec3(),
            scale = glm::vec3(1.0f);
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
