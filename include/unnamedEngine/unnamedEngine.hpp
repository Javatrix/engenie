#pragma once

#include "unnamedEngine/rendering/renderbatch.hpp"
#include "unnamedEngine/window.hpp"
#include <vector>

namespace unnamed_engine {

class Engine {
public:
  Window window;
  double mouseX = 0, mouseY = 0, lastMouseX = 0, lastMouseY = 0;
  bool limitFPS = true;
  int tickRate = 20, fps = 60;
  Engine() {}
  static Engine *getInstance();
  void init(const std::string &windowTitle, int windowWidth, int windowHeight);
  void loop(void (*updateHook)(), void (*renderHook)());
  void update(void (*hook)());
  void render(void (*hook)());
  float getInterpolation();
  void addRenderable(IRenderable *renderable);
  void removeRenderable(IRenderable *renderable);
  void addMouseListener(void (*listener)(double mouseX, double mouseY));
  void removeMouseListener(void (*listener)(double mouseX, double mouseY));
  static void mouseInput(GLFWwindow *window, double xpos, double ypos);

private:
  static Engine *instance;
  RenderBatch m_renderBatch;
  std::vector<void (*)(double mouseX, double mouseY)> m_listeners;
};
}; // namespace unnamed_engine
