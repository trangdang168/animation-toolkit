#include "atkui/framework.h"

using namespace glm;

class Star {
  public:
    float theta;
    float thetaRate;
    vec3 position;
    Star() {
      theta = 0.0;
      int num = rand() % 10;
      thetaRate = static_cast<float> (num) / 10.0f; 

      // only appear in the sky in the upper half
      position = vec3(rand() % 500, rand() % 250 + 250, rand() % 50);
    }
};

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
    starColor = vec3(0.5, 0.5, 0.5);
    numStars = 400;
    for (int i = 0; i < numStars; i++) {
      Star s = Star();
      stars.push_back(s);
    }

    oceanTheta = 0.0f;
    oceanThetaRate = 0.8f;
  }

  virtual void scene() {

    for (std::list<Star>::iterator s = stars.begin(); s != stars.end(); ++s) {
      drawStar(*s);
    }

    oceanTheta += oceanThetaRate * dt();
    drawOcean();
  }

  void drawStar(Star s) {
    float angle = s.theta + s.thetaRate * elapsedTime();
    vec3 displayedColor = starColor + vec3(0.5 * cos(angle));
    setColor(displayedColor);
    drawSphere(s.position, 5);
  }

  void drawOcean() {
    setColor(vec3(0.2, 0.5, 0.92) * 0.8f);

    // top row stay fixed
    for (int i = 40; i < 500; i += 50){
      for (int j = 40; j  < 150; j += 50) {
        drawSphere(vec3(i, j, 0), 100);
      }
    }

    // first row goes up and down
    for (int i = 40; i < 500; i += 50) {
      float y = 20 * sin(oceanTheta);
      if (i % 20 == 0) {
        y = 20 * cos(oceanTheta);
      }

      drawSphere(vec3(i, 200 + y, 0), 100);
    }
  }

  // list stores particles for stars
  vec3 starColor;
  std::list<Star> stars;
  int numStars;
  float oceanTheta;
  float oceanThetaRate;
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}

