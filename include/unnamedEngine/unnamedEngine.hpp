#pragma once

#include "unnamedEngine/layer/layer.hpp"
#include "unnamedEngine/layer/layerstack.hpp"
#include "unnamedEngine/rendering/renderbatch.hpp"
#include "unnamedEngine/window.hpp"

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
  LayerStack &getLayerStack() { return m_layerStack; }

private:
  static Engine *instance;
  static void mouseInput(GLFWwindow *window, double xpos, double ypos);
  RenderBatch m_renderBatch;
  LayerStack m_layerStack;
};
}; // namespace unnamed_engine
