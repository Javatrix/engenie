#pragma once

#include "glm/detail/type_vec.hpp"
#include "glm/glm.hpp"
#include "unnamedEngine/component/component.hpp"
#include "unnamedEngine/math/transform.hpp"
#include <memory>
#include <unordered_set>

class World;

class Entity {
public:
  Transform transform;
  virtual void update();
  void addComponent(std::shared_ptr<IEntityComponent> component);
  void removeComponent(std::shared_ptr<IEntityComponent> component);
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          bool>::type
  hasComponent() {
    for (const auto &component : m_components) {
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
    for (const auto &component : m_components) {
      if (dynamic_cast<T *>(component.get()) != nullptr) {
        return dynamic_cast<T *>(component.get());
      }
    }
    return nullptr;
  }

private:
  World *m_world;
  std::unordered_set<std::shared_ptr<IEntityComponent>> m_components;
};
