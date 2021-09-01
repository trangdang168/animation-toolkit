%% Example for user specified Jacobian.
pkg load optim;

  %% independents
  x = [1:10:100]';
  %% observed data
  y =[9.2160e-001, 3.3170e-001, 8.9789e-002, 2.8480e-002, 2.6055e-002,...
     8.3641e-003,  4.2362e-003,  3.1693e-003,  1.4739e-004,  2.9406e-004]';
  %% initial values:
  p0=[0.8; 0.05];
  %% bounds
  lb=[0; 0]; ub=[];
  %% Jacobian setting
  opts = optimset ("Jacobian", "on")

  %% model function:
  function [F,J] = myfun (p, x, y)
    F = p(1) * exp (-p(2) * x) - y;
    if nargout > 1
      J = [exp(- p(2) * x), - p(1) * x .* exp(- p(2) * x)];
    endif
  endfunction

  [c, resnorm, residual, flag, output, lambda, jacob] = ...
      lsqnonlin(@(p) myfun(p, x, y), p0, lb,  ub, opts)
      
%% independents
x = [1,1]';
%% observed data
y =[0,1]';
%% initial values:
p0=[0];
%% bounds
lb=[-3.14]; ub=[3.14];
%% Jacobian setting
opts = optimset ("Jacobian", "off")

%% model function:
function [F] = myfun2 (p, y)
  pose = [cos(p(1)); sin(p(1))]; 
  F = norm(pose - y); 
endfunction

[c, resnorm, residual, flag, output, lambda, jacob] = ...
    lsqnonlin(@(p) myfun2(p, y), p0, lb,  ub, opts)
      
