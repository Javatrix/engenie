#pragma once

#include "glad/glad.h"
#include "glm/detail/type_vec.hpp"
#include "glm/glm.hpp"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <sys/types.h>
#include <vector>

class Texture {
public:
  void bind();
  void unbind();

private:
  unsigned int m_id;
};

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 textureCoords;

  bool operator==(const Vertex &v) {
    return v.position == position && v.textureCoords == textureCoords &&
           v.normal == normal;
  }
};

class Mesh {
public:
  int indexCount;
  std::vector<Texture> textures;
  Mesh() {}
  Mesh(const std::string &modelName, const std::string &textureName);
  Mesh(const std::vector<float> &vertices,
       const std::vector<unsigned int> &indices, std::string &textureName);
  void render() {
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
  }

private:
  unsigned int m_vao, m_vbo, m_ebo;
  unsigned int m_texture;
};
