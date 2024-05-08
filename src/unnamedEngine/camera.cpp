#include "unnamedEngine/camera.hpp"
#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(glm::vec3 position, float fov)
    : Camera(position, fov, 0.001f, 10000) {}

Camera::Camera(glm::vec3 position, float fov, float near, float far)
    : m_fov(fov) {
  setNearAndFar(near, far);
}

void Camera::setFov(float fov) {
  if (fov > 0.0f && fov <= 360.0f) {
    this->m_fov = fov;
  }
}

float Camera::getFov() { return m_fov; }

void Camera::setNear(float near) {
  if (near > 0) {
    this->m_near = near;
  }
}

float Camera::getNear() { return m_near; }

void Camera::setFar(float far) {
  if (far > m_near) {
    this->m_far = far;
  }
}

float Camera::getFar() { return m_far; }

void Camera::setNearAndFar(float near, float far) {
  if (near > 0.0f && near < far) {
    this->m_near = near;
    this->m_far = far;
  }
}

glm::mat4 Camera::getProjection(int windowWidth, int windowHeight) {
  return glm::perspective(glm::radians(m_fov),
                          (float)windowWidth / windowHeight, m_near, m_far);
}

glm::mat4 Camera::getView() {
  glm::vec3 position = transform.getInterpolatedPosition();
  glm::vec3 rotation = transform.getInterpolatedRotation();
  direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  direction.y = sin(glm::radians(rotation.x));
  direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
  direction = glm::normalize(direction);
  right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));

  return glm::lookAt(position, position + direction,
                     glm::normalize(glm::cross(right, direction)));
}
