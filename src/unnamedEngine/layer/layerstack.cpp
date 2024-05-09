#include "unnamedEngine/layer/layerstack.hpp"
#include "unnamedEngine/layer/layer.hpp"
#include <algorithm>

LayerStack::LayerStack() { m_layersEnd = begin(); }

LayerStack::~LayerStack() {
  for (Layer *layer : m_layers) {
    delete layer;
  }
}

void LayerStack::pushLayer(Layer *layer) {
  m_layers.emplace(m_layersEnd, layer);
  layer->attach();
  m_layersEnd++;
}

void LayerStack::popLayer(Layer *layer) {
  auto it = std::find(begin(), m_layersEnd, layer);
  if (it != m_layersEnd) {
    m_layers.erase(it);
    layer->detach();
    m_layersEnd--;
  }
}

void LayerStack::pushOverlay(Layer *overlay) { m_layers.push_back(overlay); }

void LayerStack::popOverlay(Layer *overlay) {
  if (m_layersEnd != end()) {
    m_layers.erase(end());
  }
}
