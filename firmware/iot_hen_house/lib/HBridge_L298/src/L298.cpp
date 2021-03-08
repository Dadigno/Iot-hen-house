#include "L298.h"
#include <Arduino.h>

motor_state_t motor_state;

void init_L298(mode dr_mode)
{
    if (dr_mode == SINGLE_DC)
    {
        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        motor_state = STOP;
    }else{
        //Other not supported
    }
}

void stop_motor()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    motor_state = STOP;
}

void move_motor(motor_state_t st)
{
    if (st == CW)
    {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        motor_state = st;
    }
    else if (st == CCW)
    {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        motor_state = st;
    }
}