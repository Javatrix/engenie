#include "unnamedEngine/component/renderablecomponent.hpp"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "unnamedEngine/component/component.hpp"
#include "unnamedEngine/entity.hpp"
#include "unnamedEngine/shader.hpp"
#include "unnamedEngine/unnamedEngine.hpp"

Entity *parent = nullptr;

RenderableComponent::RenderableComponent(Mesh *mesh, Shader *program)
    : IRenderable(program), mesh(mesh) {}
void RenderableComponent::render() {
  if (parent == nullptr)
    return;

  IRenderable::render();
  glm::mat4 model = glm::mat4(1.0f);
  float interpolation =
      unnamed_engine::Engine::getInstance()->getInterpolation();
  glm::vec3 lerpedRotation =
      parent->transform.getInterpolatedRotation(interpolation);
  model = glm::rotate(model, lerpedRotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, lerpedRotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, lerpedRotation.z, glm::vec3(0, 0, 1));
  model =
      glm::scale(model, parent->transform.getInterpolatedScale(interpolation));
  model = glm::translate(
      model, parent->transform.getInterpolatedPosition(interpolation));
  shader->setMat4("model", model);
  mesh->render();
}
void RenderableComponent::updateParent(Entity *entity) { parent = entity; };
