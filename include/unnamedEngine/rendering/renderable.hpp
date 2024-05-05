#pragma once

#include "unnamedEngine/shader.hpp"

class IRenderable {
public:
  Shader *shader;
  IRenderable(Shader *shader);
  void render();
};
