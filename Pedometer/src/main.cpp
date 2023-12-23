#include "mbed.h"
#include "I3G4250D.h"
#include "LCD_DISCO_F429ZI.h"
#include "display.h"
#include "distance.h"
#include "settings.h"

int main() {
    // Initialize the LCD display
    LCD_DISCO_F429ZI lcd;

    // Display welcome screen and get the current line on the display
    int displayLine = displayWelcomeScreen(lcd, 1);

    // Initialize the gyroscope
    I3G4250D gyroscope(PF_9, PF_8, PF_7, PC_1);
    gyroscope.initialize();

    // Array to store gyroscope data (gx, gy, gz)
    float gyroscopeData[MAX_SAMPLES][3];

    // Print start message
    printf("Start:\n");

    // Pause for 2 seconds
    thread_sleep_for(1'000);


    printf("Reading Data\n");
    // ======================================================
    // Index to keep track of stored data points
    int dataIndex = 0;

    // Elapsed time
    float elapsedTime = 0;

    // Collect gyroscope data for a specified time duration
    while (MAX_TIME > elapsedTime) {
        gyroscope.readGyroscopeData(gyroscopeData[dataIndex][0], gyroscopeData[dataIndex][1], gyroscopeData[dataIndex][2]);
        thread_sleep_for(SAMPLE_TIME * 1000.0f);//Converting SAMPLE_TIME to milliseconds
        elapsedTime += SAMPLE_TIME;
        dataIndex++;
    }

    // Print end message
    printf("Reading Done\n");
    // ======================================================
    //Uncommment this to display the result in the terminal
    // for (int i = 0; i < dataIndex; i++) {
    //     printf("%4.5f, %4.5f, %4.5f\n",gyroscopeData[i][0], gyroscopeData[i][1], gyroscopeData[i][2]);
    // }

    // ======================================================
    // Calculate linear displacement using collected gyroscope data
    float distance = calculateLinearDistance(gyroscopeData, MAX_TIME, SAMPLE_TIME, RADIUS); // function returns the covered distance in m
    printf("Linear Displacement: %.4f\n", distance * 100.0f);//Printing the distance in cm
    // ======================================================

    // Displaying the end prompt on the LCD
    displayPrompt(lcd, displayLine + 2);

    // Initialize a digital input for a user button for changing the result unit
    DigitalIn userButton(PA_0);

    // Set the default unit to centimeters
    Result_Unit unit = CM;

    // Display the result initially in centimeters
    displayResult(lcd, displayLine, distance * 100.0f, CM);


    // ======================================================
    // Continuous loop for user interaction
    while (1) {
        // Check if the user button is pressed
        if (userButton.read()) {
            // Toggle between centimeters and meters
            if (unit == CM) {
                displayResult(lcd, displayLine, distance, M);
                unit = M;
            } else {
                displayResult(lcd, displayLine, distance * 100.0f, CM);
                unit = CM;
            }

            // Pause for 250 milliseconds to avoid rapid toggling
            thread_sleep_for(250);
        }
    }
    // ======================================================


    // This point is never reached in this code as the loop runs indefinitely
    // On pressing the reset button (black button on the board) the program repeats
    return 0;
}
