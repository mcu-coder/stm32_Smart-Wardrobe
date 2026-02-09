
/**********************************
包含头文件
**********************************/
#include "gpio.h"


/****
*******	LED IO初始化
*****/    
void Gpio_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);			    //使能端口时钟

	GPIO_InitStructure.GPIO_Pin  = LEDS_GPIO_PIN;  						//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
 	GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	GPIO_SetBits(LEDS_GPIO_PORT,LEDS_GPIO_PIN);  							//IO口输出高

	GPIO_InitStructure.GPIO_Pin  = LED_PIN; 									//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
 	GPIO_Init(LED_PORT, &GPIO_InitStructure);									//根据设定参数初始化
	GPIO_SetBits(LED_PORT,LED_PIN); 				 									//IO口输出高

	GPIO_InitStructure.GPIO_Pin  = BEEP_PIN; 									//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 					//设置成推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 			//IO口速度为50MHz
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);								//根据设定参数初始化
	GPIO_ResetBits(BEEP_PORT,BEEP_PIN); 				 							//IO口输出低
	
	GPIO_InitStructure.GPIO_Pin  = IRED_GPIO_PIN;  						//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		//设置成浮空输入
 	GPIO_Init(IRED_GPIO_PORT, &GPIO_InitStructure);						//根据设定参数初始化
	
	GPIO_InitStructure.GPIO_Pin  = RELAY_ZM_PIN|RELAY_XD_PIN|RELAY_JR_PIN|RELAY_TF_PIN;	//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				//设置成推挽输出
 	GPIO_Init(RELAY_ZM_PORT, &GPIO_InitStructure);								//根据设定参数初始化
	GPIO_ResetBits(RELAY_ZM_PORT,RELAY_ZM_PIN|RELAY_XD_PIN|RELAY_JR_PIN|RELAY_TF_PIN);	//IO口输出高
	
	GPIO_InitStructure.GPIO_Pin  = DOOR_PIN|SMOG_PIN;  			//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//设置成推挽输出
 	GPIO_Init(DOOR_PORT, &GPIO_InitStructure);							//根据设定参数初始化
}

