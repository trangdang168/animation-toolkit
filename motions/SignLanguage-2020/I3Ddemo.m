numFrames = 50; #1439;
halfwindowsize = 10; #100;
dt = 1/24;
for f=1:numFrames
  filename = sprintf('images/p01_INTRODUCTION/%d.png', f);

  if f <= halfwindowsize
    f1 = 1;
    f2 = halfwindowsize * 2;
  elseif f+halfwindowsize*2 >= numFrames
    f1 = numFrames-halfwindowsize*2;
    f2 = numFrames;data 
  else
    f1 = f-halfwindowsize;
    f2 = f+halfwindowsize;
  endif

  %subplot(2,1,1)
  %I = imread(filename);
  %imshow(I)

  subplot(2,1,2, "replace");
  hold on;
  title("sine");
  ylabel("units");
  plot(x(f1:f2), y(f1:f2));
  plot([f,f], [-max(y),max(y)], 'k');
  pos = get(gcf,'Position'); 
  set(gcf, 'Position', [pos(1),pos(2),pos(3),pos(3)/2]);
  pause(dt);
  hold off;
endfor


