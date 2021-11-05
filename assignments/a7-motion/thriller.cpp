#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

#define HI 1.25f
#define LO 0.75f

using namespace atk;
using namespace glm;

/*


    The basecode uses a "Devil" object to draw each character. 
    Use a vector or array to store multiple "Devil" objects. 
    Each object can have its own color, position, and size.

    Arrange 12 characters in a 4x3 grid across the floor.

    Jitter the positions of the characters so that the alignment is not exact.

    Randomize the colors of the characters.

    Randomize the sizes of the characters.


*/

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

      float space = 250.0f;
      int jitter = 20;
      vec3 center = vec3(space * (12/numCol - 1)/2.0f + 50, 0, space * (numCol-1)/2 + 50);
      
      for (int i = 0; i < numDevils; i++) {
         int row = i / numCol;
         int col = i % numCol;
         vec3 position = vec3(row * space + rand() % jitter, 0, col * space + rand() % jitter)
                           - center;
         vec3 color = agl::randomUnitVector();
         float size = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        
         _devils.push_back(Devil(position, color, size));

         // std::cout << row << " " << col << " " <<position << std::endl;
      }
   }

   virtual void scene() {
      if (!_paused) _motion.update(_skeleton, elapsedTime());
      for (int i = 0; i < _devils.size(); i++) {
         _devils[i].draw(_skeleton, *this);
      }
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   std::vector<Devil> _devils;
   int numDevils = 12;
   int numCol = 3;
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}

// #include <random>
// #include <functional>
// #include "atkui/framework.h"
// #include "atk/toolkit.h"
// #include "agl/renderer.h"
// #include "devil.h"

// using namespace atk;
// using namespace glm;

// class Thriller : public atkui::Framework
// {
// public:
//    Thriller() : atkui::Framework(atkui::Perspective) {}
//    virtual ~Thriller() {}

//    virtual void setup() {
//       BVHReader reader;
//       reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

//       vec3 position = vec3(0);
//       vec3 color = vec3(1,0,0);
//       float size = 1.0f;
//       _devil = Devil(position, color, size);
//    }

//    virtual void scene() {
//       if (!_paused) _motion.update(_skeleton, elapsedTime());
//       _devil.draw(_skeleton, *this);
//    }

//    virtual void keyUp(int key, int mods) {
//       if (key == 'P') _paused = !_paused;
//    }

// protected:
//    Motion _motion;
//    Skeleton _skeleton;
//    bool _paused = false;
//    Devil _devil;
// };

// int main(int argc, char** argv) {
//    Thriller viewer;
//    viewer.run();
// }


