#pragma once

#include "component.hpp"
#include "engenie/entity.hpp"
#include <iostream>
#include <ostream>

class TestComponent : public EntityComponent {

public:
  TestComponent(Entity &parent) : EntityComponent(parent) {}

  void update() override {
    std::cout << "UPDATING " << parent.uuid() << std::endl;
  }
};
