#include "atkui/framework.h"
#define CONTROL_POINTS 4
using namespace glm;

class Screensaver : public atkui::Framework {
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {

    // generate random control points for both curves
    curve1 = generateControlPoints();
    curve2 = generateControlPoints();

    duration = 3.0f; // set the durations for each interpolation
    t = 0.0f;
  }

  void scene() {
    t = t + (1.0f/duration) * dt();

    if (t > 1.0f) {
      t = 0.0f;
      // fill in curve 2 with new control points
      curve1 = curve2;
      curve2 = generateControlPoints();
    }

    for (int i = 0; i < CONTROL_POINTS; i ++) {
      current[i] = LERP(curve1[i], curve2[i], t);
    }

    // draw the current curve!
    float curveStep = 0.005;
    for (float tCurve = 0; tCurve < 1; tCurve += curveStep) {
      vec3 x = bernstein(tCurve, current);
      vec3 y = bernstein(tCurve + curveStep, current);
      setColor(vec3(1, 1, 1));
      drawLine(x, y);
    }
  }

  std::array <vec3, 4> generateControlPoints() {
    // modify control points in place
    std::array <vec3, 4> curve;
    for (int i = 0; i < CONTROL_POINTS; i ++) {
      curve[i] = generateRandom2dVector();
    }

    return curve;
  }

  vec3 generateRandom2dVector() {
    int x = rand() % 500;
    int y = rand() % 500;

    return vec3(x, y, 0);
  }

  vec3 LERP(vec3 b0, vec3 b1, float t) {
    return b0 * (1.0f - t) + b1 * t;
  }

  vec3 bernstein(float t, std::array<vec3, 4> curve) {
    vec3 result = pow(1.0f - t, 3.0f) * curve[0] + 3*t*pow((1.0f - t), 2.0f) * curve[1] 
                  + 3*pow(t, 2.0f)*(1.0f-t) * curve[2] + pow(t, 3.0f) * curve[3];

    return result;
  }

  private:
    std::array <vec3, 4> curve1; // stores the 4 control points for curve 1
    std::array <vec3, 4> curve2; // stores 4 control points for curve 2
    std::array <vec3, 4> current;
    float duration;
    float t; 
};

int main(int argc, char** argv) {
  Screensaver viewer;
  viewer.run();
}

