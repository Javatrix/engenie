#pragma once

#include "unnamedEngine/shader.hpp"
#include "unnamedEngine/unnamedEngine.hpp"

class IRenderable {
public:
  Shader *shader;
  IRenderable(Shader *shader) : shader(shader) {
    unnamed_engine::Engine::getInstance()->addRenderable(this);
  }
  void render() { shader->use(); }
};
