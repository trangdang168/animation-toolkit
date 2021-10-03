#include "atkui/framework.h"
// #include "interpolator_catmullrom.h"
#include "interpolator_catmullrom.h"
#include "spline.h"
using namespace glm;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
     numPoints = 100.0f;
     s.addInterpolationType("CatmullRom", &catmullrom);
     t = 0.2f;
      pallet  =  {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f
      };
  }

  virtual void setup() {
     // start from mid, left screen
   //   s.appendKey(0, vec3(50, 250, 0));
  }

  virtual void scene() {
     int counter = 1;
     for (int i = 0; i < 500; i+= 50) {
        s.appendKey(counter, vec3(i, 250 + 0.25 * i, 0));
        counter +=1;
        s.appendKey(counter, vec3(i + 25, 250 - 0.25 * i, 0));
        counter +=1;
     }

     s.setInterpolationType("CatmullRom");

     for (float i = 0.0f; i < numPoints; i+=1.0f ) {
        float time = t*i * elapsedTime();
        vec3 position = vec3(500, 500, 0) - s.getValue(time);
        setColor(pallet.at(int(i) % 5));
        drawSphere(position, 20);
     }

  }

  private:
   std::vector<vec3> keys;
   Spline s;
   float t;
   float numPoints;
   InterpolatorCatmullRom catmullrom;
   std::vector<vec3> pallet;
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}

