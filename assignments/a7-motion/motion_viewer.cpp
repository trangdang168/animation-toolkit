#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class MotionViewer : public atkui::Framework
{
public:
   MotionViewer(std::string filename) : atkui::Framework(atkui::Perspective) {
      this->filename = filename;
   }

   void setup() {
      BVHReader reader;
      reader.load(filename, skeleton, motion);
      motion.update(skeleton, 0);
   }

   void scene() {
      time += dt();

      if (currentFrame < 0) {
         currentFrame += motion.getNumKeys();
      }

      currentFrame = currentFrame % motion.getNumKeys();

      if (not paused) {
         double t = motion.getNormalizedDuration(time) * motion.getDuration();
         currentFrame = (int)(t / motion.getDeltaTime());
         motion.update(skeleton, time);
      } else {
         Pose p = motion.getKey(currentFrame);
         skeleton.setPose(p);
      }

      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }

      drawText(paused? "Paused" : "Playing", 10, 15);
      drawText("Current frame: "+std::to_string(currentFrame), 10, 35);
      drawText("Time scale: "+std::to_string(timeScale), 10, 55);
   }

   virtual void keyUp(int key, int mods) {
      if (key == GLFW_KEY_P) {
         paused = !paused;
      } else if (key == GLFW_KEY_0) {
         currentFrame = 0;
      } else if (key == GLFW_KEY_RIGHT_BRACKET) {
         double curDeltaTime = motion.getDeltaTime();
         motion.setDeltaTime(curDeltaTime / timeScale);

      } else if (key == GLFW_KEY_LEFT_BRACKET) {
         double curDeltaTime = motion.getDeltaTime();
         motion.setDeltaTime(curDeltaTime * timeScale);

      } else {
         if (key == GLFW_KEY_PERIOD && paused) {
            currentFrame++;
         } else if (key == GLFW_KEY_COMMA && paused) {
            currentFrame--;
         }
      }
   }

private:
   Skeleton skeleton;
   Motion motion;

   float timeScale = 1.5f;
   int currentFrame = 0; 
   bool paused = false;
   float time = 0;
   std::string filename;

};


int main(int argc, char** argv) {
   // std::cout <<"first arg" << argv[1] <<std::endl;
   std::string filename;
   if (argc == 1) {
      filename = "../motions/Beta/jump.bvh";
   } else {
      filename = argv[1];
   }
   MotionViewer viewer(filename);
   viewer.run();
}
