#pragma once

#include "unnamedEngine/component/component.hpp"
#include "unnamedEngine/mesh.hpp"
#include "unnamedEngine/shader.hpp"

class RenderableComponent : public IEntityComponent {
public:
  RenderableComponent(Mesh &mesh, Shader &program);
  void render();
  void updateParent(Entity *parent) override;
  Shader shader;

private:
  Mesh m_mesh;
};
