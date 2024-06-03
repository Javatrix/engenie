#include "engenie/math/transform.hpp"
#include "engenie/engenie.hpp"
#include "engenie/math/math.hpp"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <sys/types.h>

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale) {}

Transform::Transform(glm::vec3 position, glm::vec3 rotation)
    : Transform(position, rotation, glm::vec3(1.0f)) {}

Transform::Transform(glm::vec3 position)
    : Transform(position, glm::vec3(), glm::vec3(1.0f)) {}

Transform::Transform() : Transform(glm::vec3(), glm::vec3(), glm::vec3(1.0f)) {}

void Transform::update() {
  m_lastPosition = glm::vec3(position);
  m_lastRotation = glm::vec3(rotation);
  m_lastScale = glm::vec3(scale);
}

glm::vec3 Transform::getInterpolatedPosition() {
  return getInterpolatedPosition(engenie::Engine::getInstance()->deltaTime());
}
glm::vec3 Transform::getInterpolatedRotation() {
  return getInterpolatedRotation(engenie::Engine::getInstance()->deltaTime());
}
glm::vec3 Transform::getInterpolatedScale() {
  return getInterpolatedScale(engenie::Engine::getInstance()->deltaTime());
}

glm::vec3 Transform::getInterpolatedPosition(float interpolation) {
  return lerp(m_lastPosition, position, interpolation);
}

glm::vec3 Transform::getInterpolatedRotation(float interpolation) {
  return lerp(m_lastRotation, rotation, interpolation);
}

glm::vec3 Transform::getInterpolatedScale(float interpolation) {
  return lerp(m_lastScale, scale, interpolation);
}

glm::mat4 Transform::createModelMatrix() {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(glm::scale(model, scale), position);
  return model;
}
