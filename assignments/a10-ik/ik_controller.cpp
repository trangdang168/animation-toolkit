#include "ik_controller.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;
// using namespace std;

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
//   for (int j= 0; j<chain.size(); j++) {
//   // Joint * child;
//   // if (j == 0) {
//   //   child = endEffector;
//   // } else {
//   //   child = chain.at(j-1);
//   // }

//   vec3 r = endEffector->getGlobalTranslation() - chain.at(j)->getGlobalTranslation();
//   vec3 e = goalPos - endEffector->getGlobalTranslation();
//   float theta  = atan2(length(cross(r, e)), dot(r, r) + dot(r, e));
//   vec3 axis = cross(r, e) / length(cross(r, e));
//   quat rot = angleAxis(theta, axis);
//   chain.at(j)->setLocalRotation(rot);
//   skeleton.fk();

// }
  return true;
}

// solveIKCCD positions the joint given by jointid so its global position
// is located at goalPos
//
// param skeleton: the character to modify
// param jointid: the ID of the joint to pose
// param goalPos: the target position for jointid (global pos)
// param chain: the list of joints to "nudge" towards the goal
// param threshold: when the given joint is within threshold of the goal, stop iterating
// param maxIters: the max number of iterations to try to reach the goal
//
// return true/false based on whether we could reach the goal
// side effect: skeleton should by posed such that jointid is located at goalPos (or in this direction of
// goalPos if the target is out of reach)

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
    // vec3 global = endEffector->getGlobalTranslation();
    // vec3 diff = global - goalPos;

    // std::cout << "pd " << diff[0] << std::endl;
    // std::cout << diff[1] << std::endl;
    // std::cout << diff[2] << std::endl;

    // std::cout << "x " << global[0] << std::endl;
    // std::cout << global[1] << std::endl;
    // std::cout << global[2] << std::endl;
    for (int j= 0; j<chain.size(); j++) {

      vec3 r = endEffector->getGlobalTranslation() - chain.at(j)->getGlobalTranslation();
      vec3 e = goalPos - endEffector->getGlobalTranslation();
      float theta  = nudgeFactor * atan2(length(cross(r, e)), dot(r, r) + dot(r, e));
      vec3 axis = cross(r, e) / length(cross(r, e));
      
      // std::cout << "r " << r[0] << std::endl;
      // std::cout << "r " << r[1] << std::endl;
      // std::cout << "r " << r[2] << std::endl;
      // std::cout <<"e " << e[0] << std::endl;
      // std::cout <<"e " << e[1] << std::endl;
      // std::cout <<"e " << e[2] << std::endl;

      std::cout << "angle " << theta << std::endl;
      
      quat rot = angleAxis(theta, axis);
      chain.at(j)->setLocalRotation(rot);
      chain.at(j)->fk();

    }
    i++;
  }
  
  return false;
}
