#include "atkui/framework.h"

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
    eyeRadius = 25;
    leftEye = vec3(175, 250, 50);
    rightEye = vec3(325, 250, 50);
  }

  virtual void scene() {

    // detect the mouse and draw the red dot
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      vec2 position = mousePosition();
      _mouseX = position[0];
      _mouseY = position[1];
      mouseMove(_mouseX, _mouseY);

      // direct the eyes towards the dots
      vec3 target = vec3(_mouseX, _mouseY, 0);
      leftEyeLook = look(target, leftEye);
      rightEyeLook = look(target, rightEye);
      setColor(vec3(1,0,0));
      drawSphere(target, 5);
    } else {
      leftEyeLook = leftEye;
      rightEyeLook = rightEye;
    }

    drawEyes();

    drawPupil(leftEyeLook);
    drawPupil(rightEyeLook);

  }

  void drawEyes() {
    // eyes
    setColor(vec3(1, 1, 1));
    drawSphere(vec3(175, 250, 0), 80);
    drawSphere(vec3(325, 250, 0), 80);
  }

  vec3 look(vec3 target, vec3 eye) {
    vec3 direction = target - eye;
    float theta = atan2(_mouseY, _mouseX);
    vec3 newLoc = eye + theta * normalize(direction) * eyeRadius;
    return newLoc;
  }

  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }

  void drawPupil(vec3 position) {
    setColor(vec3(0,0,0));
    drawSphere(position, eyeRadius);
  }

 private:
  int _mouseX;
  int _mouseY;
  float eyeRadius;

  // the intended origin of the eye
  vec3 leftEye;
  vec3 rightEye;

  // stores where the pupil will move if it look at the target
  vec3 leftEyeLook;
  vec3 rightEyeLook;
};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}
