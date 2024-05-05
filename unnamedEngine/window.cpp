#include "unnamedEngine/window.hpp"

Window::Window(std::string title, int width, int height) {
  HANDLE = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(HANDLE);
}

void Window::setSize(int width, int height) {
  glfwSetWindowSize(HANDLE, width, height);
}

void Window::setTitle(char *title) { glfwSetWindowTitle(HANDLE, title); }

const char *Window::getTitle() { return glfwGetWindowTitle(HANDLE); }

int Window::getWidth() {
  int w;
  glfwGetWindowSize(HANDLE, &w, nullptr);
  return w;
}

int Window::getHeight() {
  int h;
  glfwGetWindowSize(HANDLE, nullptr, &h);
  return h;
}

void Window::close() { glfwSetWindowShouldClose(HANDLE, true); }

bool Window::shouldClose() { return glfwWindowShouldClose(HANDLE); }

void Window::clear() {
  glViewport(0, 0, getWidth(), getHeight());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
}

void Window::update() {
  glfwSwapBuffers(HANDLE);
  glfwPollEvents();
}

bool Window::isKeyPressed(int key) {
  return glfwGetKey(HANDLE, key) == GLFW_PRESS;
}

bool Window::isMouseButtonPressed(int button) {
  return glfwGetMouseButton(HANDLE, button) == GLFW_PRESS;
}
