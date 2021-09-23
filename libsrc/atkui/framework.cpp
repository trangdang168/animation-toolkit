#include "atkui/framework.h"
#include <algorithm>

using glm::vec3;

namespace atkui {

Framework::Framework(Display type, int screenWidth, int screenHeight) : agl::Window(), _type(type) {
  // Do our own custom setup
  setWindowSize(screenWidth, screenHeight);
  if (_type == Orthographic) {

    float zdim = 1000;
    ortho(0, screenWidth, 0, screenHeight, -zdim, zdim);
    background(vec3(0.0));
    setCameraEnabled(false); 

  } else {
    vec3 center = vec3(0, 0, 0);
    vec3 dim = vec3(500, 1000, 500);
    background(vec3(0.8));
    setupPerspectiveScene(center, dim);
    setCameraEnabled(true);
    camera.setMoveSpeed(5);

    renderer.loadShader("floor", "../shaders/floor.vs", "../shaders/floor.fs");
  }
}

Framework::~Framework() {
}

void Framework::draw() {
  if (_type == Orthographic) {
    renderer.beginShader("unlit");
  }

  scene();

  if (_type == Orthographic) {
    renderer.endShader();
  }

  if (_type == Perspective) {
    drawFloor(2000, 20, 50);
  } 

}

void Framework::drawFloor(float size, float big, float small) {
  renderer.beginShader("floor");
  renderer.setUniform("uFog.color", vec3(0.8));
  renderer.setUniform("uLargeBlockSize", 200);
  renderer.setUniform("uSmallBlockSize", 50);
  renderer.setUniform("uFog.minDist", 0.75f * size);
  renderer.setUniform("uFog.maxDist", size);
  renderer.push();
  renderer.scale(vec3(size, 0, size));
  renderer.plane();
  renderer.pop();
  renderer.endShader();
}

void Framework::setColor(const vec3& c) {
  renderer.setUniform("Material.diffuse", c);
  _color = c;
}

void Framework::drawCube(const glm::vec3& pos, const glm::vec3& size) {
  renderer.push();
  renderer.translate(pos);
  renderer.scale(size);
  renderer.cube();
  renderer.pop();
}

void Framework::drawSphere(const vec3& pos, float radius) {
  renderer.push();
  renderer.translate(pos);
  renderer.scale(vec3(radius));
  renderer.sphere();
  renderer.pop();
}

void Framework::drawLine(const vec3& a, const vec3& b) {
  renderer.line(a, b, _color, _color);
}

void Framework::drawTeapot(const vec3& a, float size) {
  renderer.push();
  renderer.translate(a);
  renderer.scale(vec3(size));
  renderer.teapot();
  renderer.pop();
}

void Framework::push() {
  renderer.push();
}

void Framework::pop() {
  renderer.pop();
}

void Framework::rotate(float angle, const glm::vec3& axis) {
  renderer.rotate(angle, axis);
}

void Framework::translate(const glm::vec3& pos) {
  renderer.translate(pos);
}

void Framework::scale(const glm::vec3& size) {
  renderer.scale(size);
}

void Framework::transform(const atk::trs& trs) {
  renderer.transform(trs.matrix());
}

}
