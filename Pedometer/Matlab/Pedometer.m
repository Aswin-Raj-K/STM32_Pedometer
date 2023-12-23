% Specify the file name
filename = '..\Data\GyroData_230cm_FS0.1_ET5.txt';

% Open the file for reading
fileID = fopen(filename, 'r');

% Define the format for reading data
formatSpec = '%f, %f, %f';

% Read data from the file
data = textscan(fileID, formatSpec, 'CollectOutput', true);

% Close the file
fclose(fileID);

% Extract gyroscope data from the cell array
gyroData = data{1};
x_axis = gyroData(:,1);
y_axis = gyroData(:,2);
z_axis = gyroData(:,3);

timeInterval = 0.1;
% Initialize an empty vector to store the values
time = zeros(1, length(y_axis));

% Generate values using a for loop
for i = 1:(length(y_axis))
    time(i) = (i-1) * timeInterval;
end

data = zeros(1, length(y_axis));
for i = 1:(length(y_axis))
    data(i) = sqrt(x_axis(i)^2 + y_axis(i)^2 + z_axis(i)^2);
end

angularDisplacement = trapz(time, data);
radius = 0.5;%in m
linearDistance = angularDisplacement * radius;

disp('Linear Distance Covered:');
disp(linearDistance * 100);

