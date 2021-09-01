# Export Bruno MAT to 3D positions for viz in openGL
load("p01/p01_INTRODUCTION/INTRODUCTION.mat");

heightInches = 5 * 12 + 9; # participant one
height = heightInches * 0.0254; # convert to meters
torsoLength = (3/8.0) * height;

% Joint order in MAT file
% joints = [spineBase, spineMid, neck, head, shoulderLeft, elbowLeft, ...
%     wristLeft, handPalmLeft, shoulderRight, elbowRight, wristRight, ...
%     handPalmRight, hipLeft, kneeLeft, ankleLeft, footLeft, hipRight, ...
%     kneeRight, ankleRight, footRight, spineShoulder, handTipLeft, ...
%     thumbLeft, handTipRight, thumbRight];

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

# Estimate ratio from meters to screen pixels
rs = abs(spinePos(2) - headPos(2));
ratio = torsoLength / rs;

head3D = to3D(headPos, ratio);
printf("estimate 2: %.2f %.2f %.2f\n", head3D(1), head3D(2), head3D(3)); 

spine3D = to3D(spinePos, ratio);
printf("estimate 2: %.2f %.2f %.2f\n", spine3D(1), spine3D(2), spine3D(3)); 

norm(head3D - spine3D) 

M = zeros(size(arr,1), 3*size(joints,2));
for f=1:size(arr,1)
  for j=1:size(joints,2)
    jointId = joints(1,j)-1;
    pos = arr(f, jointId*3+1:jointId*3+3);
    printf("estimate 1: %.2f %.2f %.2f\n", pos(1), pos(2), pos(3)); 
    pos3D = to3D(pos, ratio);
    #printf("estimate 2: %.2f %.2f %.2f\n", pos3D(1), pos3D(2), pos3D(3)); 
    M(f,(j-1)*3+1:(j-1)*3+3) = pos3D;
  endfor
endfor

#csvwrite("p01/p01_INTRODUCTION/INTRODUCTION.txt", M);