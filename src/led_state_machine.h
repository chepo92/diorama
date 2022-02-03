#include <led_control.h>
#include "globals.h"
#include <config.h>


#ifndef LED_STATE_MACHINE_H
  #define LED_STATE_MACHINE_H


void checkTurnOn1(long elapsed)
{

  // light 1
  if (run_state && !light1_state && (light1_time_cycle_index < light1_cycle_lenght) &&
      ((elapsed > light1_start_array[light1_time_cycle_index]) &&
       (elapsed < light1_stop_array[light1_time_cycle_index])))
  {
    // led on
    // turn_on_led();
    fade_in_led_1 = true;
    if (fade_in_led_1)
      pwm_ramp_1 = 0;
    Serial.println(F("Led 1 Do ramp"));
    light1_state = true;
  }
}

void checkTurnOn2(long elapsed)
{

  // On light 2
  if (run_state && !light2_state && light2_time_cycle_index < light2_cycle_lenght &&
      ((elapsed > light2_start_array[light2_time_cycle_index]) &&
       (elapsed < light2_stop_array[light2_time_cycle_index])))
  {
    // led on
    // turn_on_led_n(2);
    fade_in_led_2 = true;
    if (fade_in_led_2)
      pwm_ramp_2 = 0;
    Serial.println(F("Led 2 Do Ramp"));
    light2_state = true;
  }
}


void checkTurnOn3(long elapsed)
{

  // On light 3
  if (run_state && !light3_state && light3_time_cycle_index < light3_cycle_lenght &&
      ((elapsed > light3_start_array[light3_time_cycle_index]) &&
       (elapsed < light3_stop_array[light3_time_cycle_index])))
  {
    // led on
    // turn_on_led_n(3);
    fade_in_led_3 = true;
    if (fade_in_led_3)
      pwm_ramp_3 = 0;
    Serial.println(F("Led 3 Do Ramp"));
    light3_state = true;
  }
}

void checkTurnOn4(long elapsed)
{

  // On light 4
  if (run_state && !light4_state && light4_time_cycle_index < light4_cycle_lenght &&
      ((elapsed > light4_start_array[light4_time_cycle_index]) &&
       (elapsed < light4_stop_array[light4_time_cycle_index])))
  {
    // led on
    // turn_on_led_n(4);
    fade_in_led_4 = true;
    if (fade_in_led_4)
      pwm_ramp_4 = 0;
    Serial.println(F("Led 4 Do Ramp"));
    light4_state = true;
  }
}

void checkTurnOn5(long elapsed)
{

  // On light 5
  if (run_state && !light5_state && light5_time_cycle_index < light5_cycle_lenght &&
      ((elapsed > light5_start_array[light5_time_cycle_index]) &&
       (elapsed < light5_stop_array[light5_time_cycle_index])))
  {
    // led on
    // turn_on_led_n(5);
    fade_in_led_5 = true;
    if (fade_in_led_5)
      pwm_ramp_5 = 0;
    Serial.println(F("Led 5 Do Ramp"));
    light5_state = true;
  }
}


void checkTurnOff1(long elapsed)
{
  // stop light 1
  if ((run_state) && light1_state && (elapsed > light1_stop_array[light1_time_cycle_index]) || (!run_state && light1_state))
  {
    // Do stop
    // turn_off_led();
    Serial.println(F("Led 1 fade out"));
    light1_time_cycle_index++;
    fade_in_led_1 = false;
    fade_out_led_1 = true;
    if (fade_out_led_1)
      pwm_ramp_1 = 2048;
    light1_state = false;
  }
}

void checkTurnOff2(long elapsed)
{

  // stop light 2
  if (run_state && light2_state && (elapsed > light2_stop_array[light2_time_cycle_index]) || (!run_state && light2_state))
  {
    // Do stop
    // turn_off_led_n(2);
    fade_in_led_2 = false;
    Serial.println(F("Led 2 fade out"));
    light2_time_cycle_index++;
    light2_state = false;
    fade_out_led_2 = true;
    if (fade_out_led_2)
      pwm_ramp_2 = 2048;
  }
}

void checkTurnOff3(long elapsed)
{

  // stop light 3
  if (run_state && light3_state && (elapsed > light3_stop_array[light3_time_cycle_index]) || (!run_state && light3_state))
  {
    // Do stop
    // turn_off_led_n(3);
    fade_in_led_3 = false;
    Serial.println(F("Led 3 fade out"));
    light3_time_cycle_index++;
    light3_state = false;
    fade_out_led_3 = true;
    if (fade_out_led_3)
      pwm_ramp_3 = 2048;
  }
}

void checkTurnOff4(long elapsed)
{

  // stop light 4
  if (run_state && light4_state && (elapsed > light4_stop_array[light4_time_cycle_index]) || (!run_state && light4_state))
  {
    // Do stop
    // turn_off_led_n(4);
    fade_in_led_4 = false;
    Serial.println(F("Led 4 fade out"));
    light4_time_cycle_index++;
    light4_state = false;
    fade_out_led_4 = true;
    if (fade_out_led_4)
      pwm_ramp_4 = 2048;
  }
}

void checkTurnOff5(long elapsed)
{

  // stop light 5
  if (run_state && light5_state && (elapsed > light5_stop_array[light5_time_cycle_index]) || (!run_state && light5_state))
  {
    // Do stop
    // turn_off_led_n(5);
    fade_in_led_5 = false;
    Serial.println(F("Led 5 fade out"));
    light5_time_cycle_index++;
    light5_state = false;
    fade_out_led_5 = true;
    if (fade_out_led_5)
      pwm_ramp_5 = 2048;
  }
}

void fadeIn1()
{
  // Fade in
  if (fade_in_led_1)
  {
    if (pwm_ramp_1 > 2048)
    {
      pwm_ramp_1 = 0;
      turn_on_led();
      fade_in_led_1 = false;
      Serial.println(F("Led Full ON after ramp"));
    }
    else
    {
      ramp_led(pwm_ramp_1);
      ramp_time_counter++;
      if (ramp_time_counter > ramp_time_divisor)
      {
        pwm_ramp_1++;
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
  if (fade_in_led_2)
  {
    if (pwm_ramp_2 > 2048)
    {
      pwm_ramp_2 = 0;
      turn_on_led_n(2);
      fade_in_led_2 = false;
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
    if (pwm_ramp_1 < 0)
    {
      pwm_ramp_1 = 2048;
      turn_off_led();
      light1_state = false;
      fade_out_led_1 = false;
      Serial.println(F("Led 1 Full Off after fade out"));
    }
    else
    {
      ramp_led(pwm_ramp_1);
      ramp_time_counter++;
      if (ramp_time_counter > ramp_time_divisor)
      {
        pwm_ramp_1--;
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
void reset_light_indexes()
{
    light1_time_cycle_index = 0;
    light2_time_cycle_index = 0;
    light3_time_cycle_index = 0;
    light4_time_cycle_index = 0;
    light5_time_cycle_index = 0;
}
 


#endif