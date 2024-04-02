#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

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

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  return 0;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
