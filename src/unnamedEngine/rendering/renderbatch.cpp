#include "unnamedEngine/rendering/renderbatch.hpp"

void RenderBatch::render() {
  for (IRenderable *renderable : renderables) {
    renderable->render();
  }
}
