#pragma once

#include "engenie/layer/layerstack.hpp"
#include "engenie/window.hpp"

namespace engenie {
class Engine {
public:
  Window window;
  double mouseX = 0, mouseY = 0, lastMouseX = 0, lastMouseY = 0;
  bool limitFPS = true;
  int tickRate = 20, fps = 60;
  Engine() {}
  static Engine *getInstance();
  void init(const std::string &windowTitle, int windowWidth, int windowHeight);
  void run();
  float deltaTime();
  LayerStack &getLayerStack() { return m_layerStack; }

private:
  static Engine *instance;
  static void mouseInput(GLFWwindow *window, double xpos, double ypos);
  void update();
  void render();
  LayerStack m_layerStack;
};
}; // namespace engenie
