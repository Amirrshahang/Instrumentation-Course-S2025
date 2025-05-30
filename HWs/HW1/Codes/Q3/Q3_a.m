clc
clear
close all

temperature = [0 10 20 30 40 50 60 70 80 90 100];
voltage_increasing = [0 0.4 0.8 1.3 2.1 2.7 3.2 3.6 3.8 4 4.1];
voltage_decreasing = [0 0.1 0.3 0.6 0.9 1.5 2 2.7 3.3 3.8 4.1];

temp = [temperature, flip(temperature)]; 
voltage = [voltage_increasing, flip(voltage_decreasing)];

[max_voltage, max_index] = max(voltage);
[min_voltage, min_index] = min(voltage);

max_temp = temp(max_index);
min_temp = temp(min_index);

line = polyfit([max_temp, min_temp], [max_voltage, min_voltage], 1);
line_fit = polyval(line, temp); 


figure(1);
plot(temp, voltage, 'b-', max_temp, max_voltage, 'ro', min_temp, min_voltage, 'go');
hold on;
plot(temp, line_fit, 'r-');
xlabel('Temperature (°C)');
ylabel('Displacement (m)');
legend('Hysteresis', 'Maximum Point', 'Minimum Point', 'Fitted Line','Location', 'northwest');
title('Hysteresis and Fitted Line');
xlim ([-5 105]) ;
ylim ([-0.3 5]) ;
grid on;
hold off;

temp_FS = max(temp) - min(temp);
voltage_FS = max(voltage) - min(voltage);

Maximum_output_distances = abs(line_fit - voltage);
max_output_hystersis = max(Maximum_output_distances) /voltage_FS;
disp('Maximum output hysteresis: %FS');
disp(max_output_hystersis * 100);



temperature_differences = zeros(size(voltage));

for i = 1:length(voltage)

    idx = find(abs(voltage - voltage(i)) == 0);
    
    if ~isempty(idx)
        temperature_differences(i) = abs(temp(i) - temp(idx(1)));
    end
end

max_temp_difference = max(temperature_differences)/ temp_FS;

disp('Maximum input hysteresis: %FS');
disp(max_temp_difference * 100);



hysteresis_error_percent = zeros(size(temperature));

for i = 1:length(temperature)
    hysteresis_error = abs(voltage_increasing(i) - voltage_decreasing(i));
    
    hysteresis_error_percent(i) = (hysteresis_error / voltage_FS) * 100;
end

figure;
plot(temperature, hysteresis_error_percent, 'k-o', 'LineWidth', 2);
xlabel('Temperature (°C)');
ylabel('Hysteresis Error (%)');
title('Hysteresis Error (%) at each Temperature');
grid on;

