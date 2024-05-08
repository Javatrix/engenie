#include "unnamedEngine/component/renderablecomponent.hpp"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "unnamedEngine/component/component.hpp"
#include "unnamedEngine/entity.hpp"
#include "unnamedEngine/shader.hpp"
#include <cstdio>

Entity *parent = nullptr;

RenderableComponent::RenderableComponent(Mesh *mesh, Shader *program)
    : IRenderable(program), mesh(mesh) {}
void RenderableComponent::render() {
  if (parent == nullptr)
    return;

  IRenderable::render();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, parent->rotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, parent->rotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, parent->rotation.z, glm::vec3(0, 0, 1));
  model = glm::scale(model, parent->scale);
  model = glm::translate(model, parent->position);
  printf("%f, %f, %f\n", parent->position.x, parent->position.y,
         parent->position.z);
  shader->setMat4("model", model);
  mesh->render();
}
void RenderableComponent::updateParent(Entity *entity) { parent = entity; };
