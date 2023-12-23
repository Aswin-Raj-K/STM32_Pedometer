# Embedded Systems Final Project

**Authors:**
- Aswin Raj K (ar7997)
- Tony Yin (zy2734)
- Yuye Li (yl12032)

**Note:** Zoom in to see the plots clearly

---

## Introduction

We successfully designed a Pedometer using the STM32F429I Freedom board. The core of the project relies on harnessing data from the onboard I3G4250D gyrometer. This gyrometer provides crucial information about angular velocity, which forms the basis for calculating the distance walked.

The STM32F429I Freedom board, known for its versatility and capabilities, serves as an excellent platform for this project. Leveraging the data from the gyrometer, the Pedometer converts angular velocity into linear distance. This conversion process is a crucial step in accurately measuring the distance covered during a walk.

One of the key features of this Pedometer project is its output display. The calculated distance is prominently showcased on the onboard LCD screen.

In summary, the Pedometer project involves:

1. **Hardware:** Utilizing the STM32F429I Freedom board and tapping into the capabilities of the I3G4250D gyrometer.
2. **Data Processing:** Converting angular velocity data from the gyrometer into linear distance, enabling precise measurements of the distance walked.
3. **User Interface:** Displaying the calculated distance on the onboard LCD screen, ensuring a user-friendly and informative interaction.

Additionally, the sensor is strategically placed just above the knee to accurately measure the angular velocity. This placement enhances the precision of the Pedometer by capturing the leg's motion effectively.

## Features

- Calculates distance walked.
- Displays settings on the LCD.
- Shows the covered distance on the LCD.
- The black switch can be used to initiate a new measurement.
- The blue switch can toggle the measured distance unit between centimeters and meters displayed on the LCD.

## Methodology

The angular velocity from the sensor along the three axes is combined into its resultant value using the formula,

\[ \omega = \sqrt{\omega_x^2 + \omega_y^2 + \omega_z^2} \]

Subsequently, the resultant angular velocity (\(\omega\)) is integrated over time using trapezoidal integration to derive the angular distance moved. The trapezoidal integration formula is expressed as follows,

\[ \text{{Angular Distance}} = \sum_{n=1}^{N} \frac{1}{2} \left(\omega_{n-1} + \omega_{n}\right) \Delta t \]

where \(N\) is the total number of samples, and \(\Delta t\) represents the time step.

The obtained angular distance is then multiplied by the radius of rotation (the distance from the point of rotation to where the sensor is placed on the leg) to calculate the total distance covered.

\[ \text{{Linear Distance}} = \text{{Radius}} \times \text{{Angular Distance}} \]

## Project Details

### Folder Hierarchy

The project hierarchy is illustrated in Figure 1.

![Project Folder Structure](Figures/ProjectHeirarchy.png)

The structure includes the following components:

- **I3G4250D.cpp** and **I3G4250D.h**: Libraries for the sensor, developed by us.
- **display.cpp** and **display.h**: Contains functions for the display, implemented by us.
- **distance.cpp** and **distance.h**: Holds functions responsible for converting angular velocity to linear distance, created by us.
- **settings.h**: Contains settings for the Pedometer, including parameters such as radius, maxTime, and Sampling time.

### Usage

1. **Download and Setup:**
    - Download the provided zip file.
    - Unzip the file and import the folder into the PlatformIO (PIO) platform in Visual Studio Code (VSCode).

2. **Initiate Measurement:**
    - Locate the blue lever (PA\_0) as the user input button.
    - Press down the black lever when you are ready to start measuring.

3. **Application Start:**
    - After pressing the blue lever, the entire application will initiate within a few seconds.
    - Look for the appearance of the word "start"; this indicates that the measurement has begun.

4. **Data Display:**
    - Current measurement data will be displayed on the LCD screen.
    - The complete history of data will be printed on the computer.

5. **Measurement End:**
    - When the word "end" appears, it signifies the end of the measurement.
    - The total distance walked will be displayed.
    - Use the blue button to toggle the distance unit (cm/m).
    - Press the block button to start again.

## Results

For testing the design, the sensor was placed inside the pocket of pants just above the knee. A walking distance of 800cm, 450cm, and 290cm was covered, and the results were observed on the LCD screen. The procedure is demonstrated in the attached video, the link to which is provided at the end of this report.

The results are summarized in Table 1:

| Actual Distance (cm) | Measured Distance (by Sensor) (cm) |
|-----------------------|------------------------------------|
| 800                   | 784                                |
| 450                   | 412                                |
| 290                   | 276                                |

There is a slight error in the measured distance, which can be attributed to various factors such as sensor calibration, environmental conditions, or the placement of the sensor on the leg. Calibration adjustments and further testing may be conducted to enhance the accuracy of the measurements. These results provide valuable insights for potential refinements in the design and calibration process. Sample LCD display screen is as shown in figure 2.

![Sample LCD Screen display after measurement](Figures/lcdDisplay.jpg)

## Conclusion

In conclusion, the Pedometer project successfully demonstrates the integration of hardware components, data processing, and user interface design. The use of the STM32F429I Freedom board, coupled with the I3G4250D gyrometer, showcases a robust solution for roughly measuring the distance walked. The real-time display on the LCD screen enhances user interaction and provides immediate feedback.

Despite a slight discrepancy in the measured distance, the project lays the groundwork for further refinement. This discrepancy may be addressed through continuous calibration, environmental considerations, or adjustments in sensor placement. The insights gained from this project offer valuable lessons for the improvement of future iterations.

## Future Work

Future work on the Pedometer project could explore the following areas for enhancement:

1. **Calibration Optimization:** Further refine the calibration process to minimize measurement errors and improve accuracy.

2. **Environmental Adaptability:** Investigate ways to make the Pedometer more adaptable to varying environmental conditions, ensuring reliable performance in different scenarios.

3. **Sensor Placement Studies:** Conduct additional studies to optimize the placement of the sensor on the leg, considering factors such as motion dynamics and comfort.

4. **Enhanced User Interface:** Explore additional features for the user interface, providing more comprehensive feedback and options for users.

5. **Wireless Connectivity:** Integrate wireless communication capabilities for data transfer and remote monitoring, enhancing the overall functionality of the Pedometer.

6. **Power Efficiency:** Investigate methods to optimize power consumption, extending the device's battery life for prolonged usage.

Addressing these aspects can contribute to the development of an advanced and reliable Pedometer, making it a valuable tool for fitness tracking and motion analysis.

## Resources

1. [Project Repository](https://github.com/Aswin-Raj-K/STM32_Pedometer.git)
2. [Demo Video](https://www.youtube.com/watch?v=eO7r8S1gkYs)

---

<div align="center">
    <hr/>
    <p>End of README</p>
    <hr/>
</div>
