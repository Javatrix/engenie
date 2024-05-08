#pragma once

#include "GLFW/glfw3.h"
#include <string>

class Window {
public:
  GLFWwindow *handle;
  Window() {}
  Window(std::string title, int width, int height);
  void setSize(int width, int height);
  void setTitle(char *title);
  const char *getTitle();
  int getWidth();
  int getHeight();
  void close();
  bool shouldClose();
  void clear();
  void update();
  bool isKeyPressed(int key);
  bool isMouseButtonPressed(int button);
};
