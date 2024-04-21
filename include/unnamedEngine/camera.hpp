#pragma once

#include "glm/detail/type_mat.hpp"
#include "glm/gtc/matrix_transform.hpp"
class Camera {
public:
  glm::vec3 position, rotation, direction, right;
  Camera(glm::vec3 position, float fov) : position(position), fov(fov) {
    near = 0.001f;
    far = 10000;
  }
  Camera(glm::vec3 position, float fov, float near, float far)
      : position(position), fov(fov) {
    if (near > 0 && near < far) {
      this->near = near;
    } else {
      near = 0.001f;
    }
    if (far > near) {
      this->far = far;
    } else {
      far = 10000;
    }
  }
  void setFov(float fov) {
    if (fov > 0 && fov <= 360) {
      this->fov = fov;
    }
  }
  float getFov() { return fov; }
  void setNear(float near) {
    if (near > 0) {
      this->near = near;
    }
  }
  float getNear() { return near; }
  void setFar(float far) {
    if (far > near) {
      this->far = far;
    }
  }
  float getFar() { return far; }
  void setNearAndFar(float near, float far) {
    if (near > 0 && near < far) {
      this->near = near;
      this->far = far;
    }
  }
  glm::mat4 getProjection(int windowWidth, int windowHeight) {
    return glm::perspective(glm::radians(fov),
                            (float)windowWidth / windowHeight, near, far);
  }
  glm::mat4 getView() {
    direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    direction.y = sin(glm::radians(rotation.x));
    direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    direction = glm::normalize(direction);
    right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
    return glm::lookAt(position, position + direction, glm::normalize(glm::cross(right, direction)));
  }

private:
  float fov, near, far;
};
