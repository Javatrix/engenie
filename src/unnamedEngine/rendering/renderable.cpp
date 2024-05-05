#include "unnamedEngine/rendering/renderable.hpp"
#include "unnamedEngine/unnamedEngine.hpp"

IRenderable::IRenderable(Shader *shader) : shader(shader) {
  unnamed_engine::Engine::getInstance()->addRenderable(this);
}

void IRenderable::render() { shader->use(); }
