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
      Motion walk;
      reader.load("../motions/Beta/walking.bvh", _skeleton, walk);
      Motion martialArts;
      reader.load("../motions/Beta/back_flip_to_uppercut.bvh", _skeleton, martialArts);
      Motion leftTurn;
      reader.load("../motions/Beta/left_turn_90.bvh", _skeleton, leftTurn);

      _motion = crossfade(walk, martialArts);
      _motion = crossfade(_motion, leftTurn);
      _motion = crossfade(_motion, leftTurn);
      _motion = crossfade(_motion, walk);
      
      palette  =  {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f
      };

      for (int i = 0; i < numSkeletons; i++) {
         float size = 1;
         vec3 pos = vec3(-200 + i * 100, 0, -100);
         atkui::SkeletonDrawer drawer = atkui::SkeletonDrawer(pos, palette[i], size);
         _drawer.push_back(drawer);
      }

   }

  virtual void update()
  {
      _motion.update(_skeleton, elapsedTime());

  }

   void scene() {

      update();
      for (int i = 0; i < _drawer.size(); i++) {
         _drawer.at(i).draw(_skeleton, *this);
      }

      // draw cubes
      for (int i = 0; i < _drawer.size(); i++) {
         vec3 pos = _drawer.at(i).pos + vec3(0, 100, 350);
         setColor(palette.at(i));
         drawCube(pos, vec3(50, 50, 50));
      }

   }

   Motion reorient(const Motion& motion, const vec3& pos, float heading)
   {
      Motion result;
      
      result.setDeltaTime(motion.getDeltaTime());

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

         Transform move = desired * I * origin; // when desired 
         pose.jointRots[0] = move.r();
         pose.rootPos = move.t();

         result.appendKey(pose);

      }

      return result;
   }

  Motion crossfade( Motion motion1, Motion motion2)
  {
    Motion blend;
    int numBlendFrames = 10;
    assert(motion1.getNumKeys() > 0);
    assert(motion2.getNumKeys() > 0);
    assert(numBlendFrames <= motion1.getNumKeys());
    assert(numBlendFrames <= motion2.getNumKeys());

    int start1 = motion1.getNumKeys() - numBlendFrames;
    int start2 = 0;

    blend.setDeltaTime(motion1.getDeltaTime());

    for (int i = 0; i < start1; i++) {
      Pose pose = motion1.getKey(i);
      blend.appendKey(pose);
    }

    // reorient motion 2, before the blending
    quat rot =  motion1.getKey(motion1.getNumKeys() - 1).jointRots[0];
    float heading = glm::eulerAngles(rot)[1];
    Motion motion2Reoriented = reorient(motion2, motion1.getKey(motion1.getNumKeys() - 1).rootPos, heading);
  
    // cross fade
    for (int i = 0; i < numBlendFrames; i++) {
      float alpha = float(i) / float(numBlendFrames);
      Pose pose = Pose::Lerp(motion1.getKey(start1 + i), 
                              motion2Reoriented.getKey(start2 + i), alpha);
      blend.appendKey(pose);
    }

    for (int i = start2 + numBlendFrames; i < motion2Reoriented.getNumKeys(); i++) {
      Pose pose = motion2Reoriented.getKey(i);
      blend.appendKey(pose);
    }

    return blend;
  }

   protected:
      Skeleton _skeleton;
      Motion _motion;
      // float _duration;
      std::vector<vec3> positions;
      std::vector<vec3> palette;
      std::vector<vec3> sizes;

      std::vector<atkui::SkeletonDrawer> _drawer;
      int numSkeletons = 4;
};

int main(int argc, char** argv) {
   AUnique viewer;
   viewer.run();
   return 0;

}

