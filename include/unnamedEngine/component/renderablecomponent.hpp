#pragma once

#include "unnamedEngine/component/component.hpp"
#include "unnamedEngine/mesh.hpp"
#include "unnamedEngine/shader.hpp"
#include "unnamedEngine/unnamedEngine.hpp"

class RenderableComponent : public IEntityComponent, public IRenderable {
private:
  Mesh *mesh;

public:
  RenderableComponent(Mesh *mesh, Shader *program)
      : IRenderable(program), mesh(mesh) {}
  void render() {
    IRenderable::render();
    mesh->render();
  }
  void updateParent(Entity &entity) {}
};
