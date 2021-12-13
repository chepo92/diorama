# 1 "C:\\Users\\Axel\\AppData\\Local\\Temp\\tmpg58v78bt"
#include <Arduino.h>
# 1 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
#include <Stepper.h>
# 23 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
#include <SPI.h>
#include <FreeStack.h>


#include <SdFat.h>


#include <vs1053_SdFat.h>


#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif






SdFat sd;






vs1053 MP3player;
# 68 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
const int stepsPerRevolution = 200;


Stepper myStepper(stepsPerRevolution, A0, A1, A2, A3);

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver PCA = Adafruit_PWMServoDriver();
void setup();
void set_servo_angle(uint8_t n_servo, int angulo);
void servo_continuous(uint8_t n_servo, int dir);
void one_step();
void turn_on_led();
void turn_off_led();
void loop();
void parse_menu(byte key_command);
void help();
#line 83 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
void setup()
{

  uint8_t result;

  Serial.begin(115200);

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

#if defined(__BIOFEEDBACK_MEGA__)

  Serial.println(F("Applying ADMixer patch."));
  if (MP3player.ADMixerLoad("admxster.053") == 0)
  {
    Serial.println(F("Setting ADMixer Volume."));
    MP3player.ADMixerVol(-3);
  }
#endif


  myStepper.setSpeed(60);


  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  PCA.begin();



  PCA.setOscillatorFrequency(27000000);
  PCA.setPWMFreq(500);




  Wire.setClock(400000);

  help();
}



#define PCA_PIN_SERVO 12

unsigned int pos0 = 172;
unsigned int pos180 = 565;

int current_position = 0;

int servo_step = 1;

bool servo_angle_active;

void set_servo_angle(uint8_t n_servo, int angulo)
{
  int duty;
  duty = map(angulo, 0, 180, pos0, pos180);
  PCA.setPWM(n_servo, 0, duty);
}


void servo_continuous(uint8_t n_servo, int dir)
{
  if (dir > 0)
  {
    PCA.setPWM(n_servo, 0, 180);
  }
  else if (dir < 0)
  {
    PCA.setPWM(n_servo, 0, 360);
  }
  else
  {
    PCA.setPWM(n_servo, 0, 300);
  }
}



#define PCA_PIN_STEPPER1 4
#define PCA_PIN_STEPPER2 5
#define PCA_PIN_STEPPER3 6
#define PCA_PIN_STEPPER4 7

void one_step()
{
  PCA.setPWM(PCA_PIN_STEPPER1, 0, 1000);
  PCA.setPWM(PCA_PIN_STEPPER2, 1000, 2000);
  PCA.setPWM(PCA_PIN_STEPPER3, 2000, 3000);
  PCA.setPWM(PCA_PIN_STEPPER4, 3000, 4000);






}



boolean led_state = false;
long led_timer;
long led_period;

#define PCA_PIN_LEDS_E 8
#define PCA_PIN_LEDS_M 9

void turn_on_led()
{
  PCA.setPWM(PCA_PIN_LEDS_E, 0, 2045);
  PCA.setPWM(PCA_PIN_LEDS_E, 2045, 4090);
}

void turn_off_led()
{
  PCA.setPWM(PCA_PIN_LEDS_E, 0, 0);
  PCA.setPWM(PCA_PIN_LEDS_E, 0, 0);
}
# 244 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
void loop()
{

  one_step();


  if (servo_angle_active)
  {
    Serial.println(current_position);
    set_servo_angle(PCA_PIN_SERVO, current_position);
    current_position = current_position + servo_step;
    if (current_position <= 0)
    {
      servo_step = abs(servo_step);
    }
    if (current_position >= 180)
    {
      servo_step = -abs(servo_step);
    }
  }
# 273 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
#if defined(USE_MP3_REFILL_MEANS) && ((USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) || (USE_MP3_REFILL_MEANS == USE_MP3_Polled))

  MP3player.available();
#endif

  if (Serial.available())
  {
    parse_menu(Serial.read());
  }

  delay(100);
}

