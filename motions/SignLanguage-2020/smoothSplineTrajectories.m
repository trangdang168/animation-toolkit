% Smooths input file trajectories using a splinefit
function [] = smoothSplineTrajectories(smoothFactor, inputFile, outputFile)

  load(inputFile);
  
  spineBaseId = 1;
  spineMidId = 2;
  neckId = 3;
  headId = 4;
  shoulderLeft = 5;
  elbowLeft = 6;
  wristLeft = 7;
  handPalmLeft = 8;
  shoulderRight = 9;
  elbowRight = 10;
  wristRight = 11;
  handPalmRight = 12;
  spineShoulder = 21;
  handTipLeft = 22;
  thumbLeft = 23;
  handTipRight = 24;
  thumbRight = 25;
  
  joints = [spineBaseId, spineMidId, spineShoulder, neckId, headId, ...
            shoulderLeft, elbowLeft, wristLeft, ...
            handPalmLeft, handTipLeft, thumbLeft, ...
            shoulderRight, elbowRight, wristRight, ...
            handPalmRight, handTipRight, thumbRight];
  
  frame = 1;
  spinePos = arr(frame, (spineBaseId-1)*3+1:(spineBaseId-1)*3+3); # spine base
  headPos = arr(frame, (neckId-1)*3+1:(neckId-1)*3+3); 
  
  heightInches = 5 * 12 + 9; # participant one
  height = heightInches * 0.0254; # convert to meters
  torsoLength = (3/8.0) * height;
  
  # Estimate ratio from meters to screen pixels
  rs = abs(spinePos(2) - headPos(2));
  ratio = torsoLength / rs;
            
  for f=1:size(arr,1)
    for j=1:size(joints,2)
      jointId = joints(1,j)-1;
      pos = arr(f, jointId*3+1:jointId*3+3);
      #printf("estimate 1: %.2f %.2f %.2f\n", pos(1), pos(2), pos(3)); 
      pos3D = to3D(pos, ratio);
      #printf("estimate 2: %.2f %.2f %.2f\n", pos3D(1), pos3D(2), pos3D(3)); 
      M(f,(j-1)*3+1:(j-1)*3+3) = pos3D;
    endfor
  endfor          
  
  numFrames = size(M, 1);
  windowSize = numFrames;

  numJointsXYZ = size(M, 2); # 51 = numJoints * 3
  b = linspace(1, windowSize, floor(numFrames/smoothFactor));
  x = 1:windowSize;
  
  
  SM = zeros(size(M));
  for j=1:size(M,2)
    y = M(1:windowSize, j);
    sp = spline(b,y(:)'/spline(b,eye(length(b)),x(:)'));
    xplot = x;
    yplot = ppval(sp,xplot);
    SM(1:windowSize, j) = yplot;
  endfor
  
  csvwrite(outputFile, SM);
  
  % Visualize last trajectory as a quick test
  spb = ppval(sp,b);
  plot(1:windowSize, M(1:windowSize,j), 'g', xplot,yplot,'b',x,y,'ro',b,spb,'ks');
  legend('Spline','Data','Breakpoints','Location','SouthWest');
  title(inputFile);

end


