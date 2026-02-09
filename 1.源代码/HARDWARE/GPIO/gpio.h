
#ifndef __GPIO_H
#define __GPIO_H


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
重定义关键词
**********************************/
#define LEDS_GPIO_PORT                GPIOC        	//最小系统LED
#define LEDS_GPIO_PIN                 GPIO_Pin_13
#define LED_SYS                       PCout(13)

#define BEEP_PORT                     GPIOB					//蜂鸣器引脚
#define BEEP_PIN                      GPIO_Pin_1
#define BEEP 									    		PBout(1)

#define LED_PORT                      GPIOB					//LED灯引脚
#define LED_PIN                       GPIO_Pin_0
#define LED 									    		PBout(0)

#define IRED_GPIO_PORT                GPIOB					//红外触发引脚
#define IRED_GPIO_PIN                 GPIO_Pin_15
#define IRED                          PBin(15)

#define SMOG_GPIO_CLK                 RCC_APB2Periph_GPIOA			
#define SMOG_PORT                     GPIOA
#define SMOG_PIN                      GPIO_Pin_3
#define SMOG 													PAin(3)

#define DOOR_GPIO_CLK                 RCC_APB2Periph_GPIOA			
#define DOOR_PORT                     GPIOA
#define DOOR_PIN                      GPIO_Pin_11
#define DOOR 													PAin(11)


#define RELAY_ZM_GPIO_CLK             RCC_APB2Periph_GPIOA				//继电器引脚
#define RELAY_ZM_PORT                 GPIOA
#define RELAY_ZM_PIN                  GPIO_Pin_4
#define RELAY_ZM 									    PAout(4)

#define RELAY_XD_GPIO_CLK             RCC_APB2Periph_GPIOA				//继电器引脚
#define RELAY_XD_PORT                 GPIOA
#define RELAY_XD_PIN                  GPIO_Pin_5
#define RELAY_XD 									    PAout(5)

#define RELAY_JR_GPIO_CLK             RCC_APB2Periph_GPIOA				//继电器引脚
#define RELAY_JR_PORT                 GPIOA
#define RELAY_JR_PIN                  GPIO_Pin_6
#define RELAY_JR 									    PAout(6)

#define RELAY_TF_GPIO_CLK             RCC_APB2Periph_GPIOA				//继电器引脚
#define RELAY_TF_PORT                 GPIOA
#define RELAY_TF_PIN                  GPIO_Pin_7
#define RELAY_TF 									    PAout(7)
/**********************************
函数声明
**********************************/
void Gpio_Init(void);																//GPIO初始化


#endif

