#pragma once

#include "unnamedEngine/component/component.hpp"
#include "unnamedEngine/mesh.hpp"
#include "unnamedEngine/rendering/renderable.hpp"
#include "unnamedEngine/shader.hpp"
class RenderableComponent : public IEntityComponent, public IRenderable {
private:
  Mesh *mesh;

public:
  RenderableComponent(Entity *parent, Mesh *mesh, Shader *program)
      : IEntityComponent(parent), IRenderable(program), mesh(mesh) {}
  void render() {
    IRenderable::render();
    mesh->render();
  }
};
