#include <servo_control.h>
#include "globals.h"
#include <config.h>


#ifndef SERVO_STATE_MACHINE_H
  #define SERVO_STATE_MACHINE_H

void checkServoStart_1(uint32_t elapsed_s) {
  // Servo 1
  if (run_state && !servo_state_1 && servo_move_index_1 < servo_move_count_1 && 
  ((elapsed_s > servo_start_array_1[servo_move_index_1]) && 
  (elapsed_s < servo_stop_array_1[servo_move_index_1])))
  {
    // Do move
    Serial.println("Servo 2 On");
    Serial.print("Move index: ");
    Serial.println(servo_move_index_1);    
    servo_state_1 = true;

  }

}




void checkServoStop_1(uint32_t elapsed_s) {
  // stop servo 1 move
  if (run_state && servo_state_1 && (elapsed_s > servo_stop_array_1[servo_move_index_1]))
  {
    // Do stop
    Serial.println("Servo 2 Off");
    servo_state_1 = false;
    set_servo_angle(PCA_PIN_SERVO_1, servo_default_angle_1);

    servo_move_index_1++;

  }

}

void checkServoStart_2(uint32_t elapsed_s) {
  // Servo 2 move
  if (run_state && !servo_state_2 && servo_move_index_2 < servo_move_count_2 && 
  ((elapsed_s > servo_start_array_2[servo_move_index_2]) && 
  (elapsed_s < servo_stop_array_2[servo_move_index_2])))
  {
    // Do move
    Serial.println("Servo 2 On");
    Serial.print("Move index: ");
    Serial.println(servo_move_index_2);
    servo_state_2 = true;

  }
}

void checkServoStop_2(uint32_t elapsed_s) {
  // stop servo 2 move
  if (run_state && servo_state_2 && (elapsed_s > servo_stop_array_2[servo_move_index_2]))
  {
    // Do stop
    Serial.println("Servo 2 Off");
    servo_state_2 = false;
    set_servo_angle(PCA_PIN_SERVO_2, servo_default_angle_2);

    servo_move_index_2++;
     
  }  
}


void checkServoStart_n(uint32_t elapsed_s) {

}

void checkServoStop_n(uint32_t elapsed_s) {

}


void updateServoPosition_1(uint32_t elapsed_s) {

 if (servo_angle_active_1 || servo_state_1)
  {
    switch (servo_move_type_1)
    {
    case 0:
      if (servo_move_index_1 < servo_move_count_1 &&
         ((elapsed_s > servo_start_array_1[servo_move_index_1]) && 
         (elapsed_s < servo_stop_array_1[servo_move_index_1])))
      {
        set_servo_angle(PCA_PIN_SERVO_1, max_servo_position_2);
        //Serial.println("Servo at max position");
      }
      else if (servo_move_index_1 < servo_move_count_1 && (elapsed_s > servo_stop_array_1[servo_move_index_1]))
      {
        set_servo_angle(PCA_PIN_SERVO_1, min_servo_position_1);
        //Serial.println("Servo at min position");
      }
      break;
    case 1:
      
      long elapsed_servo_update = millis() - last_servo_update_1;
      if (elapsed_servo_update > servo_update_period_1)
      {
        // Serial.print("Current servo position: ");
        // Serial.println((servo_current_position));         
        last_servo_update_1 = millis();
        set_servo_angle(PCA_PIN_SERVO_1, servo_current_position_1);
        servo_current_position_1 = servo_current_position_1 + servo_step;

        if (servo_current_position_1 <= min_servo_position_1)
        {
          servo_step = abs(servo_step);
        }
        if (servo_current_position_1 >= max_servo_position_2)
        {
          servo_step = -abs(servo_step);
        }
      }
      break;

    default:
      break;
    }
  }

}

void updateServoPosition_2(uint32_t elapsed_s) {

  if (servo_angle_active_2 || servo_state_2)
  {
    switch (servo_move_type_2)
    {
    case 0:
      if (servo_move_index_2 < servo_move_count_2 && 
        ((elapsed_s > servo_start_array_2[servo_move_index_2]) && 
          (elapsed_s < servo_stop_array_2[servo_move_index_2])))
      {
        set_servo_angle(PCA_PIN_SERVO_2, max_servo_position_2);
        //Serial.println("Servo at max position");
      }
      else if (servo_move_index_1 < servo_move_count_1 && (elapsed_s > servo_stop_array_2[servo_move_index_2]))
      {
        set_servo_angle(PCA_PIN_SERVO_2, min_servo_position_2);
        //Serial.println("Servo at min position");
      }
      break;
    case 1:
      
      long elapsed_servo_update = millis() - last_servo_update_2;
      if (elapsed_servo_update > servo_update_period_2)
      {
        // Serial.print("Current servo position: ");
        // Serial.println((servo_current_position));         
        last_servo_update_2 = millis();
        set_servo_angle(PCA_PIN_SERVO_2, servo_current_position_2);
        servo_current_position_2 = servo_current_position_2 + servo_step_2;

        if (servo_current_position_2 <= min_servo_position_2)
        {
          servo_step_2 = abs(servo_step_2);
        }
        if (servo_current_position_2 >= max_servo_position_2)
        {
          servo_step_2 = -abs(servo_step_2);
        }
      }
      break;

    default:
      break;
    }
  }  

}

void updateServoPosition_n(uint32_t elapsed_s) {

}

#endif