#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

// a modified butterfly class

class Butterfly {
   public: 
      vec3 position;
      vec3 color;
      float size;
      Butterfly(vec3 pos, vec3 col, float size) {
         this->position = pos;
         this->color = col;
         this->size = size;
      }
};

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Perspective) {
  }

  virtual void setup() {
     numButterflies = 12;
     theta = 0.0f;
     radius = 200.0f;
     thetaRate = 2.0f;
     colors =  {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f
      };

      // arranged in a 2x3x2 cube

      distance = 200.0f;
      vec3 moveBack = 0.5f * vec3(2 * distance, 3*distance, 2 * distance);

      for (int i = 0; i < numButterflies; i++) {
         int row = i / 2;
         int col = i % 3;
         int plane = i % (2*3);
         vec3 position = vec3(row * distance, col * distance, 
                              plane) - moveBack + vec3(200.0f);
         float size = 0.1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.5-0.1)));
         Butterfly b = Butterfly(position, colors[i % 4], size);
         butterflies.push_back(b);
      }

      t = 0.0f;

      Joint* body = new Joint("Body");
      body->setLocalTranslation(vec3(1,2,1)*100.0f);
      body->setLocalRotation(glm::angleAxis(glm::radians<float>(45.0f), vec3(0,1,0)));
      skeleton.addJoint(body);

      Joint* lwing = new Joint("LWing");
      lwing->setLocalTranslation(vec3(0.1,0,0)*100.0f);
      skeleton.addJoint(lwing, body);

      Joint* lwing2 = new Joint("LWing2");
      lwing2->setLocalTranslation(vec3(0.1,0,0)*100.0f);
      skeleton.addJoint(lwing2, body);

      Joint* rwing = new Joint("RWing");
      rwing->setLocalTranslation(vec3(-0.1,0,0)*100.0f);
      skeleton.addJoint(rwing, body);

      Joint* rwing2 = new Joint("RWing2");
      rwing2->setLocalTranslation(vec3(-0.1,0,0)*100.0f);
      skeleton.addJoint(rwing2, body);

      skeleton.fk();
  }

  virtual void scene() {

      theta += dt() * thetaRate;

      float x = sin(theta) * radius;
      float y = sin(elapsedTime())*100.0f + 150.0f;
      float z = sin(theta) * radius;

      Joint* body = skeleton.getByName("Body");
      // body->setLocalTranslation();
      Joint* lwing = skeleton.getByName("LWing");
      lwing->setLocalRotation(glm::angleAxis(sin(elapsedTime()), vec3(0,0,1)));

      Joint* lwing2 = skeleton.getByName("LWing2");
      lwing2->setLocalRotation(glm::angleAxis(sin(elapsedTime()), vec3(0,0,1)));


      Joint* rwing = skeleton.getByName("RWing");
      rwing->setLocalRotation(glm::angleAxis(-sin(elapsedTime()), vec3(0,0,1))); 

      Joint* rwing2 = skeleton.getByName("RWing2");
      rwing2->setLocalRotation(glm::angleAxis(-sin(elapsedTime()), vec3(0,0,1))); 
      skeleton.fk();

     for (int i = 0; i < numButterflies; i++) {
      push();
      translate(butterflies[i].position + vec3(x, y, z));
      scale(vec3(butterflies[i].size));

      // attach geometry to skeleton 
      Transform B = body->getLocal2Global(); 
      Transform LT = lwing->getLocal2Global(); 
      Transform LT2 = lwing2->getLocal2Global(); 
      Transform RT = rwing->getLocal2Global(); 
      Transform RT2 = rwing2->getLocal2Global(); 

      // draw body
      Transform bodyGeometry(
         glm::angleAxis(glm::pi<float>()*0.5f, vec3(1,0,0)), // rotation
         vec3(0), vec3(25, 200, 25)); // position, scale

      Transform lwingGeometry(
         eulerAngleRO(XYZ, vec3(0,-M_PI/4,0)),
         vec3(-80,0,50), 
         vec3(120,20,180));

      Transform lwing2Geometry(
         eulerAngleRO(XYZ, vec3(0,-M_PI / 4,0)),
         vec3(-60,0,-60), 
         vec3(120,20,80));

      Transform rwingGeometry(
         eulerAngleRO(XYZ, vec3(0,M_PI/4,0)),
         vec3(80,0,50), 
         vec3(120,20,180));

      Transform rwing2Geometry(
         eulerAngleRO(XYZ, vec3(0,M_PI/4,0)),
         vec3(60,0,-60), 
         vec3(120,20,80));

      setColor(vec3(0.4, 0.4, 0.8));
      push();
      transform(B * bodyGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(butterflies[i].color);
      push();
      transform(LT * lwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(butterflies[i].color);
      push();
      transform(LT2 * lwing2Geometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(butterflies[i].color);
      push();
      transform(RT * rwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(butterflies[i].color);
      push();
      transform(RT2 * rwing2Geometry);
      drawSphere(vec3(0), 1);
      pop();

      pop();
     }
  }



  private:
   Skeleton skeleton;
   float t;
   int numButterflies;
   std::vector<Butterfly> butterflies;
   std::vector<vec3> colors;
   float distance;
   float theta;
   float radius;
   float thetaRate;
};

int main(int argc, char** argv) {
   srand (static_cast <unsigned> (time(0)));
   Unique viewer;
   viewer.run();
   return 0;
}

