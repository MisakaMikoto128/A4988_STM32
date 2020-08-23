#include "A4988.h"

/*脉冲周期：ms*/
#define DEFAULT_PLUS_PERIOD 200
int pulse_period = DEFAULT_PLUS_PERIOD;
int pluse_num = 0;
bool runpluse_over = true;

void initA4988(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;//GPIO端口设置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化引脚

	SLEEP_A4988 = 0;
	STEP_A4988 	= 0;
	MS1_A4988 	= 0;
	MS2_A4988 	= 0;
	MS3_A4988 	= 0;
	DIR_A4988 	= 0;
	RESET_A4988 = 1;
	ENABLEA4988();	
}

void oneStep(int direction)
{
	setDirection(direction);
	
	//TODO
}



void setMicrostep(int mode)
{
	switch(mode)
	{
		case FULL_STEP			: MICROSTEP(0,0,0); break;
		case HALF_STEP			: MICROSTEP(1,0,0); break;
		case QUARTER_STEP  	: MICROSTEP(0,1,0); break;
		case EIGHTH_STEP   	: MICROSTEP(1,1,0); break;
		case SIXTEENTH_STEP	: MICROSTEP(1,1,1); break;
		default:break;
	}
}

/*置于1ms定时器中*/
void stepPluse()
{
	static bool pluseflag = 0;
	
	if(pluse_num-- <= 0)
	{
		pluse_num = 0;
		pluseflag = false;
		runpluse_over = true;
	}else
	{
		pluseflag = true;
	}
	
	
	static int cnt = 0;
	int halfperiod = pulse_period<<1;//除以2
	if(pluseflag)// on pluse
	{
		if(cnt < halfperiod)
		{
			STEP_A4988 = 1;
		}else if(cnt >= halfperiod)
		{
			STEP_A4988 = 0;
		}
		
		if(++cnt >= pulse_period)
		{
			cnt = 0;
		}
	}
}

bool setSteppluse(int plusenum)
{
	if(runpluse_over)
	{
		pluse_num = plusenum;
		runpluse_over = false;
	}
}


inline bool getRunplusestatue()
{
	return runpluse_over;
}