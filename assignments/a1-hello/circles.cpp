#include "atkui/framework.h"
#include <list>

using namespace glm;
using glm::vec3;

// class that contains a row of circles
class CircleOfCircles {
 // radius, color, velocity, number of circles
  public:
   float radius;
   float circleRadius;
   int numCircles;
   vec3 color;
   float thetaRate;

   CircleOfCircles(float circleRadius, float thetaRate, vec3 color) {
      this->circleRadius = circleRadius;
      this->numCircles = 36;
      this->radius = 16;
      this->color = color;
      this->thetaRate = thetaRate;

   }
};


class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }

   virtual void setup() {
      center = vec3(250, 250, 0);
      numConcentricCirles = 10;
      radius = 15;
      thetaRate = 0.2;

      std::vector<vec3> pallet  =  {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f
      };

      for (int i = 1; i <= numConcentricCirles; i++) {

         // switch the direction for each circles
         float direction = 1.0f;
         if (i % 2 == 0) {
            direction = -1.0f;
         }
         vec3 color = pallet[i % 5];
         CircleOfCircles c = CircleOfCircles(50*i, direction * thetaRate, color);
         concentricCircles.push_back(c);
      }
   }

   virtual void scene() {
      for (std::list<CircleOfCircles>::iterator c=concentricCircles.begin() ; c != concentricCircles.end(); ++c) {
         drawOneCircleOfCircle(*c);
      }
   }

   // an array of cicle rows
   void drawOneCircleOfCircle(CircleOfCircles c) {

      setColor(c.color);
      float theta = radians(360.0f) / (c.numCircles);
      
      for (int i = 0; i < c.numCircles; i++) {

         float newTheta = theta * i +  c.thetaRate * elapsedTime();
        
         float x = c.circleRadius* cos(newTheta) + center[0]; 
         float y = c.circleRadius * sin(newTheta) + center[1];
         drawSphere(vec3(x, y, 0), c.radius);

      }
   }  
   
   private:
      vec3 center; // stores the big center's circle's coordinates
      int numConcentricCirles;
      float radius; // the smallest circle's radius
      // CircleOfCircles c = CircleOfCircles(vec3(250, 250, 0), 128.0f, 16, 0.3, vec3(0, 0, 1));
      std::list<CircleOfCircles> concentricCircles;
      float thetaRate; // how fast will all the circles move
      std::vector<vec3> pallet;

};

int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}
