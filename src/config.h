// #ifndef ARDUINO_H
// #define ARDUINO_H
// #endif
// #ifndef GLOBALS_H
// #define GLOBALS_H
// #endif

// #ifndef SERVO_CONTROL_H
// #define SERVO_CONTROL_H
// #endif

#ifndef CONFIG_H
#define CONFIG_H

#define DIORAMA_NUMBER 4  

// Individual Settings for each Diorama
#if DIORAMA_NUMBER == 1 // El establo

int max_playtime = 125; // 1:35 (60+35)

// steppers
int stepper1_cycle_count = 1;
int stepper1_start_array[] = {61}; //  {1} ; //
int stepper1_stop_array[] = {94}; //  {34} ;// 

int stepper1_steps_cw  = 20000; // No pasarme de 32mil o usar var long
int stepper1_steps_ccw = 20000 ;

boolean stepper1_start_direction = 0 ;  // Direccion que avanza el stepper

// LED lights, rampla de luz
int ramp_time_divisor = 5; 
int ramp_pwm_step = 10;  

//  Mamá
int light1_cycle_lenght = 1;
long light1_start_array[] = {5};
long light1_stop_array[] = {118};

// Buey
int light2_cycle_lenght = 1;
long light2_start_array[] = {32};
long light2_stop_array[] = {115};

// Ovejaperro
int light3_cycle_lenght = 1;
int light3_start_array[] = {18};
int light3_stop_array[] = {110};

// Ocas
int light4_cycle_lenght = 1;
int light4_start_array[] = {60};
int light4_stop_array[] = {115};

// Light 5 is backlight
int light5_cycle_lenght = 1;
int light5_start_array[] = {0};
int light5_stop_array[] = {120};


// Servos
// Perroveja
int servo_move_count_1 = 1;
int servo_start_array_1[] = {19};
int servo_stop_array_1[] = {39};

int servo_default_position_1 = 1500;
int min_servo_position_1 = 1300;
int max_servo_position_1 = 1500;


// Buey
int servo_move_count_2 = 3;
int servo_start_array_2[] = {33, 50, 72};
int servo_stop_array_2[] = {45, 67, 84};

int servo_default_position_2 = 1500;
int min_servo_position_2 = 1300;
int max_servo_position_2 = 1500;

//  
int servo_move_count_3 = 0;
int servo_start_array_3[] = {0};
int servo_stop_array_3[] = {0};

// 
int servo_move_count_4 = 0;
int servo_start_array_4[] = {0};
int servo_stop_array_4[] = {0};

/* Servo Control */
int servo_move_type_1 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_3 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_4 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};


// Not used
int servo_default_position_3 = 1300;
int servo_default_position_4 = 1300;


int min_servo_position_3 = 1300;
int max_servo_position_3 = 1500;

int min_servo_position_4 = 1300;
int max_servo_position_4 = 1500;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 450; // pwm 180°

unsigned long last_servo_update_1;
unsigned long last_servo_update_2;
unsigned long last_servo_update_3;
unsigned long last_servo_update_4;

// Mientras mayor el numero, mas lento se mueve
unsigned long servo_update_period_1 = 5; 
unsigned long servo_update_period_2 = 5;
unsigned long servo_update_period_3 = 5;
unsigned long servo_update_period_4 = 5;

//Steps de cada servo, mientras mayor, mas rapido se mueve
int servo_step_1 = 1;
int servo_step_2 = 1;
int servo_step_3 = 1;
int servo_step_4 = 1;

#elif DIORAMA_NUMBER == 2 // Se va la lancha

long max_playtime = 120; // 1:50 = 60+50

// steppers
int stepper1_cycle_count = 1;
long stepper1_start_array[] = {19};
long stepper1_stop_array[] = {48};

int stepper1_steps_cw  = 2000; 
int stepper1_steps_ccw = 2000 ; 

// LED lights

int ramp_time_divisor = 5; 
int ramp_pwm_step = 10;  

//  Pescador
int light1_cycle_lenght = 1;
long light1_start_array[] = {5};
long light1_stop_array[] = {114};

// Barco
int light2_cycle_lenght = 1;
long light2_start_array[] = {29};
long light2_stop_array[] = {103};

// Peces
int light3_cycle_lenght = 1;
int light3_start_array[] = {49};
int light3_stop_array[] = {100};

// Faro
int light4_cycle_lenght = 1;
int light4_start_array[] = {3};
int light4_stop_array[] = {106};

// Light 5 is backlight
int light5_cycle_lenght = 1;
int light5_start_array[] = {0};
int light5_stop_array[] = {118};

// Servos
// Peces
int servo_move_count_1 = 1;
int servo_start_array_1[] = {49};
int servo_stop_array_1[] = {75};

// Remos pescador
int servo_move_count_2 = 1;
int servo_start_array_2[] = {10};
int servo_stop_array_2[] = {114};

