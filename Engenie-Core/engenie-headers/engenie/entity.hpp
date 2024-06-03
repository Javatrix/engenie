#pragma once

#include "engenie/component/component.hpp"
#include "engenie/math/transform.hpp"
#include <algorithm>
#include <cstdint>
#include <random>
#include <type_traits>
#include <typeinfo>
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
  template <typename T>
  typename std::enable_if<std::is_base_of<EntityComponent, T>::value, T *>::type
  addComponent(T component) {
    m_components.push_back(component);
    return &component;
  }
  template <typename T>
  typename std::enable_if<std::is_base_of<EntityComponent, T>::value, T *>::type
  getComponent() {
    for (EntityComponent *c : m_components) {
      if (typeid(*c) == typeid(T))
        return c;
    }
  }
  template <typename T>
  std::enable_if<std::is_base_of<EntityComponent, T>::value, T *>
  removeComponent() {
    auto it = std::find_if(m_components.begin(), m_components.end(),
                           [](EntityComponent *component) {
                             return typeid(*component) == typeid(T);
                           });
    if (it != m_components.end())
      m_components.erase(it);
  }

private:
  World *m_world;
  uint64_t m_uuid;
  std::vector<EntityComponent *> m_components;
};
