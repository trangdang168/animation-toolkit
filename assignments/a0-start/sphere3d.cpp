#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }

  virtual void setup() {
    origin = vec3(0, 0, 0);
    currentPosition = vec3(0);
    velocity = vec3(0);
  }

  virtual void scene() {

    // update position for the sphere
    currentPosition = currentPosition + velocity * dt();
    // std::cout <<  velocity << std::endl;

    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(currentPosition, radius);
  }


  // overriding method here
  void keyUp(int key, int mods) {
    if (key == GLFW_KEY_SPACE) {
      // std::cout <<  "Pressed space bar" << std::endl;
      // generate a random unit vector
      velocity = 100.0f * agl::randomUnitVector();	
      // std::cout <<  velocity << std::endl;

    } else if (key == GLFW_KEY_R) {
      std::cout <<  "Pressed R" << std::endl;

      // move back
      currentPosition = origin;
      velocity = vec3(0);
    }
  }

  vec3 velocity;
  vec3 origin;
  vec3 currentPosition;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
