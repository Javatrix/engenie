#pragma once

#include "engenie/component/component.hpp"
#include "engenie/math/transform.hpp"
#include <cstdint>
#include <random>
#include <vector>

class World;

class Entity {
public:
  Transform transform;
  Entity() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> random;
    m_uuid = random(gen);
  }
  virtual void update();
  uint64_t uuid() { return m_uuid; }

private:
  World *m_world;
  uint64_t m_uuid;
  std::vector<IEntityComponent *> m_components;
};
