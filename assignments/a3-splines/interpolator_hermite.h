#ifndef _interpolator_hermite_
#define _interpolator_hermite_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "interpolator.h"

//--------------------------------
// Hermite 
//--------------------------------

class InterpolatorHermite : public Interpolator
{
public:
    InterpolatorHermite() : Interpolator("Hermite"), mClampDir(glm::vec3(1,0,0)) {}

    virtual glm::vec3 interpolate(int segment, double u) const {
    
       glm::vec3 result = glm::vec3(0);
       double segmentLoc = double(segment) * 2.0;
    //    double iDouble = double(segmentLoc);
       // H 3 0
       result += bernstein(u, 3.0, 0.0, mCtrlPoints.at(segmentLoc));
       result += bernstein(u, 3.0, 1.0, mCtrlPoints.at(segmentLoc));
 
       // H 3 1
       result += (1.0f/3.0f) * bernstein(u, 3.0, 1.0, mCtrlPoints.at(segmentLoc+ 1));

       // H 3 2
       result -= (1.0f/3.0f) * bernstein(u, 3.0, 2.0, mCtrlPoints.at(segmentLoc+ 3));
       // H 3 3
       result += bernstein(u, 3.0, 2.0, mCtrlPoints.at(segmentLoc+2));
       result += bernstein(u, 3.0, 3.0, mCtrlPoints.at(segmentLoc+2));
       return result;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
        
        mCtrlPoints.clear();

        // Solve the system of linear equations
        Eigen::MatrixXf A(5, 5);
        Eigen::MatrixXf p(5, 3);
        Eigen::MatrixXf pPrime(5, 3); // slopes for each control point

        // matrix A, natural end points
        //A(0,0) =  2; A(0,1) = 1; A(0,2) = 0; A(0,3) = 0; A(0,4) = 0;
        A(1,0) =  1; A(1,1) = 4; A(1,2) = 1; A(1,3) = 0; A(1,4) = 0;
        A(2,0) =  0; A(2,1) = 1; A(2,2) = 4; A(2,3) = 1; A(2,4) = 0;
        A(3,0) =  0; A(3,1) = 0; A(3,2) = 1; A(3,3) = 4; A(3,4) = 1;
        //A(4,0) =  0; A(4,1) = 0; A(4,2) = 0; A(4,3) = 1; A(4,4) = 2;
            
        
        // matrix P, natural / clamped end points
        glm::vec3 v1 = 3.0f * (keys.at(2) - keys.at(0));
        glm::vec3 v2 = 3.0f * (keys.at(3) - keys.at(1));
        glm::vec3 v3 = 3.0f * (keys.at(4) - keys.at(2));

        p(1,0) = v1[0]; p(1,1) = v1[1]; p(1,2) = v1[2]; 
        p(2,0) = v2[0]; p(2,1) = v2[1]; p(2,2) = v2[2]; 
        p(3,0) = v3[0]; p(3,1) = v3[1]; p(3,2) = v3[2]; 


        if (isClamped()) {
            // set up clamped A
            A(0,0) =  1; A(0,1) = 0; A(0,2) = 0; A(0,3) = 0; A(0,4) = 0;
            A(4,0) =  0; A(4,1) = 0; A(4,2) = 0; A(4,3) = 0; A(4,4) = 1;

            // set up clamped p
            p(0,0) = mClampDir[0];
            p(0,1) = mClampDir[1];
            p(0,2) = mClampDir[2]; 

        } else {
            // set up natural A

            A(0,0) =  2; A(0,1) = 1; A(0,2) = 0; A(0,3) = 0; A(0,4) = 0;
            A(4,0) =  0; A(4,1) = 0; A(4,2) = 0; A(4,3) = 1; A(4,4) = 2;

            // set up natural p
            glm::vec3 v0 = 3.0f * (keys.at(1) - keys.at(0));
            p(0,0) = v0[0]; p(0,1) = v0[1]; p(0,2) = v0[2];
        }

        if (isClamped()) {
            p(4,0) = mClampDir[0];
            p(4,1) = mClampDir[1];
            p(4,2) = mClampDir[2]; 
        } else {
            glm::vec3 v4 = 3.0f * (keys.at(4) - keys.at(3));
            p(4,0) = v4[0]; p(4,1) = v4[1]; p(4,2) = v4[2]; 
        }

        pPrime = A.inverse() * p;
        for (int i = 0; i < 5; i ++) {
            mCtrlPoints.push_back(keys.at(i));
            glm::vec3 pVal = glm::vec3(0);
            pVal[0] = pPrime(i, 0);
            pVal[1] = pPrime(i, 1);
            pVal[2] = pPrime(i, 2);
            mCtrlPoints.push_back(pVal);
        }
    }

    void setClamped(bool c) { mIsClamped = c; }
    bool isClamped() const { return mIsClamped; }

    void setClampedDirection(const glm::vec3& v) { mClampDir = v; }
    glm::vec3 getClampDirection() const { return mClampDir; }

    double factorial (double x) const {
        if (x == 0) {
            return 1.0;
        }
        double res = 1.0f;
        for (double i = 1.0f; i <= x; i+=1.0f) {
            res *= i;
        }

        return res;
    }

    glm::vec3 bernstein(double t, double n, double i, glm::vec3 controlPoint) const {
        
        float combination = float (factorial(n) / (factorial(n - i) * factorial(i)));
        float a = float(pow(1.0 - t, n - i)); // a is 1 - t
        float b = float(pow(t, i)); // b is t
        return combination * a * b * controlPoint;
    }

private:
    bool mIsClamped = true;
    glm::vec3 mClampDir;
};

#endif
