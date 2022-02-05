// #include <Stepper.h>

#include "Arduino.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include <SPI.h>
#include <FreeStack.h>

// Add the SdFat Libraries
#include <SdFat.h>

// and the MP3 Shield Library
#include <vs1053_SdFat.h>

// Files in src
#include <config.h>
#include <globals.h>
#include <stepper_lite.h>
#include <servo_control.h>
#include <servo_state_machine.h>
#include <led_control.h>
#include <serial_menu.h>
#include <led_state_machine.h>

// Below is not needed if interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif

#define FW_VERSION 2

#define DISABLE_SD_MP3

void reset_all()
{
  all_lights_off();
  servo_defaults();
}


void setup()
{

  uint8_t result; // result code from some function as to be tested at later time.

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.print("Fw version: ");
  Serial.println(FW_VERSION);
  Serial.print("Diorama: ");
  Serial.println(DIORAMA_NUMBER);
  
  Serial.print(F("F_CPU = "));
  Serial.println(F_CPU);
  Serial.print(F("Free RAM = ")); // available in Version 1.0 F() bases the string to into Flash, to use less SRAM.
  Serial.print(FreeStack(), DEC); // FreeStack() is provided by SdFat
  Serial.println(F(" Should be a base line of 1028, on ATmega328 when using INTx"));

  #if !defined(DISABLE_SD_MP3)  
    // Initialize the SdCard.
    if (!sd.begin(SD_SEL, SPI_FULL_SPEED))
      sd.initErrorHalt();
    // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
    if (!sd.chdir("/"))
      sd.errorHalt("sd.chdir");

    // Initialize the MP3 Player Shield
    result = MP3player.begin();
    // check result, see readme for error codes.
    if (result != 0)
    {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to start MP3 player"));
      if (result == 6)
      {
        Serial.println(F("Warning: patch file not found, skipping."));           // can be removed for space, if needed.
        Serial.println(F("Use the \"d\" command to verify SdCard can be read")); // can be removed for space, if needed.
      }
    }
    // Set volume
    MP3player.setVolume(2, 2); // commit new volume
  #endif


  // Setup stepper pins
  pinMode(STEPPER_PIN_A, OUTPUT);
  pinMode(STEPPER_PIN_B, OUTPUT);
  pinMode(STEPPER_PIN_C, OUTPUT);
  pinMode(STEPPER_PIN_D, OUTPUT);


  PCA1.begin();
  PCA2.begin();

  PCA1.setOscillatorFrequency(27000000); // The int.osc. is closer to 27MHz
  PCA2.setOscillatorFrequency(27000000); // The int.osc. is closer to 27MHz

  PCA1.setPWMFreq(1500);  // 1.5 kHz for the lights                              
  PCA2.setPWMFreq(50);  // 50 Hz for the servos

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);

  // help();

  pinMode(buttonPin, INPUT_PULLUP);

  // Initial state, everything off
  reset_all() ; 

}

//------------------------------------------------------------------------------
/**
 * \brief Main Loop the Arduino Chip
 *
 * This is called at the end of Arduino kernel's main loop before recycling.
 * And is where the user's serial input of bytes are read and analyzed by
 * parsed_menu.
 *
 * Additionally, if the means of refilling is not interrupt based then the
 * MP3player object is serviced with the availaible function.
 *
 * \note Actual examples of the libraries public functions are implemented in
 * the parse_menu() function.
 */
void loop()
{

  // -------- Start Button
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState)
    {
      buttonState = reading;

      // only play if the new button state is LOW (inverted logic, due to input_pullup)
      if (buttonState == LOW)
      {
        run_state = true;
        Serial.println("Button Start");
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;

  // -------- End Button

  uint8_t result; // result code from some function as to be tested at later time.
  int track_number = 1;

  if (run_state && !prev_play_state)
  {
    // tell the MP3 Shield to play a track
#if !defined(DISABLE_SD_MP3)
    result = MP3player.playTrack(track_number);
#endif        
    start_play_time = millis();
    prev_play_state = true;
    Serial.println(F("Start Play"));
  }

  
  long time_now = millis()  ; 
  long elapsed = time_now - start_play_time;
  uint32_t elapsed_s = elapsed /1000 ; 
  long elapsed_timer_print = time_now - last_timer_print;

  if (run_state && ( elapsed_timer_print >  1000))
  {
      Serial.println(elapsed_s) ; 
      last_timer_print = time_now; 
  }

  if (run_state && (elapsed_s > max_playtime))
  {
    run_state = false;
    prev_play_state = false;
    Serial.println("Play timeout");

    // Reset indexes
    servo_move_index_1 = 0;
    servo_move_index_2 = 0;

    reset_light_indexes(); 

    stepper_time_index = 0 ; 
    stepper_stop_flag = false ; 
    // Reset lights and servos  
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

  fadeOut1();
  fadeOut2();

  checkServoStart_1( elapsed_s); 
  checkServoStop_1( elapsed_s) ;
  updateServoPosition_1( elapsed_s);

  checkServoStart_2( elapsed_s); 
  checkServoStop_2( elapsed_s) ;
  updateServoPosition_2( elapsed_s);

  // Control stepper

  if (run_state && !stepper_state && stepper_time_index < stepper_cycle_count && 
    ((elapsed > stepper_start_array[stepper_time_index]) && 
    (elapsed < stepper_stop_array[stepper_time_index])))
  {
    stepper_state = true;
    stepper_running = true;

    steps_cw = 100 ; 
    steps_ccw = 100 ; 
    // myStepper.step(stepsPerRevolution);
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
      // myStepper.step(-stepsPerRevolution);
      Serial.println(F("Stop stepper"));
      Serial.print("Counter: ");
      Serial.println(stepCounter);   
      stepCounter = 0;     
    }    
    else
    {
      stepCounter = 0;
      stepper_direction = !stepper_direction;
      // Serial.println("reset stepper");
      Serial.print("Change stepper Direction ");
      Serial.println(stepper_direction);
    }
  }

  // flag stop stepper

  if (run_state && stepper_state && (stepper_time_index < stepper_cycle_count) && (elapsed > stepper_stop_array[stepper_time_index]))
  {
    //stepper_state = false ;
    stepper_stop_flag = true ; 
    stepper_time_index++;
    Serial.println("Stop stepper flag");

  }

  // Serial Commands
  if (Serial.available())
  {
    parse_menu(Serial.read()); // get command from serial input
  }

  // Serial1 replies
  if (Serial1.available() && relay_commands)
  {
    byte read_reply = Serial1.read(); // get command from serial1 input
    //Serial.print("R:") ;
    Serial.write(read_reply) ; // Relay reply to serial (usb)
  }

}




