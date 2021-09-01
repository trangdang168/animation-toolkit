load("p01/p01_INTRODUCTION/INTRODUCTION.mat");

for f=1:1713
  filename = sprintf('images/p01_INTRODUCTION/%d.png', f);
  I = imread(filename);
  imshow(I)
  hold on
  
  % joints = [spineBase, spineMid, neck, head, shoulderLeft, elbowLeft, ...
  %     wristLeft, handPalmLeft, shoulderRight, elbowRight, wristRight, ...
  %     handPalmRight, hipLeft, kneeLeft, ankleLeft, footLeft, hipRight, ...
  %     kneeRight, ankleRight, footRight, spineShoulder, handTipLeft, ...
  %     thumbLeft, handTipRight, thumbRight];
  
  x = [arr(f, 1),arr(f, 4),arr(f, 7),arr(f,10),arr(f,13),arr(f,16), ...
       arr(f,19),arr(f,22),arr(f,25),arr(f,28),arr(f,31),arr(f,34), ...
       arr(f,37),arr(f,40),arr(f,43),arr(f,46),arr(f,49),arr(f,52), ...
       arr(f,55),arr(f,58),arr(f,61),arr(f,64),arr(f,67),arr(f,70), ...
       arr(f,73)];
  y = [arr(f, 2),arr(f, 5),arr(f, 8),arr(f,11),arr(f,14),arr(f,17), ...
       arr(f,20),arr(f,23),arr(f,26),arr(f,29),arr(f,32),arr(f,35), ...
       arr(f,38),arr(f,41),arr(f,44),arr(f,47),arr(f,50),arr(f,53), ...
       arr(f,56),arr(f,59),arr(f,62),arr(f,65),arr(f,68),arr(f,71), ...
       arr(f,74)];
   
  x = x + ones(size(x))*25; 
  lowerSpine    = [x( 1),x( 2);y( 1),y( 2)];
  upperSpine    = [x( 2),x(21);y( 2),y(21)];
  neck          = [x(21),x( 3);y(21),y( 3)];
  head          = [x( 3),x( 4);y( 3),y( 4)];
  leftShoulder  = [x(21),x( 5);y(21),y( 5)];
  rightShoulder = [x(21),x( 9);y(21),y( 9)];
  leftBiceps    = [x( 5),x( 6);y( 5),y( 6)];
  rightBiceps   = [x( 9),x(10);y( 9),y(10)];
  leftForearm   = [x( 6),x( 7);y( 6),y( 7)];
  rightForearm  = [x(10),x(11);y(10),y(11)];
  Hand1Left     = [x( 7),x( 8);y( 7),y( 8)];
  Hand1Right    = [x(11),x(12);y(11),y(12)];
  hipLeft       = [x( 1),x(13);y( 1),y(13)];
  hipRight      = [x( 1),x(17);y( 1),y(17)];
  tightLeft     = [x(13),x(14);y(13),y(14)];
  tightRight    = [x(17),x(18);y(17),y(18)];
  chinLeft      = [x(14),x(15);y(14),y(15)];
  chinRight     = [x(18),x(19);y(18),y(19)];
  footLeft      = [x(15),x(16);y(15),y(16)];
  footRight     = [x(19),x(20);y(19),y(20)];
  Hand2Left     = [x( 7),x(22);y( 7),y(22)];
  Hand2Right    = [x(11),x(24);y(11),y(24)];
  Hand3Left     = [x( 7),x(23);y( 7),y(23)];
  Hand3Right    = [x(11),x(25);y(11),y(25)];
  
  scatter(x, y, 50, 'r', 'filled')
  
  plot(lowerSpine(1,:),lowerSpine(2,:),'b','LineWidth',2)
  plot(upperSpine(1,:),upperSpine(2,:),'b','LineWidth',2)
  plot(neck(1,:),neck(2,:),'b','LineWidth',2)
  plot(head(1,:),head(2,:),'b','LineWidth',2)
  plot(leftShoulder(1,:),leftShoulder(2,:),'g','LineWidth',2)
  plot(rightShoulder(1,:),rightShoulder(2,:),'r','LineWidth',2)
  plot(leftBiceps(1,:),leftBiceps(2,:),'g','LineWidth',2)
  plot(rightBiceps(1,:),rightBiceps(2,:),'r','LineWidth',2)
  plot(leftForearm(1,:),leftForearm(2,:),'g','LineWidth',2)
  plot(rightForearm(1,:),rightForearm(2,:),'r','LineWidth',2)
  plot(Hand1Left(1,:),Hand1Left(2,:),'g','LineWidth',2)
  plot(Hand1Right(1,:),Hand1Right(2,:),'r','LineWidth',2)
  plot(hipLeft(1,:),hipLeft(2,:),'b','LineWidth',2)
  plot(hipRight(1,:),hipRight(2,:),'b','LineWidth',2)
  plot(tightLeft(1,:),tightLeft(2,:),'b','LineWidth',2)
  plot(tightRight(1,:),tightRight(2,:),'b','LineWidth',2)
  % plot(chinLeft(1,:),chinLeft(2,:),'b','LineWidth',2)
  % plot(chinRight(1,:),chinRight(2,:),'b','LineWidth',2)
  % plot(footLeft(1,:),footLeft(2,:),'b','LineWidth',2)
  % plot(footRight(1,:),footRight(2,:),'b','LineWidth',2)
  plot(Hand2Left(1,:),Hand2Left(2,:),'b','LineWidth',2)
  plot(Hand2Right(1,:),Hand2Right(2,:),'b','LineWidth',2)
  plot(Hand3Left(1,:),Hand3Left(2,:),'b','LineWidth',2)
  plot(Hand3Right(1,:),Hand3Right(2,:),'b','LineWidth',2)
  
  outname = sprintf('brunopoints%d.png', f);
  saveas(gcf, outname);
  hold off
  pause(0.1);
endfor