#include <stm32f10x.h>
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "A4988.h"

/*
版权所有:
作者：林愿留
*/

int main()
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
	
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
