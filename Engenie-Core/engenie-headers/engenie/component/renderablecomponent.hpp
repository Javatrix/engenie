#pragma once

#include "engenie/component/component.hpp"
#include "engenie/mesh.hpp"
#include "engenie/shader.hpp"

class RenderableComponent : public IEntityComponent {
public:
  RenderableComponent(Mesh &mesh, Shader &program);
  void render();
  void updateParent(Entity *parent) override;
  Shader shader;

private:
  Mesh m_mesh;
};
