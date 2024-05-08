#include "unnamedEngine/math/math.hpp"
#include "glm/glm.hpp"

glm::vec3 lerp(glm::vec3 vec1, glm::vec3 vec2, float interpolation) {
  return vec1 + (vec2 - vec1) * glm::clamp<float>(interpolation, 0, 1);
}
