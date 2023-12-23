#include "LCD_DISCO_F429ZI.h"
#include "settings.h"
#include "display.h"

// Function to draw a horizontal line on the LCD screen
void printLine(LCD_DISCO_F429ZI lcd, int line) {
    BSP_LCD_DrawHLine(0, LINE(line), lcd.GetXSize());
}

// Function to display the welcome screen on the LCD
int displayWelcomeScreen(LCD_DISCO_F429ZI lcd, int line) {
    char display_buf[80];

    // Set font and display "Pedometer" at the center of the screen
    lcd.SetFont(&Font24);
    lcd.DisplayStringAt(0, LINE(line++), (uint8_t *)"Pedometer", CENTER_MODE);

    // Set font size and draw a horizontal line
    lcd.SetFont(&Font16);
    line++;
    printLine(lcd, line++);

    // Display information about radius, sampling time, and max time
    snprintf(display_buf, sizeof(display_buf), "Radius: %dcm", (int)(RADIUS * 100.0f));
    lcd.DisplayStringAtLine(line++, (uint8_t *)display_buf);

    snprintf(display_buf, sizeof(display_buf), "Sampling Time: %.2fs", SAMPLE_TIME);
    lcd.DisplayStringAtLine(line++, (uint8_t *)display_buf);

    snprintf(display_buf, sizeof(display_buf), "Max Time: %.2fs", MAX_TIME);
    lcd.DisplayStringAtLine(line++, (uint8_t *)display_buf);

    // Draw another horizontal line
    printLine(lcd, line++);

    // Return the updated line value
    return line;
}

// Function to display the result on the LCD
int displayResult(LCD_DISCO_F429ZI lcd, int line, float distance, Result_Unit state) {
    char display_buf[80];

    // Check the unit state and format the distance accordingly
    if (state == CM) {
        lcd.ClearStringLine(line);
        snprintf(display_buf, sizeof(display_buf), "Distance: %.2fcm", distance);
    } else {
        lcd.ClearStringLine(line);
        snprintf(display_buf, sizeof(display_buf), "Distance: %.4fm", distance);
    }

    // Display the formatted distance
    lcd.DisplayStringAtLine(line++, (uint8_t *)display_buf);

    // Draw another horizontal line
    printLine(lcd, line++);

    // Return the updated line value
    return line;
}

// Function to display a prompt on the LCD
int displayPrompt(LCD_DISCO_F429ZI lcd, int line) {
    char display_buf[80];

    // Display the prompt message
    snprintf(display_buf, sizeof(display_buf), "Press black button");
    lcd.DisplayStringAtLine(line++, (uint8_t *)display_buf);

    // Display a secondary prompt message
    snprintf(display_buf, sizeof(display_buf), "to measure again..");
    lcd.DisplayStringAtLine(line++, (uint8_t *)display_buf);

    // Return the updated line value
    return line;
}
