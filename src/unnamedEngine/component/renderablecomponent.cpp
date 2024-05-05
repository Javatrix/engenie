#include "unnamedEngine/component/renderablecomponent.hpp"

RenderableComponent::RenderableComponent(Mesh *mesh, Shader *program)
      : IRenderable(program), mesh(mesh) {}
  void RenderableComponent::render() {
    IRenderable::render();
    mesh->render();
  }
  void updateParent(Entity &entity) {}
