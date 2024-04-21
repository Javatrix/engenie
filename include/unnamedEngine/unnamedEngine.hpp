#pragma once

#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "unnamedEngine/window.hpp"
#include <iostream>

namespace unnamed_engine {
inline void glfwError(int error, const char *description) {
  fprintf(stderr, "GLFW error: %s\n", description);
}

Window window;
double mouseX, mouseY, lastMouseX, lastMouseY;
inline void update(void (*hook)(Window &window)) {
  hook(window);
  lastMouseX = mouseX;
  lastMouseY = mouseY;
}

inline void render(void (*hook)(Window &window)) {
  window.clear();
  hook(window);
  window.update();
}

inline void mouseInput(GLFWwindow *window, double xpos, double ypos) {
  mouseX = xpos;
  mouseY = ypos;
}

inline int initUnnamedEngine(std::string title, int width, int height) {
  if (!glfwInit()) {
    std::cout << "Couldn't load GLFW." << std::endl;
    return -1;
  }

  glfwSetErrorCallback(glfwError);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = Window(title, width, height);
  if (!window.HANDLE) {
    std::cout << "Window creation failed." << std::endl;
    return -1;
  }

  glfwSetCursorPosCallback(window.HANDLE, mouseInput);

  glfwMakeContextCurrent(window.HANDLE);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  return 0;
}

inline void loop(void (*update)(Window &window),
                 void (*render)(Window &window)) {
  while (!window.shouldClose()) {
    unnamed_engine::update(update);
    unnamed_engine::render(render);
  }
}
} // namespace unnamed_engine
