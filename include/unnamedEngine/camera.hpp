#pragma once

#include "glm/glm.hpp"

class Camera {
public:
  glm::vec3 position, rotation, direction, right;
  Camera(glm::vec3 position, float fov);
  Camera(glm::vec3 position, float fov, float near, float far);
  void setFov(float fov);
  float getFov();
  void setNear(float near);
  float getNear();
  void setFar(float far);
  float getFar();
  void setNearAndFar(float near, float far);
  glm::mat4 getProjection(int windowWidth, int windowHeight);
  glm::mat4 getView();

private:
  float fov, near, far;
};
