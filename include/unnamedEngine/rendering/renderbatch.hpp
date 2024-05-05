#pragma once

#include "unnamedEngine/rendering/renderable.hpp"
#include <unordered_set>

class RenderBatch {
public:
  std::unordered_set<IRenderable *> renderables;
  void render() {
    for (IRenderable *renderable : renderables) {
      renderable->render();
    }
  }
};
