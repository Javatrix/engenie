#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void glfwError(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    cout << "Error loading libraries." << endl;
    return -1;
  }

  glfwSetErrorCallback(glfwError);

  GLFWwindow *window =
      glfwCreateWindow(640, 480, "An amazing GLFW example", NULL, NULL);
  if (!window) {
    cout << "Window creation failed." << endl;
    return -1;
  }

  glfwMakeContextCurrent(window);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  return 0;
}
