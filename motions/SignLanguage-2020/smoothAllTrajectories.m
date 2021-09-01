% To run this file, first set the workspace directory to 
%     <path>/motions/SignLanguage-2020

smoothFactor = 2; % smaller -> more detail; larger -> less
smoothSplineTrajectories(smoothFactor, ...
   'p01/p01_INTRODUCTION/INTRODUCTION.mat', ...
   'p01/p01_INTRODUCTION/INTRODUCTION_Smooth.txt');