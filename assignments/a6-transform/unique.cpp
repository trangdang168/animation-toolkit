#include <iostream>
#include <cmath>
#include "atkmath/constants.h"
#include "atkui/framework.h"
#include "atk/toolkit.h"

using glm::vec3;
using namespace atk;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Perspective) {

  }

  virtual void setup() {
      numJoints = 4;
      jointWidth = 10.0f;
      color = vec3(0,0,0);
      numTentacles = 6;
      up = vec3(0,100,0);

     for (int i =0; i < numTentacles; i++) {
         Skeleton t;
         float x = sin(360 / numTentacles * i);
         float z = cos(360 / numTentacles * i);
         vec3 displacement = vec3(x,0,z);
         std::string name = "root" + std::to_string(i);
         Joint* prev;
         for (int i = 0; i < numJoints; i++) {

            if (i == 0) {
               Joint * cur = new Joint(name);
               cur->setLocalTranslation(vec3(0,0,0) + up);
               t.addJoint(cur);
               prev = cur;
               
               
            } else {
               Joint * cur = new Joint(name + std::to_string(i));
               cur->setLocalTranslation(up + displacement * float(i * 50));
               t.addJoint(cur, prev);
               prev = cur;
            }

            t.fk();
            tentacles.push_back(t);
         }
     }
  }

  virtual void scene() {

     setColor(vec3(1,0,0));
     setColor(color);
     for (int i = 0; i < tentacles.size(); i++) {
        tentacles.at(i).fk();
        
        for (int j = 0; j <tentacles.at(i).getNumJoints(); j++){

         Joint *joint = tentacles.at(i).getByID(j);
         glm::highp_quat q = glm::angleAxis(sin(elapsedTime()+j), vec3(0,0,1));
         joint->setLocalRotation(q);
        }
        drawSkleletons(tentacles.at(i));
     }

     drawSphere(up, 200.0f);

     setColor(vec3(1,1,1));
     drawSphere(vec3(-100,50,0), 50.0f);
     drawSphere(vec3(-100,100,0), 50.0f);
     
     setColor(vec3(0,0,0));
     drawSphere(vec3(-120,50,0), 20.0f);
     drawSphere(vec3(-120,100,0), 20.0f);

   }

   void drawSkleletons(Skeleton tentacle) {
      for (int i = 0; i <tentacle.getNumJoints(); i++)
      {

         Joint *j = tentacle.getByID(i);
         if (j->getParent() == NULL)
         {
            continue;
         }
         Joint *parent = j->getParent();
         vec3 globalParentPos = parent->getGlobalTranslation();
         vec3 globalPos = j->getGlobalTranslation();
         drawEllipsoid(globalParentPos, globalPos, jointWidth);
      }
   }

  private:
  int numJoints;
  float jointWidth;
  int numTentacles;
  std::vector<Skeleton> tentacles;
  vec3 color;
  vec3 up;


};


int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}
