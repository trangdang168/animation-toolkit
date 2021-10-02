#include <cmath>
#include "spline.h"
#include "math.h"
#include "interpolator_linear.h"

// global interpolator to use as default
static InterpolatorLinear gDefaultInterpolator; 

Spline::Spline() : 
  mDirty(true),
  mInterpolator(&gDefaultInterpolator) {
}

Spline::~Spline() {
}

void Spline::addInterpolationType(const std::string& name, Interpolator* interp) {
  mInterpolators[name] = interp;
}

void Spline::setInterpolationType(const std::string& name) {
  assert(mInterpolators.count(name) != 0);
  mInterpolator = mInterpolators[name];
  mDirty = true;
}

const std::string& Spline::getInterpolationType() const {
  return mInterpolator->getType();
}

void Spline::editKey(int keyID, const glm::vec3& value) {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys[keyID] = value;
  mDirty = true;
}

int Spline::appendKey(float time, const glm::vec3& value) {
  mKeys.push_back(value);
  mTimes.push_back(time);
  mDirty = true;
  return mKeys.size();
}

void Spline::deleteKey(int keyID) {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys.erase(mKeys.begin() + keyID);
  mTimes.erase(mTimes.begin() + keyID);
  mDirty = true;
}

glm::vec3 Spline::getKey(int keyID) const {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mKeys[keyID];
}

float Spline::getTime(int keyID) const {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mTimes[keyID];
}

int Spline::getNumKeys() const {
  return (int) mKeys.size();
}

void Spline::clear() {
  mKeys.clear();
  mTimes.clear();
  mInterpolator->clearControlPoints();
}

float Spline::getDuration() const {
  if (mKeys.size() == 0) return 0;
  int lastIdx = mKeys.size() - 1;
  return mTimes[lastIdx];
}

int Spline::getNumControlPoints() const {
  return mInterpolator->getNumControlPoints();
}

const glm::vec3& Spline::getControlPoint(int id) const {
  return mInterpolator->getControlPoint(id);
}

int Spline::getNumSegments() const {
  if (mKeys.size() > 1) return mKeys.size()-1;
  return 0;
}

void Spline::computeControlPoints() {
  mInterpolator->computeControlPoints(mKeys);
}

void Spline::editControlPoint(int id, const glm::vec3& v) {
  mInterpolator->editControlPoint(id, v);
}

glm::vec3 Spline::getValue(float t) const {
  if (mDirty) 
  {
    mInterpolator->computeControlPoints(mKeys);
    mDirty = false;
  }
  float normalizedTime = 0.0f;
  int segment = 0;

  if (mTimes.size() == 0) {
    normalizedTime = 0.0f;
    segment = 0;
  } else if (t <= mTimes[0]) {
    normalizedTime = mTimes[0];
    segment = 0;
  } else if (t >= getDuration()) {
    normalizedTime = getDuration();

    // the first point of the last segment
    segment = mTimes.size() - 2;
  } else {

    // search for the segment with binary search
    for (int i = 0; i < mTimes.size() - 1; i++){
      if (t >= mTimes[i] && t < mTimes[i+1]) {
        segment = i;
        break;
      }
    }
    normalizedTime = (t - mTimes[segment]) / (mTimes[segment + 1] - mTimes[segment]);
  }

  if (getNumControlPoints() == 0) {
    return glm::vec3(0);
  } else {
    glm::vec3 result = mInterpolator->interpolate(segment, normalizedTime);
    // compute the value [0, 1] along the segment for interpolation
    return result; 
  }
}

