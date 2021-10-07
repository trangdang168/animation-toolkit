#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Matrix3 Rx(float angle) {

   Matrix3 rotationMat = Matrix3(1.0,  0.0,  0.0,
                                 0.0,  cos(angle),  -sin(angle),
                                 0.0,  sin(angle),  cos(angle)
                                 );
   return rotationMat;
}

Matrix3 Ry(float angle) {

   Matrix3 rotationMat = Matrix3(cos(angle), 0.0, sin(angle),
                                 0.0, 1.0, 0.0,
                                 -sin(angle), 0.0,cos(angle)
                                 );

   // std::cout << "Ry, sin,cos,angle" << std::endl;
   // std::cout << rotationMat << std::endl;
   // std::cout<< sin(angle) <<std::endl;
   // std::cout<< cos(angle) <<std::endl;
   // std::cout << angle << std::endl;

   return rotationMat;
}

Matrix3 Rz(float angle) {

   Matrix3 rotationMat = Matrix3(cos(angle),  -sin(angle),  0.0,
                                 sin(angle),  cos(angle),  0.0,
                                 0.0,  0.0,  1.0
                                 );
   // std::cout << "Rz, sin,cos,angle" << std::endl;
   // std::cout << rotationMat << std::endl;
   // std::cout<< sin(angle) <<std::endl;
   // std::cout<< cos(angle) <<std::endl;
   // std::cout << angle << std::endl;

   return rotationMat;
}

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   return Vector3();
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   return Vector3();
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   *this = Identity;

   // 
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   *this = Identity;
   Matrix3 result = Rx(angleRad[0]) * Rz(angleRad[2]) * Ry(angleRad[1]);

   *this = result;

   std::cout << "angle rad" <<std::endl;
   std::cout << angleRad <<std::endl;

}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   *this = Identity;
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   *this = Identity;
   Matrix3 result = Rz(angleRad[2]) * Ry(angleRad[1]) * Rx(angleRad[0]);
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   // TODO
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   // TODO
   *this = Identity;
}

}