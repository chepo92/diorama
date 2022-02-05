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
    set_servo_angle(PCA2_PIN_SERVO_1, servo_default_angle_1);

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
    set_servo_angle(PCA2_PIN_SERVO_2, servo_default_angle_2);

    servo_move_index_2++;
     
  }  
}


void checkServoStart_3(uint32_t elapsed_s) {
  // Servo 3 move
  if (run_state && !servo_state_3 && servo_move_index_3 < servo_move_count_3 && 
  ((elapsed_s > servo_start_array_3[servo_move_index_3]) && 
  (elapsed_s < servo_stop_array_3[servo_move_index_3])))
  {
    // Do move
    Serial.println("Servo 3 On");
    Serial.print("Move index: ");
    Serial.println(servo_move_index_3);
    servo_state_3 = true;

  }
}

void checkServoStop_3(uint32_t elapsed_s) {
  // stop servo 3 move
  if (run_state && servo_state_3 && (elapsed_s > servo_stop_array_3[servo_move_index_3]))
  {
    // Do stop
    Serial.println("Servo 3 Off");
    servo_state_3 = false;
    set_servo_angle(PCA2_PIN_SERVO_3, servo_default_angle_3);

    servo_move_index_3++;
     
  }  
}


void checkServoStart_4(uint32_t elapsed_s) {
  // Servo 4 move
  if (run_state && !servo_state_4 && servo_move_index_4 < servo_move_count_4 && 
  ((elapsed_s > servo_start_array_4[servo_move_index_4]) && 
  (elapsed_s < servo_stop_array_4[servo_move_index_4])))
  {
    // Do move
    Serial.println("Servo 4 On");
    Serial.print("Move index: ");
    Serial.println(servo_move_index_4);
    servo_state_4 = true;

  }
}

void checkServoStop_4(uint32_t elapsed_s) {
  // stop servo 4 move
  if (run_state && servo_state_4 && (elapsed_s > servo_stop_array_4[servo_move_index_4]))
  {
    // Do stop
    Serial.println("Servo 4 Off");
    servo_state_4 = false;
    set_servo_angle(PCA2_PIN_SERVO_4, servo_default_angle_4);

    servo_move_index_4++;
     
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
        set_servo_angle(PCA2_PIN_SERVO_1, max_servo_position_2);
        //Serial.println("Servo at max position");
      }
      else if (servo_move_index_1 < servo_move_count_1 && (elapsed_s > servo_stop_array_1[servo_move_index_1]))
      {
        set_servo_angle(PCA2_PIN_SERVO_1, min_servo_position_1);
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

        Serial.println(servo_current_position_1) ;
        set_servo_us(PCA2_pin_servo_1, servo_current_position_1);
        //set_servo_angle(PCA2_PIN_SERVO_1, servo_current_position_1);
        servo_current_position_1 = servo_current_position_1 + servo_step;

        if (servo_current_position_1 <= min_servo_position_1)
        {
          servo_step = abs(servo_step);
        }
        if (servo_current_position_1 >= max_servo_position_1)
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
        set_servo_angle(PCA2_PIN_SERVO_2, max_servo_position_2);
        //Serial.println("Servo at max position");
      }
      else if (servo_move_index_2 < servo_move_count_2 && (elapsed_s > servo_stop_array_2[servo_move_index_2]))
      {
        set_servo_angle(PCA2_PIN_SERVO_2, min_servo_position_2);
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
        set_servo_us(PCA2_pin_servo_2, servo_current_position_2);
        //set_servo_angle(PCA2_PIN_SERVO_2, servo_current_position_2);
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



void updateServoPosition_3(uint32_t elapsed_s) {

  if (servo_angle_active_3 || servo_state_3)
  {
    switch (servo_move_type_3)
    {
    case 0:
      if (servo_move_index_3 < servo_move_count_3 && 
        ((elapsed_s > servo_start_array_3[servo_move_index_3]) && 
          (elapsed_s < servo_stop_array_3[servo_move_index_3])))
      {
        set_servo_angle(PCA2_PIN_SERVO_3, max_servo_position_3);
        //Serial.println("Servo at max position");
      }
      else if (servo_move_index_1 < servo_move_count_1 && (elapsed_s > servo_stop_array_3[servo_move_index_3]))
      {
        set_servo_angle(PCA2_pin_servo_3, min_servo_position_3);
        //Serial.println("Servo at min position");
      }
      break;
    case 1:
      
      long elapsed_servo_update = millis() - last_servo_update_3;
      if (elapsed_servo_update > servo_update_period_3)
      {
        // Serial.print("Current servo position: ");
        // Serial.println((servo_current_position));         
        last_servo_update_3 = millis();
        set_servo_us(PCA2_pin_servo_3, servo_current_position_3);
        //set_servo_angle(PCA3_PIN_SERVO_3, servo_current_position_3);
        servo_current_position_3 = servo_current_position_3 + servo_step_3;

        if (servo_current_position_3 <= min_servo_position_3)
        {
          servo_step_3 = abs(servo_step_3);
        }
        if (servo_current_position_3 >= max_servo_position_3)
        {
          servo_step_3 = -abs(servo_step_3);
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