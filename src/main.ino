// #include <Stepper.h>

#include <SPI.h>
#include <FreeStack.h>

// Add the SdFat Libraries
#include <SdFat.h>

// and the MP3 Shield Library
#include <vs1053_SdFat.h>

// Below is not needed if interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif

#define FW_VERSION 1

#define DIORAMA_NUMBER 5

/**
 * \brief Object instancing the SdFat library.
 *
 * principal object for handling all SdCard functions.
 */
SdFat sd;

vs1053 MP3player;

// const int stepsPerRevolution = 200; // change this to fit the number of steps per revolutio for your motor

// Pins

#define STEPPER_PIN_A A0
#define STEPPER_PIN_B A1
#define STEPPER_PIN_C A2
#define STEPPER_PIN_D A3

const int buttonPin = 5; // the number of the pushbutton pin

#define PCA_PIN_LEDS_E1 8
#define PCA_PIN_LEDS_M1 9

#define PCA_PIN_LEDS_E2 10
#define PCA_PIN_LEDS_M2 11

#define PCA_PIN_SERVO_1 12
#define PCA_PIN_SERVO_2 13

#define NUMBER_OF_STEPS_PER_REV 512
// initialize the stepper library on pins 8 through 11:
// Stepper myStepper(stepsPerRevolution, A0, A1, A2, A3);

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver PCA = Adafruit_PWMServoDriver();

// Button debounce
// constants won't change. They're used here to set pin numbers:

// Variables will change:
int run_state = false; // the current state of the output

int prev_play_state = false;
long start_play_time = 0;

int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

int servo_current_position = 0;
int servo_current_position_2 = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

/* State machine */


boolean light1_state;
boolean light2_state;

boolean manual_led_state;
boolean manual_led_state_2;

boolean stepper_state;
boolean stepper_running;
boolean stepper_direction;
boolean stepper_stop_flag ; 

boolean servo_state;
boolean servo_state_2;

boolean servo_angle_active;
boolean servo_angle_active_2;

int stepper_time_index;
int light1_time_index;
int light2_time_index;

int servo_move_index;
int servo_move_index_2;

int ramp_time_counter;
int ramp_time_counter_2;


long seconds_display ; 
long last_timer_print ; 

// Individual Settings for each Diorama
#if DIORAMA_NUMBER == 1 // el establo

long max_playtime = 128000; // 

// steppers
int stepper_cycle_count = 0;
long stepper_start_array[] = {0};
long stepper_stop_array[] = {0};

int steps_cw;
int steps_ccw;

// LED lights

int ramp_time_divisor = 5; 

int light1_cycle_count = 1;
long light1_start_array[] = {0};
long light1_stop_array[] = {115000};

int light2_cycle_lenght = 1;
long light2_start_array[] = {46000};
long light2_stop_array[] = {115000};

// Servos
int servo_move_count = 1;
long servo_start_array[] = {46000};
long servo_stop_array[] = {56000};

int servo_move_count_2 = 1;
long servo_start_array_2[] = {33000};
long servo_stop_array_2[] = {37000};

/* Servo Control */
int servo_move_type = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

int servo_default_angle = 20;
int servo_default_angle_2 = 90;

int min_servo_position = 20;
int max_servo_position = 90;

int min_servo_position_2 = 40;
int max_servo_position_2 = 90;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 480; // pwm 180°

long last_servo_update;
long last_servo_update_2;
long servo_update_period = 10;
long servo_update_period_2 = 20;

int servo_step = 1;
int servo_step_2 = 1;

#elif DIORAMA_NUMBER == 2 // Se va la lancha


long max_playtime = 120000; // 1:50 = 60+50

// steppers
int stepper_cycle_count = 0;
long stepper_start_array[] = {0};
long stepper_stop_array[] = {0};

int steps_cw;
int steps_ccw;

// LED lights

int ramp_time_divisor = 5; 

