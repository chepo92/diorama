# 1 "C:\\Users\\Axel\\AppData\\Local\\Temp\\tmpxj5vrowb"
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
#include <servo_state_machine.h>
#include <led_control.h>
#include <serial_menu.h>
#include <led_state_machine.h>


#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif

#define FW_VERSION 2

#define DISABLE_SD_MP3
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
  Serial1.begin(115200);
  Serial.print("Fw version: ");
  Serial.println(FW_VERSION);
  Serial.print("Diorama: ");
  Serial.println(DIORAMA_NUMBER);

  Serial.print(F("F_CPU = "));
  Serial.println(F_CPU);
  Serial.print(F("Free RAM = "));
  Serial.print(FreeStack(), DEC);
  Serial.println(F(" Should be a base line of 1028, on ATmega328 when using INTx"));

  #if !defined(DISABLE_SD_MP3)

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
  #endif



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
# 113 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
  pinMode(buttonPin, INPUT_PULLUP);


  reset_all() ;


  Serial1.print('s');

}
# 137 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
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

#if !defined(DISABLE_SD_MP3)
    result = MP3player.playTrack(track_number);

#endif
    start_play_time = millis();
    prev_play_state = true;
    Serial.println(F("Start Play"));


    Serial1.print('1');
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


    servo_move_index_1 = 0;
    servo_move_index_2 = 0;

    reset_light_indexes();

    stepper_time_index = 0 ;
    stepper_stop_flag = false ;

    reset_all();

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
  fadeIn3();
  fadeIn4();
  fadeIn5();

  fadeOut1();
  fadeOut2();
  fadeOut3();
  fadeOut4();
  fadeOut5();

  checkServoStart_1( elapsed_s);
  checkServoStop_1( elapsed_s) ;
  updateServoPosition_1( elapsed_s);

  checkServoStart_2( elapsed_s);
  checkServoStop_2( elapsed_s) ;
  updateServoPosition_2( elapsed_s);

  checkServoStart_3( elapsed_s);
  checkServoStop_3( elapsed_s) ;
  updateServoPosition_3( elapsed_s);

  checkServoStart_4( elapsed_s);
  checkServoStop_4( elapsed_s) ;
  updateServoPosition_4( elapsed_s);



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


  if (Serial1.available() && relay_commands)
  {
    byte read_reply = Serial1.read();

    Serial.write(read_reply) ;
  }

}