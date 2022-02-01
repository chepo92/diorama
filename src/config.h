#define DIORAMA_NUMBER 5

// Individual Settings for each Diorama
#if DIORAMA_NUMBER == 1 // el establo

int max_playtime = 128; // 

// steppers
int stepper_cycle_count = 0;
int stepper_start_array[] = {0};
int stepper_stop_array[] = {0};

int steps_cw;
int steps_ccw;

// LED lights

int ramp_time_divisor = 5; 

int light1_cycle_count = 1;
int light1_start_array[] = {0};
int light1_stop_array[] = {115};

int light2_cycle_lenght = 1;
int light2_start_array[] = {46};
int light2_stop_array[] = {115};

// Servos
int servo_move_count = 1;
int servo_start_array[] = {46};
int servo_stop_array[] = {56};

int servo_move_count_2 = 1;
int servo_start_array_2[] = {33};
int servo_stop_array_2[] = {37};

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


int max_playtime = 100; // 

// steppers
int stepper_cycle_count = 1;
int stepper_start_array[] = {20};
int stepper_stop_array[] =  {40};

int steps_cw;
int steps_ccw;

// LED lights

int ramp_time_divisor = 5; 

int light1_cycle_count = 1;
int light1_start_array[] = {0};
int light1_stop_array[] = {99};

int light2_cycle_lenght = 0;
int light2_start_array[] = {0};
int light2_stop_array[] = {0};

// Servos
int servo_move_count = 2;
int servo_start_array[] = {3, 63};
int servo_stop_array[] = {15, 73};

int servo_move_count_2 = 3;
int servo_start_array_2[] = {17, 47, 77};
int servo_stop_array_2[] = {22, 59, 82};

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

unsigned int last_servo_update;
unsigned int last_servo_update_2;
unsigned int servo_update_period = 40;
unsigned int servo_update_period_2 = 40;

uint8_t servo_step = 1;
uint8_t servo_step_2 = 1;

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