#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);
    
    setColor(vec3(1, 1, 1));
    float step = 0.05;

    if (keyIsDown(GLFW_KEY_1)) {
        for (float t = 0; t < 1; t += step) {
          vec3 x = bernstein(t);
          vec3 y = bernstein(t + step);
          setColor(vec3(1, 1, 1));
          drawLine(x, y);
      }
    } else if (keyIsDown(GLFW_KEY_2)) {
      // draw Casteljau
      for (float t = 0; t < 1; t += step) {
        
        vec3 x = casteljau(t);
        vec3 y = casteljau(t + step);
        drawLine(x, y);
      }
    }
  }

  vec3 bernstein(float t) {
    vec3 result = pow(1.0f - t, 3.0f) * B0 + 3*t*pow((1.0f - t), 2.0f) * B1 
                  + 3*pow(t, 2.0f)*(1.0f-t)*B2 + pow(t, 3.0f) * B3;

    return result;
  }

  vec3 LERP(vec3 b0, vec3 b1, float t) {
    return b0 * (1.0f - t) + b1 * t;
  }

  vec3 casteljau(float t) {
    vec3 b10 = LERP(B0, B1, t);
    vec3 b11 = LERP(B1, B2, t);
    vec3 b12 = LERP(B2, B3, t);

    // level 2
    vec3 b20 = LERP(b10, b11, t);
    vec3 b21 = LERP(b11, b12, t);

    vec3 b30 = LERP(b20, b21, t);
    return b30;
  }

  void keyUp(int key, int mod) {
    // setColor(vec3(1, 1, 1));
    float step = 0.05;

    if (key == GLFW_KEY_1) {
  
    }
    else if (key == GLFW_KEY_2) {
      // draw Casteljau
    }
  }

 private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);
};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}
