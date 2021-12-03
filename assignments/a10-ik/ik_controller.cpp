#include "ik_controller.h"
#include "atkui/framework.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;

bool IKController::solveIKAnalytic(Skeleton& skeleton, 
    int jointid, const vec3& goalPos, float epsilon) {
  if (jointid == -1) return true;

  Joint* ankle = skeleton.getByID(jointid);
  if (!ankle->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* knee = ankle->getParent();
  if (!knee->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* hip = knee->getParent();

  // TODO: Your code here
  Joint* endEffector = skeleton.getByID(jointid);
  Joint* parent = endEffector->getParent();

  // compute parent with analytic
  return true;
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;

  // TODO: Your code here
  // TODO account for the delta too
  Joint* endEffector = skeleton.getByID(jointid);
  vec3 global = endEffector->getGlobalTranslation();

  int i = 0;
   while (length(endEffector->getGlobalTranslation() - goalPos) > threshold 
          && i < maxIters){
          // std::cout << "-------" << std::endl;
          // std::cout << "dist " << endEffector->getGlobalTranslation() - goalPos << std::endl;
    for (int j= 0; j<chain.size(); j++) {

      Joint* curJoint = chain.at(j);
      Joint* curJointParent = curJoint->getParent();

      vec3 r = endEffector->getGlobalTranslation() - curJoint->getGlobalTranslation();
      vec3 e = goalPos - endEffector->getGlobalTranslation();
      //std::cout << "-------" << std::endl;
      // std::cout << "end  " << endEffector->getGlobalTranslation() << std::endl;
      // std::cout << "cur " <<  curJoint->getGlobalTranslation() << std::endl;
      
      std::cout << "e " << e << std::endl;
      std::cout << "r " << r << std::endl;
      
      vec3 crossRE = cross(r, e);
      vec3 axis;
      
      if (length(crossRE) == 0) {
        axis = vec3(0, 0, 1);
      } else {
        axis = normalize(crossRE);
      }

      float theta  = nudgeFactor * atan2(length(crossRE), dot(r, r) + dot(r, e));
      

      std::cout << atan2(length(cross(r, e)), dot(r, r) + dot(r, e)) << std::endl;
      // std::cout <<  "axis " << axis << std::endl;

      vec3 localAxis = (curJointParent != skeleton.getRoot()) ? curJointParent->getLocal2Global().inverse().transformVector(axis) : axis;
      // std::cout << "parent " << curJointParent->getLocal2Global().inverse().transformVector(axis) << std::endl;
      // std::cout << "parent " << curJointParent->getName() << std::endl;

      // std::cout << "angle " << theta << std::endl;

      // std::cout << "localAxis " << localAxis << std::endl;
      quat rot = angleAxis(theta, localAxis);
      std::cout << "rot " << rot << std::endl;
      Transform move = Transform::Rot(rot);
      curJoint->setLocal2Parent(curJoint->getLocal2Parent() * move);
      curJoint->fk();

      //std::cout << "ee after " << endEffector->getGlobalTranslation() << std::endl;
    }
    i++;
  }
  
  return false;
}
