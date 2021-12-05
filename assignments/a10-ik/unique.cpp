#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include "ik_controller.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ADancer : public atkui::Framework
{
public:
   ADancer() : atkui::Framework(atkui::Perspective) {}
   virtual ~ADancer() {}

   void setup()
   {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _motion);
      addKeys(_motion, _motion);
      _skeleton.fk();
      _drawer.color = vec3(1,0,0);

      for (int i = 0; i < numBoxes; i++) {
         float z =  100 * float(i);
         // std::cout << z << std::endl;
         positions.push_back(vec3(0, 0, z));
         float height = float(rand() % 3) * 30;
         sizes.push_back(vec3(50, height, distance));
      }

      _leftFootId = _skeleton.getByName("Beta:LeftFoot")->getID();

      _rightFootId = _skeleton.getByName("Beta:RightFoot")->getID();

      palette =  {
         vec3(0,165,227)/255.0f,
         vec3(141,215,191)/255.0f,
         vec3(255,150,197)/255.0f,
         vec3(255,87,104)/255.0f
      };

      leftFootJoint = _skeleton.getByName("Beta:LeftFoot");
      rightFootJoint = _skeleton.getByName("Beta:RightFoot");
   }

   void update()
   {
      _motion.update(_skeleton, elapsedTime());

      _lfootRotation = _skeleton.getByName("Beta:LeftFoot")->getGlobalRotation();
      _rfootRotation = _skeleton.getByName("Beta:RightFoot")->getGlobalRotation();

      vec3 leftFoot = leftFootJoint->getGlobalTranslation();
      vec3 rightFoot = rightFootJoint->getGlobalTranslation();

      // int leftFootWithinBox = int(leftFoot[2]) % 100;
      int leftFootBox = int(leftFoot[2]) / 100;

      IKController ik;

      vec3 newLeftFoot = leftFoot;
      newLeftFoot[1] = sizes.at(leftFootBox)[1];
      ik.solveIKAnalytic(_skeleton, _leftFootId, newLeftFoot, 0.001f);

      // int rightFootWithinBox = int(rightFoot[2]) % 100;
      int rightFootBox = int(rightFoot[2]) / 100;

      vec3 newRightFoot = rightFoot;
      newRightFoot[1] = sizes.at(rightFootBox)[1] + 10.f;
      ik.solveIKAnalytic(_skeleton, _rightFootId, newRightFoot, 0.001f);


      leftFootJoint->setLocalRotation(leftFootJoint->getLocalRotation() * inverse(leftFootJoint->getGlobalRotation()) * _lfootRotation);
      rightFootJoint->setLocalRotation(rightFootJoint->getLocalRotation() * inverse(rightFootJoint->getGlobalRotation()) * _rfootRotation);
      _skeleton.fk();
   }

   void scene()
   {  
      update();
      _drawer.draw(_skeleton, *this);
      setColor(vec3(0,0,1));

      for (int i = 0; i < numBoxes; i++) {
         setColor(palette.at(i));
         drawCube(positions.at(i), sizes.at(i));
      }
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


protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;


   int _leftFootId;
   vec3 _leftFootTarget;
   quat _lfootRotation;
   int _rightFootId;
   vec3 _rightFootTarget;
   quat _rfootRotation;
   Joint* leftFootJoint;
   Joint* rightFootJoint;

   std::vector<vec3> positions;
   std::vector<vec3> sizes;
   std::vector<vec3> palette;
   float distance = 100; 
   int numBoxes = 4;
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}

