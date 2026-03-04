
#ifndef __ADC_H
#define __ADC_H


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
PIN口定义
**********************************/
#define ADC1_0_GPIO_CLK_ENABLE      		RCC_APB2Periph_GPIOA				//ADC1_0引脚
#define ADC1_0_CHANNEL_CLK_ENABLE      	RCC_APB2Periph_ADC1
#define ADC1_0_PORT                			GPIOA
#define ADC1_0_PIN                  		GPIO_Pin_0
#define ADC1_1_PIN                  		GPIO_Pin_1
#define ADC1_2_PIN                  		GPIO_Pin_2
#define ADC1_0  												ADC1


/**********************************
函数声明
**********************************/
void Adc_Init(void);																								//ADC初始化函数
u16  Get_Adc(u8 ch); 																								//获得ADC值函数
u16 Get_Adc_Average(u8 ch,u8 times); 																//获得ADC平均值函数


#endif 

