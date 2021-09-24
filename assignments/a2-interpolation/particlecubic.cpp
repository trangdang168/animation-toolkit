#include "atkui/framework.h"
using namespace glm;

class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {
    B0 = vec3(50,  50, 0);
    B1 = vec3(150, 200, 0);
    B2 = vec3(270, 100, 0);
    B3 = vec3(400, 450, 0);
    duration = 5.0f; // should take 5s to traverse the curve
    step = 1.0f / duration;
  }

  void scene() {
    float tP = fmod(step * elapsedTime(), 1); // particle's
    vec3 pos = casteljau(tP);
    setColor(vec3(1, 1, 0));
    drawSphere(pos, 10);

    setColor(vec3(0, 0, 0));
    drawCurve();
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

  void drawCurve() {
    // draw Casteljau
    float step = 0.005;
    for (float t = 0; t < 1; t += step) {
      
      vec3 x = casteljau(t);
      vec3 y = casteljau(t + step);
      drawLine(x, y);
    }
  }

  private:
    vec3 B0;
    vec3 B1;
    vec3 B2;
    vec3 B3;
    float duration;
    // vec3 pos; // sphere position
    float step; // the size of step the sphere will move with
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}

