#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"
#include <iostream>
#include <cmath>

using namespace glm;
using namespace std;
using namespace atk;

class WASDSimple : public atkui::Framework
{
public:
  WASDSimple() : atkui::Framework(atkui::Perspective) {}

  virtual void setup()
  {
    BVHReader reader;
    reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
    _drawer.showAxes = true;

    vec3 rootPosition = _walk.getKey(0).rootPos;
    _position = rootPosition;
    speed = 10.0f;

    // fix the pose
    for (int i = 1; i < _walk.getNumKeys(); i++) {
      Pose pose = _walk.getKey(i);
      pose.rootPos = rootPosition;
      _walk.editKey(i, pose);

    }
    
  }

  virtual void scene()
  {
    update();
    _drawer.draw(_skeleton, *this);

    // draw heading
    vec3 p = _skeleton.getRoot()->getGlobalTranslation();
    p[1] = 10; // set height close above the floor

    setColor(vec3(0, 1, 1));
    push();
    translate(p);
    rotate(_heading, vec3(0, 1, 0));
    translate(vec3(0,0,25));
    scale(vec3(10, 10, 50));
    drawCylinder(vec3(0), 1.0f);
    pop();
}

   void reorientInplace(Motion& motion, const vec3& pos, float heading)
   {

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

         motion.editKey(i, pose);
      }
   }

  virtual void update()
  {
    _walk.update(_skeleton, elapsedTime());

    // TODO: Your code here
    Joint* head = _skeleton.getByName("Beta:Head");
    vec3 headPosition = head->getLocal2Global().transformPoint(vec3(0, 0, 0));
    vec3 cameraPosition= head->getLocal2Global().transformPoint(vec3(0, 0, -300));
    lookAt(cameraPosition, headPosition, vec3(0, 1, 0));


    // update heading when key is down
    if (keyIsDown('D')) {
        _heading -= 0.05;
       reorientInplace(_walk, _position, -0.05);
    }
    if (keyIsDown('A')) {
      _heading += 0.05;
      reorientInplace(_walk, _position, 0.05);
    }
  }

protected:
  float _heading;

  Motion _walk;
  Skeleton _skeleton;
  atkui::SkeletonDrawer _drawer;
  vec3 _position;
  float speed;
};

int main(int argc, char **argv)
{
  WASDSimple viewer;
  viewer.run();
}
