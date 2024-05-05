#include "unnamedEngine/camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(glm::vec3 position, float fov) : position(position), fov(fov) {
  near = 0.001f;
  far = 10000;
}
Camera::Camera(glm::vec3 position, float fov, float near, float far)
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
void Camera::setFov(float fov) {
  if (fov > 0 && fov <= 360) {
    this->fov = fov;
  }
}
float Camera::getFov() { return fov; }
void Camera::setNear(float near) {
  if (near > 0) {
    this->near = near;
  }
}
float Camera::getNear() { return near; }
void Camera::setFar(float far) {
  if (far > near) {
    this->far = far;
  }
}
float Camera::getFar() { return far; }
void Camera::setNearAndFar(float near, float far) {
  if (near > 0 && near < far) {
    this->near = near;
    this->far = far;
  }
}
glm::mat4 Camera::getProjection(int windowWidth, int windowHeight) {
  return glm::perspective(glm::radians(fov), (float)windowWidth / windowHeight,
                          near, far);
}
glm::mat4 Camera::getView() {
  direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  direction.y = sin(glm::radians(rotation.x));
  direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  direction = glm::normalize(direction);
  right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
  return glm::lookAt(position, position + direction,
                     glm::normalize(glm::cross(right, direction)));
}