int light1_cycle_count = 1;
long light1_start_array[] = {0};
long light1_stop_array[] = {100000};

int light2_cycle_lenght = 1;
long light2_start_array[] = {23000};
long light2_stop_array[] = {80000};

// Servos
int servo_move_count = 1;
long servo_start_array[] = {28000};
long servo_stop_array[] = {85000};

/* Servo Control */
int servo_move_type = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

int servo_default_angle = 90;

int min_servo_position = 20;
int max_servo_position = 90;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 480; // pwm 180°

long last_servo_update;
long servo_update_period = 10;

int servo_step = 1;

#elif DIORAMA_NUMBER == 3 // Arrurru 

long max_playtime = 100000; // 

// steppers
int stepper_cycle_count = 0;
long stepper_start_array[] = {0};
long stepper_stop_array[] = {0};

int steps_cw;
int steps_ccw;

// LED lights

int ramp_time_divisor = 5; 

int light1_cycle_count = 1;
long light1_start_array[] = {0};
long light1_stop_array[] = {90000};

int light2_cycle_lenght = 1;
long light2_start_array[] = {45000};
long light2_stop_array[] = {90000};

// Servos
int servo_move_count = 1;
long servo_start_array[] = {5000};
long servo_stop_array[] = {80000};

int servo_move_count_2 = 1;
long servo_start_array_2[] = {33000};
long servo_stop_array_2[] = {37000};

/* Servo Control */
int servo_move_type = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

int servo_default_angle = 55;
int servo_default_angle_2 = 90;

int min_servo_position = 40;
int max_servo_position = 70;

int min_servo_position_2 = 40;
int max_servo_position_2 = 90;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 480; // pwm 180°

long last_servo_update;
long last_servo_update_2;
long servo_update_period = 40;
long servo_update_period_2 = 20;

int servo_step = 1;
int servo_step_2 = 1;

#elif DIORAMA_NUMBER == 4 // Cucu


long max_playtime = 90000; // 

// steppers
int stepper_cycle_count = 1;
long stepper_start_array[] = {20000};
long stepper_stop_array[] =  {40000};

int steps_cw;
int steps_ccw;

// LED lights

int ramp_time_divisor = 5; 

int light1_cycle_count = 1;
long light1_start_array[] = {0};
long light1_stop_array[] = {73000};

int light2_cycle_lenght = 1;
long light2_start_array[] = {11000};
long light2_stop_array[] = {72000};

// Servos
int servo_move_count = 1;
long servo_start_array[] = {35000};
long servo_stop_array[] = {45000};

int servo_move_count_2 = 1;
long servo_start_array_2[] = {40000};
long servo_stop_array_2[] = {50000};

/* Servo Control */
int servo_move_type = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

int servo_default_angle = 80;
int servo_default_angle_2 = 90;

int min_servo_position = 20;
int max_servo_position = 80;

int min_servo_position_2 = 20;
int max_servo_position_2 = 90;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 480; // pwm 180°

long last_servo_update;
long last_servo_update_2;
long servo_update_period = 40;
long servo_update_period_2 = 20;

int servo_step = 1;
int servo_step_2 = 1;

#elif DIORAMA_NUMBER == 5  


long max_playtime = 100000; // 

// steppers
int stepper_cycle_count = 1;
long stepper_start_array[] = {20000};
long stepper_stop_array[] =  {40000};

int steps_cw;
int steps_ccw;

// LED lights

int ramp_time_divisor = 5; 

int light1_cycle_count = 1;
long light1_start_array[] = {0};
long light1_stop_array[] = {9900};

int light2_cycle_lenght = 1;
long light2_start_array[] = {60000};
long light2_stop_array[] = {85000};

// Servos
int servo_move_count = 2;
long servo_start_array[] = {3000, 63000};
long servo_stop_array[] = {15000, 73000};

int servo_move_count_2 = 3;
long servo_start_array_2[] = {17000, 47000, 77000};
long servo_stop_array_2[] = {22000, 59000, 82000};

