#include "atkui/framework.h"

using namespace glm;

class Particle {
 public:
    float speed;
    vec3 color;
    vec3 position;
  Particle() {
    position = vec3(rand() % 500, rand() % 500, 0);
    color = agl::randomUnitVector();
    speed = 100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200.0f-100.0f)));
  } 
};

class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {

    radius = 10.0f;
    // direction = agl::randomUnitVector();
    direction = vec3(1, 1, 0);
    for (int i = 0; i < numParticles; i++) {
      Particle p = Particle();
      particles.push_back(p);
    }
  }

  virtual void scene() {

    for (std::list<Particle>::iterator p=particles.begin() ; p != particles.end(); ++p) {
      vec3 newPosition = moveParticle(*p);
      setColor((*p).color);
      drawSphere(newPosition, radius);
    }
  }

  float wrapAround(float num) {
    int numInt = static_cast<int>(num);
    int mod = numInt % 500;
    float intAndFloatDiff = num - static_cast<float>(numInt);
    float modFloat = static_cast<float>  (mod);
    return modFloat + intAndFloatDiff;
  } 

  // move one particle
  vec3 moveParticle(Particle p) {
    vec3 newPosition = p.position + p.speed * direction * elapsedTime();

    // wrap arround
    if (newPosition[0] > 500 || newPosition[0] < 0) {
      newPosition[0] = wrapAround(newPosition[0]);
    } 

    if (newPosition[1] > 500 || newPosition[1] < 0) {
      newPosition[1] = wrapAround(newPosition[1]);
    } 

    if (newPosition[2] > 500 || newPosition[2] < 0) {
      newPosition[2] = wrapAround(newPosition[2]);
    } 

    return newPosition;
  }

  private:
    int numParticles = 200;
    float radius;
    std::list<Particle> particles;
    vec3 direction;
};

int main(int argc, char** argv) {

  // set the seed for randomization
  srand (static_cast <unsigned> (time(0)));
  Particles viewer;
  viewer.run();
  return 0;
}
