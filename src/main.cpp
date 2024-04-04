#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"
#include "stb_image.h"

using namespace std;

void windowResizeCallback(GLFWwindow *, int, int);
void processInput(GLFWwindow *);

void glfwError(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    cout << "Error loading libraries." << endl;
    return -1;
  }

  glfwSetErrorCallback(glfwError);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window =
      glfwCreateWindow(640, 480, "An amazing GLFW example", NULL, NULL);
  if (!window) {
    cout << "Window creation failed." << endl;
    return -1;
  }
  glfwMakeContextCurrent(window);

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

  float vertices[] = {
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

  unsigned int indices[] = {
      0,  1,  2,  0,  2,  3,  // Front face
      4,  5,  6,  4,  6,  7,  // Back face
      8,  9,  10, 8,  10, 11, // Top face
      12, 13, 14, 12, 14, 15, // Bottom face
      16, 17, 18, 16, 18, 19, // Right face
      20, 21, 22, 20, 22, 23  // Left face
  };

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  stbi_set_flip_vertically_on_load(true);
  int width, height, nrChannels;
  unsigned char *data = stbi_load("resources/textures/texture.jpg", &width,
                                  &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  Shader shader("resources/shaders/vertex.glsl",
                "resources/shaders/fragment.glsl");

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, texture);
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model =
        glm::rotate(model, glm::radians((float)glfwGetTime() * 16), glm::vec3(1.0f, 0.25f, 0.5f));
    int modelLoc = glGetUniformLocation(shader.id, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    int viewLoc = glGetUniformLocation(shader.id, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection;
    projection = glm::perspective(
        glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);
    int projectionLoc = glGetUniformLocation(shader.id, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
