#include "unnamedEngine/component/renderablecomponent.hpp"
#include "unnamedEngine/component/component.hpp"

Entity *parent = nullptr;

RenderableComponent::RenderableComponent(Mesh *mesh, Shader *program)
    : IRenderable(program), mesh(mesh) {}
void RenderableComponent::render() {
  IRenderable::render();
  mesh->render();
}
void RenderableComponent::updateParent(Entity &entity) { parent = &entity; };
