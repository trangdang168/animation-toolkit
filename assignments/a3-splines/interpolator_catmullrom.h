#ifndef _interpolator_catmullrom_
#define _interpolator_catmullrom_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Catmull-Rom 
//--------------------------------

class InterpolatorCatmullRom : public Interpolator
{
public:
    InterpolatorCatmullRom() : Interpolator("Catmull-Rom") {}

    virtual glm::vec3 interpolate(int segment, double u) const {
       float coefficients [4] = {1.0f, 3.0f, 3.0f, 1.0f};
      //  float uFloat = float(u);
       glm::vec3 result = glm::vec3(0);
       for (int i = 0; i < 4; i ++) {
          float a = float(pow(1.0 - u, 3.0 - i)); // a is 1 - t
          float b = float(pow(u, i)); // b is t
          result += coefficients[i] * a * b * mCtrlPoints[i + segment*3];
       }
       return result;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       // todo: your code here
       // see: interpolator.h and writeup for details
       // segment 0
       mCtrlPoints.push_back(keys.at(0));
       mCtrlPoints.push_back(mCtrlPoints.at(0) + (1.0f/6.0f) * (keys.at(1) - keys.at(0)));
       mCtrlPoints.push_back(keys.at(2) - (1.0f/6.0f) * (keys.at(2) - keys.at(0)));

      // segment 1 keys.at(2) - keys.at(0)
       mCtrlPoints.push_back(keys.at(1));
       mCtrlPoints.push_back(keys.at(1) + (1.0f/6.0f) * (keys.at(2) - keys.at(0)));
       mCtrlPoints.push_back(keys.at(2)- (1.0f/6.0f) * (keys.at(2) - keys.at(1)));
       mCtrlPoints.push_back(keys.at(2));
    }
};

#endif
