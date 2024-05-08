#pragma once

#include "unnamedEngine/component/component.hpp"
#include "unnamedEngine/mesh.hpp"
#include "unnamedEngine/rendering/renderable.hpp"
#include "unnamedEngine/shader.hpp"

class RenderableComponent : public IEntityComponent, public IRenderable {
private:
  Mesh *mesh;

public:
  RenderableComponent(Mesh *mesh, Shader *program);
  void render();
  void updateParent(Entity *entity);
};
