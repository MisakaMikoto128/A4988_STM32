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

	while(1)
	{
			delay_ms(1000);   
			oneStep(CW);
	}
}
