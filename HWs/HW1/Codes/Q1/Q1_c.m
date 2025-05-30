clc; 
clear;
close all;

X = [-1; 0; 1; 2; 3]; 
Y = [-2; 2; 4; 4; 2];

Phi = [X.^2, X, ones(size(X))];

Teta_m = zeros(3,1);

alpha = 1;
P = (10^alpha) * eye(3);

for i = 1:length(Y)
    phi_n = Phi(i, :)';
    y_n = Y(i);
    
    e_m = y_n - phi_n' * Teta_m;
    
    K_m = (P * phi_n) / (1 + phi_n' * P * phi_n);
    
    Teta_m = Teta_m + K_m * e_m;
    
    P = P - (K_m * phi_n') * P;
end
fprintf('alpha = %.f\n', alpha(1));
fprintf('a2 = %.4f\n', Teta_m(1));
fprintf('a1 = %.4f\n', Teta_m(2));
fprintf('a0 = %.4f\n', Teta_m(3));



X = [-1; 0; 1; 2; 3]; 
Y = [-2; 2; 4; 4; 2];

Phi = [X.^2, X, ones(size(X))];

Teta_m = zeros(3,1);

alpha = 2;
P = (10^alpha) * eye(3);

for i = 1:length(Y)
    phi_n = Phi(i, :)';
    y_n = Y(i);
    
    e_m = y_n - phi_n' * Teta_m;
    
    K_m = (P * phi_n) / (1 + phi_n' * P * phi_n);
    
    Teta_m = Teta_m + K_m * e_m;
    
    P = P - (K_m * phi_n') * P;
end
fprintf('\n \n alpha = %.f\n', alpha(1));
fprintf('a2 = %.4f\n', Teta_m(1));
fprintf('a1 = %.4f\n', Teta_m(2));
fprintf('a0 = %.4f\n', Teta_m(3));




X = [-1; 0; 1; 2; 3]; 
Y = [-2; 2; 4; 4; 2];

Phi = [X.^2, X, ones(size(X))];

Teta_m = zeros(3,1);

alpha = 5;
P = (10^alpha) * eye(3);

for i = 1:length(Y)
    phi_n = Phi(i, :)';
    y_n = Y(i);
    
    e_m = y_n - phi_n' * Teta_m;
    
    K_m = (P * phi_n) / (1 + phi_n' * P * phi_n);
    
    Teta_m = Teta_m + K_m * e_m;
    
    P = P - (K_m * phi_n') * P;
end
fprintf('\n \n alpha = %.f\n', alpha(1));
fprintf('a2 = %.4f\n', Teta_m(1));
fprintf('a1 = %.4f\n', Teta_m(2));
fprintf('a0 = %.4f\n', Teta_m(3));