// Not used
int servo_move_count_3 = 0;
int servo_start_array_3[] = {0};
int servo_stop_array_3[] = {0};

// Not used
int servo_move_count_4 = 0;
int servo_start_array_4[] = {0};
int servo_stop_array_4[] = {0};

/* Servo Control */
int servo_move_type_1 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_3 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_4 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

int servo_default_position_1 = 1500;
int servo_default_position_2 = 1300;
int servo_default_position_3 = 1300;
int servo_default_position_4 = 1300;

int min_servo_position_1 = 1300;
int max_servo_position_1 = 1500;

int min_servo_position_2 = 1300;
int max_servo_position_2 = 1500;

int min_servo_position_3 = 1300;
int max_servo_position_3 = 1500;

int min_servo_position_4 = 1300;
int max_servo_position_4 = 1500;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 450; // pwm 180°

unsigned long last_servo_update_1;
unsigned long last_servo_update_2;
unsigned long last_servo_update_3;
unsigned long last_servo_update_4;

unsigned long servo_update_period_1 = 5;
unsigned long servo_update_period_2 = 5;
unsigned long servo_update_period_3 = 5;
unsigned long servo_update_period_4 = 5;

int servo_step_1 = 1;
int servo_step_2 = 1;
int servo_step_3 = 1;
int servo_step_4 = 1;

#elif DIORAMA_NUMBER == 3 // Arrurru 

long max_playtime = 100; // 

// steppers
// Caracol
int stepper1_cycle_count =       1;
long stepper1_start_array[] = {29};
long stepper1_stop_array[] =  {65};

int stepper1_steps_cw = 100*20; 
int stepper1_steps_ccw = 100*20 ; 

boolean stepper1_start_direction = 0 ; 
unsigned long step_period_1 = 10 ; 

// Arbol   
int  stepper2_cycle_count   =      1;
long stepper2_start_array[] =    {12};
long stepper2_stop_array[]  =    {55};

int stepper2_steps_cw  = 100*75; 
int stepper2_steps_ccw = 100*75; 

boolean stepper2_start_direction = 0 ; 
unsigned long step_period_2 = 3 ;


// LED lights

int ramp_time_divisor = 5; 
int ramp_pwm_step = 10;  

// Caballitos y Luna 
int light1_cycle_lenght = 1;
long light1_start_array[] = {8};
long light1_stop_array[] = {90};

// Pez caracol
int light2_cycle_lenght = 1;
long light2_start_array[] = {29};
long light2_stop_array[] = {78};

// Arbol
int light3_cycle_lenght = 1;
int light3_start_array[] = {12};
int light3_stop_array[] = {84};

// Mamá
int light4_cycle_lenght = 1;
int light4_start_array[] = {3};
int light4_stop_array[] = {95};

// Light 5 is backlight
int light5_cycle_lenght = 1;
int light5_start_array[] = {0};
int light5_stop_array[] = {98};

/* Servo Control */
// Mamá
int servo_move_count_1 = 1;
long servo_start_array_1[] = {5};
long servo_stop_array_1[] = {95};

int servo_move_count_2 = 0;
long servo_start_array_2[] = {0};
long servo_stop_array_2[] = {0};

// 
int servo_move_count_3 = 0;
int servo_start_array_3[] = {0};
int servo_stop_array_3[] = {0};

// 
int servo_move_count_4 = 0;
int servo_start_array_4[] = {0};
int servo_stop_array_4[] = {0};

/* Servo Control */
int servo_move_type_1 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_3 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_4 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

int servo_default_position_1 = 1500;
int servo_default_position_2 = 1300;
int servo_default_position_3 = 1300;
int servo_default_position_4 = 1300;

int min_servo_position_1 = 1300;
int max_servo_position_1 = 1500;

int min_servo_position_2 = 1300;
int max_servo_position_2 = 1500;

int min_servo_position_3 = 1300;
int max_servo_position_3 = 1500;

int min_servo_position_4 = 1300;
int max_servo_position_4 = 1500;

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 480; // pwm 180°

unsigned long last_servo_update_1;
unsigned long last_servo_update_2;
unsigned long last_servo_update_3;
unsigned long last_servo_update_4;

unsigned long servo_update_period_1 = 5;
unsigned long servo_update_period_2 = 5;
unsigned long servo_update_period_3 = 5;
unsigned long servo_update_period_4 = 5;

int servo_step_1 = 1;
int servo_step_2 = 1;
int servo_step_3 = 1;
int servo_step_4 = 1;

#elif DIORAMA_NUMBER == 4 // Cucu

long max_playtime = 105; // 

// steppers
// Pajaros
int  stepper1_cycle_count   =      1;
long stepper1_start_array[] =    {3};
long stepper1_stop_array[]  =  {95};

