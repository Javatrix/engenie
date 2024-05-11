#include "glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "engenie/camera.hpp"
#include "engenie/component/component.hpp"
#include "engenie/component/renderablecomponent.hpp"
#include "engenie/engenie.hpp"
#include "engenie/entity.hpp"
#include "engenie/layer/layer.hpp"
#include "engenie/material.hpp"
#include "engenie/mesh.hpp"
#include "engenie/shader.hpp"
#include "engenie/window.hpp"
#include "glm/detail/func_trigonometric.hpp"
#include "glm/detail/type_vec.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using engine = engenie::Engine;

Window window;

void processInput();

Camera camera(glm::vec3(0, 0, 0), 45);
glm::vec3 diffuseDir(0, -1, 0.5);
glm::vec4 diffuseColor(1, 0.9, 0.9, 1);

float angle = 45, angle2;
Mesh mesh;

Material mat(glm::vec3(0.1, 0.8, 1), glm::vec3(1, 0.8, 0.1), 0.4, 64);

Entity entity;
Shader *shader;

class OurGameLayer : public Layer {
  void render() override {
    Shader shader = entity.getComponent<RenderableComponent>()->shader;

    shader.use();

    diffuseDir.y = glm::cos(glm::radians(angle));
    diffuseDir.x = glm::sin(glm::radians(angle));
    diffuseDir.z = glm::sin(glm::radians(angle2));
    shader.setFloat("ambientStrength", 0.2);
    shader.setVec3("diffuseDir", diffuseDir);
    shader.setVec4("diffuseColor", diffuseColor);
    shader.setVec3("viewPos", camera.transform.getInterpolatedPosition());
    shader.setFloat("specularity", 0.4);
    shader.setFloat("shininess", 256);
    shader.setMaterial("material", mat);
    shader.setMat4("projection",
                   camera.getProjection(window.getWidth(), window.getHeight()));
    shader.setMat4("view", camera.getView());
    entity.getComponent<RenderableComponent>()->render();
  }
  void update() override {
    camera.update();
    entity.update();
    processInput();
  }
};

int main(int argc, char *argv[]) {
  engine::getInstance()->init("Unnamed Engine", 840, 680);
  window = engine::getInstance()->window;

  mesh = Mesh("resources/models/cube.dae", "resources/textures/texture.jpg");

  shader = new Shader("resources/shaders/vertex.glsl",
                      "resources/shaders/fragment.glsl");

  entity.addComponent(std::make_shared<RenderableComponent>(mesh, *shader));

  Layer *mainLayer = new OurGameLayer();
  engine::getInstance()->getLayerStack().pushLayer(mainLayer);
  engine::getInstance()->run();
}

void processInput() {
  if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
    window.close();
  }
  float speed = 0.5f;
  if (window.isKeyPressed(GLFW_KEY_W)) {
    camera.transform.position += speed * camera.direction;
  }
  if (window.isKeyPressed(GLFW_KEY_S)) {
    camera.transform.position -= speed * camera.direction;
  }
  if (window.isKeyPressed(GLFW_KEY_A)) {
    camera.transform.position -= speed * camera.right;
  }
  if (window.isKeyPressed(GLFW_KEY_D)) {
    camera.transform.position += speed * camera.right;
  }
  if (window.isKeyPressed(GLFW_KEY_SPACE)) {
    camera.transform.position.y += speed;
  }
  if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
    camera.transform.position.y -= speed;
  }
  if (window.isKeyPressed(GLFW_KEY_RIGHT)) {
    angle += 5;
  } else if (window.isKeyPressed(GLFW_KEY_LEFT)) {
    angle -= 5;
  }
  if (window.isKeyPressed(GLFW_KEY_UP)) {
    angle2 += 5;
  } else if (window.isKeyPressed(GLFW_KEY_DOWN)) {
    angle2 -= 5;
  }
  if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    camera.transform.rotation.x -=
        (engine::getInstance()->mouseY - engine::getInstance()->lastMouseY) /
        2.0;
    camera.transform.rotation.y +=
        (engine::getInstance()->mouseX - engine::getInstance()->lastMouseX) /
        2.0;
  } else {
    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}
