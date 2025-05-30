clc
clear
close all

X = [-1; 0; 1; 2; 3]; 
Y = [-2; 2; 4; 4; 2];

Phi = [X.^2, X, ones(size(X))];

A = (Phi' * Phi) \ (Phi' * Y);

a2 = A(1);
a1 = A(2);
a0 = A(3);

fprintf('a2 = %.3f\n', a2);
fprintf('a1 = %.4f\n', a1);
fprintf('a0 = %.4f\n', a0);
