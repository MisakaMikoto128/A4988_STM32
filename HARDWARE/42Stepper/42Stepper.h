#ifndef _42STEPPER_H_
#define _42STEPPER_H_
#include "A4988.h"
#include <stdbool.h>

#define MINANGLE 1.8f
#define MINMOVE 1.8f
#define MAXROTATEANGLE (360*12)
#define MINROTATEANGLE (0)

#define SYS_MOVE_DIV 0.02f		/*系统精度 旋转最小角度移动的距离*/
#define MINANGLE_NUM_OF1MM (1.0f/SYS_MOVE_DIV)
extern float rotate_angle_now;


bool checkangle(float angle);
bool move1mm();

bool moveNmm(float distance);

bool rotateMinangle();

bool rotateAngle(float angle);

bool rotateNminangle(int num_angle);
#endif //!_42STEPPER_H_