#include <mbed.h>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include "gyrometer_data.h"

DigitalIn userButton(PA_0);   // Using the Blue Pump as user's Button
bool button_pressed = false;  // Default as false

int main()
{
  // gyroscope raw data
  Gyroscope_RawData raw_data;

  // distance record in meter
  float record = 0.0f;
  float sensitivity = 0.f;

  int16_t Z_Data_Array[100];
  float degreeBuf = 0.f;

  while (1) {
    printf("\rThe distance moved in past 20 seconds is %fm, hit user button to try again.",record);
    fflush(stdout);

    if(userButton.read()) button_pressed = 1;

    if (button_pressed) {
      float distanceBuf = 0.f;
      InitiateGyroscope(&raw_data, ODR_800_CUTOFF_110, ODR_800_HIGH_PASS_56, FULL_SCALE_500, &sensitivity);

      printf("\r\nMonitoring...\r\n");


      for(int i = 0; i < 100; ++i) {
        GetGyroValue(&raw_data);
        Z_Data_Array[i] = raw_data.z_raw;
        wait_us(200000);
        if(raw_data.z_raw > 0) {
          degreeBuf += raw_data.z_raw * 0.2 * sensitivity;
        } else {
          if(degreeBuf > 0) {
            distanceBuf += 2*(Distance_from_the_axis_of_rotation * sin(degreeBuf*M_PI/360));
            degreeBuf = 0;
          }
        }
        printf("Current distance moved: %f, current tangent velocity: %f.\n", distanceBuf, 
        raw_data.z_raw * sensitivity * DEGREE_TO_RAD * Distance_from_the_axis_of_rotation);
      }


    //   for(int i = 0; i < 40; ++i) { // 20 seconds / 0.5 seconds per sample = 40 samples
    //     GetGyroValue(&raw_data);
    //     wait_us(500000); // 0.5 second interval

    //     float angular_velocity = raw_data.z_raw * sensitivity * DEGREE_TO_RAD; // rad/s
    //     float linear_velocity = Distance_from_the_axis_of_rotation * angular_velocity; // m/s
    //     distanceBuf += linear_velocity * 0.5; // v*t, distance in meters

    //     printf("Current distance moved: %f, current linear velocity: %f.\n", distanceBuf, linear_velocity);
    // }


      record = distanceBuf;

      // reset flag
      button_pressed = false;

      // turn off gyroscope
      WriteByte(CTRL_REG_1, 0x00);
    }
  }
}