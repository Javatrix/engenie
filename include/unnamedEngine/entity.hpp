#pragma once

#include "glm/glm.hpp"
#include "unnamedEngine/component/component.hpp"
#include <vector>

class World;

class Entity {
private:
  World *world;
  std::vector<IEntityComponent *> components;
  glm::vec3 lastPosition, lastRotation, lastScale;
  glm::vec3 position, rotation, scale;

public:
  void update() {
    lastPosition = position;
    lastRotation = rotation;
    lastScale = scale;

    for (IEntityComponent *component : components) {
      component->updateParent();
    }
  }
};
