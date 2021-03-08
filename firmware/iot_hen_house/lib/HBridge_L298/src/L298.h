#ifndef L298_h
#define L298_h

/*
    Configuration based on your hardware
*/

///Wiring L298 definition

//Out1 & Out2 controls
#define in1 5//GPIO5, label D1
#define in2 4//GPIO4, labed D2
#define EnA //hardware Pulled up 

//Out1 & Out2 controls
//#define in3 //not used
//#define in4 //not used
//#define Enb //not used

enum mode{
    STEPPER = 0,
    SINGLE_DC = 1,
    DOUBLE_DC = 2,
};

typedef enum{
    CW,
    CCW,
    STOP
} motor_state_t;

void init_L298(mode dr_mode);
void stop_motor();
void move_motor(motor_state_t st);

#endif