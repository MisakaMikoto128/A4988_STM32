#include "42Stepper.h"
float rotate_angle_now = 0;

/*判断旋转相应角度后是否超出范围 angle是最小角度的整数倍*/
bool checkangle(float angle)
{
	float tmp = rotate_angle_now;
	if(DIR_A4988 == CW)
	{
		tmp += angle;
	}else
	{
		tmp -= angle;
	}
	return tmp <= MAXROTATEANGLE && tmp >= MINROTATEANGLE;
}

bool move1mm()
{
	rotateNminangle(MINANGLE_NUM_OF1MM);
}

/*distance - mm*/
bool moveNmm(float distance)
{
	int n = distance / SYS_MOVE_DIV;//需要旋转几个最小角度
	rotateNminangle(n);
}

bool rotateMinangle()
{
	rotateNminangle(1);
}

bool rotateAngle(float angle)
{
	int n = angle / MINANGLE;
	return rotateNminangle(n);
}


/*旋转n个最小角度*/
bool rotateNminangle(int num_angle)
{
	if(checkangle(num_angle*MINANGLE))
	{
		if(DIR_A4988 == CW)
		{
			rotate_angle_now += num_angle*MINANGLE;
		}else
		{
			rotate_angle_now -= num_angle*MINANGLE;
		}
		setSteppluse(num_angle);
		return true;
	}else
	{
		return false;
	}
}