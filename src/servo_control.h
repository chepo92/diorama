#include "Arduino.h"
// #include "globals.h"
// #include "config.h"

// #ifndef ARDUINO_H
// #define ARDUINO_H
// #endif
// #ifndef GLOBALS_H
// #define GLOBALS_H
// #endif
// #ifndef CONFIG_H
// #define CONFIG_H
// #endif
// #ifndef LED_CONTROL_H
// #define LED_CONTROL_H
// #endif

#ifndef SERVO_CONTROL_H
    #define SERVO_CONTROL_H


    void set_servo_angle(uint8_t n_servo, int angulo)
    {
        int duty;
        duty = map(angulo, 0, 180, pos0_pwm, pos180_pwm);
        PCA2.setPWM(n_servo, 0, duty);
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

    void servo_defaults()
    {
        set_servo_angle(PCA2_PIN_SERVO_1, servo_default_angle_1);
        set_servo_angle(PCA2_PIN_SERVO_2, servo_default_angle_2);
        servo_current_position_1 = servo_default_angle_1;
        servo_current_position_2 = servo_default_angle_2;
    }
    
    void all_servos_max () { 
        servo_current_position_1 = max_servo_position_1;
        servo_current_position_2 = max_servo_position_2;
        set_servo_angle(PCA2_PIN_SERVO_1, servo_current_position_1);
        set_servo_angle(PCA2_PIN_SERVO_2, servo_current_position_2);        
    }


#endif