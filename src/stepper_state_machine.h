#include <stepper_lite.h>
#include "globals.h"
#include <config.h>


#ifndef STEPPER_STATE_MACHINE_H
  #define STEPPER_STATE_MACHINE_H

void checkStepperStart_1(uint32_t elapsed_s) {
  // Stepper move start
  if (run_state && !stepper1_state && stepper1_time_cycle_index < stepper1_cycle_count && 
    ((elapsed_s > stepper1_start_array[stepper1_time_cycle_index]) && 
    (elapsed_s < stepper1_stop_array[stepper1_time_cycle_index])))
  {
    stepper1_state = true;
    stepper1_running = true;
    stepper1_direction = stepper1_start_direction ; 
    // myStepper.step(stepsPerRevolution);
    Serial.println(F("Move Stepper 1"));
  }
}

void checkStepperStop_1(uint32_t elapsed_s) {
  // Stepper move stop
  // flag stop stepper
  if (run_state && stepper1_state && (stepper1_time_cycle_index < stepper1_cycle_count) && (elapsed_s > stepper1_stop_array[stepper1_time_cycle_index]))
  {
    Serial.println("Stop stepper 1 flag");
    //stepper1_state = false ;
    stepper1_stop_flag = true ; 
    stepper1_time_cycle_index++;
  }

  // Stop stepper 
  //if (run_state && stepper1_state && stepper1_stop_flag && stepper1_step_net_counter==0 ) {
    if (stepper1_state && stepper1_stop_flag && stepper1_step_net_counter==0 ) {
    
    stepper1_state = false;
    stepper1_running = false; 
    stepper1_stop_flag = false;      

    stepperOff_1(); 
    // myStepper.step(-stepsPerRevolution);
    Serial.println(F("Stop stepper 1"));
    //Serial.print("Counter: ");
    //Serial.println(stepCounter_1);   
    stepCounter_1 = 0;     
  }   


}

void updateStepperPosition_1(uint32_t elapsed_s) {
  // Stepper move 
  if (stepper1_running) // stepper is running
  {
    unsigned long current_step_time = millis() ;
    if (current_step_time - last_step_time_1 > step_period_1 )
    {
      last_step_time_1 = current_step_time ;   
      if (stepper1_direction) // CW direction 
      {
        if (stepCounter_1 < stepper1_steps_cw)
        {
          //oneCycleCW();
          asyncStep_1(stepper1_step);
          stepper1_step++; 
          if (stepper1_step > 7 )
          {
            stepper1_step = 0 ; 
          }
          //Serial.print(stepper1_step);
          
        //   Serial.print(stepCounter_1);
        //   Serial.print("#");
        //   Serial.println(stepper1_step_net_counter);
          stepCounter_1++;
          stepper1_step_net_counter++ ; 
        } 
        else
        {
          stepCounter_1 = 0;
          stepper1_direction = !stepper1_direction;
          Serial.println("");       
          Serial.print("Change stepper 1 Direction ");
          Serial.println(stepper1_direction);        
        }
      }
      else   {
        if (stepCounter_1 < stepper1_steps_ccw)
        {
          //oneCycleCCW();
          asyncStep_1(stepper1_step);
          stepper1_step--; 
          if (stepper1_step < 0 )
          {
            stepper1_step = 7 ; 
          }
          //Serial.print(stepper1_step);
        //   Serial.print(stepCounter_1);
        //   Serial.print("#");
        //   Serial.println(stepper1_step_net_counter);

          stepCounter_1++;
          stepper1_step_net_counter--;
        }   
        else
        {
          stepCounter_1 = 0;
          stepper1_direction = !stepper1_direction;
          // Serial.println("reset stepper");
          Serial.println("");       
          Serial.print("Change stepper 1 Direction ");
          Serial.println(stepper1_direction);
        }
      }
      
    }    
  }
}





void checkStepperStart_2(uint32_t elapsed_s) {
  // Stepper move start
  if (run_state && !stepper2_state && stepper2_time_cycle_index < stepper2_cycle_count && 
    ((elapsed_s > stepper2_start_array[stepper2_time_cycle_index]) && 
    (elapsed_s < stepper2_stop_array[stepper2_time_cycle_index])))
  {
    stepper2_state = true;
    stepper2_running = true;
    stepper2_direction = stepper2_start_direction ; 
    // myStepper.step(stepsPerRevolution);
    Serial.println(F("Move Stepper 2"));
  }
}

void checkStepperStop_2(uint32_t elapsed_s) {
  // Stepper move stop
  // flag stop stepper
  if (run_state && stepper2_state && (stepper2_time_cycle_index < stepper2_cycle_count) && (elapsed_s > stepper2_stop_array[stepper2_time_cycle_index]))
  {
    Serial.println("Stop stepper 2 flag");
    //stepper2_state = false ;
    stepper2_stop_flag = true ; 
    stepper2_time_cycle_index++;
  }

  // Stop stepper 
  //if (run_state && stepper2_state && stepper2_stop_flag && stepper2_step_net_counter==0 ) {
    if (stepper2_state && stepper2_stop_flag && stepper2_step_net_counter==0 ) {
    
    stepper2_state = false;
    stepper2_running = false; 
    stepper2_stop_flag = false;      

    stepperOff_2(); 
    // myStepper.step(-stepsPerRevolution);
    Serial.println(F("Stop 2 stepper"));
    //Serial.print("Counter: ");
    //Serial.println(stepCounter_2);   
    stepCounter_2 = 0;     
  }   


}

void updateStepperPosition_2(uint32_t elapsed_s) {
  // Stepper move 
  if (stepper2_running) // stepper is running
  {
    unsigned long current_step_time = millis() ;
    if (current_step_time - last_step_time_2 > step_period_2 )
    {
      last_step_time_2 = current_step_time ;   
      if (stepper2_direction) // CW direction 
      {
        if (stepCounter_2 < stepper2_steps_cw)
        {
          //oneCycleCW();
          asyncStep_2(stepper2_step);
          stepper2_step++; 
          if (stepper2_step > 7 )
          {
            stepper2_step = 0 ; 
          }
          //Serial.print(stepper2_step);
          
        //   Serial.print(stepCounter_2);
        //   Serial.print("#");
        //   Serial.println(stepper2_step_net_counter);
          stepCounter_2++;
          stepper2_step_net_counter++ ; 
        } 
        else
        {
          stepCounter_2 = 0;
          stepper2_direction = !stepper2_direction;
          Serial.println("");       
          Serial.print("Change stepper 2 Direction ");
          Serial.println(stepper2_direction);        
        }
      }
      else   {
        if (stepCounter_2 < stepper2_steps_ccw)
        {
          //oneCycleCCW();
          asyncStep_2(stepper2_step);
          stepper2_step--; 
          if (stepper2_step < 0 )
          {
            stepper2_step = 7 ; 
          }
          //Serial.print(stepper2_step);
        //   Serial.print(stepCounter_2);
        //   Serial.print("#");
        //   Serial.println(stepper2_step_net_counter);

          stepCounter_2++;
          stepper2_step_net_counter--;
        }   
        else
        {
          stepCounter_2 = 0;
          stepper2_direction = !stepper2_direction;
          // Serial.println("reset stepper");
          Serial.println("");       
          Serial.print("Change stepper 2 Direction ");
          Serial.println(stepper2_direction);
        }
      }
        // Serial.print(stepCounter_2);
          Serial.print("#");
          Serial.println(stepper2_step_net_counter);


    }    
  }
}


#endif