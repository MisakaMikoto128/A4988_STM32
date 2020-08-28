#include "sys.h"
#ifndef _A4988_H_
#define _A4988_H_

#include <stdbool.h>
#define SIMPLIFICATION 
/*引脚定义*/
#define SLEEP_A4988 	PAout(0)
#define STEP_A4988 		PAout(1)
#define MS1_A4988 		PAout(2)
#define MS2_A4988 		PAout(3)
#define MS3_A4988 		PAout(4)
#define DIR_A4988 		PAout(5)
#define ENABLE_A4988 	PAout(6)	//____	有上划线表明是低电平有效
#define RESET_A4988 	PAout(7)	//____




#define ENABLEA4988() 	ENABLE_A4988 = 0
#define DISABLEA4988() 	ENABLE_A4988 = 1

/*面对转轴观察*/
#define CW 	0		//clockwise 顺时针
#define CCW 1		//counter-clockwise 逆时针


/*Microstep Resolution*/
#define FULL_STEP				0x01	//default
#define HALF_STEP			  0x02
#define QUARTER_STEP    0x03
#define EIGHTH_STEP     0x04
#define SIXTEENTH_STEP  0x05
#define MICROSTEP(MS1,MS2,MS3) (MS1_A4988 = (MS1),MS2_A4988 = (MS2),MS3_A4988 = (MS3))

// Motor steps per rotation
extern const int STEPS_PER_REV;

void initA4988(void);

void oneStep(int direction);

void setMicrostep(int mode);

#define setDirection(direction) (DIR_A4988 = (direction)&0x01)  //X&0x01 根据X最低位使得X转换为bool值


/*脉冲周期：ms*/
#define DEFAULT_PLUS_PERIOD 2
#define MIN_PLUS_PERIOD 2
#define RUN_OVER true
extern int pulse_period;
//extern const int duty_cycle ;
/*置于1ms定时器中*/
void stepPluse();
bool getRunplusestatue();
bool setSteppluse(int plusenum);
int setPluseperid(int pluseperid);
#endif