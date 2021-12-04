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
      _skeleton.fk();
      _drawer.color = vec3(1,0,0);

   }

   void update()
   {
      _motion.update(_skeleton, elapsedTime());

      IKController ik;

      // TODO: Your code here

   }

   void scene()
   {  
      update();
      _drawer.draw(_skeleton, *this);
      setColor(vec3(0,0,1));
   }

protected:
   Cyclops _drawer;
   Skeleton _skeleton;
   Motion _motion;

   float speed = 2.0;

   int leftFootId;
   vec3 leftFootTarget;
   quat _lfootRotation;
   int rightFootId;
   vec3 rightFootTarget;
   quat _rfootRotation;

   float epsilon = 0.0001f;
    std::vector<char> 
};

int main(int argc, char** argv)
{
   ADancer viewer;
   viewer.run();
   return 0;
}

