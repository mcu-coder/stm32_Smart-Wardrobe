
#ifndef __KEY_H
#define __KEY_H


/**********************************
包含头文件
**********************************/
#include "sys.h" 


/**********************************
重定义关键词
**********************************/
#define KEY1_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB		//按键2引脚
#define KEY1_PORT                 GPIOB
#define KEY1_PIN                  GPIO_Pin_7
#define KEY1  										PBin(7)

#define KEY2_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB		//按键3引脚
#define KEY2_PORT                 GPIOB
#define KEY2_PIN                  GPIO_Pin_8
#define KEY2  										PBin(8)

#define KEY3_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB		//按键3引脚
#define KEY3_PORT                 GPIOB
#define KEY3_PIN                  GPIO_Pin_9
#define KEY3  										PBin(9)

/**********************************
函数声明
**********************************/
void Key_Init(void);																			//IO初始化
u8 Chiclet_Keyboard_Scan(u8 mode);  											//按键扫描函数


#endif

