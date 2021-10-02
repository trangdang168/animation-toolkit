#ifndef _interpolator_linear_H_
#define _interpolator_linear_H_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Linear 
//--------------------------------

class InterpolatorLinear : public Interpolator
{
public:
    InterpolatorLinear() : Interpolator("Linear") {
    }
    virtual glm::vec3 interpolate(int segment, double u) const {
      float uFloat = float(u);

      glm::vec3 point1 = mCtrlPoints[segment];
      glm::vec3 point2 = mCtrlPoints[segment + 1];


      return point1 * (1.0f - uFloat) + point2 * uFloat;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
      mCtrlPoints.clear();
      for (int i=0; i < keys.size(); i++) 
         mCtrlPoints.push_back(keys.at(i));
    }

};

#endif
