
#include "Arduino.h"

#ifndef STEPPER_LITE_MACHINE_H
  #define STEPPER_LITE_MACHINE_H

// Pins
byte stepper1_pin_A = 8 ;
byte stepper1_pin_B = 9 ;
byte stepper1_pin_C = 10 ;
byte stepper1_pin_D = 11 ;

#define STEPPER1_PIN_A 8
#define STEPPER1_PIN_B 9
#define STEPPER1_PIN_C 10
#define STEPPER1_PIN_D 11

#define STEPPER1_PIN_A 8
#define STEPPER1_PIN_B 9
#define STEPPER1_PIN_C 10
#define STEPPER1_PIN_D 11

#define STEPPER2_PIN_A 40
#define STEPPER2_PIN_B 42
#define STEPPER2_PIN_C 44
#define STEPPER2_PIN_D 46

/* Functions */

int stepCounter_1 = 0;
int stepCounter_2 = 0;

void writeStep_1(int a, int b, int c, int d)
{
  digitalWrite(STEPPER1_PIN_A, a);
  digitalWrite(STEPPER1_PIN_B, b);
  digitalWrite(STEPPER1_PIN_C, c);
  digitalWrite(STEPPER1_PIN_D, d);
}

void writeStep_2(int a, int b, int c, int d)
{
  digitalWrite(STEPPER2_PIN_A, a);
  digitalWrite(STEPPER2_PIN_B, b);
  digitalWrite(STEPPER2_PIN_C, c);
  digitalWrite(STEPPER2_PIN_D, d);
}

void stepperOff_1()
{
  writeStep_1(0, 0, 0, 0);
}

void stepperOff_2()
{
  writeStep_2(0, 0, 0, 0);
}

void oneCycleCW() // ~ 8 steps?
{
  byte stepdelay = 8 ;
  writeStep_1(1, 0, 0, 0);
  delay(stepdelay);
  writeStep_1(1, 1, 0, 0);
  delay(stepdelay);
  writeStep_1(0, 1, 0, 0);
  delay(stepdelay);
  writeStep_1(0, 1, 1, 0);
  delay(stepdelay);
  writeStep_1(0, 0, 1, 0);
  delay(stepdelay);
  writeStep_1(0, 0, 1, 1);
  delay(stepdelay);
  writeStep_1(0, 0, 0, 1);
  delay(stepdelay);
  writeStep_1(1, 0, 0, 1);
  delay(stepdelay);
}

void oneCycleCCW() // ~ 8 steps?
{
  byte stepdelay = 8 ;
  writeStep_1(1, 0, 0, 1);
  delay(stepdelay);
  writeStep_1(0, 0, 0, 1);
  delay(stepdelay);
  writeStep_1(0, 0, 1, 1);
  delay(stepdelay);
  writeStep_1(0, 0, 1, 0);
  delay(stepdelay);
  writeStep_1(0, 1, 1, 0);
  delay(stepdelay);
  writeStep_1(0, 1, 0, 0);
  delay(stepdelay);
  writeStep_1(1, 1, 0, 0);
  delay(stepdelay);
  writeStep_1(1, 0, 0, 0);
  delay(stepdelay);
}

/**
 * @brief 
 * 
 * @param step 0-7
 */
void asyncStep_1 (int step) {
switch (step)
{
case 0:
  /* code */
  writeStep_1(1, 0, 0, 0);
  break;
case 1:
  /* code */
  writeStep_1(1, 1, 0, 0);
  break;
case 2:
  /* code */
  writeStep_1(0, 1, 0, 0);

  break;
case 3:
  /* code */
  writeStep_1(0, 1, 1, 0);

  break;
case 4:
  /* code */
  writeStep_1(0, 0, 1, 0);

  break;
case 5:
  /* code */
  writeStep_1(0, 0, 1, 1);

  break;
case 6:
  /* code */
  writeStep_1(0, 0, 0, 1);

  break;
case 7:
  /* code */
  writeStep_1(1, 0, 0, 1);

  break;              
  
default:
  break;
}
  
}


/**
 * @brief 
 * 
 * @param step 0-7
 */
void asyncStep_2 (int step) {
switch (step)
{
case 0:
  /* code */
  writeStep_2(1, 0, 0, 0);
  break;
case 1:
  /* code */
  writeStep_2(1, 1, 0, 0);
  break;
case 2:
  /* code */
  writeStep_2(0, 1, 0, 0);

  break;
case 3:
  /* code */
  writeStep_2(0, 1, 1, 0);

  break;
case 4:
  /* code */
  writeStep_2(0, 0, 1, 0);

  break;
case 5:
  /* code */
  writeStep_2(0, 0, 1, 1);

  break;
case 6:
  /* code */
  writeStep_2(0, 0, 0, 1);

  break;
case 7:
  /* code */
  writeStep_2(1, 0, 0, 1);

  break;              
  
default:
  break;
}
  
}


#endif