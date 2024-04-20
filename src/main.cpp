#include "glad/glad.h"
#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"
#include "unnamedEngine/camera.hpp"
#include "unnamedEngine/mesh.hpp"
#include "unnamedEngine/window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"
#include "stb_image.h"

using namespace std;

void processInput(Window &);

void glfwError(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

Camera camera(glm::vec3(0, 0, 0), 45);
Window window;
int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    cout << "Error loading libraries." << endl;
    return -1;
  }

  glfwSetErrorCallback(glfwError);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = Window("Epic GLFW Something", 840, 460);
  if (!window.HANDLE) {
    cout << "Window creation failed." << endl;
    return -1;
  }

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    cout << "Failed to initialize GLAD" << endl;
    return -1;
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  vector<float> vertices = {
      // Positions          // Texture coordinates
      // Front face
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // Bottom-left
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // Bottom-right
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // Top-right
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // Top-left
      // Back face
      -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // Bottom-left
      0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Bottom-right
      0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // Top-right
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // Top-left
      // Top face
      -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // Front-bottom-left
      0.5f, 0.5f, -0.5f, 1.0f, 0.0f,  // Front-bottom-right
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // Front-top-right
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // Front-top-left
      // Bottom face
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Front-bottom-left
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // Front-bottom-right
      0.5f, -0.5f, 0.5f, 1.0f, 1.0f,   // Front-top-right
      -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // Front-top-left
                                       // Right face
      0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Front-bottom-left
      0.5f, 0.5f, -0.5f, 1.0f, 0.0f,   // Front-bottom-right
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // Front-top-right
      0.5f, -0.5f, 0.5f, 0.0f, 1.0f,   // Front-top-left
      // Left face
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Front-bottom-left
      -0.5f, 0.5f, -0.5f, 1.0f, 0.0f,  // Front-bottom-right
      -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // Front-top-right
      -0.5f, -0.5f, 0.5f, 0.0f, 1.0f   // Front-top-left
  };

  vector<unsigned int> indices = {
      0,  1,  2,  0,  2,  3,  // Front face
      4,  5,  6,  4,  6,  7,  // Back face
      8,  9,  10, 8,  10, 11, // Top face
      12, 13, 14, 12, 14, 15, // Bottom face
      16, 17, 18, 16, 18, 19, // Right face
      20, 21, 22, 20, 22, 23  // Left face
  };

  Mesh mesh(vertices, indices, "resources/textures/texture.jpg");

  Shader shader("resources/shaders/vertex.glsl",
                "resources/shaders/fragment.glsl");

  while (!window.shouldClose()) {
    processInput(window);
    window.clear();

    glBindTexture(GL_TEXTURE_2D, mesh.texture);
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * 0),
                        glm::vec3(1.0f, 0.25f, 0.5f));
    int modelLoc = glGetUniformLocation(shader.id, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 projection =
        camera.getProjection(window.getWidth(), window.getHeight());
    int projectionLoc = glGetUniformLocation(shader.id, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 view = camera.getView();
    int viewLoc = glGetUniformLocation(shader.id, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    mesh.render();

    window.update();
  }

  return 0;
}

void processInput(Window &window) {
  if (window.isKeyPressed(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    window.close();
  }
  if (window.isKeyPressed(GLFW_KEY_W) == GLFW_PRESS) {
    camera.position.z -= 0.1f;
  }
  if (window.isKeyPressed(GLFW_KEY_S) == GLFW_PRESS) {
    camera.position.z += 0.1f;
  }
  if (window.isKeyPressed(GLFW_KEY_A) == GLFW_PRESS) {
    camera.position.x -= 0.1f;
  }
  if (window.isKeyPressed(GLFW_KEY_D) == GLFW_PRESS) {
    camera.position.x += 0.1f;
  }
  if (window.isKeyPressed(GLFW_KEY_SPACE) == GLFW_PRESS) {
    camera.position.y += 0.1f;
  }
  if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    camera.position.y -= 0.1f;
  }
}
