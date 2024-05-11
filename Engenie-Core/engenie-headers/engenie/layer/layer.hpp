#pragma once

#include "engenie/event/event.hpp"
#include <string>

class Layer {
public:
  Layer(const std::string &name = "Layer") : m_debugName(name) {}
  virtual void render() {}
  virtual void update() {}
  virtual void attach() {}
  virtual void detach() {}
  virtual void onEvent(Event &event) {}
  inline const std::string &getName() const { return m_debugName; }

protected:
  std::string m_debugName;
};