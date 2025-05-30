clc
clear
close all

kp = 50; tau = 30; P = 10;

t = linspace(0, 400, 1000);  

y = (kp * P) * (t / tau^2) .* exp(-t / tau);

[max_y, max_index] = max(y);
t_max = t(max_index);

fprintf('Maximum plasma insulin concentration: %.4f mU/L\n', max_y);
fprintf('Time of maximum concentration: %.4f minutes\n', t_max);

figure;
plot(t, y, 'k', 'LineWidth', 2); 
hold on;
xlabel('Time (minutes)');
ylabel('Insulin Concentration (mU/L)');
grid on;
