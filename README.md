# AnimationToolkit

Simple animation library

Design goals:
- keep the code simple and minimal
- don't repeat code between classes
- the code should match the pseudocode from class
- the code should be easily unit testable
- it should be easy to prototype animation algorithms using the code (esp. create small demo applications)

# Demos (/examples)

* behaviors
  * ABehaviorDemo - bloids demo using physics-based steerable controller
* blend
  * ABlend - blends two walking motions (strafe + forward walk) of the same length
  * AStyle - blends walking motions (sad, confident, chicken)
  * ABadBlend - blends two different motions (left_strafe + flip to upper cut)
* boxes
  * AStackingBoxes-2018 - positioning boxes using transforms (values from 2018)
  * AStackingBoxes-2019 - positioning boxes using transforms (values from 2019)
* characters
  * ASkeletonPractice - Simple program using ASkeleton API
  * ACharacterViewer - demo containing custom characters (googly eyes, bear, blinky)
  * AFancy - character with top hat and monocle
  * AButterfly - simple skeleton with root and two joints
  * AButterflyWings - simple skeleton with geometry for the wings and body (spheres)
  * AButterflyBonus - full butterfly animation
  * AThriller - Warrok thriller dance with devil character
  * AThrillerCrowd - a grid of randomized devil dancers
* crossfade
  * ACrossfadeViewer - crossfade demo (implementation is in libsrc/animation/MotionBlender)
  * AInterpolateBlend - uses interpolate to generate the transition (move to motion blender?)
  * AReorient - modify the starting position and direction of forward walk
* curveEditor
  * ACurveEditor - Spline curve editor demo
  * ACurveViewer - Uses old spline API to draw a hard-coded spline curve (2018 assignment)
  * ACurveBonus - two procedural curve demos (old API)
     * Dots - spheres animated with randomly generated splines
     * Grass - animated control points with yellow/green lines
  * ACurveDot - animates a dot based on curve editor (integrated into curveEditor in 2019)
  * ATestHermite - test interpolated values for in-class example
  * ATestCatmullRom - test interpolated values for in-class example
  * hermite.m - octave file for solving for slopes
* cyclops
  * ALooker - Cyclops character looks at a target
  * ADancer - Cyclops character with animated hands and hips (based on IK)
* fk
  * AFKViewer - viewer for motion files
* footclamp
  * AFootClamp - foot clamp demo on uneven terrain
* ik
  * AIKSimple - Two-link chain with joints along +x axis
  * AIKViewer - Interactive IK demo (CCD + Analytic)
  * ACCDStep - Performs CCD one step at a time
* ikWalk
  * IK walker, never completed
* interpolation
  * AParticleLerp - animate single particle position using lerp
  * AColorLerp1 - animate single particle color
  * AColorLerp2 - animate single particle position and color
  * AGradient - two-way color gradient visualized with nxn grid of cubes
  * ADrawCubic - sets control points and draws a single curve (for testing)
  * AParticleCubic - animates a dot along the path of a cubic
  * AAnimateCube - interpolates between two curves
  * AWavy - bonus demo with control points animated with sine
  * AScreensaver - interpolates between succsessive randomized curves
* keyviewer
  * AKeyviewer - character key frame editor (2018, uses old API)
  * AKeyframeCone - uses a position and rotational spline to animate a cone to travel the corners of a square
* particles
  * AFireworksViewer - fireworks with rocket demo 
  * AParticleViewer - general particle system demo with lots of options
* physics
  * AUnstoppable - character punches a wall
  * ABoxSim1 - implement simple net force example
  * ABoxSim2 - implement simple net force example
  * ABoxSim3 - implement simple net force example
  * AForceParticle - simulates a simple particle under forces
  * ABoxSim-2019 - simple net force example as part o the assignment
* rotations
  * ATeapotsviewer - grid of teapots for testing conversions
  * ASlerpTeapotCompare - compares different implementations of interpolating rotations (class demo)
  * ASlerpteapot - simple rotation spline with 3 keys 
  * ARipples - grid of rotating cubes which respond to mouse
  * AQuatMultiply - random test
* shapes
  * AShape - simple draw program using a shape class (intro assignment 2018)
  * ABonusShape - example draw demos
    * AShapeHead
    * AShapeColor
    * AFlower
    * ATorus
    * AShapePath
    * AShapeSpiral
* splines - old kruft spline code (not used)
* steering 
  * ASteeringDemo - single character with physics-based steering controller
  * ASteeringbehaviorDemo - boid behaviors with steerable character
* tentacles
  * Atentacle - procedurally animated tentacle
* trig - intro assignment 2019
  * AEyes - eyes look back and fortht a target
  * ALook - eyes look at a target controlled by the mouse
  * AVelocity - many particles all moving in the same direction
  * ACircles - concentric circles, rotating in opposite directions
  * AOscillate - circle moves up and down
  * ALine - line points to the mouse
  * AField - grid of lines 
  * AParticle - simple single particle moves in a straight line (class example)
  * ACircle - simple single particle moves in a circle (class example)
* unitTests - unit tests
* viewer2d - Empty 2D scene
* viewer3d - Empty 3D scene
* wasdController
   * AWASDSimple - simple keyboard-based controller which overrides the root position/rotation of a walking character

  
# Course spring 2019 post-mortem

- Simple test programs (skeleton/motion pratice) worked great for learning APIs
- leaving base-code more open-ended made it easier for students


# Course spring 2018 post-mortem

- make gallery of student work for course webpage
- Backup course notes
- finish ragdoll
- Document examples/assignments
- ODE QWOP
- update unit tests for blend and ik
- update code for behavior assignment
- todo: add comments to code (see AGLObjects.h)
- http://www.gdcvault.com/play/1022984/IK-Rig-Procedural-Pose
- cross product on bigger spaces: https://en.wikipedia.org/wiki/Cross_product#Generalizations
- converting between LHS and RHS (points vs vectors): http://www.howtobuildsoftware.com/index.php/how-do/bT1K/3d-rotation-geometry-coordinate-systems-euler-angles-right-handed-euler-angles-xyz-to-left-handed-euler-angles-xyz
- git-hook to check file sizes
- check gimbol lock (quat multiply)
- Save assignment grade templates
