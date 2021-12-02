#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "cyclops.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace glm;
using namespace std;

class ALooker : public atkui::Framework {
public:
   ALooker() : atkui::Framework(atkui::Perspective) {}
   virtual ~ALooker() {}

   void setup() {
      Motion motion;
      BVHReader reader;
      reader.load("../motions/Beta/idle.bvh", _skeleton, motion);
      motion.update(_skeleton, 0);

      _drawer.color = vec3(1,0,0);
      _head = _skeleton.getByName("Beta:Head");
   }

   void reset(Joint* head) {
      head->setLocalRotation(IdentityQ);
      head->fk();
   }

   void lookAtTarget(Joint* head, const vec3& target) {
      // TODO: Your code here
      // translate target to global

      vec3 globalHead = head->getGlobalTranslation();
      vec3 direction = target - globalHead;
      vec3 normalizedDirection = normalize(direction);

      // compute head's new local rotation
      vec3 z = normalizedDirection;
      vec3 x = cross(vec3(0, 1, 0), z);
      vec3 y = cross(z, x);

      // std::cout <<"target " << target << endl;
      
      quat rotation = quat_cast(mat3x3(x, y, z));

      // std::cout <<"rot" << rotation << endl;

      Transform newLocal2Global = Transform::Rot(rotation);
      newLocal2Global.setT(head->getLocal2Global().t());
      Transform move = head->getLocal2Global().inverse() * newLocal2Global;
      Transform newLocal2Parent = head->getLocal2Parent()* move;
      
      head->setLocal2Parent(newLocal2Parent);
      head->fk();
   }

   void scene() {  
      float r = 100;
      float angle = elapsedTime();
      _target = vec3(r * cos(angle), r * sin(angle) + r, 150);

      reset(_head);
      lookAtTarget(_head, _target);
      _drawer.draw(_skeleton, *this);

      vec3 globalHeadPos = _head->getGlobalTranslation();
      vec3 globalForward = _head->getGlobalRotation() * vec3(0,0,1);

      setColor(vec3(0,0,1));
      drawLine(globalHeadPos, globalHeadPos + 200.0f*globalForward);
      drawSphere(_target, 5);
   }

   Cyclops _drawer;
   Skeleton _skeleton;
   Joint* _head;
   vec3 _target;
};

int main(int argc, char** argv) {
   ALooker viewer;
   viewer.run();
   return 0;
}

