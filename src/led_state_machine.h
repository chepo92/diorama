#include <led_control.h>
#include "globals.h"
#include <config.h>


#ifndef LED_STATE_MACHINE_H
  #define LED_STATE_MACHINE_H


void checkTurnOn1(long elapsed)
{

  // light 1
  if (run_state && !light1_state && (light1_time_index < light1_cycle_count) &&
      ((elapsed > light1_start_array[light1_time_index]) &&
       (elapsed < light1_stop_array[light1_time_index])))
  {
    // led on
    // turn_on_led();
    do_ramp_led_1 = true;
    if (do_ramp_led_1)
      pwm_ramp = 0;
    Serial.println(F("Led 1 Do ramp"));
    light1_state = true;
  }
}

void checkTurnOff1(long elapsed)
{
  // stop light 1
  if ((run_state) && light1_state && (elapsed > light1_stop_array[light1_time_index]) || (!run_state && light1_state))
  {
    // Do stop
    // turn_off_led();
    Serial.println(F("Led 1 fade out"));
    light1_time_index++;
    do_ramp_led_1 = false;
    fade_out_led_1 = true;
    if (fade_out_led_1)
      pwm_ramp = 2048;
    light1_state = false;
  }
}

void checkTurnOn2(long elapsed)
{

  // On light 2
  if (run_state && !light2_state && light2_time_index < light2_cycle_lenght &&
      ((elapsed > light2_start_array[light2_time_index]) &&
       (elapsed < light2_stop_array[light2_time_index])))
  {
    // led on
    // turn_on_led_n(2);
    do_ramp_led_2 = true;
    if (do_ramp_led_2)
      pwm_ramp_2 = 0;
    Serial.println(F("Led 2 Do Ramp"));
    light2_state = true;
  }
}

void checkTurnOff2(long elapsed)
{

  // stop light 2
  if (run_state && light2_state && (elapsed > light2_stop_array[light2_time_index]) || (!run_state && light2_state))
  {
    // Do stop
    // turn_off_led_n(2);
    do_ramp_led_2 = false;
    Serial.println(F("Led 2 fade out"));
    light2_time_index++;
    light2_state = false;
    fade_out_led_2 = true;
    if (fade_out_led_2)
      pwm_ramp_2 = 2048;
  }
}

void fadeIn1()
{
  // Fade in
  if (do_ramp_led_1)
  {
    if (pwm_ramp > 2048)
    {
      pwm_ramp = 0;
      turn_on_led();
      do_ramp_led_1 = false;
      Serial.println(F("Led Full ON after ramp"));
    }
    else
    {
      ramp_led(pwm_ramp);
      ramp_time_counter++;
      if (ramp_time_counter > ramp_time_divisor)
      {
        pwm_ramp++;
        ramp_time_counter = 0;
        // Serial.println(F("Ramp UP 1 "));
        // Serial.println(pwm_ramp);
      }
    }
  }
}
void fadeIn2()
{
  // Fade in
  if (do_ramp_led_2)
  {
    if (pwm_ramp_2 > 2048)
    {
      pwm_ramp_2 = 0;
      turn_on_led_n(2);
      do_ramp_led_2 = false;
      Serial.println(F("Led 2 Full ON after ramp"));
    }
    else
    {
      ramp_led_2(pwm_ramp_2);
      ramp_time_counter_2++;
      if (ramp_time_counter_2 > ramp_time_divisor)
      {
        pwm_ramp_2++;
        ramp_time_counter_2 = 0;
        // Serial.println(F("Ramp UP"));
      }
    }
  }
}
void fadeOut1()
{
  // Fade out
  if (fade_out_led_1)
  {
    if (pwm_ramp < 0)
    {
      pwm_ramp = 2048;
      turn_off_led();
      light1_state = false;
      fade_out_led_1 = false;
      Serial.println(F("Led 1 Full Off after fade out"));
    }
    else
    {
      ramp_led(pwm_ramp);
      ramp_time_counter++;
      if (ramp_time_counter > ramp_time_divisor)
      {
        pwm_ramp--;
        ramp_time_counter = 0;
      }
    }
  }
}
void fadeOut2()
{

  // Fade out
  if (fade_out_led_2)
  {
    if (pwm_ramp_2 < 0)
    {
      pwm_ramp_2 = 2048;
      turn_off_led_n(2);
      light2_state = false;
      fade_out_led_2 = false;
      Serial.println(F("Led 2 Full Off after fade out"));
    }
    else
    {
      ramp_led_2(pwm_ramp_2);
      ramp_time_counter_2++;
      if (ramp_time_counter_2 > ramp_time_divisor)
      {
        pwm_ramp_2--;
        ramp_time_counter_2 = 0;
      }
    }
  }
}

#endif