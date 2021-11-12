#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace atkui;
using namespace glm;

class AUnique : public atkui::Framework
{
public:
   AUnique() : atkui::Framework(atkui::Perspective) {}
   virtual ~AUnique() {}

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _motion1);
      reader.load("../motions/Beta/right_turn_90.bvh", _skeleton, _motion2);
      
      addKeys(_main, _motion1);
      addKeys(_main, _motion2);
      addKeys(_main, _motion1);
      addKeys(_main, _motion2);
      addKeys(_main, _motion1);
      addKeys(_main, _motion2);
   }

   void scene() {
      _main.update(_skeleton, elapsedTime() * 0.25);
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);

   }

   Motion reorient(const Motion& motion, const vec3& pos, float heading)
   {
      Motion result;
      result.setFramerate(motion.getFramerate());

      // compute transformations
      quat desiredRot = glm::angleAxis(heading, vec3(0,1,0));
      Transform desired = Transform::Rot(desiredRot);
      desired.setT(pos);

      Transform I = Transform::Translate(-motion.getKey(0).rootPos);

      for (int i = 0; i < motion.getNumKeys(); i++) {
         Pose pose = motion.getKey(i);
         vec3 d = pose.rootPos;
         quat rot = pose.jointRots[0];
         Transform origin = Transform();
         origin.setR(rot);
         origin.setT(d);

         Transform move = desired * I * origin;
         pose.jointRots[0] = move.r();
         pose.rootPos = move.t();

         result.appendKey(pose);
      }
      
      return result;
   }

   void addKeys(Motion& m, const Motion& addition) {
      Motion alignedAddition;
      if (m.getNumKeys() != 0) {
         vec3 pos = m.getKey(m.getNumKeys() - 1).rootPos;
         quat rot =  m.getKey(m.getNumKeys() - 1).jointRots[0];
         float heading = glm::angle(rot);
         alignedAddition = reorient(addition, pos, heading);
      } else {
         alignedAddition = addition;    
      }
      for (int i = 0; i < alignedAddition.getNumKeys(); i++) {
         
         m.appendKey(alignedAddition.getKey(i));
      }
   }


   void drawMotion(const Motion& m, const vec3& offset)
   {
      double t = elapsedTime() * 0.5;
      double time = m.getNormalizedDuration(t) * m.getDuration();
      m.update(_skeleton, time, false);

      SkeletonDrawer drawer;
      drawer.pos = offset;
      drawer.draw(_skeleton, *this);
   }

   protected:
      Skeleton _skeleton;
      Motion _blend;
      Motion _motion1;
      Motion _motion2;
      Motion _main;
      float _duration;
};

int main(int argc, char** argv) {
   AUnique viewer;
   viewer.run();
   return 0;

}

