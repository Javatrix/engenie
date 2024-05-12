#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

class Entity;

class IEntityComponent {
public:
  IEntityComponent() {}
  virtual void updateParent(Entity *parent) = 0;
};

class ComponentManager {
public:
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          T *>::type
  getComponent() {
    if (!isRegistered<T>()) {
      T component;
      m_components.push_back(component);
      return component;
    }
    for (const auto &component : m_components) {
      if (dynamic_cast<T>(component) != nullptr) {
        return component;
      }
    }
    return nullptr;
  }

private:
  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          bool>::type
  isRegistered() {
    for (const auto &component : m_components) {
      if (dynamic_cast<T>(component) != nullptr) {
        return true;
      }
    }
    return false;
  }
  std::vector<IEntityComponent> m_components;
};
