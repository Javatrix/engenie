#pragma once

#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "unnamedEngine/window.hpp"
#include <cstdio>
#include <functional>
#include <iostream>
#include <vector>

namespace unnamed_engine {
inline void glfwError(int error, const char *description) {
  fprintf(stderr, "GLFW error: %s\n", description);
}

class Engine {
private:
  static Engine *instance;
  std::vector<void (*)(double mouseX, double mouseY)> listeners;

public:
  Window window;
  double mouseX, mouseY, lastMouseX, lastMouseY;
  bool limitFPS = true;
  int updateRate = 20, fps = 60;
  Engine() {}
  static Engine *getInstance() {
    if (!instance) {
      instance = new Engine();
    }
    return instance;
  }
  void init(const std::string &windowTitle, int windowWidth, int windowHeight) {
    if (!glfwInit()) {
      std::cout << "Couldn't load GLFW." << std::endl;
      return;
    }

    glfwSetErrorCallback(glfwError);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = Window(windowTitle, windowWidth, windowHeight);
    if (!window.HANDLE) {
      std::cout << "Window creation failed." << std::endl;
      return;
    }

    glfwSetCursorPosCallback(window.HANDLE, mouseInput);

    glfwMakeContextCurrent(window.HANDLE);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return;
    }
  }
  void loop(void (*updateHook)(), void (*renderHook)()) {
    double lastUpdate = glfwGetTime(), lastRender = glfwGetTime();
    while (!window.shouldClose()) {
      double currentTime = glfwGetTime();
      if (currentTime - lastUpdate >= 1.0 / updateRate) {
        update(updateHook);
        lastUpdate = currentTime;
      }
      if (!limitFPS || currentTime - lastRender >= 1.0 / fps) {
        render(renderHook);
        lastRender = currentTime;
      }
    }
  }
  void update(void (*hook)()) {
    hook();
    lastMouseX = mouseX;
    lastMouseY = mouseY;
  }
  void render(void (*hook)()) {
    window.clear();
    hook();
    window.update();
  }
  void addMouseListener(void (*listener)(double mouseX, double mouseY)) {
    listeners.push_back(listener);
  }
  void removeMouseListener(void (*listener)(double mouseX, double mouseY)) {
    listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
                                   [&](void (*f)(double, double)) {
                                     return f == listener;
                                   }),

                    listeners.end());
  }
  static void mouseInput(GLFWwindow *window, double xpos, double ypos) {
    if (!getInstance()) {
      return;
    }
    getInstance()->mouseX = xpos;
    getInstance()->mouseY = ypos;
    for (auto listener : getInstance()->listeners) {
      listener(xpos, ypos);
    }
  }
};

Engine *Engine::instance = nullptr;
} // namespace unnamed_engine
