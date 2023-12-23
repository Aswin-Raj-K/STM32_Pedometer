#include "mbed.h"
#include "distance.h"

// Function to calculate linear distance based on gyroscope data
float calculateLinearDistance(const float gyroData[][3], float maxTime, float timeInterval, float radius) {
    // Print a message indicating the start of the calculation
    printf("Calculating Distance\n");

    // Calculate the size of the data array based on the time parameters
    int size = maxTime / timeInterval;

    // Array to store the calculated data values
    float data[100];

    // Calculate the magnitude of gyroscope data for each time step
    for (int32_t i = 0; i < size; ++i) {
        data[i] = std::sqrt(gyroData[i][0] * gyroData[i][0] + gyroData[i][1] * gyroData[i][1] + gyroData[i][2] * gyroData[i][2]);
    }

    // Calculate angular displacement using trapezoidal integration
    float angularDisplacement = 0.0;
    for (int i = 1; i < size; ++i) {
        angularDisplacement += 0.5 * (data[i - 1] + data[i]) * (timeInterval + 0.12);
    }

    // Print the calculated angular displacement
    printf("Angular Displacement: %.4f\n", angularDisplacement);

    // Calculate linear distance covered using the formula: linearDistance = angularDisplacement * radius
    float linearDistance = angularDisplacement * radius;

    // Print a message indicating the end of the calculation
    printf("Calculation Done\n");

    // Return the calculated linear distance
    return linearDistance;
}