uint32_t millis_prv;
# 296 "H:/Mi unidad/Proyectos/Arduino/Proyectos/Diorama/codigoBase/src/main.ino"
void parse_menu(byte key_command)
{

  uint8_t result;



  char title[30];
  char artist[30];
  char album[30];

  Serial.print(F("Received command: "));
  Serial.write(key_command);
  Serial.println(F(" "));


  if (key_command == 's')
  {
    Serial.println(F("Stopping"));
    MP3player.stopTrack();


  }
  else if (key_command >= '1' && key_command <= '9')
  {

    key_command = key_command - 48;

#if USE_MULTIPLE_CARDS
    sd.chvol();
#endif

    result = MP3player.playTrack(key_command);


    if (result != 0)
    {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to play track"));
    }
    else
    {

      Serial.println(F("Playing:"));



      MP3player.trackTitle((char *)&title);
      MP3player.trackArtist((char *)&artist);
      MP3player.trackAlbum((char *)&album);


      Serial.write((byte *)&title, 30);
      Serial.println();
      Serial.print(F("by:  "));
      Serial.write((byte *)&artist, 30);
      Serial.println();
      Serial.print(F("Album:  "));
      Serial.write((byte *)&album, 30);
      Serial.println();
    }


  }
  else if ((key_command == '-') || (key_command == '+'))
  {
    union twobyte mp3_vol;
    mp3_vol.word = MP3player.getVolume();

    if (key_command == '-')
    {

      if (mp3_vol.byte[1] >= 254)
      {
        mp3_vol.byte[1] = 254;
      }
      else
      {
        mp3_vol.byte[1] += 2;
      }
    }
    else
    {
      if (mp3_vol.byte[1] <= 2)
      {
        mp3_vol.byte[1] = 2;
      }
      else
      {
        mp3_vol.byte[1] -= 2;
      }
    }

    MP3player.setVolume(mp3_vol.byte[1], mp3_vol.byte[1]);
    Serial.print(F("Volume changed to -"));
    Serial.print(mp3_vol.byte[1] >> 1, 1);
    Serial.println(F("[dB]"));


  }
  else if ((key_command == '>') || (key_command == '<'))
  {
    uint16_t playspeed = MP3player.getPlaySpeed();

    if (key_command == '>')
    {

      if (playspeed >= 254)
      {
        playspeed = 5;
      }
      else
      {
        playspeed += 1;
      }
    }
    else
    {
      if (playspeed == 0)
      {
        playspeed = 0;
      }
      else
      {
        playspeed -= 1;
      }
    }
    MP3player.setPlaySpeed(playspeed);
    Serial.print(F("playspeed to "));
    Serial.println(playspeed, DEC);



  }
  else if (key_command == 'f' || key_command == 'F')
  {
    uint32_t offset = 0;
    if (key_command == 'F')
    {
      offset = 2000;
    }


    char trackName[] = "track001.mp3";

#if USE_MULTIPLE_CARDS
    sd.chvol();
#endif

    result = MP3player.playMP3(trackName, offset);

    if (result != 0)
    {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to play track"));
    }


  }
  else if (key_command == 'd')
  {
    if (!MP3player.isPlaying())
    {



      Serial.println(F("Files found (name date time size):"));
      sd.ls(LS_R | LS_DATE | LS_SIZE);
    }
    else
    {
      Serial.println(F("Busy Playing Files, try again later."));
    }


  }
  else if (key_command == 'i')
  {
    MP3player.getAudioInfo();
  }
  else if (key_command == 'p')
  {
    if (MP3player.getState() == playback)
    {
      MP3player.pauseMusic();
      Serial.println(F("Pausing"));
    }
    else if (MP3player.getState() == paused_playback)
    {
      MP3player.resumeMusic();
      Serial.println(F("Resuming"));
    }
    else
    {
      Serial.println(F("Not Playing!"));
    }
  }
  else if (key_command == 't')
  {
    int8_t teststate = MP3player.enableTestSineWave(126);
    if (teststate == -1)
    {
      Serial.println(F("Un-Available while playing music or chip in reset."));
    }
    else if (teststate == 1)
    {
      Serial.println(F("Enabling Test Sine Wave"));
    }
    else if (teststate == 2)
    {
      MP3player.disableTestSineWave();
      Serial.println(F("Disabling Test Sine Wave"));
    }
  }
  else if (key_command == 'S')
  {
    Serial.println(F("Current State of VS10xx is."));
    Serial.print(F("isPlaying() = "));
    Serial.println(MP3player.isPlaying());

    Serial.print(F("getState() = "));
    switch (MP3player.getState())
    {
    case uninitialized:
      Serial.print(F("uninitialized"));
      break;
    case initialized:
      Serial.print(F("initialized"));
      break;
    case deactivated:
      Serial.print(F("deactivated"));
      break;
    case loading:
      Serial.print(F("loading"));
      break;
    case ready:
      Serial.print(F("ready"));
      break;
    case playback:
      Serial.print(F("playback"));
      break;
    case paused_playback:
      Serial.print(F("paused_playback"));
      break;
    case testing_memory:
      Serial.print(F("testing_memory"));
      break;
    case testing_sinewave:
      Serial.print(F("testing_sinewave"));
      break;
    }
    Serial.println();
  }
  else if (key_command == 'b')
  {
    Serial.println(F("Playing Static MIDI file."));
    MP3player.SendSingleMIDInote();
    Serial.println(F("Ended Static MIDI file."));

#if !defined(__AVR_ATmega32U4__)
  }
  else if (key_command == 'm')
  {
    uint16_t teststate = MP3player.memoryTest();
    if (teststate == -1)
    {
      Serial.println(F("Un-Available while playing music or chip in reset."));
    }
    else if (teststate == 2)
    {
      teststate = MP3player.disableTestSineWave();
      Serial.println(F("Un-Available while Sine Wave Test"));
    }
    else
    {
      Serial.print(F("Memory Test Results = "));
      Serial.println(teststate, HEX);
      Serial.println(F("Result should be 0x83FF."));
      Serial.println(F("Reset is needed to recover to normal operation"));
    }
  }
  else if (key_command == 'e')
  {
    uint8_t earspeaker = MP3player.getEarSpeaker();
    if (earspeaker >= 3)
    {
      earspeaker = 0;
    }
    else
    {
      earspeaker++;
    }
    MP3player.setEarSpeaker(earspeaker);
    Serial.print(F("earspeaker to "));
    Serial.println(earspeaker, DEC);
  }
  else if (key_command == 'r')
  {
    MP3player.resumeMusic(2000);
  }
  else if (key_command == 'R')
  {
    MP3player.stopTrack();
    MP3player.vs_init();
    Serial.println(F("Reseting VS10xx chip"));
  }
  else if (key_command == 'g')
  {
    int32_t offset_ms = 20000;
    Serial.print(F("jumping to "));
    Serial.print(offset_ms, DEC);
    Serial.println(F("[milliseconds]"));
    result = MP3player.skipTo(offset_ms);
    if (result != 0)
    {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to skip track"));
    }
  }
  else if (key_command == 'k')
  {
    int32_t offset_ms = -1000;
    Serial.print(F("moving = "));
    Serial.print(offset_ms, DEC);
    Serial.println(F("[milliseconds]"));
    result = MP3player.skip(offset_ms);
    if (result != 0)
    {
      Serial.print(F("Error code: "));
      Serial.print(result);
      Serial.println(F(" when trying to skip track"));
    }
  }
  else if (key_command == 'O')
  {
    MP3player.end();
    Serial.println(F("VS10xx placed into low power reset mode."));
  }
  else if (key_command == 'o')
  {
    MP3player.begin();
    Serial.println(F("VS10xx restored from low power reset mode."));
  }
  else if (key_command == 'D')
  {
    uint16_t diff_state = MP3player.getDifferentialOutput();
    Serial.print(F("Differential Mode "));
    if (diff_state == 0)
    {
      MP3player.setDifferentialOutput(1);
      Serial.println(F("Enabled."));
    }
    else
    {
      MP3player.setDifferentialOutput(0);
      Serial.println(F("Disabled."));
    }
  }
  else if (key_command == 'V')
  {
    MP3player.setVUmeter(1);
    Serial.println(F("Use \"No line ending\""));
    Serial.print(F("VU meter = "));
    Serial.println(MP3player.getVUmeter());
    Serial.println(F("Hit Any key to stop."));

    while (!Serial.available())
    {
      union twobyte vu;
      vu.word = MP3player.getVUlevel();
      Serial.print(F("VU: L = "));
      Serial.print(vu.byte[1]);
      Serial.print(F(" / R = "));
      Serial.print(vu.byte[0]);
      Serial.println(" dB");
      delay(1000);
    }
    Serial.read();

    MP3player.setVUmeter(0);
    Serial.print(F("VU meter = "));
    Serial.println(MP3player.getVUmeter());
  }
  else if (key_command == 'T')
  {
    uint16_t TrebleFrequency = MP3player.getTrebleFrequency();
    Serial.print(F("Former TrebleFrequency = "));
    Serial.println(TrebleFrequency, DEC);
    if (TrebleFrequency >= 15000)
    {
      TrebleFrequency = 0;
    }
    else
    {
      TrebleFrequency += 1000;
    }
    MP3player.setTrebleFrequency(TrebleFrequency);
    Serial.print(F("New TrebleFrequency = "));
    Serial.println(MP3player.getTrebleFrequency(), DEC);
  }
  else if (key_command == 'E')
  {
    int8_t TrebleAmplitude = MP3player.getTrebleAmplitude();
    Serial.print(F("Former TrebleAmplitude = "));
    Serial.println(TrebleAmplitude, DEC);
    if (TrebleAmplitude >= 7)
    {
      TrebleAmplitude = -8;
    }
    else
    {
      TrebleAmplitude++;
    }
    MP3player.setTrebleAmplitude(TrebleAmplitude);
    Serial.print(F("New TrebleAmplitude = "));
    Serial.println(MP3player.getTrebleAmplitude(), DEC);
  }
  else if (key_command == 'B')
  {
    uint16_t BassFrequency = MP3player.getBassFrequency();
    Serial.print(F("Former BassFrequency = "));
    Serial.println(BassFrequency, DEC);
    if (BassFrequency >= 150)
    {
      BassFrequency = 0;
    }
    else
    {
      BassFrequency += 10;
    }
    MP3player.setBassFrequency(BassFrequency);
    Serial.print(F("New BassFrequency = "));
    Serial.println(MP3player.getBassFrequency(), DEC);
  }
  else if (key_command == 'C')
  {
    uint16_t BassAmplitude = MP3player.getBassAmplitude();
    Serial.print(F("Former BassAmplitude = "));
    Serial.println(BassAmplitude, DEC);
    if (BassAmplitude >= 15)
    {
      BassAmplitude = 0;
    }
    else
    {
      BassAmplitude++;
    }
    MP3player.setBassAmplitude(BassAmplitude);
    Serial.print(F("New BassAmplitude = "));
    Serial.println(MP3player.getBassAmplitude(), DEC);
  }
  else if (key_command == 'M')
  {
    uint16_t monostate = MP3player.getMonoMode();
    Serial.print(F("Mono Mode "));
    if (monostate == 0)
    {
      MP3player.setMonoMode(1);
      Serial.println(F("Enabled."));
    }
    else
    {
      MP3player.setMonoMode(0);
      Serial.println(F("Disabled."));
    }
#endif
  }
  else if (key_command == 'h')
  {
    help();
  }
  else if (key_command == 'l')
  {
    led_state = !led_state;
    if (led_state)
    {
      turn_on_led();

    }
    else
    {
      turn_off_led();

    }
  }
  else if (key_command == 'w')
  {
    servo_angle_active =!servo_angle_active;
  }


  Serial.print(F("Time since last command: "));
  Serial.println((float)(millis() - millis_prv) / 1000, 2);
  millis_prv = millis();
  Serial.print(F("Enter s,1-9,+,-,>,<,f,F,d,i,p,t,S,b"));
#if !defined(__AVR_ATmega32U4__)
  Serial.print(F(",m,e,r,R,g,k,O,o,D,V,B,C,T,E,M:"));
#endif
  Serial.println(F(",h :"));
}







