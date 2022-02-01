
#include "Arduino.h"


// Pins

#define STEPPER_PIN_A A0
#define STEPPER_PIN_B A1
#define STEPPER_PIN_C A2
#define STEPPER_PIN_D A3

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
  writeStep(1, 0, 0, 0);
  delay(5);
  writeStep(1, 1, 0, 0);
  delay(5);
  writeStep(0, 1, 0, 0);
  delay(5);
  writeStep(0, 1, 1, 0);
  delay(5);
  writeStep(0, 0, 1, 0);
  delay(5);
  writeStep(0, 0, 1, 1);
  delay(5);
  writeStep(0, 0, 0, 1);
  delay(5);
  writeStep(1, 0, 0, 1);
  delay(5);
}

void oneCycleCCW() // ~ 8 steps?
{
  writeStep(1, 0, 0, 1);
  delay(5);
  writeStep(0, 0, 0, 1);
  delay(5);
  writeStep(0, 0, 1, 1);
  delay(5);
  writeStep(0, 0, 1, 0);
  delay(5);
  writeStep(0, 1, 1, 0);
  delay(5);
  writeStep(0, 1, 0, 0);
  delay(5);
  writeStep(1, 1, 0, 0);
  delay(5);
  writeStep(1, 0, 0, 0);
  delay(5);
}