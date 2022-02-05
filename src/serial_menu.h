#include "Arduino.h"

#define DISABLE_SD_MP3
//------------------------------------------------------------------------------
/**
 * \brief Decode the Menu.
 * 
 *  
 */

uint32_t millis_prv;
#define DISABLE_SD_MP3

void parse_menu(byte key_command)
{

  uint8_t result; // result code from some function as to be tested at later time.

  // Note these buffer may be desired to exist globably.
  // but do take much space if only needed temporarily, hence they are here.
  char title[30];  // buffer to contain the extract the Title from the current filehandles
  char artist[30]; // buffer to contain the extract the artist name from the current filehandles
  char album[30];  // buffer to contain the extract the album name from the current filehandles

  Serial.print(F("Received command: "));
  Serial.write(key_command);
  Serial.println(F(" "));

  // if s, stop the current track
  if (key_command == 's')
  {
    Serial.println(F("Stopping"));
#if !defined(DISABLE_SD_MP3)
    MP3player.stopTrack();
#endif
    if (relay_commands)
    {
      Serial1.write(key_command); 
    }
    
    // if 1-9, play corresponding track
  }
  else if (key_command >= '1' && key_command <= '9')
  {
    if (relay_commands)
    {
      //Serial1.print('1');
      //Serial1.println('1');
      //Serial1.write(49);
      //Serial.println("relayed");
      Serial1.write(key_command); 
    }

    // convert ascii numbers to real numbers
    key_command = key_command - 48;

#if USE_MULTIPLE_CARDS
    sd.chvol(); // assign desired sdcard's volume.
#endif

#if !defined(DISABLE_SD_MP3)

    // tell the MP3 Shield to play a track
    result = MP3player.playTrack(key_command);

    // check result, see readme for error codes.
    if (result != 0)
    {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to play track"));
    }
    else
    {

      Serial.println(F("Playing:"));

      // we can get track info by using the following functions and arguments
      // the functions will extract the requested information, and put it in the array we pass in
      MP3player.trackTitle((char *)&title);
      MP3player.trackArtist((char *)&artist);
      MP3player.trackAlbum((char *)&album);

      // print out the arrays of track information
      Serial.write((byte *)&title, 30);
      Serial.println();
      Serial.print(F("by:  "));
      Serial.write((byte *)&artist, 30);
      Serial.println();
      Serial.print(F("Album:  "));
      Serial.write((byte *)&album, 30);
      Serial.println();
    }
#endif
    if (relay_commands)
    {
      //Serial1.print("1");
      //Serial1.println("1");
      //Serial1.write(49);
      Serial1.write(key_command); 
    }
    // if +/- to change volume
  }
  else if ((key_command == '-') || (key_command == '+'))
  {

#if !defined(DISABLE_SD_MP3)
   
    union twobyte mp3_vol;                // create key_command existing variable that can be both word and double byte of left and right.
    mp3_vol.word = MP3player.getVolume(); // returns a double uint8_t of Left and Right packed into int16_t

    if (key_command == '-')
    { // note dB is negative
      // assume equal balance and use byte[1] for math
      if (mp3_vol.byte[1] >= 254)
      { // range check
        mp3_vol.byte[1] = 254;
      }
      else
      {
        mp3_vol.byte[1] += 2; // keep it simpler with whole dB's
      }
    }
    else
    {
      if (mp3_vol.byte[1] <= 2)
      { // range check
        mp3_vol.byte[1] = 2;
      }
      else
      {
        mp3_vol.byte[1] -= 2;
      }
    }
    // push byte[1] into both left and right assuming equal balance.
    MP3player.setVolume(mp3_vol.byte[1], mp3_vol.byte[1]); // commit new volume
    Serial.print(F("Volume changed to -"));
    Serial.print(mp3_vol.byte[1] >> 1, 1);
    Serial.println(F("[dB]"));
     
#endif 
    // if < or > to change Play Speed
  }
  else if (key_command == 'j')
  {
    servo_defaults(); 
  }
  else if (key_command == 'h')
  {
    all_servos_min(); 
  }
  else if (key_command == 'H')
  {
    all_servos_max(); 
  }
  else if (key_command == 'l')
  {
    manual_led_state_1 = !manual_led_state_1;
    if (manual_led_state_1)
    {
      Serial.println("manual led on");
      turn_on_led_1();
      // delay(5000) ; 
      // servo_continuous(PCA2_PIN_SERVO_1, 1);
    }
    else
    {
      Serial.println("manual led off");
      turn_off_led_1();
      // servo_continuous(PCA2_PIN_SERVO_1, -1);
    }
  }
  else if (key_command == 'L')
  {
    manual_led_state_2 = !manual_led_state_2;
    if (manual_led_state_2)
    {
      Serial.println("manual led2 on");
      turn_on_led_n(2);
      // servo_continuous(PCA2_PIN_SERVO_1, 1);
    }
    else
    {
      Serial.println("manual led2 off");
      turn_off_led_n(2);
      // servo_continuous(PCA2_PIN_SERVO_1, -1);
    }
  }
  else if (key_command == 'y')
  {
    all_lights_on();
    turn_on_led_5();
  }  
  else if (key_command == 'Y')
  {
    all_lights_off();
    turn_off_led_5();
  }  

  else if (key_command == 't')
  {
    pwm_light_1 = 0;
    pwm_light_2 = 0;
    pwm_light_3 = 0;
    pwm_light_4 = 0;
    pwm_light_5 = 0;

    fade_in_led_1 = !fade_in_led_1;
    fade_in_led_2 = !fade_in_led_2;
    fade_in_led_3 = !fade_in_led_3;
    fade_in_led_4 = !fade_in_led_4;
    fade_in_led_5 = !fade_in_led_5;
  }
  else if (key_command == 'T')
  {
    pwm_light_1 = 4095;
    pwm_light_2 = 4095;
    pwm_light_3 = 4095;
    pwm_light_4 = 4095;
    pwm_light_5 = 4095;

    fade_out_led_1 = !fade_out_led_1;
    fade_out_led_2 = !fade_out_led_2;
    fade_out_led_3 = !fade_out_led_3;
    fade_out_led_4 = !fade_out_led_4;
    fade_out_led_5 = !fade_out_led_5;
  }   
  else if (key_command == 'w')
  {
    servo_angle_active_1 = !servo_angle_active_1;
  }
  else if (key_command == 'W')
  {
    servo_angle_active_2 = !servo_angle_active_2;
  }
  else if (key_command == 'e')
  {
    servo_angle_active_3 = !servo_angle_active_3;
  }
  else if (key_command == 'E')
  {
    servo_angle_active_4 = !servo_angle_active_4;
  }    
  else if (key_command == 'r') //Luces peces led1
  {
    Serial.println("manual ramp 1");
    fade_in_led_1 = !fade_in_led_1;
  }  
  else if (key_command == 'R') //Llamas led2
  {
    Serial.println("manual ramp 2");
    fade_in_led_2 = !fade_in_led_2;
  }  

  else if (key_command == 'z') //Mama led3
  {
    Serial.println("manual ramp 3");
    fade_in_led_3 = !fade_in_led_3;
  } 

  else if (key_command == 'x') //Pajarraco led4
  {
    Serial.println("manual ramp 4");
    fade_in_led_4 = !fade_in_led_4;
  } 

  else if (key_command == 'c') //Led trasero, no prende con esta funcion XD
  {
    Serial.println("manual ramp 5");
    turn_on_led_n(pin_light_5);
  } 

  else if (key_command == 'f')
  {
    Serial.println("manual fade out 1");
    fade_out_led_1 = !fade_out_led_1;
    pwm_light_1 = 2048 ;
  }  
  else if (key_command == 'F')
  {
    Serial.println("manual fade out 2");
    fade_out_led_2 = !fade_out_led_2;
    pwm_light_2 = 2048;
  }
  else if (key_command == 'p')
  {
    set_servo_angle(PCA2_PIN_SERVO_1, min_servo_position_1);
    Serial.println("Servo at min position");
  }
  else if (key_command == 'P')
  {
    set_servo_angle(PCA2_PIN_SERVO_1, max_servo_position_2);
    Serial.println("Servo at max position");
  }
  else if (key_command == 'o')
  {
    set_servo_angle(PCA2_PIN_SERVO_2, min_servo_position_2);
    Serial.println("Servo 2 at min position");
  }
  else if (key_command == 'O')
  {
    set_servo_angle(PCA2_PIN_SERVO_2, max_servo_position_2);
    Serial.println("Servo 2 at max position");
  }
  else if (key_command == 'C')
  {
    Serial.println("manual Step CCW");
    stepper_running = !stepper_running;
    steps_ccw = 100;
    // myStepper.step(stepsPerRevolution) ;
  }
  else if (key_command == 'c')
  {
    Serial.println("manual Step CW");
    stepper_running = !stepper_running;
    steps_cw = 100;
    // myStepper.step(-stepsPerRevolution) ;
  }
  else if (key_command == 'u')
  {
    run_state = true;
  }

  // print prompt after key stroke has been processed.
  Serial.print(F("Time since last command: "));
  Serial.println((float)(millis() - millis_prv) / 1000, 2);
  millis_prv = millis();
  Serial.print(F("Enter s,1-9,+,-,>,<,f,F,d,i,p,t,S,b"));

  Serial.print(F(",m,e,r,R,g,k,O,o,D,V,B,C,T,E,M:"));

  Serial.println(F(",h :"));
}

// //------------------------------------------------------------------------------
// /**
//  * \brief Print Help Menu.
//  *
//  * Prints a full menu of the commands available along with descriptions.
//  */
void help()
{
  Serial.println(F("Arduino vs1053 Library Example:"));
  // Serial.println(F(" courtesy of Bill Porter & Michael P. Flaga"));
  Serial.println(F("COMMANDS:"));
  Serial.println(F(" [1-9] to play a track"));

  Serial.println(F(" [s] to stop playing"));
  // Serial.println(F(" [d] display directory of SdCard"));
  Serial.println(F(" [+ or -] to change volume"));

  Serial.println(F(" [h] this help"));
}