/* Servo Control */
int servo_move_type = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

int servo_default_angle = 60;
int servo_default_angle_2 = 40;

int min_servo_position = 40;
int max_servo_position = 80;

int min_servo_position_2 = 30;
int max_servo_position_2 = 50;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 480; // pwm 180°

long last_servo_update;
long last_servo_update_2;
long servo_update_period = 40;
long servo_update_period_2 = 40;

int servo_step = 1;
int servo_step_2 = 1;

#elif DIORAMA_NUMBER == 6  // Se va la lancha 

long max_playtime = 150000; // 1:50 = 60+50

// steppers
int stepper_cycle_count = 0;
long stepper_start_array[] = {};
long stepper_stop_array[] = {};

int steps_cw;
int steps_ccw;

// LED lights

int light1_cycle_count = 1;
long light1_start_array[] = {100000};
long light1_stop_array[] = {145000};

int light2_cycle_lenght = 1;
long light2_start_array[] = {0};
long light2_stop_array[] = {145000};

// Servos
int servo_move_count = 1;
long servo_start_array[] = {105000};
long servo_stop_array[] = {145000};

/* Servo Control */
int servo_move_type = 0; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

int servo_default_angle = 90;

int min_servo_position = 90;
int max_servo_position = 20;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 480; // pwm 180°

long last_servo_update;
long servo_update_period = 10;

int servo_step = 1;

#endif

void set_servo_angle(uint8_t n_servo, int angulo)
{
  int duty;
  duty = map(angulo, 0, 180, pos0_pwm, pos180_pwm);
  PCA.setPWM(n_servo, 0, duty);
}

// Needs debug/calibration
void servo_continuous(uint8_t n_servo, int dir)
{
  if (dir > 0)
  { // CW
    set_servo_angle(n_servo, 10);
  }
  else if (dir < 0)
  { // CCW
    set_servo_angle(n_servo, 45);
  }
  else
  {
    set_servo_angle(n_servo, 90);
  }
}

/* Stepper Control */

int stepCounter = 0;

void stepperOff()
{
  writeStep(0, 0, 0, 0);
}

void writeStep(int a, int b, int c, int d)
{
  digitalWrite(STEPPER_PIN_A, a);
  digitalWrite(STEPPER_PIN_B, b);
  digitalWrite(STEPPER_PIN_C, c);
  digitalWrite(STEPPER_PIN_D, d);
}

void oneCycleCW() // ~ 8 steps?
{
  writeStep(1, 0, 0, 0);
  delay(5);
  writeStep(1, 1, 0, 0);
  delay(5);
  writeStep(0, 1, 0, 0);
  delay(5);
  writeStep(0, 1, 1, 0);
  delay(5);
  writeStep(0, 0, 1, 0);
  delay(5);
  writeStep(0, 0, 1, 1);
  delay(5);
  writeStep(0, 0, 0, 1);
  delay(5);
  writeStep(1, 0, 0, 1);
  delay(5);
}

void oneCycleCCW() // ~ 8 steps?
{
  writeStep(1, 0, 0, 1);
  delay(5);
  writeStep(0, 0, 0, 1);
  delay(5);
  writeStep(0, 0, 1, 1);
  delay(5);
  writeStep(0, 0, 1, 0);
  delay(5);
  writeStep(0, 1, 1, 0);
  delay(5);
  writeStep(0, 1, 0, 0);
  delay(5);
  writeStep(1, 1, 0, 0);
  delay(5);
  writeStep(1, 0, 0, 0);
  delay(5);
}

/* LED control */
boolean do_ramp_led;
boolean do_ramp_led_2;

boolean fade_in_led_1;
boolean fade_in_led_2;

boolean fade_out_led_1;
boolean fade_out_led_2;

int pwm_ramp = 0;
int pwm_ramp_2 = 0;

