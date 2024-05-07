#pragma once

#include "glm/glm.hpp"
#include "unnamedEngine/component/component.hpp"
#include <algorithm>
#include <unordered_set>

class World;

class Entity {
private:
  World *world;
  std::unordered_set<IEntityComponent *> components;
  glm::vec3 lastPosition, lastRotation, lastScale;

public:
  glm::vec3 position, rotation, scale;
  void update();
  void addComponent(IEntityComponent *component);
  void removeComponent(IEntityComponent *component);
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          bool>::type
  hasComponent() {
    return std::find_if(components.begin(), components.end(),
                        [](IEntityComponent *component) {
                          return dynamic_cast<T *>(component) != nullptr;
                        }) != components.end();
  }
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          T *>::type
  getComponent() {
    auto it = std::find_if(components.begin(), components.end(),
                           [](IEntityComponent *component) {
                             return dynamic_cast<T *>(component) != nullptr;
                           });
    if (it == components.end()) {
      return nullptr;
    }
    return dynamic_cast<T *>(*it);
  }
};
