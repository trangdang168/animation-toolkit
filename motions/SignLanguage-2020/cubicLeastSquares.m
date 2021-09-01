qb = 0:20;
M = eye(length(b));
xplot = linspace(b(1),b(end));
phi5 = spline(b,M(5,:),xplot);
plot(xplot,phi5,b,0,'ro')

b = linspace(0,2*pi,5);
x = linspace(0,2*pi,20);
y = cos(x) + 0.2*randn(size(x));
sp = spline(b,y(:)'/spline(b,eye(length(b)),x(:)'));
xplot = linspace(0,2*pi);
yplot = ppval(sp,xplot);
spb = ppval(sp,b);
plot(xplot,yplot,'b',x,y,'ro',b,spb,'ks');
legend('Spline','Data','Breakpoints','Location','SouthWest');
axis([-1 7 -1.5 1.5]);

