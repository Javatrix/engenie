#pragma once

#include "unnamedEngine/event/event.hpp"
class Layer {
  virtual void render();
  virtual void attach();
  virtual void detach();
  virtual void onEvent(Event &event);
}
