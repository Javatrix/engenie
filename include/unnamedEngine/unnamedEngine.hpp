#pragma once

#include "unnamedEngine/rendering/renderbatch.hpp"
#include "unnamedEngine/window.hpp"
#include <vector>

namespace unnamed_engine {

class Engine {
private:
  static Engine *instance;
  RenderBatch renderBatch;
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
  void init(const std::string &windowTitle, int windowWidth, int windowHeight);
  void loop(void (*updateHook)(), void (*renderHook)());
  void update(void (*hook)());
  void render(void (*hook)());
  void addRenderable(IRenderable *renderable);
  void removeRenderable(IRenderable *renderable);
  void addMouseListener(void (*listener)(double mouseX, double mouseY));
  void removeMouseListener(void (*listener)(double mouseX, double mouseY));
  static void mouseInput(GLFWwindow *window, double xpos, double ypos);
};
}; // namespace unnamed_engine
