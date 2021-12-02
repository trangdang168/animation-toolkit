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

    _position = _walk.getKey(0).rootPos;

    _speed = 50.0f;
    
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


  virtual void update()
  {

    // compute transformations
    _walk.update(_skeleton, elapsedTime());

    // TODO: Your code here
    Pose pose = _skeleton.getPose();
    quat headingRotation = glm::angleAxis(_heading, vec3(0, 1, 0));

    // set heading rotation
    pose.jointRots[0] = headingRotation;

    // update position
    Transform headingTransform = Transform::Rot(headingRotation);
    pose.rootPos += _position + _speed * headingTransform.transformVector(vec3(0, 0, 1)) * dt();
    // add to skeleton
    _skeleton.setPose(pose);

    // set camera to follow the head
    Joint* head = _skeleton.getByName("Beta:Head");
    vec3 headPosition = head->getLocal2Global().transformPoint(vec3(0, 0, 0));
    vec3 cameraPosition= head->getLocal2Global().transformPoint(vec3(0, 0, -300));
    lookAt(cameraPosition, headPosition, vec3(0, 1, 0));


    // update heading when key is down
    if (keyIsDown('D')) {
        _heading -= 0.05;
      //  reorientInplace(_walk, _position, _heading);
    }
    if (keyIsDown('A')) {
      _heading += 0.05;
      // reorientInplace(_walk, _position, _heading);
    }
  }

protected:
  float _heading;

  Motion _walk;
  Skeleton _skeleton;
  atkui::SkeletonDrawer _drawer;
  vec3 _position;
  float _speed;
};

int main(int argc, char **argv)
{
  WASDSimple viewer;
  viewer.run();
}
