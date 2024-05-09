#pragma once

#include "unnamedEngine/layer/layer.hpp"
#include <vector>
class LayerStack {
public:
  LayerStack();
  ~LayerStack();
  void pushLayer(Layer *layer);
  void popLayer(Layer *layer);
  void pushOverlay(Layer *overlay);
  void popOverlay(Layer *overlay);

  std::vector<Layer *>::iterator begin() { return m_layers.begin(); }
  std::vector<Layer *>::iterator end() { return m_layers.end(); }

private:
  std::vector<Layer *> m_layers;
  std::vector<Layer *>::iterator m_layersEnd;
};
