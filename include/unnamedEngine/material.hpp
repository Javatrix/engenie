#pragma once

#include "glm/vec3.hpp"

struct Material {
  Material(glm::vec3 ambient, glm::vec3 diffuse, float specularity,
           float shininess)
      : ambient(ambient), diffuse(diffuse), specularity(specularity),
        shininess(shininess) {}
  glm::vec3 ambient;
  glm::vec3 diffuse;
  float specularity;
  float shininess;
};
