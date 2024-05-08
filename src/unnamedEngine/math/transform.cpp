#include "unnamedEngine/math/transform.hpp"
#include "glm/detail/func_common.hpp"
#include "glm/detail/type_vec.hpp"
#include "unnamedEngine/math/math.hpp"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position), rotation(rotation), scale(scale) {}

Transform::Transform(glm::vec3 position, glm::vec3 rotation)
    : Transform(position, rotation, glm::vec3(1.0f)) {}

Transform::Transform(glm::vec3 position)
    : Transform(position, glm::vec3(), glm::vec3(1.0f)) {}

Transform::Transform() : Transform(glm::vec3(), glm::vec3(), glm::vec3(1.0f)) {}

void Transform::update() {
  lastPosition = glm::vec3(position);
  lastRotation = glm::vec3(rotation);
  lastScale = glm::vec3(scale);
}

glm::vec3 Transform::getInterpolatedPosition(float interpolation) {
  return lerp(lastPosition, position, interpolation);
}

glm::vec3 Transform::getInterpolatedRotation(float interpolation) {
  return lerp(lastRotation, rotation, interpolation);
}

glm::vec3 Transform::getInterpolatedScale(float interpolation) {
  return lerp(lastScale, scale, interpolation);
}
