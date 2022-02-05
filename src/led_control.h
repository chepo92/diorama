// #include "Arduino.h"
// #include "globals.h"
// #include "config.h"
// #include "servo_control.h"

#ifndef LED_CONTROL_H
  #define LED_CONTROL_H

  /* LED control */
  // boolean do_ramp_led_1;
  // boolean do_ramp_led_2;


  boolean fade_in_led_1;
  boolean fade_in_led_2;
  boolean fade_in_led_3;
  boolean fade_in_led_4;
  boolean fade_in_led_5;

  boolean fade_out_led_1;
  boolean fade_out_led_2;
  boolean fade_out_led_3;
  boolean fade_out_led_4;
  boolean fade_out_led_5;

  int pwm_light_1 = 0;
  int pwm_light_2 = 0;
  int pwm_light_3 = 0;
  int pwm_light_4 = 0;
  int pwm_light_5 = 0;

  void ramp_led_1(int current_ramp)
  {
    PCA1.setPWM(PCA1_PIN_LEDS_E1, 0, current_ramp);
    PCA1.setPWM(PCA1_PIN_LEDS_M1, current_ramp, 4095);
  }

  void ramp_led_2(int current_ramp)
  {
    PCA1.setPWM(PCA1_PIN_LEDS_E2, 0, current_ramp);
    PCA1.setPWM(PCA1_PIN_LEDS_M2, current_ramp, 4095);
  }

  void apply_pwm_led_n(int pin, int current_ramp)
  {
    PCA1.setPWM(pin, 0, current_ramp);    
  }  

  void turn_on_led_1()
  {
    PCA1.setPWM(PCA1_PIN_LEDS_E1, 0, 2045);
    PCA1.setPWM(PCA1_PIN_LEDS_M1, 2045, 4090);
  }

  void turn_off_led_1()
  {
    PCA1.setPWM(PCA1_PIN_LEDS_E1, 0, 0);
    PCA1.setPWM(PCA1_PIN_LEDS_M1, 0, 0);
  }

  void turn_on_led_n(int ledPin)
  {
    PCA1.setPWM(ledPin, 0, 4095);
  }

  void turn_off_led_n(int ledPin)
  {
    PCA1.setPWM(ledPin, 0, 0);
  }



  void all_lights_off()
  {

     for(int i = 0 ; i < 16 ; i++) {
      turn_off_led_n(i);
    }
  }

  void all_lights_on()
  {

    for(int i = 0 ; i < 16 ; i++) {
      turn_on_led_n(i);
    }
 
  }


#endif