// #include "Arduino.h"
// #include "globals.h"
// #include "config.h"
// #include "servo_control.h"

#ifndef LED_CONTROL_H
  #define LED_CONTROL_H

  /* LED control */
  boolean do_ramp_led;
  boolean do_ramp_led_2;

  boolean fade_in_led_1;
  boolean fade_in_led_2;

  boolean fade_out_led_1;
  boolean fade_out_led_2;

  int pwm_ramp = 0;
  int pwm_ramp_2 = 0;

  void ramp_led(int current_ramp)
  {
    PCA1.setPWM(PCA_PIN_LEDS_E1, 0, current_ramp);
    PCA1.setPWM(PCA_PIN_LEDS_M1, current_ramp, 4095);
  }

  void ramp_led_2(int current_ramp)
  {
    PCA1.setPWM(PCA_PIN_LEDS_E2, 0, current_ramp);
    PCA1.setPWM(PCA_PIN_LEDS_M2, current_ramp, 4095);
  }

  void turn_on_led()
  {
    PCA1.setPWM(PCA_PIN_LEDS_E1, 0, 2045);
    PCA1.setPWM(PCA_PIN_LEDS_M1, 2045, 4090);
  }

  void turn_off_led()
  {
    PCA1.setPWM(PCA_PIN_LEDS_E1, 0, 0);
    PCA1.setPWM(PCA_PIN_LEDS_M1, 0, 0);
  }

  void turn_on_led_n(int ledIndx)
  {
    switch (ledIndx)
    {
    case 1:
      PCA1.setPWM(PCA_PIN_LEDS_E1, 0, 2045);
      PCA1.setPWM(PCA_PIN_LEDS_M1, 2045, 4095);
      break;
    case 2:
      PCA1.setPWM(PCA_PIN_LEDS_E2, 0, 2045);
      PCA1.setPWM(PCA_PIN_LEDS_M2, 2045, 4095);
      break;
    default:
      break;
    }
  }

  void turn_off_led_n(int ledIndx)
  {
    switch (ledIndx)
    {
    case 1:
      PCA1.setPWM(PCA_PIN_LEDS_E1, 0, 0);
      PCA1.setPWM(PCA_PIN_LEDS_M1, 0, 0);
      break;
    case 2:
      PCA1.setPWM(PCA_PIN_LEDS_E2, 0, 0);
      PCA1.setPWM(PCA_PIN_LEDS_M2, 0, 0);
      break;
    default:
      break;
    }
  }

  void reset_all()
  {
    turn_off_led();
    turn_off_led_n(2);
    set_servo_angle(PCA_PIN_SERVO_1, servo_default_angle);
    set_servo_angle(PCA_PIN_SERVO_2, servo_default_angle_2);
    servo_current_position = servo_default_angle;
    servo_current_position_2 = servo_default_angle_2;
  }

#endif