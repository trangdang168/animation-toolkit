#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	// TODO
	return Quaternion(1,0,0,0);
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	angleRad = 2 * acos(mW);
	Vector3 v = Vector3(mX, mY, mZ);
	axis = v * 1/sin(angleRad/2);

}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	Vector3 v = sin(angleRad/2) * axis;
	double w = cos(angleRad/2);
	mW = w;
	mX = v[0]; mY = v[1]; mZ = v[2];
	normalize();
}

Matrix3 Quaternion::toMatrix () const
{
	// TODO
	return Matrix3::Identity;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	// TODO
}

}