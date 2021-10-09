#include "atkui/framework.h"
#include "atkmath/constants.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include <iostream>

using atkmath::Matrix3;
using atkmath::Vector3;
using atkmath::Deg2Rad;
using glm::vec3;

class Shape {
 public:
    vec3 top;
    vec3 right;
    vec3 bottom;
    vec3 left;
    vec3 color;
  Shape() {
    top = vec3(0);
    bottom = vec3(0);
    left = vec3(0);
    right = vec3(0);
    color = vec3(0);
  } 
  Shape(vec3 top, vec3 bottom, vec3 left, vec3 right, vec3 color) {
    this->top = top;
    this->bottom = bottom;
    this->left = left;
    this->right = right;
    this->color = color;
  } 
};

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
      
  }

  virtual void setup() {
   //   r = 100.0f;
   //   location = Vector3(250, 250, 0);
  
   pallet  =  {
      vec3(0,165,227)/255.0f,
      vec3(141,215,191)/255.0f,
      vec3(255,150,197)/255.0f,
      vec3(255,87,104)/255.0f,
      vec3(255,162,58)/255.0f
   };
   eulerAngle = Vector3(0,0,0);
   for (float i = 50; i < 500; i +=50) {
      for(float j = 50; j < 500; j +=50) {
         int color = rand() % 5;
         vec3 top = vec3(i, j, 0);
         vec3 bottom = vec3(i, j - 25, 0);
         vec3 left = vec3(i - 12.5, j - 12.5, 0);
         vec3 right = vec3(i - 12.5, j + 12.5, 0);
         shapes.push_back(Shape(top, bottom, left, right, pallet[color]));
      }
   }
  }

  virtual void scene() {
     eulerAngle[2] +=2;
     eulerAngle[2] = fmod(eulerAngle[2], 360.0f);

     Matrix3 m = Matrix3();
     m.fromEulerAnglesZYX(eulerAngle * Deg2Rad);
     for (int i = 0; i < shapes.size(); i+=1) {
        Vector3 newTop = m * Vector3(shapes[i].right[0] - shapes[i].top[0], 
                                       shapes[i].right[1] - shapes[i].top[1], 
                                       shapes[i].right[2] - shapes[i].top[2]);
        Vector3 newRight = m * Vector3(shapes[i].bottom[0] - shapes[i].right[0], 
                                       shapes[i].bottom[1] - shapes[i].right[1], 
                                       shapes[i].bottom[2] - shapes[i].right[2]);
        Vector3 newBottom = m * Vector3(shapes[i].left[0] - shapes[i].bottom[0], 
                                       shapes[i].left[1] - shapes[i].bottom[1], 
                                       shapes[i].left[2] - shapes[i].bottom[2]);
        Vector3 newLeft = m * Vector3(shapes[i].top[0] - shapes[i].left[0], 
                                       shapes[i].top[1] - shapes[i].left[1], 
                                       shapes[i].top[2] - shapes[i].left[2]);
        Shape toDraw = Shape(shapes[i].top + vectorToVec3(newTop), 
                              shapes[i].right + vectorToVec3(newRight), 
                              shapes[i].bottom + vectorToVec3(newBottom), 
                              shapes[i].left + vectorToVec3(newLeft), shapes[i].color);
        drawShape(toDraw);
     }

  }

  void drawShape(Shape r) {
     setColor(r.color);
     drawLine(r.top, r.right);
     drawLine(r.right, r.bottom);
     drawLine(r.bottom, r.left);
     drawLine(r.left, r.top);
  }

  vec3 vectorToVec3(Vector3 a) {
     return vec3(a[0], a[1], a[2]);
  }

  private:
      std::vector<vec3>pallet;
      Vector3 eulerAngle;
      // vec3 center;
      std::vector<Shape> shapes;
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}