#pragma once

#include "glm/detail/type_vec.hpp"
#include "glm/glm.hpp"

class Transform {
public:
  glm::vec3 position = glm::vec3(), rotation = glm::vec3(),
            scale = glm::vec3(1.0f);
  Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
  Transform(glm::vec3 position, glm::vec3 rotation);
  Transform(glm::vec3 position);
  Transform();
  void update();
  glm::vec3 getInterpolatedPosition(float interpolation);
  glm::vec3 getInterpolatedRotation(float interpolation);
  glm::vec3 getInterpolatedScale(float interpolation);

private:
  glm::vec3 lastPosition = glm::vec3(position),
            lastRotation = glm::vec3(rotation), lastScale = glm::vec3(scale);
};