void ramp_led(int current_ramp)
{
  PCA.setPWM(PCA_PIN_LEDS_E1, 0, current_ramp);
  PCA.setPWM(PCA_PIN_LEDS_M1, current_ramp, 4095);
}

void ramp_led_2(int current_ramp)
{
  PCA.setPWM(PCA_PIN_LEDS_E2, 0, current_ramp);
  PCA.setPWM(PCA_PIN_LEDS_M2, current_ramp, 4095);
}

void turn_on_led()
{
  PCA.setPWM(PCA_PIN_LEDS_E1, 0, 2045);
  PCA.setPWM(PCA_PIN_LEDS_M1, 2045, 4090);
}

void turn_off_led()
{
  PCA.setPWM(PCA_PIN_LEDS_E1, 0, 0);
  PCA.setPWM(PCA_PIN_LEDS_M1, 0, 0);
}

void turn_on_led_n(int ledIndx) {
  switch (ledIndx)
  {
  case 1:
    PCA.setPWM(PCA_PIN_LEDS_E1, 0, 2045);
    PCA.setPWM(PCA_PIN_LEDS_M1, 2045, 4095);
    break;
  case 2:
    PCA.setPWM(PCA_PIN_LEDS_E2, 0, 2045);
    PCA.setPWM(PCA_PIN_LEDS_M2, 2045, 4095);
    break;  
  default:
    break;
  }
  
}

void turn_off_led_n(int ledIndx) {
  switch (ledIndx)
  {
  case 1:
    PCA.setPWM(PCA_PIN_LEDS_E1, 0, 0);
    PCA.setPWM(PCA_PIN_LEDS_M1, 0, 0);
    break;
  case 2:
    PCA.setPWM(PCA_PIN_LEDS_E2, 0, 0);
    PCA.setPWM(PCA_PIN_LEDS_M2, 0, 0);
    break;  
  default:
    break;
  }
}

void reset_all()
{
  turn_off_led();
  turn_off_led_n(2);
  set_servo_angle(PCA_PIN_SERVO_1, servo_default_angle);
  set_servo_angle(PCA_PIN_SERVO_2, servo_default_angle_2);
  servo_current_position = servo_default_angle ; 
  servo_current_position_2 = servo_default_angle_2 ; 
}

