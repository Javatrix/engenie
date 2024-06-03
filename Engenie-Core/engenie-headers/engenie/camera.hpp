#pragma once

#include "engenie/entity.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/glm.hpp"

class Camera : public Entity {
public:
  glm::vec3 direction, right;
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
  float m_fov, m_near, m_far;
};
