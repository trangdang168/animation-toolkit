#include "atkui/framework.cpp"

using glm::vec3;

class Example : public atkui::Framework {
 public:
  Example() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
      theta = 0.0;
      thetaRate = 0.1;
      r = 100.0;
  }

  virtual void scene() {
      theta += thetaRate * dt();
      float px = r * cos(theta);
      float py = r * sin(theta);
      setColor(vec3(1,0,0));
      drawSphere(vec3(250 + px, 250 + py, 0), 100);
      
  }

    // start angle
    private: // best practice
      float theta;
      float thetaRate;
      float r;

};

int main(int argc, char** argv) {
  Example example;
  example.run();
}