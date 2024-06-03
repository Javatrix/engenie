#include "engenie/entity.hpp"
#include "engenie/component/component.hpp"

void Entity::update() {
  transform.update();
  for (EntityComponent *c : m_components) {
    c->update();
  }
}
