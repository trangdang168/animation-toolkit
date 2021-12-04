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
      reader.load("../motions/Beta/idle.bvh", _skeleton, _motion);
      _skeleton.fk();
      _drawer.color = vec3(1,0,0);

      _lhandOriginal = _skeleton.getByName("Beta:LeftHand")->getGlobalTranslation();
      _rhandOriginal = _skeleton.getByName("Beta:RightHand")->getGlobalTranslation();
      _lhandTarget = _lhandOriginal + vec3(-30, 30, 0);
      _rhandTarget = _rhandOriginal + vec3(30, 30, 0);
      handRange = 0.8f;
      leftHandId = _skeleton.getByName("Beta:LeftHand")->getID();
      rightHandId = _skeleton.getByName("Beta:RightHand")->getID();

      // hipId = _skeleton.getByName("Beta:Hip")->getID();
      // hipTarget = _skeleton.getByID(hipId)->getGlobalTranslation();

      // leftFootId = _skeleton.getByName("Beta:LeftFoot")->getID();

      // rightFootId = _skeleton.getByName("Beta:RightFoot")->getID();
   }

   void update()
   {
      _motion.update(_skeleton, elapsedTime());

      IKController ik;
      // TODO: Your code here
      _lhandTarget[1] +=  handRange * sin(elapsedTime() * speed);
      _rhandTarget[1] += handRange * sin(elapsedTime() * speed);

      // hipTarget[0] += 10 * sin(elapsedTime());

      ik.solveIKAnalytic(_skeleton, leftHandId, _lhandTarget, epsilon);
      ik.solveIKAnalytic(_skeleton, rightHandId, _rhandTarget, epsilon);

   }

   void scene()
   {  
      update();
      _drawer.draw(_skeleton, *this);
      setColor(vec3(0,0,1));
      drawSphere(_lhandTarget, 10);
      drawSphere(_rhandTarget, 10);
   }

protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;

   // Hand target positions
   vec3 _lhandTarget;
   vec3 _lhandOriginal;
   vec3 _rhandTarget;
   vec3 _rhandOriginal;
   float handRange;
   int leftHandId;
   int rightHandId;

   // int hipId;
   // vec3 hipTarget;

   // int leftFootId;
   // vec3 leftFootTarget;
   // int rightFootId;
   // vec3 rightFootTarget;

   float epsilon = 10.0f;
   float speed = 1.0;
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}

