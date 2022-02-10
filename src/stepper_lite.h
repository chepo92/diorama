
#include "Arduino.h"


// Pins
byte stepper_pin_A = 8 ;
byte stepper_pin_B = 9 ;
byte stepper_pin_C = 10 ;
byte stepper_pin_D = 11 ;

#define STEPPER_PIN_A 8
#define STEPPER_PIN_B 9
#define STEPPER_PIN_C 10
#define STEPPER_PIN_D 11

/* Functions */

int stepCounter = 0;

void writeStep(int a, int b, int c, int d)
{
  digitalWrite(STEPPER_PIN_A, a);
  digitalWrite(STEPPER_PIN_B, b);
  digitalWrite(STEPPER_PIN_C, c);
  digitalWrite(STEPPER_PIN_D, d);
}

void stepperOff()
{
  writeStep(0, 0, 0, 0);
}

void oneCycleCW() // ~ 8 steps?
{
  byte stepdelay = 8 ;
  writeStep(1, 0, 0, 0);
  delay(stepdelay);
  writeStep(1, 1, 0, 0);
  delay(stepdelay);
  writeStep(0, 1, 0, 0);
  delay(stepdelay);
  writeStep(0, 1, 1, 0);
  delay(stepdelay);
  writeStep(0, 0, 1, 0);
  delay(stepdelay);
  writeStep(0, 0, 1, 1);
  delay(stepdelay);
  writeStep(0, 0, 0, 1);
  delay(stepdelay);
  writeStep(1, 0, 0, 1);
  delay(stepdelay);
}

void oneCycleCCW() // ~ 8 steps?
{
  byte stepdelay = 8 ;
  writeStep(1, 0, 0, 1);
  delay(stepdelay);
  writeStep(0, 0, 0, 1);
  delay(stepdelay);
  writeStep(0, 0, 1, 1);
  delay(stepdelay);
  writeStep(0, 0, 1, 0);
  delay(stepdelay);
  writeStep(0, 1, 1, 0);
  delay(stepdelay);
  writeStep(0, 1, 0, 0);
  delay(stepdelay);
  writeStep(1, 1, 0, 0);
  delay(stepdelay);
  writeStep(1, 0, 0, 0);
  delay(stepdelay);
}

/**
 * @brief 
 * 
 * @param step 0-7
 */
void asyncStep (int step) {
switch (step)
{
case 0:
  /* code */
  writeStep(1, 0, 0, 0);
  break;
case 1:
  /* code */
  writeStep(1, 1, 0, 0);
  break;
case 2:
  /* code */
  writeStep(0, 1, 0, 0);

  break;
case 3:
  /* code */
  writeStep(0, 1, 1, 0);

  break;
case 4:
  /* code */
  writeStep(0, 0, 1, 0);

  break;
case 5:
  /* code */
  writeStep(0, 0, 1, 1);

  break;
case 6:
  /* code */
  writeStep(0, 0, 0, 1);

  break;
case 7:
  /* code */
  writeStep(1, 0, 0, 1);

  break;              
  
default:
  break;
}


  
}