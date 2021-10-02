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
        Eigen::MatrixXf A = Eigen::MatrixXf::Zero(keys.size(), keys.size());
        Eigen::MatrixXf p = Eigen::MatrixXf::Zero(keys.size(), 3);
        Eigen::MatrixXf pPrime = Eigen::MatrixXf::Zero(keys.size(), 3); // slopes for each control point


        // matrix A
        for (int i = 0; i < keys.size() - 2; i++) {
            A(i+1, i) = 1;
            A(i+1, i+1) = 4;
            A(i+1, i+2) = 1;
        }
        
        for (int i = 0; i < keys.size() - 2; i++) {
            glm::vec3 v = 3.0f * (keys.at(i+2) - keys.at(i));
            p(i+1, 0) = v[0];
            p(i+1, 1) = v[1];
            p(i+1, 2) = v[2]; 
        }


        // set up clamped or natural top
        if (isClamped()) {
            // set up clamped A
            A(0, 0) = 1;

            // set up clamped p
            p(0,0) = mClampDir[0];
            p(0,1) = mClampDir[1];
            p(0,2) = mClampDir[2]; 

        } else {
            // set up natural A
            A(0, 0) = 2;
            A(0, 1) = 1;

            // set up natural p
            glm::vec3 v0 = 3.0f * (keys.at(1) - keys.at(0));
            p(0,0) = v0[0]; p(0,1) = v0[1]; p(0,2) = v0[2];
        }

        // set up clamped or natural bottom
        if (isClamped()) {
            A(keys.size() - 1, keys.size() - 1) = 1;

            p(keys.size() - 1,0) = mClampDir[0];
            p(keys.size() - 1,1) = mClampDir[1];
            p(keys.size() - 1,2) = mClampDir[2]; 
        } else {
            A(keys.size() - 1, keys.size() - 2) = 1;
            A(keys.size() - 1, keys.size() - 1) = 2;

            glm::vec3 v = 3.0f * (keys.at(keys.size() - 1) - keys.at(keys.size() - 2));
            p(keys.size() - 1,0) = v[0]; p(keys.size()-1,1) = v[1]; p(keys.size()-1,2) = v[2]; 
        }

        pPrime = A.inverse() * p;
        for (int i = 0; i < keys.size(); i ++) {
            mCtrlPoints.push_back(keys.at(i));
            glm::vec3 pVal = glm::vec3(0);
            pVal[0] = pPrime(i, 0);
            pVal[1] = pPrime(i, 1);
            pVal[2] = pPrime(i, 2);
            mCtrlPoints.push_back(pVal);
        }

        // std::cout<< "result"<<std::endl;
        // std::cout<<A<<std::endl;
        // std::cout<<p<<std::endl;
        // std::cout<<pPrime<<std::endl;
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