#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

   /*
   {{1, 0, 0}, {0, c_x, -s_x}, {0, s_x, c_x}} 
   * {{c_z, -s_z, 0}, {s_z, c_z, 0}, {0, 0, 1}} 
   * {{c_y, 0, s_y}, {0, 1, 0}, {-s_y, 0, c_y}}
   */

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

   float y = asin(m13);
   float x;
   float z;

   if (m11 == 0 & m12==0 & m13==1 & m23==0 & m33 == 0) {
      z = 0;
      x = atan2(m21, m22);
   } else if (m11 == 0 & m12==0 & m13==-1 & m23==0 & m33 == 0) {
      x = 0;
      z = atan2(m21, m22);
   } else {
      z = atan2(-m12, m11);
      x = atan2(-m23, m33);
   }

   // 90 degree
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesXZY() const
{

   float z = asin(-m12);
   float y;
   float x;
   if (m12==-1) {

      y = -atan2(m31, m21);
      x = 0;
   } else if (m12==1) {
      x = 0;
      y = atan2(-m31, m33);
   } else {
      y = atan2(m13,m11);
      x = atan2(m32, m22);
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
   float x = asin(-m23);
   float y;
   float z;

   if (m23==-1) {
      z = atan2(m31, m11);
      y = 0;
   } else if (m23==1) {
      z = 0;
      y = atan2(-m31, m11);
   } else {
      y = atan2(m13, m33);
      z = atan2(m21, m22);
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesYZX() const
{

   float z = asin(m21);
   float x = 0.0;
   float y = 0.0;

   if (m21==1) {
      x = atan2(m32, m33);
      y = 0;
   } else if (m21==-1) {
      x = 0;
      y = -atan2(m32, m12);
   } else {
      x = atan2(-m23, m22);
      y = atan2(-m31, m11);
   }
   return Vector3(x, y, z);
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   float x = asin(m32);
   float y = 0.0;
   float z = 0.0;

   if (m32==1) {
      y = atan2(m21, m11);
      z = 0;
   } else if (m32==-1) {
      y = 0;
      z = atan2(m21, m11);
   } else {
      y = atan2(-m31, m33);
      z = atan2(-m12, m22);
   }
   return Vector3(x,y,z);
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   float x = 0.0;
   float y = asin(-m31);
   float z = 0.0;

   if (m31==-1) {
      z = 0;
      x = atan2(m12,m22);
   } else if (m31==1) {
      z = 0;
      x = atan2(-m12, m22);
   } else {
      z = atan2(m21, m11);
      x = atan2(m32, m33);
   }
   return Vector3(x, y, z);
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   *this = Identity;
   Matrix3 result = Rx(angleRad[0]) * Ry(angleRad[1]) * Rz(angleRad[2]);

   *this = result;
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   *this = Identity;
   Matrix3 result = Rx(angleRad[0]) * Rz(angleRad[2]) * Ry(angleRad[1]);

   *this = result;

   // std::cout << "angle rad" <<std::endl;
   // std::cout << angleRad <<std::endl;

}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   *this = Identity;
   Matrix3 result = Ry(angleRad[1]) * Rx(angleRad[0]) * Rz(angleRad[2]);
   *this = result;
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   *this = Identity;
   Matrix3 result = Ry(angleRad[1]) * Rz(angleRad[2]) * Rx(angleRad[0]);
   *this = result;
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   *this = Identity;
   Matrix3 result = Rz(angleRad[2]) * Rx(angleRad[0]) * Ry(angleRad[1]);
   *this = result;
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   *this = Identity;
   Matrix3 result = Rz(angleRad[2]) * Ry(angleRad[1]) * Rx(angleRad[0]);
   *this = result;
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   // TODO
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   // TODO
   *this = Identity;
   m11 = cos(angleRad) + (1-cos(angleRad)) * pow(axis[0], 2);
   m12 = -sin(angleRad) * axis[2] + (1 - cos(angleRad))*axis[0]*axis[1];
   m13 = axis[1]*sin(angleRad) + axis[0] * axis[2] * (1-cos(angleRad));
   m21 = axis[0]*axis[1] * (1 - cos(angleRad)) + axis[2] * sin(angleRad);
   m22 = cos(angleRad) + pow(axis[1], 2) * (1 - cos(angleRad));
   m23 = axis[1]*axis[2]*(1-cos(angleRad)) - axis[0]*sin(angleRad);
   m31 = axis[0] * axis[1] * (1-cos(angleRad)) - axis[1] * sin(angleRad);
   m32 = axis[1] * axis[2] * (1 - cos(angleRad)) + axis[0] * sin(angleRad);
   m33 = cos(angleRad) + pow(axis[2], 2) * (1 - cos(angleRad));

}

}

/*

{{cos(y), 0, sin(y)}, {0, 1, 0}, {-sin(y), 0, cos(y)}} * {{1, 0, 0}, {0, cos(x), -sin(x)}, {0, sin(x), cos(x)}} * {{cos(z), -sin(z), 0}, {sin(z), cos(z), 0}, {0, 0, 1}}

*/