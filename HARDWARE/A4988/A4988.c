#include "A4988.h"
#include "timer.h"

int pulse_period = DEFAULT_PLUS_PERIOD;
int pluse_num = 0;
bool runpluse_over = true;
const int STEPS_PER_REV = 200;
void initA4988(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;//GPIO�˿�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ������

	TIM3_Int_Init(10,7200);  //1ms
	
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
	(direction == DIR_A4988) ? setDirection(direction) : 0 ;
	setSteppluse(1);
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

/*����1ms��ʱ����*/
void stepPluse()
{
	if(runpluse_over == false)
	{		
			static int cnt = 0;
			if(cnt < pulse_period)//����������
			{
				STEP_A4988 = 1;
			}else if(cnt >= pulse_period)
			{
				STEP_A4988 = 0;
				
				if(cnt >= 2*pulse_period)//�趨��������
				{
					cnt = 0;
					pluse_num--;
					if(pluse_num <= 0)
					{
						pluse_num = 0;
						runpluse_over = true;
					}
				}
			}
			cnt++;
	}
}

/*�����µ��������� ����ֵ-��ǰ����״̬ true-���óɹ�*/
bool setSteppluse(int plusenum)
{
	if(runpluse_over)
	{
		pluse_num = plusenum;
		runpluse_over = false;
	}
	return runpluse_over;
}

/*ms*/
int setPluseperid(int pluseperid)
{
	return pulse_period = pluseperid <= MIN_PLUS_PERIOD ? MIN_PLUS_PERIOD : pluseperid;;
}

inline bool getRunplusestatue()
{
	return runpluse_over;
}