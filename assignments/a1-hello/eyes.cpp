#include "atkui/framework.h"

using namespace glm;
using glm::vec3;


class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
      radius = 30.0f;
    }

    virtual void scene() {

      // eyes
      setColor(vec3(1, 1, 1));
      drawSphere(vec3(175, 250, 0), 80);
      drawSphere(vec3(325, 250, 0), 80);

      // theta += thetaRate * dt();
      // float px = radius * cos(theta);  
      float px = radius * cos(elapsedTime());

      setColor(vec3(0, 0, 0));
      drawSphere(vec3(175 + px, 250, 50), 30);
      drawSphere(vec3(325 + px, 250, 50), 30);
    }

    // eyes moving to the side
    private:
      float radius; // how wide the moving eyes would go
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
