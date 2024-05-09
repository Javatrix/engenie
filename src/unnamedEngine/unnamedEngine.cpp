#include "unnamedEngine/unnamedEngine.hpp"
#include "unnamedEngine/layer/layer.hpp"

#include <iostream>
#include <sys/types.h>

void glfwError(int error, const char *description) {
  fprintf(stderr, "GLFW error: %s\n", description);
}

using namespace unnamed_engine;

Engine *Engine::instance = nullptr;
float interpolation = 0;

Engine *Engine::getInstance() {
  if (!instance) {
    instance = new Engine();
  }
  return instance;
}

void Engine::init(const std::string &windowTitle, int windowWidth,
                  int windowHeight) {
  if (!glfwInit()) {
    std::cout << "Couldn't load GLFW." << std::endl;
    return;
  }

  glfwSetErrorCallback(glfwError);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = Window(windowTitle, windowWidth, windowHeight);
  if (!window.handle) {
    std::cout << "Window creation failed." << std::endl;
    return;
  }

  glfwSetCursorPosCallback(window.handle, mouseInput);

  glfwMakeContextCurrent(window.handle);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return;
  }
}

void Engine::loop(void (*updateHook)(), void (*renderHook)()) {
  double lastUpdate = glfwGetTime(), lastRender = glfwGetTime();
  while (!window.shouldClose()) {
    double currentTime = glfwGetTime();
    if (currentTime - lastUpdate >= 1.0 / tickRate) {
      update(updateHook);
      lastUpdate = currentTime;
    }
    if (!limitFPS || currentTime - lastRender >= 1.0 / fps) {
      interpolation = (currentTime - lastUpdate) / (1.0 / tickRate);
      render(renderHook);
      lastRender = currentTime;
    }
  }
}

void Engine::update(void (*hook)()) {
  hook();
  lastMouseX = mouseX;
  lastMouseY = mouseY;
}

void Engine::render(void (*hook)()) {
  window.clear();
  hook();
  m_renderBatch.render();
  window.update();
}

float Engine::getInterpolation() { return interpolation; }

void Engine::addRenderable(IRenderable *renderable) {
  m_renderBatch.renderables.insert(renderable);
}

void Engine::removeRenderable(IRenderable *renderable) {
  m_renderBatch.renderables.erase(renderable);
}

void Engine::pushLayer(Layer &layer) {
  m_layerStack.push(layer);
  layer.attach();
}

Layer Engine::popLayer() {
  Layer layer = m_layerStack.top();
  m_layerStack.pop();
  layer.detach();
  return layer;
}

void Engine::mouseInput(GLFWwindow *window, double xpos, double ypos) {
  if (!getInstance()) {
    return;
  }
  getInstance()->mouseX = xpos;
  getInstance()->mouseY = ypos;
}
