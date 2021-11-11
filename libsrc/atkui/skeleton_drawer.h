#ifndef SKELETON_H_
#define SKELETON_H_

#include "atkui/framework.h"

namespace atkui {

class SkeletonDrawer
{
public:
   SkeletonDrawer() {}
   SkeletonDrawer(const glm::vec3& p, const glm::vec3& c, float s) {
      pos = p;
      size = glm::vec3(s);
      color = c;
   }
   virtual ~SkeletonDrawer() {}

   void draw(const atk::Skeleton& skeleton, atkui::Framework& f) {

      f.push();
      f.translate(pos);
      f.scale(size);
      f.setColor(color);

      float jointRadius = 10;
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         atk::Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;
         if (joint->getParent()->getName().find("Hand") != std::string::npos) continue; // skip hands

         glm::vec3 p1 = joint->getGlobalTranslation();
         glm::vec3 p2 = joint->getParent()->getGlobalTranslation();
         f.drawEllipsoid(p1, p2, jointRadius);
         f.drawSphere(p2, jointRadius);
         f.drawSphere(p1, jointRadius);
      }
      f.pop();
   }

public:
   glm::vec3 color = glm::vec3(0.1,0.3,1.0);
   glm::vec3 size = glm::vec3(1.0);
   glm::vec3 pos = glm::vec3(0);
};

}  // end namespace atkui

#endif
