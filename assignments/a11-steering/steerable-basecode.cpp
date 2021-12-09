#include "steerable.h"
#include "behaviors.h"

using namespace glm;
using namespace atk;

float ASteerable::kVelKv = 5.0; // v0
float ASteerable::kOriKv = 16.0;   // v1
float ASteerable::kOriKp = 64.0; // p1

// Given a desired velocity, veld, and dt, compute a transform holding 
// the new orientation and change in position
//
// rotation control: tau = I * (-Kv1 * thetaDot + Kp1 * (thetaD - theta))
// translation control: f = m * Kv0 * (vd - v)
void ASteerable::senseControlAct(const vec3& veld, float dt)
{
   // Compute _vd and _thetad
   _vd = length(veld);
   std::cout << "veld " << _veld << std::endl;
   _thetad = atan2(_veld[0], _veld[2]);

   // // compute _force and _torque
   // kOriKv = pow(_thetad, 2);
   // float zeta = 1.0f;
   // kOriKp = 2 * _thetad * zeta;

   // kVelKv = 0.02f;

   std::cout << "------- " << std::endl;
   std::cout << "state[2] " << _state[2] << std::endl;
   std::cout << "state[3] " << _state[3] << std::endl;

   std::cout << "kv " << kOriKv << std::endl;
   std::cout << "kp " << kOriKp << std::endl;
   _force = _mass * kVelKv * (_vd - _state[2]);
   _torque = _inertia * (-kOriKv * _state[3] + 
            kOriKp * (_thetad - _state[1]));

   // find derivative
   // enum {VEL, AVEL, f/m, t/m};
   float derivative[4];
   derivative[0] = _state[2];
   derivative[1] = _state[3];
   derivative[2] = _force/_mass;
   derivative[3] = _torque/_inertia;

   std::cout << "f " << _force << std::endl;
   std::cout << "t " << _torque << std::endl;
   // update state
   for (int i = 0; i < 4; i++) {
      _state[i] += dt * derivative[i]; 
   }

   // compute global position and orientation and update _characterRoot
   quat rot = glm::angleAxis(_state[ORI], vec3(0,1,0));
   vec3 localPos(0,0,_state[POS]);

   _characterRoot.setT(rot * localPos + _characterRoot.t());
   _characterRoot.setR(rot); 
}

// randomize the colors, characters, and animation times here
void ASteerable::randomizeAppearance()
{
   // to randomize the walking animations, compute different initial values 
   // for _time

   // to randomize color, call _drawer.setColor

   // to randomize shape, compute random values for _drawer.setJointRadius
   // or randomly assign different drawers to have a mix of characters
}

