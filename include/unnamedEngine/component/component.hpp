#pragma once

class Entity;

class IEntityComponent {
private:
  Entity *parent;

public:
  IEntityComponent(Entity *parent) : parent(parent) {}
  virtual void updateParent() = 0;
};
