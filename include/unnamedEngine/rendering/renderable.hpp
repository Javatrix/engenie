#pragma once

#include "unnamedEngine/shader.hpp"
class IRenderable {
private:
  Shader *shader;

public:
  IRenderable(Shader *shader) : shader(shader) {}
  void render() { shader->use(); }
};
