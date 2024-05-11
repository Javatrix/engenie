
#include "engenie/window.hpp"

Window::Window(std::string title, int width, int height) {
  handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwMakeContextCurrent(handle);
}

void Window::setSize(int width, int height) {
  glfwSetWindowSize(handle, width, height);
}

void Window::setTitle(char *title) { glfwSetWindowTitle(handle, title); }

const char *Window::getTitle() { return glfwGetWindowTitle(handle); }

int Window::getWidth() {
  int w;
  glfwGetWindowSize(handle, &w, nullptr);
  return w;
}

int Window::getHeight() {
  int h;
  glfwGetWindowSize(handle, nullptr, &h);
  return h;
}

void Window::close() { glfwSetWindowShouldClose(handle, true); }

bool Window::shouldClose() { return glfwWindowShouldClose(handle); }

void Window::clear() {
  glViewport(0, 0, getWidth(), getHeight());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
}

void Window::update() {
  glfwSwapBuffers(handle);
  glfwPollEvents();
}

bool Window::isKeyPressed(int key) {
  return glfwGetKey(handle, key) == GLFW_PRESS;
}

bool Window::isMouseButtonPressed(int button) {
  return glfwGetMouseButton(handle, button) == GLFW_PRESS;
}
