
#ifndef __OLED_H__
#define __OLED_H__


/**********************************
包含头文件
**********************************/
#include "sys.h" 


/**********************************
PIN口定义
**********************************/
#define OLED_SCL_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SCL引脚
#define OLED_SCL_PORT                 GPIOB
#define OLED_SCL_PIN                  GPIO_Pin_5
#define OLED_SCL  										PBout(5)

#define OLED_SDA_GPIO_CLK_ENABLE      RCC_APB2Periph_GPIOB				//SDA引脚
#define OLED_SDA_PORT                 GPIOB
#define OLED_SDA_PIN                  GPIO_Pin_6
#define OLED_SDA  										PBout(6)


/**********************************
函数声明
**********************************/
void Oled_Init(void);																							//OLED初始化函数
void Oled_Clear_All(void);																				//OLED清全屏函数
void Oled_ShowString(uint8_t x,uint8_t y,char *chr);							//OLED显示字符串函数
void Oled_ShowCHinese(uint8_t x,uint8_t y,char *P);								//OLED显示中文函数
void Oled_ShowNum_2(uint8_t x,uint8_t y,uint8_t num);             //显示两位数字

#endif

