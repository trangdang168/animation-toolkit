#include "atkui/framework.cpp"

using glm::vec3;

class Example : public atkui::Framework {
 public:
  Example() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
      theta = 0.0;
      thetaRate = 0.5;
      h = 150.0;
  }

  virtual void scene() {
      theta += thetaRate * dt();
      float px = h * cos(theta);
    //   float py = h * sin(theta);
      float py = 0;

      // 
      setColor(vec3(1,0,0));
      drawSphere(vec3(250 + px, 250 + py, 0), 50);
      
  }

    // start angle
    private: // best practice
      float theta;
      float thetaRate;
      float h;

};

int main(int argc, char** argv) {
  Example example;
  example.run();
}