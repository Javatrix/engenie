#pragma once

#include "unnamedEngine/entity.hpp"
#include <vector>

class World {
public:
  std::vector<Entity *> entities;
  void update() {
    for (Entity *entity : entities) {
      entity->update();
    }
  }
};
