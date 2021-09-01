function outPos = to3D(inPos, ratio)
  
  xs = inPos(1)-400; # hard-code width/height to 400
  ys = 400-inPos(2);
  xsw = xs * ratio;
  ysw = ys * ratio;
  
  thetaV = 60/2 * pi/180; # hard-code camera fov
  thetaH = 70.6/2 * pi/180;
  zsw = 400 * ratio / tan(thetaV);
  dir = [xsw, ysw, zsw];
  len = norm(dir);
  yw = ysw / len * inPos(3);
  xw = xsw / len * inPos(3);
  zw = zsw / len * inPos(3); 

  outPos = [xw, yw, zw];
