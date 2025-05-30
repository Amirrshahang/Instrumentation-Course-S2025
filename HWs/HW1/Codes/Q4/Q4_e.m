clc
clear
close all

kp = 50;  P = 10; tau = 30; U_rate = 1; T_injection = 10;

t = linspace(0, 500, 10000);  
u = (t >= 0 & t <= T_injection) * U_rate;

y = zeros(size(t));
dt = t(2) - t(1);

for i = 2:length(t)
    dy = (kp / tau^3) * (trapz(t(1:i), u(1:i) .* exp(-(t(i) - t(1:i)) / tau))) * dt;
    y(i) = y(i-1) + dy;
end
y2 = (kp * P) * (t / tau^2) .* exp(-t / tau);

figure;
plot(t, y, 'b', 'LineWidth', 2);
hold on
plot(t, y2, 'k', 'LineWidth', 2); 
xlabel('Time (minutes)');
ylabel('Insulin Concentration (mU/L)');
grid on;
