#pragma once

#include "unnamedEngine/event/event.hpp"
class Layer {
public:
  virtual void render();
  virtual void attach();
  virtual void detach();
  virtual void onEvent(Event &event);
}
