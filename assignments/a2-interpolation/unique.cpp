#include "atkui/framework.h"
#define NUM_BRANCHES 20
#define LO 80
#define HI 250

using namespace glm;

class Firework {
   public:
      vec3 color;
      vec3 position;
      float radius;
   Firework(vec3 position, vec3 color) {
      radius = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
      this->position = position;
      this->color = color;
   }
};

class Fireworks : public atkui::Framework {
 public:
  Fireworks() : atkui::Framework(atkui::Orthographic) {
  }

  void setup() {    
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
    maxFireworks = 10;
  }

  void drawFireworkBranch(vec3 start, vec3 target, vec3 colorStart, 
                           vec3 colorEnd) {
     float numVecs = 50.0f;
     vec3 smallVec = (target - start) * (1.0f/ numVecs);
     for (float i = 0; i < numVecs; i+=1.0f) {
        float t = i / numVecs;
        vec3 color = colorStart * (1.0f - t) + colorEnd * (t);
        setColor(color);
        drawLine(start + i * smallVec, start + (i + 1) * smallVec);
     }
  }

  void drawFirework(Firework f) {

     vec3 position = f.position;
     float radius = f.radius;
     vec3 color1 = f.color;

     // calculate theta
     float theta = radians(360.0f) / (NUM_BRANCHES);
     vec3 color2 = float(0.1) * color1; // firework goes from darker to lighter
     for (int i = 0; i < NUM_BRANCHES; i++) {
        float newTheta = theta * i;
        //target position
        float x = cos(newTheta) * radius + position[0];
        float y = sin(newTheta) * radius + position[1];
        drawFireworkBranch(position, vec3(x, y, 0), color2, color1);  
     }

     // draw straightlines from center to sides


     // interpolate the color for each points starting from the center
  }

  void scene() {
   if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      vec2 position = mousePosition();
      _mouseX = position[0];
      _mouseY = position[1];
      mouseMove(_mouseX, _mouseY);

      vec3 color = agl::randomUnitVector();
      // drawFirework(vec3(_mouseX, _mouseY, 0), 100.0f, color);
      Firework f = Firework(vec3(_mouseX, _mouseY, 0), color);

      if (fireworks.size() == maxFireworks) {
         fireworks.pop_front();
      }

      fireworks.push_back(f);
    }

   for (std::list<Firework>::iterator f=fireworks.begin() ; f != fireworks.end(); ++f) {
      drawFirework(*f);
    }
  }

  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }

  private:
   int _mouseX;
   int _mouseY;
   std::list<Firework> fireworks;
   int maxFireworks;
};

int main(int argc, char** argv) {
  Fireworks viewer;
  viewer.run();
}
