#include <stm32f10x.h>
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "A4988.h"

/*
��Ȩ����:
���ߣ���Ը��
*/

int main()
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
	
	initA4988();

	int t = 1;
	setDirection(CCW);


	while(1)
	{  
//		setSteppluse(1);
		oneStep(CW);
		delay_ms(1000);
		
//			oneStep(CW);
		
		// Spin motor one rotation slowly
		//for(int x = 0; x < STEPS_PER_REV; x++) {
//			STEP_A4988 = 1; 
//			delay_ms(t); 
//			STEP_A4988 = 0;
//			delay_ms(t); 
		//}
		//delay_ms(1000); 
	}
}