void setup()
{

  uint8_t result; // result code from some function as to be tested at later time.

  Serial.begin(115200);
  Serial.print("Fw version: ");
  Serial.println(FW_VERSION);
  Serial.print("Diorama: ");
  Serial.println(DIORAMA_NUMBER);
  
  Serial.print(F("F_CPU = "));
  Serial.println(F_CPU);
  Serial.print(F("Free RAM = ")); // available in Version 1.0 F() bases the string to into Flash, to use less SRAM.
  Serial.print(FreeStack(), DEC); // FreeStack() is provided by SdFat
  Serial.println(F(" Should be a base line of 1028, on ATmega328 when using INTx"));

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

#if defined(__BIOFEEDBACK_MEGA__) // or other reasons, of your choosing.
  // Typically not used by most shields, hence commented out.
  Serial.println(F("Applying ADMixer patch."));
  if (MP3player.ADMixerLoad("admxster.053") == 0)
  {
    Serial.println(F("Setting ADMixer Volume."));
    MP3player.ADMixerVol(-3);
  }
#endif

  // set the speed at 60 rpm:
  // myStepper.setSpeed(10);

  pinMode(STEPPER_PIN_A, OUTPUT);
  pinMode(STEPPER_PIN_B, OUTPUT);
  pinMode(STEPPER_PIN_C, OUTPUT);
  pinMode(STEPPER_PIN_D, OUTPUT);

  // do one turn
  // Serial.println("clockwise");
  // myStepper.step(stepsPerRevolution);
  // delay(500);

  PCA.begin();
  // In theory the internal oscillator is 25MHz but it really isn't
  // that precise. You can 'calibrate' by tweaking this number till
  // you get the frequency you're expecting!
  PCA.setOscillatorFrequency(27000000); // The int.osc. is closer to 27MHz
  PCA.setPWMFreq(50);                   // 60 for the servo                // This is the maximum PWM frequency

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);

  help();

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
    result = MP3player.playTrack(track_number);
    start_play_time = millis();
    prev_play_state = true;
    Serial.println(F("Start Play"));
  }

  /* Resets machine state after x millisseconds */
  long time_now = millis()  ; 
  long elapsed = time_now - start_play_time;
  long elapsed_timer_print = time_now - last_timer_print;

  if (run_state && ( elapsed_timer_print >  1000))
  {
      Serial.println(elapsed/1000) ; 
      last_timer_print = time_now; 
  }

  if (run_state && (elapsed > max_playtime))
  {
    run_state = false;
    prev_play_state = false;
    Serial.println("Play timeout");

    // Reset indexes
    servo_move_index = 0;
    servo_move_index_2 = 0;
    light1_time_index = 0;
    light2_time_index = 0;
    stepper_time_index = 0 ; 

    stepper_stop_flag = false ; 
    // Reset positions 
    reset_all(); 

  }

  // Servo 1
  if (run_state && !servo_state && servo_move_index < servo_move_count && ((elapsed > servo_start_array[servo_move_index]) && (elapsed < servo_stop_array[servo_move_index])))
  {
    // Do move
    Serial.println("Servo 2 On");
    Serial.print("Move index: ");
    Serial.println(servo_move_index);    
    servo_state = true;
  }

  // stop servo 1 move
  if (run_state && servo_state && (elapsed > servo_stop_array[servo_move_index]))
  {
    // Do stop
    Serial.println("Servo 2 Off");
    servo_state = false;
    set_servo_angle(PCA_PIN_SERVO_1, servo_default_angle);

    servo_move_index++;
  }

  // Servo 2 move
  if (run_state && !servo_state_2 && servo_move_index_2 < servo_move_count_2 && ((elapsed > servo_start_array_2[servo_move_index_2]) && (elapsed < servo_stop_array_2[servo_move_index_2])))
  {
    // Do move
    Serial.println("Servo 2 On");
    Serial.print("Move index: ");
    Serial.println(servo_move_index_2);
    servo_state_2 = true;
  }

  // stop servo 2 move
  if (run_state && servo_state_2 && (elapsed > servo_stop_array_2[servo_move_index_2]))
  {
    // Do stop
    Serial.println("Servo 2 Off");
    servo_state_2 = false;
    set_servo_angle(PCA_PIN_SERVO_2, servo_default_angle_2);

    servo_move_index_2++;
  }  

  // light 1
  if (run_state && !light1_state && (light1_time_index < light1_cycle_count) && ((elapsed > light1_start_array[light1_time_index]) && (elapsed < light1_stop_array[light1_time_index])))
  {
    // led on
    // turn_on_led();
    do_ramp_led = true;
    if (do_ramp_led) pwm_ramp = 0 ; 
    Serial.println(F("Led 1 Do ramp"));
    light1_state = true;
  }

  // stop light 1
  if ( (run_state) && light1_state && (elapsed > light1_stop_array[light1_time_index]) || (!run_state && light1_state))
  {
    // Do stop
    // turn_off_led();
    Serial.println(F("Led 1 fade out"));
    light1_time_index++;
    do_ramp_led = false;
    fade_out_led_1 = true ; 
    if(fade_out_led_1) pwm_ramp = 2048 ; 
    light1_state = false;
  }

  // On light 2
  if (run_state && !light2_state && light2_time_index < light2_cycle_lenght && ((elapsed > light2_start_array[light2_time_index]) && (elapsed < light2_stop_array[light2_time_index])))
  {
    // led on
    // turn_on_led_n(2);
    do_ramp_led_2 = true;
    if (do_ramp_led_2) pwm_ramp_2 = 0 ; 
    Serial.println(F("Led 2 Do Ramp"));
    light2_state = true;
  }

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
    if(fade_out_led_2) pwm_ramp_2 = 2048 ; 
    
  }

  if (do_ramp_led)
  {
    if (pwm_ramp > 2048)
    {
      pwm_ramp = 0;
      turn_on_led();
      do_ramp_led = false;
      Serial.println(F("Led Full ON after ramp"));
    }
    else
    {
      ramp_led(pwm_ramp);
      ramp_time_counter ++ ; 
      if (ramp_time_counter > ramp_time_divisor ) {
        pwm_ramp ++;
        ramp_time_counter = 0 ; 
        // Serial.println(F("Ramp UP 1 "));
        // Serial.println(pwm_ramp);
      }
      
    }
  }

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
      ramp_time_counter_2 ++ ; 
      if (ramp_time_counter_2 > ramp_time_divisor ) {
        pwm_ramp_2 ++;
        ramp_time_counter_2 = 0 ; 
        // Serial.println(F("Ramp UP"));
      }
    }
  }

  if (fade_out_led_1)
  {
    if (pwm_ramp < 0)
    {
      pwm_ramp = 2048;
      turn_off_led();
      light1_state = false ; 
      fade_out_led_1 = false;
      Serial.println(F("Led 1 Full Off after fade out"));
    }
    else
    {
      ramp_led(pwm_ramp);
      ramp_time_counter ++ ; 
      if (ramp_time_counter > ramp_time_divisor ) {
        pwm_ramp -- ;
        ramp_time_counter = 0 ; 
      }      
    }
  }

  if (fade_out_led_2)
  {
    if (pwm_ramp_2 < 0)
    {
      pwm_ramp_2 = 2048;
      turn_off_led_n(2);
      light2_state = false ; 
      fade_out_led_2 = false;
      Serial.println(F("Led 2 Full Off after fade out"));
    }
    else
    {
      ramp_led_2(pwm_ramp_2);
      ramp_time_counter_2 ++ ; 
      if (ramp_time_counter_2 > ramp_time_divisor ) {
        pwm_ramp_2 -- ;
        ramp_time_counter_2 = 0 ; 
      }      
    }
  }  


  if (servo_angle_active || servo_state)
  {
    switch (servo_move_type)
    {
    case 0:
      if (servo_move_index < servo_move_count && ((elapsed > servo_start_array[servo_move_index]) && (elapsed < servo_stop_array[servo_move_index])))
      {
        set_servo_angle(PCA_PIN_SERVO_1, max_servo_position);
        //Serial.println("Servo at max position");
      }
      else if (servo_move_index < servo_move_count && (elapsed > servo_stop_array[servo_move_index]))
      {
        set_servo_angle(PCA_PIN_SERVO_1, min_servo_position);
        //Serial.println("Servo at min position");
      }
      break;
    case 1:
      
      long elapsed_servo_update = millis() - last_servo_update;
      if (elapsed_servo_update > servo_update_period)
      {
        // Serial.print("Current servo position: ");
        // Serial.println((servo_current_position));         
        last_servo_update = millis();
        set_servo_angle(PCA_PIN_SERVO_1, servo_current_position);
        servo_current_position = servo_current_position + servo_step;

        if (servo_current_position <= min_servo_position)
        {
          servo_step = abs(servo_step);
        }
        if (servo_current_position >= max_servo_position)
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
      if (servo_move_index_2 < servo_move_count_2 && ((elapsed > servo_start_array_2[servo_move_index_2]) && (elapsed < servo_stop_array_2[servo_move_index_2])))
      {
        set_servo_angle(PCA_PIN_SERVO_2, max_servo_position_2);
        //Serial.println("Servo at max position");
      }
      else if (servo_move_index < servo_move_count && (elapsed > servo_stop_array_2[servo_move_index_2]))
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

  // Control stepper
  if (run_state && !stepper_state && stepper_time_index < stepper_cycle_count && ((elapsed > stepper_start_array[stepper_time_index]) && (elapsed < stepper_stop_array[stepper_time_index])))
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

  // // Drive each PWM in a 'wave'
  // for (uint16_t i=0; i<4096; i += 8) {
  //   for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) {
  //     pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
  //   }
  // }

// Below is only needed if not interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) && ((USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) || (USE_MP3_REFILL_MEANS == USE_MP3_Polled))

  MP3player.available();
#endif

  if (Serial.available())
  {
    parse_menu(Serial.read()); // get command from serial input
  }

  // delay(100); // slow the loop
}

uint32_t millis_prv;

//------------------------------------------------------------------------------
/**
 * \brief Decode the Menu.
 *
 * Parses through the characters of the users input, executing corresponding
 * MP3player library functions and features then displaying a brief menu and
 * prompting for next input command.
 */
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
    MP3player.stopTrack();

    // if 1-9, play corresponding track
  }
  else if (key_command >= '1' && key_command <= '9')
  {
    // convert ascii numbers to real numbers
    key_command = key_command - 48;

#if USE_MULTIPLE_CARDS
    sd.chvol(); // assign desired sdcard's volume.
#endif
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

    // if +/- to change volume
  }
  else if ((key_command == '-') || (key_command == '+'))
  {
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

    // if < or > to change Play Speed
  }

  else if (key_command == 'h')
  {
    help();
  }
  else if (key_command == 'l')
  {
    manual_led_state = !manual_led_state;
    if (manual_led_state)
    {
      Serial.println("manual led on");
      turn_on_led();
      // delay(5000) ; 
      // servo_continuous(PCA_PIN_SERVO_1, 1);
    }
    else
    {
      Serial.println("manual led off");
      turn_off_led();
      // servo_continuous(PCA_PIN_SERVO_1, -1);
    }
  }
  else if (key_command == 'L')
  {
    manual_led_state_2 = !manual_led_state_2;
    if (manual_led_state_2)
    {
      Serial.println("manual led2 on");
      turn_on_led_n(2);
      // servo_continuous(PCA_PIN_SERVO_1, 1);
    }
    else
    {
      Serial.println("manual led2 off");
      turn_off_led_n(2);
      // servo_continuous(PCA_PIN_SERVO_1, -1);
    }
  }  
  else if (key_command == 'w')
  {
    servo_angle_active = !servo_angle_active;
  }
  else if (key_command == 'W')
  {
    servo_angle_active_2 = !servo_angle_active_2;
  }  
  else if (key_command == 'r')
  {
    Serial.println("manual ramp 1");
    do_ramp_led = !do_ramp_led;
  }  
  else if (key_command == 'R')
  {
    Serial.println("manual ramp 2");
    do_ramp_led_2 = !do_ramp_led_2;
  }  
  else if (key_command == 'f')
  {
    Serial.println("manual fade out 1");
    fade_out_led_1 = !fade_out_led_1;
    pwm_ramp = 2048 ;
  }  
  else if (key_command == 'F')
  {
    Serial.println("manual fade out 2");
    fade_out_led_2 = !fade_out_led_2;
    pwm_ramp_2 = 2048 ;
  }      
  else if (key_command == 'p')
  {
    set_servo_angle(PCA_PIN_SERVO_1, min_servo_position);
    Serial.println("Servo at min position");
  }
  else if (key_command == 'P')
  {
    set_servo_angle(PCA_PIN_SERVO_1, max_servo_position);
    Serial.println("Servo at max position");
  }
  else if (key_command == 'o')
  {
    set_servo_angle(PCA_PIN_SERVO_2, min_servo_position_2);
    Serial.println("Servo 2 at min position");
  }
  else if (key_command == 'O')
  {
    set_servo_angle(PCA_PIN_SERVO_2, max_servo_position_2);
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

//------------------------------------------------------------------------------
/**
 * \brief Print Help Menu.
 *
 * Prints a full menu of the commands available along with descriptions.
 */
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
