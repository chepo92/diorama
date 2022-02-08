
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