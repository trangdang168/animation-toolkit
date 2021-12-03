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

  std::cout << "-----------"<<std::endl;
  // TODO: Your code here

  float kneeAnkle = length(ankle->getLocalTranslation());
  if (length(goalPos - ankle->getGlobalTranslation())< epsilon) {
      return true;
  }
  float hipKnee = length(knee->getLocalTranslation());

  std::cout << "goal " << goalPos <<std::endl;
  // std::cout << "hip " << hip->getGlobalTranslation() <<std::endl;
  // std::cout << "hip knee " << hipKnee <<std::endl;
  // std::cout << "knee ankle" << kneeAnkle <<std::endl;

  vec3 hipToDesiredAnkle = goalPos - hip->getGlobalTranslation();
  float r = length(hipToDesiredAnkle);
  // std::cout << "r" << r <<std::endl;
  float cosTheta2Z = (pow(r, 2) - pow(hipKnee, 2) - pow(kneeAnkle, 2)) 
                      / (-2 * kneeAnkle * hipKnee);

  // clamp cosTheta2Z to [-1.0f, 1.0f]
  cosTheta2Z = std::max(std::min(cosTheta2Z, 1.0f), -1.0f); // clamps cphi
  float theta2Z = acos(cosTheta2Z) - float(M_PI);

  // std::cout << "cos theta2z " << cosTheta2Z <<std::endl;
  
  // rotating the parent joint (the knee)
  vec3 limbDir = normalize(knee->getLocalTranslation());
  vec3 axis = cross(limbDir, vec3(0,0,-1));
  if (limbDir[1] < 0) axis = cross(limbDir, vec3(0,0,1));
  quat rot = angleAxis(theta2Z, axis);

  std::cout << "parent rot axis " << axis <<std::endl;
  std::cout << "theta2z " << theta2Z <<std::endl;
  Transform newKnee = Transform(rot, knee->getLocalTranslation(), vec3(1));
  knee->setLocal2Parent(newKnee);

  // knee->setLocalRotation(rot);
  std::cout << "parent rot " << rot <<std::endl;

  // set identity location for hip to avoid twisting
  // ankle->setLocalRotation(IdentityQ);
  hip->setLocalRotation(IdentityQ);

  std::cout << "parent trans " << newKnee << std::endl;
  skeleton.fk();

  // angle axis method
  vec3 newAnkle = ankle->getGlobalTranslation();
  vec3 newR = newAnkle - hip->getGlobalTranslation();
  vec3 e = goalPos - newAnkle;
  vec3 crossRE = cross(newR, e);

  if (length(crossRE) == 0) {
    crossRE = vec3(0, 0, 1);
  }

  std::cout << "newAnkle " << newAnkle << std::endl;
  std::cout << "hip global " << hip->getGlobalTranslation() << std::endl;

  vec3 u = normalize(crossRE);
  if (hip != skeleton.getRoot()) {
    u = hip->getParent()->getLocal2Global().inverse().transformVector(u);
  }

  float phi = atan(length(crossRE), dot(newR, e) + dot(newR, newR));

  std::cout << "phi " << phi << std::endl;
  std::cout << "u " << u << std::endl;

  quat hipRot = angleAxis(phi, u);

  Transform moveHip = Transform::Rot(hipRot);

  hip->setLocal2Parent(hip->getLocal2Parent()* moveHip);
  skeleton.fk();

  std::cout << "final pos " <<ankle->getGlobalTranslation() << std::endl;

  if (length(ankle->getGlobalTranslation() - goalPos) < epsilon) {
    return true;
  } else {
    return false;
  }
  
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;

  // TODO: Your code here
  Joint* endEffector = skeleton.getByID(jointid);
  vec3 global = endEffector->getGlobalTranslation();

  int i = 0;
   while (length(endEffector->getGlobalTranslation() - goalPos) > threshold 
          && i < maxIters){
    for (int j= 0; j<chain.size(); j++) {

      Joint* curJoint = chain.at(j);
      Joint* curJointParent = curJoint->getParent();

      vec3 r = endEffector->getGlobalTranslation() - curJoint->getGlobalTranslation();
      vec3 e = goalPos - endEffector->getGlobalTranslation();
      //std::cout << "-------" << std::endl;
      // std::cout << "e " << e << std::endl;
      // std::cout << "r " << r << std::endl;
      
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
      // std::cout << "rot " << rot << std::endl;
      Transform move = Transform::Rot(rot);
      curJoint->setLocal2Parent(curJoint->getLocal2Parent() * move);
      skeleton.fk();

      //std::cout << "ee after " << endEffector->getGlobalTranslation() << std::endl;
    }
    i++;
  }
  
  return false;
}
