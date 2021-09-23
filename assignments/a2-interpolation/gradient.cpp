#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class Gradient : public atkui::Framework {
 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  
  }

  virtual void scene() {

    vec3 nw = vec3(1,1,0);
    vec3 ne = vec3(0,1,1);
    vec3 sw = vec3(1,0,0);
    vec3 se = vec3(1,0,1);

    int width = 250;
    int numSquares = 10;
    int size = width / numSquares;

    int xStart = 125;
    int yStart = 375;

    for (int i =0; i < numSquares; i++) {
      for (int j = 0; j < numSquares; j++) {
        int x = xStart + i * size;
        int y = yStart - j * size;

        float tx = static_cast <float> (i) /  static_cast <float> (numSquares);
        float ty = static_cast <float> (j) /  static_cast <float> (numSquares);
        vec3 colorx0 = nw * (1.0f - tx) + ne * tx;
        vec3 colorx1 = sw * (1.0f - tx) + se * tx;
        vec3 color = colorx0 * (1.0f - ty) + colorx1 * (ty);
        setColor(color);
        drawCube(vec3(x, y, 0), vec3(size, size, 0));
      }
    }
  }
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
