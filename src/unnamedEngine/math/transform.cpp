#include "unnamedEngine/math/transform.hpp"
#include "glm/detail/type_vec.hpp"
#include "unnamedEngine/math/math.hpp"
#include "unnamedEngine/unnamedEngine.hpp"
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
  return getInterpolatedPosition(
      unnamed_engine::Engine::getInstance()->getInterpolation());
}
glm::vec3 Transform::getInterpolatedRotation() {
  return getInterpolatedRotation(
      unnamed_engine::Engine::getInstance()->getInterpolation());
}
glm::vec3 Transform::getInterpolatedScale() {
  return getInterpolatedScale(
      unnamed_engine::Engine::getInstance()->getInterpolation());
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
