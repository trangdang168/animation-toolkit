#ifndef ATKUI_Framework_H_
#define ATKUI_Framework_H_

#include "atk/math.h"
#include "agl/window.h"
#include "agl/aglm.h"
#include <vector>

namespace atkui {
  /**
   * Orthographic: 2D
   * Perspective: 3D
   * Only object in front of the camera can be seen.
   */ 
enum Display { Orthographic, Perspective };

class Framework : public agl::Window {
 public:
  Framework(Display type);
  virtual ~Framework();

 protected:
  virtual void scene() {} // override to update and draw custom components

  virtual void draw() override;
  virtual void setColor(const glm::vec3& c);
  virtual void drawSphere(const glm::vec3& pos, float radius);
  virtual void drawLine(const glm::vec3& a, const glm::vec3& b);
  virtual void drawFloor(float size, float big = 200, float small = 50);
  int _type;

 private:
  glm::vec3 _color;
};
}
#endif
