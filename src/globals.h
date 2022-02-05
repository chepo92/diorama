#include "Arduino.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <SPI.h>
#include <FreeStack.h>

// Add the SdFat Libraries
#include <SdFat.h>

// and the MP3 Shield Library
#include <vs1053_SdFat.h>

#ifndef GLOBALS_H
  #define GLOBALS_H

#if !defined(DISABLE_SD_MP3)  
    SdFat sd;
    vs1053 MP3player;
#endif

// default address 0x40
// PCA 1 controls LEDS
Adafruit_PWMServoDriver PCA1 = Adafruit_PWMServoDriver(0x40);

// PCA 2 Controls servos
Adafruit_PWMServoDriver PCA2 = Adafruit_PWMServoDriver(0x41);


// Pins
const int buttonPin = 5; // the number of the pushbutton pin

byte pin_light_1 = 4 ;  
byte pin_light_2 = 5;  
byte pin_light_3 = 6 ;  
byte pin_light_4 = 7 ;  
byte pin_light_5 = 12 ;  

#define PCA1_PIN_LEDS_E1 8
#define PCA1_PIN_LEDS_M1 9

#define PCA1_PIN_LEDS_E2 10
#define PCA1_PIN_LEDS_M2 11

#define PCA2_PIN_SERVO_1  8
#define PCA2_PIN_SERVO_2  9

byte PCA2_pin_servo_1 = 8 ;
byte PCA2_pin_servo_2 = 9 ;
byte PCA2_pin_servo_3 = 10 ;
byte PCA2_pin_servo_4 = 11 ;


#define NUMBER_OF_STEPS_PER_REV 512


// Button debounce
// constants won't change. They're used here to set pin numbers:

// Variables will change:
int run_state = false; // the current state of the output

int prev_play_state = false;
long start_play_time = 0;

int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

int servo_current_position_1 = 0;
int servo_current_position_2 = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

/* State machine */


boolean light1_state;
boolean light2_state;
boolean light3_state;
boolean light4_state;
boolean light5_state;

boolean manual_led_state_1;
boolean manual_led_state_2;
boolean manual_led_state_3;
boolean manual_led_state_4;
boolean manual_led_state_5;

boolean stepper_state;
boolean stepper_running;
boolean stepper_direction;
boolean stepper_stop_flag ; 

boolean servo_state_1;
boolean servo_state_2;

boolean servo_angle_active_1;
boolean servo_angle_active_2;

int stepper_time_index;

int light1_time_cycle_index;
int light2_time_cycle_index;
int light3_time_cycle_index;
int light4_time_cycle_index;
int light5_time_cycle_index;

int servo_move_index_1;
int servo_move_index_2;

int ramp_time_counter_1;
int ramp_time_counter_2;
int ramp_time_counter_3;
int ramp_time_counter_4;
int ramp_time_counter_5;

int seconds_display ;  // millis to sec
int last_timer_print ; 

boolean relay_commands =  true ; 

#endif