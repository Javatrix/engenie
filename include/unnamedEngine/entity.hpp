#pragma once

#include "glm/glm.hpp"
#include "unnamedEngine/component/component.hpp"
#include <unordered_set>

class World;

class Entity {
private:
  World *world;
  std::unordered_set<IEntityComponent *> components;
  glm::vec3 lastPosition, lastRotation, lastScale;
  glm::vec3 position, rotation, scale;

public:
  void update();
  void addComponent(IEntityComponent *component);
  void removeComponent(IEntityComponent *component);
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          bool>::type
  hasComponent();
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          T *>::type
  getComponent();
};
