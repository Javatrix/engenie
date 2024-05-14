#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <vector>

class Entity;

class IEntityComponent {
public:
  IEntityComponent() {}
  virtual void updateParent(Entity *parent) = 0;
};
class ComponentManager {
public:
  using component_index_map = std::unordered_map<std::type_index, int>;

  template <typename EntityComponent>
  typename std::enable_if<
      std::is_base_of<IEntityComponent, EntityComponent>::value,
      EntityComponent *>::type
  addComponent(std::shared_ptr<EntityComponent> c) {
    int typeIndex = getComponentTypeIndex<EntityComponent>();
    m_components.emplace(m_components.begin() + typeIndex, c.get());
    for (auto &[type, index] : m_componentTypeIndices) {
      if (index > typeIndex)
        index++;
    }
    return c.get();
  }

  template <typename EntityComponent>
  typename std::enable_if<
      std::is_base_of<IEntityComponent, EntityComponent>::value, void>::type
  removeComponent(EntityComponent *c) {
    auto it =
        std::find(m_componentTypeIndices.begin() + getComponentTypeIndex<*c>(),
                  m_componentTypeIndices.end(), *c);
    if (it == m_componentTypeIndices.end()) {
      delete c;
      return;
    }
    for (auto &[type, index] : m_componentTypeIndices) {
      if (index > it)
        index--;
    }
  }

  template <typename T>
  typename std::enable_if<std::is_base_of<IEntityComponent, T>::value,
                          int>::type
  getComponentTypeIndex() {
    auto typeIndex = std::type_index(typeid(T));
    auto it = m_componentTypeIndices.find(typeIndex);
    if (it != m_componentTypeIndices.end()) {
      return it->second;
    }
    std::cout << "Index: "
              << std::distance(m_components.begin(), m_components.end())
              << std::endl;
    return std::distance(m_components.begin(), m_components.end());
  }

private:
  std::vector<IEntityComponent> m_components;
  component_index_map m_componentTypeIndices;
};
