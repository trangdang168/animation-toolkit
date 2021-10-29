#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	Quaternion q;
	double cosOmega = Dot(q0, q1);
	double omega = acos(cosOmega);

	if (cosOmega < 0) {
		cosOmega = -cosOmega;
		Quaternion q2 = -q1;
		q = (sin(omega * (1.0 - t))/sin(omega)) * q0 + 
			(sin(omega * t)/sin(omega)) * q2;
	} else {
		q = (sin(omega * (1.0 - t))/sin(omega)) * q0 + 
			(sin(omega * t)/sin(omega)) * q1;
	}

	q.normalize();
	return q;
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
	Matrix3 mat = Matrix3();
	mat[0][0] = 1 - 2*(pow(mY, 2) + pow(mZ, 2));
	mat[0][1] = 2 * (mX * mY - mZ * mW);
	mat[0][2] = 2 * (mX*mZ + mW * mY);
	mat[1][0] = 2 * (mX * mY + mW * mZ);
	mat[1][1] = 1 - 2*(pow(mX, 2) + pow(mZ, 2));
	mat[1][2] = 2 * (mY*mZ - mW * mX);
	mat[2][0] = 2 * (mX * mZ - mW * mY);
	mat[2][1] = 2 * (mY * mZ + mW * mX);
	mat[2][2] = 1 - 2 * (pow(mY, 2) + pow(mX, 2));
	return mat;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	// TODO
	double wSquare = 0.25 * (rot[0][0] + rot[1][1] + rot[2][2] +1);
	double xSquare = 0.25 * (1 + rot[0][0] - rot[1][1] - rot[2][2]);
	double ySquare = 0.25 * (1- rot[0][0] + rot[1][1] - rot[2][2]);
	double zSquare = 0.25 * (1 - rot[0][0] - rot[1][1] + rot[2][2]);

	double wx = 0.25 * (rot[2][1] - rot[1][2]);
	double wy = 0.25 * (rot[0][2] - rot[2][0]);
	double wz = 0.25 * (rot[1][0] - rot[0][1] );

	double xy = 0.25 * (rot[1][0] + rot[0][1]);
	double yz = 0.25 * (rot[1][2] + rot[2][1]);
	double xz= 0.25 * (rot[0][2] + rot[2][0]);

	double w=0; 
	double x=0;
	double y=0; 
	double z=0;

	if (wSquare >= xSquare & wSquare >= ySquare & wSquare >= zSquare) {

		w = sqrt(wSquare);
		x = wx / w;
		y = wy / w;
		z = wz / w;

	} else if (xSquare >= ySquare & xSquare >= zSquare & xSquare >= wSquare) {

		x = sqrt(xSquare);
		w = wx / x;
		y = xy / x;
		z = xz / x;

	} else if (ySquare >= xSquare & ySquare >= zSquare & ySquare >= xSquare & ySquare >= wSquare) {

		y = sqrt(ySquare);
		w = wy / y;
		x = xy / y;
		z = yz / z;

	} else { // zSquare the largest

		z = sqrt(zSquare);
		x =xz/z;
		w = wz/z;
		y =yz/z;
	}
	mX = x;
	mY = y;
	mZ = z;
	mW = w;
	normalize();
}

}