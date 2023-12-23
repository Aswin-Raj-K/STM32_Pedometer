#ifndef PEDOMETER_DISPLAY
#define PEDOMETER_DISPLAY

// Enumeration to represent the result unit (centimeters or meters)
typedef enum {
    CM = 0,
    M = 1,
} Result_Unit;

// Function declarations for displaying information on the LCD
int displayWelcomeScreen(LCD_DISCO_F429ZI lcd, int line);
int displayResult(LCD_DISCO_F429ZI lcd, int line, float distance, Result_Unit state);
void printLine(LCD_DISCO_F429ZI lcd, int line);
int displayPrompt(LCD_DISCO_F429ZI lcd, int line);

#endif
