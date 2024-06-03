#pragma once

class Entity;

class EntityComponent {
public:
  EntityComponent(Entity &parent) : parent(parent) {}

public:
  virtual void update() {}

public:
  Entity &parent;
};
