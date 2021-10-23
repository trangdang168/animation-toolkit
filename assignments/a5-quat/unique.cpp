#include <iostream>
#include <cmath>
#include "atkmath/constants.h"
#include "atkui/framework.h"
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
#include "atkmath/vector3.h"

using atkmath::Deg2Rad;
using atkmath::Matrix3;
using atkmath::Quaternion;
using atkmath::Vector3;
using glm::vec3;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Perspective) {
      
  }

  virtual void setup() {
     angle = 0.0;
     axis = Vector3 (0, 0.5, 0.25);
     pallet = {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f
      };
      radius = 20.0f;
      housePosition = vec3(50, 50, 0);
  }

  virtual void scene() {
   // create rotation matrix
  
   angle += 0.05;
   // use transform on that rotation matrix

   quat.fromAxisAngle(axis, fmod(angle, 360.0) * Deg2Rad);
   Matrix3 qmat = quat.toMatrix();
   glm::mat4 mMat4 = qmat.writeToMat4();

   // add a random sphere
   if (positions.size() == 200) {
      for (int i = 0; i < 4; i++)
         positions.pop_front();
   }

   vec3 position(rand() % 500, rand() % 500, 0);
   positions.push_back(position);

   int i = 0;
   for (std::list<vec3>::iterator it=positions.begin(); it != positions.end(); ++it) {
      vec3 color = pallet[i % 4];
      drawParticles(*it, color);
      i++;
   }

   setColor(vec3(255, 233, 0)/255.0f);
   drawCube(housePosition, vec3(100, 100, 100));
   setColor(vec3(1,0,0));
   drawCube(housePosition + vec3(0,100,0), vec3(100, 100, 100));

  }

  void drawParticles(vec3 position, vec3 color) {
   setColor(color);
   push();
   translate(position);
   rotate(angle, vec3(axis[0], axis[1], axis[2]));
   drawSphere(housePosition + position, radius);
   pop();

  }

  private:
   // vec3 sunPosition;
   double angle;
   Quaternion quat;
   Vector3 axis;
   // vec3 earthPosition;
   // vec3 sunPosition; 
   // vec3 moonPosition;
   vec3 housePosition;
   std::list<vec3> positions;
   std::vector<vec3> pallet;
   float radius;
};

int main(int argc, char** argv) {
   srand (time(NULL));
   Unique viewer;
   viewer.run();
   return 0;
}
