#include "atkui/framework.h"
#include <array>
#define CONTROL_POINTS 4
using namespace glm;

class Curve {
  public:
    vec3 color;
    std::array <vec3, 4> controlPoints;
    Curve(std::array <vec3, 4> controlPoints) {
      this->color = agl::randomUnitVector();
      this->controlPoints = controlPoints;
    }

    Curve() {
      this->color = vec3(0, 0, 0);
      this->controlPoints = std::array <vec3, 4> ();
    }
};

class Screensaver : public atkui::Framework {
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {

    // generate random control points for both curves
    curve1 = Curve(generateControlPoints());

    curve2 = Curve(generateControlPoints());

    current = curve1;

    duration = 1.0f; // set the durations for each interpolation
    t = 0.0f;

    savedCurvesSize = 50;
  }

  void scene() {
    t = t + (1.0f/duration) * dt();

    if (t > 1.0f) {
      t = 0.0f;
      // fill in curve 2 with new control points
      if (curves.size() == savedCurvesSize) {
        curves.pop_front();
      }
      if (fmod(elapsedTime(), 0.8) == 0) {
       curves.push_back(curve1);
      } 
      curve1 = curve2;
      curve2 = Curve(generateControlPoints());
      current.color = curve2.color;
    }

    for (int i = 0; i < CONTROL_POINTS; i ++) {
      current.controlPoints[i] = LERP(curve1.controlPoints[i], 
                                      curve2.controlPoints[i], t);
    }

    // draw the current curve!
    drawCurve(curve1);
    drawCurve(curve2);
    drawCurve(current);

    for (std::list<Curve>::iterator c=curves.begin() ; c != curves.end(); ++c) {
      drawCurve(*c);
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

  void drawCurve(Curve curve) {
    setColor(curve.color);
    float curveStep = 0.005;
    for (float tCurve = 0; tCurve < 1; tCurve += curveStep) {
      vec3 x = bernstein(tCurve, curve.controlPoints);
      vec3 y = bernstein(tCurve + curveStep, curve.controlPoints);
      drawLine(x, y);
    }
  }

  private:
    Curve curve1; 
    Curve curve2; 
    Curve current;

    float duration;
    float t; 

    // trailing effects
    std::list<Curve> curves;
    int savedCurvesSize;
};

int main(int argc, char** argv) {
  srand (static_cast <unsigned> (time(0)));
  Screensaver viewer;
  viewer.run();
}

