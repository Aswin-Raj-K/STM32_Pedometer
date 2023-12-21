#include "mbed.h"
#include "I3G4250D.h"
#include "drivers/LCD_DISCO_F429ZI.h"

DigitalIn userButton(PA_0); // Using the Blue Button as user's Button
bool button_pressed = false; // Default as false

int main(){
  LCD_DISCO_F429ZI lcd;

  while (1) {
    if (userButton.read()) button_pressed = true;

    if (button_pressed) {
      thread_sleep_for(1'000);
      I3G4250D gyroscope(PF_9, PF_8, PF_7, PC_1);
      gyroscope.initialize();
      // Variables to store gyroscope data
      float gx, gy, gz;
      float elapsedTime = 0; 
      float maxTime = 8;
      printf("Start:\n");
      thread_sleep_for(2'000);
      printf("Data:\n");

      while (maxTime > elapsedTime)
      {
        gyroscope.readGyroscopeData(gx, gy, gz);
        // Buffer for the formatted string
        char display_buf_gx[80]; // Buffer for gx
        char display_buf_gy[80]; // Buffer for gy
        char display_buf_gz[80]; // Buffer for gz

        // Format the strings
        snprintf(display_buf_gx, sizeof(display_buf_gx), "gx: %4.5f", gx);
        snprintf(display_buf_gy, sizeof(display_buf_gy), "gy: %4.5f", gy);
        snprintf(display_buf_gz, sizeof(display_buf_gz), "gz: %4.5f", gz);

        // Display each string on a separate line
        lcd.DisplayStringAtLine(0, (uint8_t *)display_buf_gx);
        lcd.DisplayStringAtLine(1, (uint8_t *)display_buf_gy);
        lcd.DisplayStringAtLine(2, (uint8_t *)display_buf_gz);

        printf("gx: %4.5f \t gy: %4.5f \t gz: %4.5f\n",gx,gy,gz);
        thread_sleep_for(500);
        elapsedTime += 0.5;
      }
      printf("End:\n");
      // return 0;

      // Reset flag
      button_pressed = false;
    }
  }
}