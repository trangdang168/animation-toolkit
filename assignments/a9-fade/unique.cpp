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
      _motion = crossfade(walk, walk);
      palette  =  {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f,
         vec3(255,162,58)/255.0f
      };

      
      for (float z = 0; z < 500; z+=100) {
         positions.push_back(vec3(0, 0, z));
      }

      for (int i = 0; i < 5; i++) {
         int height = rand() % 8;
         sizes.push_back(vec3(50, height * 15, 30));
      }
   }

  virtual void update()
  {
      _motion.update(_skeleton, elapsedTime());
      Pose pose = _skeleton.getPose();
      Joint* leftFoot = _skeleton.getByName("Beta:LeftFoot");
      Joint* lowerLeg = leftFoot->getParent();
      std::cout << leftFoot->getParent() << std::endl;
      vec3 leftFootPosition = leftFoot->getGlobalTranslation();
      vec3 clampedLeftFoot = clampFoot(leftFootPosition);
      if (clampedLeftFoot != vec3(-1, -1, -1)) {
         vec3 newLeftFoot = clampedLeftFoot;
         vec3 localLeftFoot = leftFoot->getLocal2Global().inverse().transformPoint(newLeftFoot);
         vec3 newLocalLowerLeg = leftFoot->getLocal2Parent().transformPoint(newLeftFoot);
         vec3 newGlobalLowerLeg = lowerLeg->getLocal2Global().transformPoint(newLocalLowerLeg);
         solveIKTwoLink(lowerLeg, newGlobalLowerLeg);
      }
      Joint* rightFoot = _skeleton.getByName("Beta:RightFoot");
      vec3 rightFootPosition = rightFoot->getGlobalTranslation();
      vec3 clampedRightFoot = clampFoot(rightFootPosition);
      if (clampedRightFoot != vec3(-1, -1, -1)) {
         // IK
      }

  }

   void scene() {
      for (int i = 0; i < positions.size(); i++) {
         setColor(palette.at(i));
         drawCube(positions.at(i), sizes.at(i));
      }

      update();
      _drawer.draw(_skeleton, *this);

   }

   vec3 clampFoot(vec3 footPosition) {
      int box = int(footPosition[2]) / 100; 
      float space = fmod(footPosition[2], 100.f);

      // clamping the boxes
      if (box > 4) {
         box = 4;
      } else if (box < 0) {
         box = 0;
      }

      if (space > 30.0f && space < 70.0f) {
         return vec3(-1, -1, -1);
      } else if (space <= 30.0f) {
         return vec3(footPosition[0], sizes.at(box)[1], footPosition[2]);
      } else {
         return vec3(footPosition[0], sizes.at(box + 1)[1], footPosition[2]);
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


 void solveIKTwoLink(Joint* lowerLeg, const vec3 &goalPosition)
  {
    // todo: implement two link IK algorithm
    // aligning length
    vec3 rootPosition = lowerLeg->getGlobalTranslation();
    Joint* upperLeg = lowerLeg->getParent();

    vec3 translation1 = upperLeg->getLocalTranslation();
    float length1 = length(translation1);
    Joint * hips = upperLeg->getParent();
    vec3 translation2 = hips->getLocalTranslation();
    float length2 = length(translation2);

    float r = distance(goalPosition, rootPosition);

    float cosPhi =  (pow(r, 2) - pow(length1, 2) - pow(length2, 2)) 
                    / (-2 * length1 * length2);

    if (cosPhi > 1.0f) {
      cosPhi = 1.0f;
    } else if (cosPhi < -1.0f) {
      cosPhi = -1.0f;
    }
    float phi = acos(cosPhi);

    float theta2z = M_PI - phi;

    float sinTheta1z = -length2 * sin(theta2z) / r;
    float theta1z = asin(sinTheta1z);

    // align directions

    float gamma = asin(goalPosition[1] / r);
    float beta = atan2(-goalPosition[2], goalPosition[0]);

    // final rotations
    quat R12 = angleAxis(theta2z, vec3(0, 0, 1));
    quat R01 = angleAxis(beta, vec3(0, 1, 0)) * angleAxis(gamma, vec3(0, 0, 1))
                * angleAxis(theta1z, vec3(0, 0, 1));

    hips->setLocalRotation(R01);
    upperLeg->setLocalRotation(R12);
    _skeleton.fk();

  }

   protected:
      Skeleton _skeleton;
      Motion _motion;
      // float _duration;
      std::vector<vec3> positions;
      std::vector<vec3> palette;
      std::vector<vec3> sizes;

      atkui::SkeletonDrawer _drawer;
};

int main(int argc, char** argv) {
   AUnique viewer;
   viewer.run();
   return 0;

}