int stepper1_steps_cw  = 100*15; 
int stepper1_steps_ccw = 100*15 ; 

boolean stepper1_start_direction = 0 ; 
unsigned long step_period_1 = 1 ;

// Conejo 
int  stepper2_cycle_count   =      1;
long stepper2_start_array[] =    {25};
long stepper2_stop_array[]  =    {33};

int stepper2_steps_cw  = 100*8; 
int stepper2_steps_ccw = 100*8 ; 

boolean stepper2_start_direction = 0 ; 
unsigned long step_period_2 = 1 ;

// LED lights
int ramp_time_divisor = 5; 
int ramp_pwm_step = 10;  

//  buho
int light1_cycle_lenght = 1;
long light1_start_array[] = {12};
long light1_stop_array[] = {80};

// conejito 
int light2_cycle_lenght = 1;
long light2_start_array[] = {24};
long light2_stop_array[] = {80};

// ciervos
int light3_cycle_lenght = 1;
int light3_start_array[] = {25};
int light3_stop_array[] = {80};

// Cucu
int light4_cycle_lenght = 1;
int light4_start_array[] = {2};
int light4_stop_array[] = {86};

// Light 5 is backlight
int light5_cycle_lenght = 1;
int light5_start_array[] = {0};
int light5_stop_array[] = {86};


// Servos
// Huemul arriba
int min_servo_position_1 = 1200;
int max_servo_position_1 = 1800;
int servo_default_position_1 = 1200;

int servo_move_count_1 = 2;
int servo_start_array_1[] = {34, 62};
int servo_stop_array_1[] = {48, 76};

// Huemul abajo
int min_servo_position_2 = 1300;
int max_servo_position_2 = 1800;
int servo_default_position_2 = 1300;

int servo_move_count_2 = 2;
int servo_start_array_2[] = {25, 48};
int servo_stop_array_2[] = {32, 64};

//  cucu / buho 
int min_servo_position_3 = 1200;
int max_servo_position_3 = 1700;
int servo_default_position_3 = 1700;

int servo_move_count_3 = 2;
int servo_start_array_3[] = {13, 34};
int servo_stop_array_3[] = {24, 43};

// 
int min_servo_position_4 = 1300;
int max_servo_position_4 = 1500;
int servo_default_position_4 = 1300;

int servo_move_count_4 = 0;
int servo_start_array_4[] = {0};
int servo_stop_array_4[] = {0};

/* Servo Control */
int servo_move_type_1 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_3 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_4 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 450; // pwm 180°

unsigned long last_servo_update_1;
unsigned long last_servo_update_2;
unsigned long last_servo_update_3;
unsigned long last_servo_update_4;

unsigned long servo_update_period_1 = 5;
unsigned long servo_update_period_2 = 5;
unsigned long servo_update_period_3 = 5;
unsigned long servo_update_period_4 = 5;

int servo_step_1 = 1;
int servo_step_2 = 1;
int servo_step_3 = 1;
int servo_step_4 = 1;

#elif DIORAMA_NUMBER == 5 // Pajarito 

// in seconds
int max_playtime = 100; 

// steppers
// Peces
int stepper1_cycle_count = 2;
int stepper1_start_array[] = {17, 45};
int stepper1_stop_array[] =  {30, 59};

int stepper1_steps_cw = 100*20; 
int stepper1_steps_ccw = 100*20 ; 

boolean stepper1_start_direction = 0 ; 
unsigned long step_period_1 = 1 ; 

int stepper2_cycle_count = 0;
int stepper2_start_array[] = {0};
int stepper2_stop_array[] =  {0};

int stepper2_steps_cw = 0; 
int stepper2_steps_ccw = 0 ; 

boolean stepper2_start_direction = 0 ; 
unsigned long step_period_2 = 1 ;

// LED lights

int ramp_time_divisor = 5; 
int ramp_pwm_step = 10; 

// Peces 
int light1_cycle_lenght = 2;
int light1_start_array[] = {17, 45};
int light1_stop_array[] = {30, 59};

// Llamas
int light2_cycle_lenght = 2;
int light2_start_array[] = {5, 33};
int light2_stop_array[] = {15, 44};

// Madre
int light3_cycle_lenght = 1;
int light3_start_array[] = {16};
int light3_stop_array[] = {98};

// Pajarito
int light4_cycle_lenght = 1;
int light4_start_array[] = {4};
int light4_stop_array[] = {78};

// Light 5 is backlight
int light5_cycle_lenght = 1;
int light5_start_array[] = {0};
int light5_stop_array[] = {99};


// Servos

// Mama
int min_servo_position_1 = 2200;
int max_servo_position_1 = 2500;
int servo_default_position_1 = 2500;

int servo_move_count_1 = 3;
int servo_start_array_1[] = {17, 45, 75};
int servo_stop_array_1[] = {32, 59, 98};

