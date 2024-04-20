#pragma once

#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <string>

class Window {
public:
  GLFWwindow *HANDLE;
  Window() {}
  Window(std::string title, int width, int height) {
    HANDLE = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(HANDLE);
  }
  void setSize(int width, int height) {
    glfwSetWindowSize(HANDLE, width, height);
  }
  void setTitle(char *title) { glfwSetWindowTitle(HANDLE, title); }
  const char *getTitle() { return glfwGetWindowTitle(HANDLE); }
  int getWidth() {
    int w;
    glfwGetWindowSize(HANDLE, &w, nullptr);
    return w;
  }
  int getHeight() {
    int h;
    glfwGetWindowSize(HANDLE, nullptr, &h);
    return h;
  }
  void close() { glfwSetWindowShouldClose(HANDLE, true); }
  bool shouldClose() { return glfwWindowShouldClose(HANDLE); }
  void clear() {
    glViewport(0, 0, getWidth(), getHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
  }
  void update() {
    glfwSwapBuffers(HANDLE);
    glfwPollEvents();
  }
  bool isKeyPressed(int key) {
    return glfwGetKey(HANDLE, key) == GLFW_PRESS;
  }
  bool isMouseButtonPressed(int button) {
    return glfwGetMouseButton(HANDLE, button) == GLFW_PRESS;
  }
};
