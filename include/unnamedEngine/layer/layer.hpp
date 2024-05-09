#pragma once

class Layer {
  virtual void render();
  virtual void attach();
  virtual void detach();
  virtual void onEvent(Event &event);
}