void help()
{
  Serial.println(F("Arduino vs1053 Library Example:"));
  Serial.println(F(" courtesy of Bill Porter & Michael P. Flaga"));
  Serial.println(F("COMMANDS:"));
  Serial.println(F(" [1-9] to play a track"));
  Serial.println(F(" [f] play track001.mp3 by filename example"));
  Serial.println(F(" [F] same as [f] but with initial skip of 2 second"));
  Serial.println(F(" [s] to stop playing"));
  Serial.println(F(" [d] display directory of SdCard"));
  Serial.println(F(" [+ or -] to change volume"));
  Serial.println(F(" [> or <] to increment or decrement play speed by 1 factor"));
  Serial.println(F(" [i] retrieve current audio information (partial list)"));
  Serial.println(F(" [p] to pause."));
  Serial.println(F(" [t] to toggle sine wave test"));
  Serial.println(F(" [S] Show State of Device."));
  Serial.println(F(" [b] Play a MIDI File Beep"));
#if !defined(__AVR_ATmega32U4__)
  Serial.println(F(" [e] increment Spatial EarSpeaker, default is 0, wraps after 4"));
  Serial.println(F(" [m] perform memory test. reset is needed after to recover."));
  Serial.println(F(" [M] Toggle between Mono and Stereo Output."));
  Serial.println(F(" [g] Skip to a predetermined offset of ms in current track."));
  Serial.println(F(" [k] Skip a predetermined number of ms in current track."));
  Serial.println(F(" [r] resumes play from 2s from begin of file"));
  Serial.println(F(" [R] Resets and initializes VS10xx chip."));
  Serial.println(F(" [O] turns OFF the VS10xx into low power reset."));
  Serial.println(F(" [o] turns ON the VS10xx out of low power reset."));
  Serial.println(F(" [D] to toggle SM_DIFF between inphase and differential output"));
  Serial.println(F(" [V] Enable VU meter Test."));
  Serial.println(F(" [B] Increament bass frequency by 10Hz"));
  Serial.println(F(" [C] Increament bass amplitude by 1dB"));
  Serial.println(F(" [T] Increament treble frequency by 1000Hz"));
  Serial.println(F(" [E] Increament treble amplitude by 1dB"));
#endif
  Serial.println(F(" [h] this help"));
}