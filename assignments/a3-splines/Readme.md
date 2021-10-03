# Readme

## Linear splines

```
control points: vec3(0.000000, 0.000000, 0.000000)
control points: vec3(1.000000, 1.000000, 0.000000)
control points: vec3(2.000000, 0.000000, 0.000000)
interpolate(0, 0) = vec3(0.000000, 0.000000, 0.000000)
interpolate(1, 1) = vec3(2.000000, 0.000000, 0.000000)
interpolate(1, 0.5) = vec3(1.500000, 0.500000, 0.000000)
```

Confirmed that output match the one in the lab write-up.

## Catmull-ROM splines

```
control points: vec3(0.000000, 0.000000, 0.000000)
control points: vec3(0.166667, 0.166667, 0.000000)
control points: vec3(0.666667, 1.000000, 0.000000)
control points: vec3(1.000000, 1.000000, 0.000000)
control points: vec3(1.333333, 1.000000, 0.000000)
control points: vec3(1.833333, 0.166667, 0.000000)
control points: vec3(2.000000, 0.000000, 0.000000)
interpolate(0, 0) = vec3(0.000000, 0.000000, 0.000000)
interpolate(1, 1) = vec3(2.000000, 0.000000, 0.000000)
interpolate(1, 0.5) = vec3(1.562500, 0.562500, 0.000000)
```
Confirmed that output match the one in the lab write-up.


## Hermite spline

```
control point: vec3(0.000000, 0.000000, 0.000000)
control point: vec3(1.000000, 0.000000, 0.000000)
control point: vec3(1.000000, 2.000000, 0.000000)
control point: vec3(1.321428, 2.035714, 0.000000)
control point: vec3(3.000000, 3.000000, 0.000000)
control point: vec3(2.714286, 0.857143, 0.000000)
control point: vec3(6.000000, 3.000000, 0.000000)
control point: vec3(2.821429, -2.464286, 0.000000)
control point: vec3(8.000000, 0.000000, 0.000000)
control point: vec3(1.000000, 0.000000, 0.000000)
(clamped) interpolate(0, 0) = vec3(0.000000, 0.000000, 0.000000)
(clamped) interpolate(3, 1) = vec3(8.000000, 0.000000, 0.000000)
(clamped) interpolate(2, 0.5) = vec3(4.486608, 3.415179, 0.000000)
(natural) interpolate(0, 0) = vec3(0.082321, 0.224750, 0.000000)
(natural) interpolate(3, 1) = vec3(7.831821, 0.374250, 0.000000)
(natural) interpolate(2, 0.5) = vec3(4.513393, 3.281250, 0.000000)
```
Confirmed that output match the one in the lab write-up.

## Spline

```
-------------------------------
Current interpolation type: Linear
Number of control points: 0
Duration: 0
getValue(0): vec3(0.000000, 0.000000, 0.000000)

-------------------------------
Current interpolation type: Linear
Number of control points: 2
Duration: 1
getValue(-1): vec3(0.000000, 0.000000, 0.000000)
getValue(5): vec3(1.000000, 1.000000, 0.000000)
getValue(0.5): vec3(0.500000, 0.500000, 0.000000)
getValue(0): vec3(0.000000, 0.000000, 0.000000)
getValue(1): vec3(1.000000, 1.000000, 0.000000)

-------------------------------
Current interpolation type: Linear
Number of control points: 3
Duration: 2
getValue(1.5): vec3(1.500000, 0.500000, 0.000000)

-------------------------------
Current interpolation type: Catmull-Rom
Number of control points: 7
Duration: 2
getValue(1.5): vec3(1.562500, 0.562500, 0.000000)

-------------------------------
Current interpolation type: Hermite
Number of control points: 6
Duration: 2
getValue(1.5): (clamped) vec3(1.500000, 0.500000, 0.000000)
getValue(1.5): (natural) vec3(1.500000, 0.687500, 0.000000)

-------------------------------
Current interpolation type: Hermite
Number of control points: 6
Duration: 2
getValue(1.5): (natural)vec3(1.906250, 1.093750, 0.000000)

-------------------------------
Current interpolation type: Hermite
Number of control points: 4
Duration: 2
getValue(1.5): vec3(2.250000, 0.750000, 0.000000)
```

Confirmed that output match the one in the lab write-up.

## Curve editor

![Curve editor](http://g.recordit.co/IIGsdydR0s.gif)

The user can add, edit, remove and view control points of splines on the curve editor.

## Unique!

![colorful spheres](http://g.recordit.co/nCF5imncCR.gif)

Playing colorful spheres!
