#pragma once

#include "engenie/entity.hpp"
#include <vector>

class World {
public:
  std::vector<Entity *> entities;
  void update();
};
