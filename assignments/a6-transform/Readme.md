# Readme

## Slerp 

### Test output

```
q0 0 0 0 1
q1 0 0 0.866025 0.5
t=0.25: 0 0 0.258819 0.965926
t=0.5: 0 0 0.5 0.866025
t=0.75: 0 0 0.707107 0.707107
t=1: 0 0 0.866025 0.5
```

The test output matches the sample output.

### Gif

![Teapots rotation using Slerps](http://g.recordit.co/RtMyepYHNf.gif)

A rotating teapots using slerp.

## Stacking Boxes

![Boxes stacked final result](http://g.recordit.co/ltyJTRLqFg.gif)

Final order of the stacked box.

## Skeleton

```
The number of joints is 66
0 Beta:Hips
1 Beta:Spine
2 Beta:Spine1
3 Beta:Spine2
4 Beta:Neck
5 Beta:Neck1
6 Beta:Head
Siteta:Head
8 Beta:LeftShoulder
9 Beta:LeftArm
10 Beta:LeftForeArm
11 Beta:LeftHand
12 Beta:LeftHandThumb1
13 Beta:LeftHandThumb2
14 Beta:LeftHandThumb3
Siteeta:LeftHandThumb3
16 Beta:LeftHandMiddle1
17 Beta:LeftHandMiddle2
18 Beta:LeftHandMiddle3
Siteeta:LeftHandMiddle3
20 Beta:LeftHandIndex1
21 Beta:LeftHandIndex2
22 Beta:LeftHandIndex3
Siteeta:LeftHandIndex3
24 Beta:LeftHandRing1
25 Beta:LeftHandRing2
26 Beta:LeftHandRing3
Siteeta:LeftHandRing3
28 Beta:LeftHandPinky1
29 Beta:LeftHandPinky2
30 Beta:LeftHandPinky3
Siteeta:LeftHandPinky3
32 Beta:RightShoulder
33 Beta:RightArm
34 Beta:RightForeArm
35 Beta:RightHand
36 Beta:RightHandThumb1
37 Beta:RightHandThumb2
38 Beta:RightHandThumb3
Siteeta:RightHandThumb3
40 Beta:RightHandIndex1
41 Beta:RightHandIndex2
42 Beta:RightHandIndex3
Siteeta:RightHandIndex3
44 Beta:RightHandMiddle1
45 Beta:RightHandMiddle2
46 Beta:RightHandMiddle3
Siteeta:RightHandMiddle3
48 Beta:RightHandRing1
49 Beta:RightHandRing2
50 Beta:RightHandRing3
Siteeta:RightHandRing3
52 Beta:RightHandPinky1
53 Beta:RightHandPinky2
54 Beta:RightHandPinky3
Siteeta:RightHandPinky3
56 Beta:LeftUpLeg
57 Beta:LeftLeg
58 Beta:LeftFoot
59 Beta:LeftToeBase
Siteeta:LeftToeBase
61 Beta:RightUpLeg
62 Beta:RightLeg
63 Beta:RightFoot
64 Beta:RightToeBase
Siteeta:RightToeBase
The root joint name is: Beta:Hips
The root joint ID is: 0
The root joint's number of children is: 3
Beta:Spine
Beta:LeftUpLeg
Beta:RightUpLeg
Beta:LeftHand
The offset between the left hand and its parent is vec3(27.873800, 0.000000, 0.000000)
The parent of the hand is Beta:LeftForeArm
```

Output from skeleton_practice.cpp

## Tentacle

![Moving tentacle](http://g.recordit.co/PLeTe8i76N.gif)

A moving tentacle.

## Unique

![Spider trying to get up](http://g.recordit.co/b5blkJlvFb.gif)

A spider trying to get up but kept on swinging its legs around instead.


