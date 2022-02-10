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

    void set_servo_us(uint8_t n_servo, int microsec)
    {
        /**
         * @brief min value ~ 400 us, max value 2200 us, center: 1300
         * 
         */
        PCA2.writeMicroseconds(n_servo, microsec);
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
        set_servo_us(PCA2_PIN_SERVO_1, servo_default_position_1);
        set_servo_us(PCA2_PIN_SERVO_2, servo_default_position_2);
        set_servo_us(PCA2_PIN_SERVO_3, servo_default_position_3);
        set_servo_us(PCA2_PIN_SERVO_4, servo_default_position_4);
        servo_current_position_1 = servo_default_position_1;
        servo_current_position_2 = servo_default_position_2;
        servo_current_position_3 = servo_default_position_3;        
        servo_current_position_4 = servo_default_position_4;

    }

    void all_servos_min () { 
        servo_current_position_1 = min_servo_position_1;
        servo_current_position_2 = min_servo_position_2;
        servo_current_position_3 = min_servo_position_3;
        servo_current_position_4 = min_servo_position_4;

        set_servo_us(PCA2_PIN_SERVO_1, servo_current_position_1);
        set_servo_us(PCA2_PIN_SERVO_2, servo_current_position_2);   
        set_servo_us(PCA2_PIN_SERVO_3, servo_current_position_3);        
        set_servo_us(PCA2_PIN_SERVO_4, servo_current_position_4);        

    }    
    
    void all_servos_max () { 
        servo_current_position_1 = max_servo_position_1;
        servo_current_position_2 = max_servo_position_2;
        servo_current_position_3 = max_servo_position_3;
        servo_current_position_4 = max_servo_position_4;

        set_servo_us(PCA2_PIN_SERVO_1, servo_current_position_1);
        set_servo_us(PCA2_PIN_SERVO_2, servo_current_position_2);     
        set_servo_us(PCA2_PIN_SERVO_3, servo_current_position_3);        
        set_servo_us(PCA2_PIN_SERVO_4, servo_current_position_4);        

    }


#endif