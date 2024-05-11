#pragma once

class Entity;

class IEntityComponent {
public:
  IEntityComponent() {}
  virtual void updateParent(Entity *parent) = 0;
};
