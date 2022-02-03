# 1 "C:\\Users\\Axel\\AppData\\Local\\Temp\\tmplixdn70g"
#include <Arduino.h>
# 1 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"


#include "Arduino.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <SPI.h>
#include <FreeStack.h>


#include <SdFat.h>


#include <vs1053_SdFat.h>


#include <config.h>
#include <globals.h>
#include <stepper_lite.h>
#include <servo_control.h>
#include <led_control.h>
#include <serial_menu.h>
#include <led_state_machine.h>


#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif

#define FW_VERSION 2
void reset_all();
void setup();
void loop();
#line 38 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
void reset_all()
{
  all_lights_off();
  servo_defaults();
}

void setup()
{

  uint8_t result;

  Serial.begin(115200);
  Serial.print("Fw version: ");
  Serial.println(FW_VERSION);
  Serial.print("Diorama: ");
  Serial.println(DIORAMA_NUMBER);

  Serial.print(F("F_CPU = "));
  Serial.println(F_CPU);
  Serial.print(F("Free RAM = "));
  Serial.print(FreeStack(), DEC);
  Serial.println(F(" Should be a base line of 1028, on ATmega328 when using INTx"));


  if (!sd.begin(SD_SEL, SPI_FULL_SPEED))
    sd.initErrorHalt();

  if (!sd.chdir("/"))
    sd.errorHalt("sd.chdir");


  result = MP3player.begin();

  if (result != 0)
  {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
    if (result == 6)
    {
      Serial.println(F("Warning: patch file not found, skipping."));
      Serial.println(F("Use the \"d\" command to verify SdCard can be read"));
    }
  }

  MP3player.setVolume(2, 2);


  pinMode(STEPPER_PIN_A, OUTPUT);
  pinMode(STEPPER_PIN_B, OUTPUT);
  pinMode(STEPPER_PIN_C, OUTPUT);
  pinMode(STEPPER_PIN_D, OUTPUT);


  PCA1.begin();
  PCA2.begin();

  PCA1.setOscillatorFrequency(27000000);
  PCA2.setOscillatorFrequency(27000000);

  PCA1.setPWMFreq(1500);
  PCA2.setPWMFreq(50);




  Wire.setClock(400000);



  pinMode(buttonPin, INPUT_PULLUP);


  reset_all() ;

}
# 129 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
void loop()
{



  int reading = digitalRead(buttonPin);






  if (reading != lastButtonState)
  {

    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {




    if (reading != buttonState)
    {
      buttonState = reading;


      if (buttonState == LOW)
      {
        run_state = true;
        Serial.println("Button Start");
      }
    }
  }


  lastButtonState = reading;



  uint8_t result;
  int track_number = 1;

  if (run_state && !prev_play_state)
  {

    result = MP3player.playTrack(track_number);
    start_play_time = millis();
    prev_play_state = true;
    Serial.println(F("Start Play"));
  }


  long time_now = millis() ;
  long elapsed = time_now - start_play_time;
  uint32_t elapsed_s = elapsed /1000 ;
  long elapsed_timer_print = time_now - last_timer_print;

  if (run_state && ( elapsed_timer_print > 1000))
  {
      Serial.println(elapsed_s) ;
      last_timer_print = time_now;
  }

  if (run_state && (elapsed_s > max_playtime))
  {
    run_state = false;
    prev_play_state = false;
    Serial.println("Play timeout");


    servo_move_index = 0;
    servo_move_index_2 = 0;

    reset_light_indexes();

    stepper_time_index = 0 ;
    stepper_stop_flag = false ;

    reset_all();

  }


  if (run_state && !servo_state && servo_move_index < servo_move_count &&
  ((elapsed > servo_start_array[servo_move_index]) &&
  (elapsed < servo_stop_array[servo_move_index])))
  {

    Serial.println("Servo 2 On");
    Serial.print("Move index: ");
    Serial.println(servo_move_index);
    servo_state = true;

  }


  if (run_state && servo_state && (elapsed > servo_stop_array[servo_move_index]))
  {

    Serial.println("Servo 2 Off");
    servo_state = false;
    set_servo_angle(PCA_PIN_SERVO_1, servo_default_angle_1);

    servo_move_index++;

  }





  if (run_state && !servo_state_2 && servo_move_index_2 < servo_move_count_2 &&
  ((elapsed > servo_start_array_2[servo_move_index_2]) &&
  (elapsed < servo_stop_array_2[servo_move_index_2])))
  {

    Serial.println("Servo 2 On");
    Serial.print("Move index: ");
    Serial.println(servo_move_index_2);
    servo_state_2 = true;

  }


  if (run_state && servo_state_2 && (elapsed > servo_stop_array_2[servo_move_index_2]))
  {

    Serial.println("Servo 2 Off");
    servo_state_2 = false;
    set_servo_angle(PCA_PIN_SERVO_2, servo_default_angle_2);

    servo_move_index_2++;

  }

  checkTurnOn1(elapsed_s);
  checkTurnOn2(elapsed_s);
  checkTurnOn3(elapsed_s);
  checkTurnOn4(elapsed_s);
  checkTurnOn5(elapsed_s);

  checkTurnOff1(elapsed_s);
  checkTurnOff2(elapsed_s);
  checkTurnOff3(elapsed_s);
  checkTurnOff4(elapsed_s);
  checkTurnOff5(elapsed_s);

  fadeIn1();
  fadeIn2();

  fadeOut1();
  fadeOut2();

  if (servo_angle_active || servo_state)
  {
    switch (servo_move_type)
    {
    case 0:
      if (servo_move_index < servo_move_count &&
         ((elapsed > servo_start_array[servo_move_index]) &&
         (elapsed < servo_stop_array[servo_move_index])))
      {
        set_servo_angle(PCA_PIN_SERVO_1, max_servo_position_2);

      }
      else if (servo_move_index < servo_move_count && (elapsed > servo_stop_array[servo_move_index]))
      {
        set_servo_angle(PCA_PIN_SERVO_1, min_servo_position_1);

      }
      break;
    case 1:

      long elapsed_servo_update = millis() - last_servo_update_1;
      if (elapsed_servo_update > servo_update_period_1)
      {


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

  if (servo_angle_active_2 || servo_state_2)
  {
    switch (servo_move_type_2)
    {
    case 0:
      if (servo_move_index_2 < servo_move_count_2 &&
        ((elapsed > servo_start_array_2[servo_move_index_2]) &&
          (elapsed < servo_stop_array_2[servo_move_index_2])))
      {
        set_servo_angle(PCA_PIN_SERVO_2, max_servo_position_2);

      }
      else if (servo_move_index < servo_move_count && (elapsed > servo_stop_array_2[servo_move_index_2]))
      {
        set_servo_angle(PCA_PIN_SERVO_2, min_servo_position_2);

      }
      break;
    case 1:

      long elapsed_servo_update = millis() - last_servo_update_2;
      if (elapsed_servo_update > servo_update_period_2)
      {


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



  if (run_state && !stepper_state && stepper_time_index < stepper_cycle_count &&
    ((elapsed > stepper_start_array[stepper_time_index]) &&
    (elapsed < stepper_stop_array[stepper_time_index])))
  {
    stepper_state = true;
    stepper_running = true;

    steps_cw = 100 ;
    steps_ccw = 100 ;

    Serial.println(F("Move Stepper"));
  }

  if (stepper_running)
  {
    if (stepper_direction)
    {
      if (stepCounter < steps_cw)
      {
        oneCycleCW();
        stepCounter++;
      }
      else
      {
        stepCounter = 0;
        stepper_direction = !stepper_direction;
        Serial.print("Change stepper Direction ");
        Serial.println(stepper_direction);
      }
    }
    else if (stepCounter < steps_ccw)
    {
      oneCycleCCW();
      stepCounter++;
    }
    else if (stepper_stop_flag) {

      stepper_state = false;
      stepper_running = false;
      stepperOff();

      Serial.println(F("Stop stepper"));
      Serial.print("Counter: ");
      Serial.println(stepCounter);
      stepCounter = 0;
    }
    else
    {
      stepCounter = 0;
      stepper_direction = !stepper_direction;

      Serial.print("Change stepper Direction ");
      Serial.println(stepper_direction);
    }
  }



  if (run_state && stepper_state && (stepper_time_index < stepper_cycle_count) && (elapsed > stepper_stop_array[stepper_time_index]))
  {

    stepper_stop_flag = true ;
    stepper_time_index++;
    Serial.println("Stop stepper flag");

  }


  if (Serial.available())
  {
    parse_menu(Serial.read());
  }

}