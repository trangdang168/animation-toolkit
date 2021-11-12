#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

#define START_KEY 120

using namespace atk;
using namespace atkui;
using namespace glm;

class ASplice : public atkui::Framework
{
public:
   ASplice() : atkui::Framework(atkui::Perspective) {}
   virtual ~ASplice() {}

   void setup()
   {
      _alpha = 0;

      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
      reader.load("../motions/Beta/gangnam_style.bvh", _skeleton, _upper);
      _splice = spliceUpperBody(_lower, _upper, _alpha);
   }

   Motion spliceUpperBody(const Motion& lower, const Motion& upper, float alpha)
   {
      Motion result;
      result.setFramerate(lower.getFramerate());

      // traverse all joints
      for (int lowerFrame = 0; lowerFrame < lower.getNumKeys(); lowerFrame++) {
         Pose pose = lower.getKey(lowerFrame); // lower body
         Pose newPose;
         newPose.deepCopy(pose);
         
         // set the upper body's rotation to be the blend
         Joint * upperBodyRoot = _skeleton.getByName("Beta:Spine1");
         std::list<Joint *> queue;
         queue.push_back(upperBodyRoot);
         
         
         while (!queue.empty()) {
            // go into the children
            Joint * cur = queue.front();
            int jointId = cur->getID();

            // blend
            quat r = slerp(upper.getKey(START_KEY + lowerFrame).jointRots[jointId], 
                           lower.getKey(lowerFrame).jointRots[jointId], alpha);
            
            newPose.jointRots[jointId] = r;

            for (int j = 0; j < cur->getNumChildren(); j++) {
               queue.push_back(cur->getChildAt(j));
            }
            queue.pop_front();
   
         }
      
         result.appendKey(newPose);

      }
      
      return result;
   }

   void scene()
   {  
      _splice.update(_skeleton, elapsedTime() * 0.5);
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
      drawText("alpha: "+std::to_string(_alpha), 10, 15);
   }

   void keyUp(int key, int mods) 
   {
      if (key == GLFW_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (key == GLFW_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
   }

   Skeleton _skeleton;
   Motion _upper;
   Motion _lower;
   Motion _splice;
   float _alpha;
};

int main(int argc, char** argv)
{
   ASplice viewer;
   viewer.run();
   return 0;
}