// Pajarito
int min_servo_position_2 = 1900;
int max_servo_position_2 = 2200;
int servo_default_position_2 = 2200;

int servo_move_count_2 = 3;
int servo_start_array_2[] = {5, 33 , 62};
int servo_stop_array_2[] = {19, 48 , 77 };

// Llamas Der
int min_servo_position_3 = 1800;
int max_servo_position_3 = 2200;
int servo_default_position_3 = 1800;

int servo_move_count_3 = 2;
int servo_start_array_3[] = {5, 33};
int servo_stop_array_3[] = {15, 44};

// Llamas Izq
int min_servo_position_4 =  400;
int max_servo_position_4 = 700;
int servo_default_position_4 = 400;

int servo_move_count_4 = 2;
int servo_start_array_4[] = {5 , 33};
int servo_stop_array_4[] = {15, 44};

/* Servo Control */
int servo_move_type_1 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_3 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_4 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};

unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 450; // pwm 180°

unsigned long last_servo_update_1;
unsigned long last_servo_update_2;
unsigned long last_servo_update_3;
unsigned long last_servo_update_4;

unsigned long servo_update_period_1 = 5;
unsigned long servo_update_period_2 = 5;
unsigned long servo_update_period_3 = 5;
unsigned long servo_update_period_4 = 5;

int servo_step_1 = 1;
int servo_step_2 = 1;
int servo_step_3 = 1;
int servo_step_4 = 1;

#elif DIORAMA_NUMBER == 6 // Mira niñita 

long max_playtime = 150; // 120+30

// steppers
int stepper1_cycle_count = 1;
long stepper1_start_array[] = {45}; //45
long stepper1_stop_array[] = {64};  // 64

int stepper1_steps_cw  = 9000; 
int stepper1_steps_ccw = 9000 ; 

boolean stepper1_start_direction = 0 ; 
unsigned long step_period_1 = 1 ; 

int stepper2_cycle_count = 0;
int stepper2_start_array[] = {0};
int stepper2_stop_array[] =  {0};

int stepper2_steps_cw = 0; 
int stepper2_steps_ccw = 0 ; 

boolean stepper2_start_direction = 0 ; 
unsigned long step_period_2 = 1 ;

// LED lights
int ramp_time_divisor = 5; 
int ramp_pwm_step = 10;  

//  perro
int light1_cycle_lenght = 1;
long light1_start_array[] = {65};
long light1_stop_array[] = {118};

// papa y niña
int light2_cycle_lenght = 1;
long light2_start_array[] = {11};
long light2_stop_array[] = {145};

// Peces voladores
int light3_cycle_lenght = 1;
int light3_start_array[] = {44};
int light3_stop_array[] = {135};

// Luna
int light4_cycle_lenght = 1;
int light4_start_array[] = {25};
int light4_stop_array[] = {130};

// Light 5 is backlight
int light5_cycle_lenght = 1;
int light5_start_array[] = {0};
int light5_stop_array[] = {145};

// Servos
// Perro
int min_servo_position_1 = 1000;
int max_servo_position_1 = 1800;
int servo_default_position_1 = 1800;

int servo_move_count_1 = 1;
int servo_start_array_1[] = {65};
int servo_stop_array_1[] = {77};

// Ballena
int min_servo_position_2 = 400;
int max_servo_position_2 = 2200;
int servo_default_position_2 = 400;

int servo_move_count_2 = 1;
int servo_start_array_2[] = {118};
int servo_stop_array_2[] = {145};

// 
int min_servo_position_3 = 1300;
int max_servo_position_3 = 1500;
int servo_default_position_3 = 1300;
 
int servo_move_count_3 = 0;
int servo_start_array_3[] = {0};
int servo_stop_array_3[] = {0};

// 
int min_servo_position_4 = 1000;
int max_servo_position_4 = 1800;
int servo_default_position_4 = 1300;

int servo_move_count_4 = 0;
int servo_start_array_4[] = {0};
int servo_stop_array_4[] = {0};

/* Servo Control */
int servo_move_type_1 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_2 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_3 = 1; // 0 : initial, final; 1: move continuous.
int servo_move_type_4 = 1; // 0 : initial, final; 1: move continuous.

int servo_angles[] = {0};



unsigned int pos0_pwm = 100;   // pwm at 0°
unsigned int pos180_pwm = 450; // pwm 180°

unsigned long last_servo_update_1;
unsigned long last_servo_update_2;
unsigned long last_servo_update_3;
unsigned long last_servo_update_4;

unsigned long servo_update_period_1 = 5;
unsigned long servo_update_period_2 = 5;
unsigned long servo_update_period_3 = 5;
unsigned long servo_update_period_4 = 5;

int servo_step_1 = 1;
int servo_step_2 = 1;
int servo_step_3 = 1;
int servo_step_4 = 1;

#endif

#endif