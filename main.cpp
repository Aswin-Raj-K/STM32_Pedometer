#include "mbed.h"
#include "I3G4250D.h"

int main(){
  thread_sleep_for(1'000);
  I3G4250D gyroscope(PF_9, PF_8, PF_7, PC_1);
  gyroscope.initialize();
  // Variables to store gyroscope data
  float gx, gy, gz;
  float elapsedTime = 0; 
  float maxTime = 8;
  printf("Start:\n");
  thread_sleep_for(5'000);
  printf("Data:\n");

  while (maxTime > elapsedTime)
  {
    gyroscope.readGyroscopeData(gx, gy, gz);
    printf("gx: %4.5f \t gy: %4.5f \t gz: %4.5f\n",gx,gy,gz);
    thread_sleep_for(500);
    elapsedTime += 0.5;
  }
  printf("End:\n");
  return 0;
}