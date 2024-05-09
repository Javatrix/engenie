#pragma once

#include "unnamedEngine/event/event.hpp"
class Layer {
public:
  void render() {}
  void attach() {}
  void detach() {}
  void onEvent(Event &event) {}
};
