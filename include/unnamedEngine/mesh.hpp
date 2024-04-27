#pragma once

#include "glad/glad.h"
#include "glm/detail/type_vec.hpp"
#include "glm/glm.hpp"
#include "stb_image.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstddef>
#include <iostream>
#include <sys/types.h>
#include <vector>

using namespace std;

class Texture {
public:
  void bind() { glBindTexture(GL_TEXTURE_2D, id); }
  void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

private:
  unsigned int id;
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
  vector<Texture> textures;
  Mesh() {}
  Mesh(const std::string &modelName, const std::string &textureName) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    Assimp::Importer importer;
    const aiScene *scene =
        importer.ReadFile(modelName, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
      std::cerr << "Error loading model: " << importer.GetErrorString()
                << std::endl;
    }

    aiMesh *mesh = scene->mMeshes[0];
    vector<Vertex> nonIndexedVertices;
    for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
      Vertex v;
      aiVector3D vertex = mesh->mVertices[j];
      v.position = glm::vec3(vertex.x, vertex.y, vertex.z);
      nonIndexedVertices.push_back(v);
      if (find(vertices.begin(), vertices.end(), v) == vertices.end()) {
        vertices.push_back(v);
      }

      if (mesh->HasNormals()) {
        aiVector3D normal = mesh->mNormals[j];
        v.normal = glm::vec3(normal.x, normal.y, normal.z);
      } else {
        v.normal = glm::vec3(0.0f, 0.0f, 0.0f);
      }

      if (mesh->HasTextureCoords(0)) {
        aiVector3D texCoord = mesh->mTextureCoords[0][j];
        v.textureCoords = glm::vec2(texCoord.x, texCoord.y);
      } else {
        v.textureCoords = glm::vec2(0.0f, 0.0f);
      }
    }

    // Populate indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
      aiFace face = mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; ++j) {
        uint index = distance(vertices.begin(),
                              find(vertices.begin(), vertices.end(),
                                   nonIndexedVertices[face.mIndices[j]]));
        indices.push_back(index);
      }
    }

    // Generate OpenGL buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // Bind VAO
    glBindVertexArray(vao);

    // Bind VBO and upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    // Bind EBO and upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    // Specify vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)0); // Position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)(offsetof(Vertex, normal))); // Normal
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        (void *)(offsetof(Vertex, textureCoords))); // Texture coordinates

    // Cleanup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(textureName.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    indexCount = indices.size();
  }
  Mesh(const vector<float> &vertices, const vector<unsigned int> &indices,
       const string &textureName) {
    indexCount = indices.size();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(textureName.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      cout << "Failed to load texture" << endl;
    }

    stbi_image_free(data);
  }
  void render() {
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
  }

private:
  unsigned int vao, vbo, ebo;
  unsigned int texture;
};
