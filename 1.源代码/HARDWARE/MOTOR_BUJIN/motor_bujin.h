

#ifndef __MOTOR_BUJIN_H
#define __MOTOR_BUJIN_H


/**********************************
包含头文件
**********************************/
#include "sys.h" 


/**********************************
宏定义
**********************************/
#define           MOTOR_SPEED			            0					//电机转速0-10
#define           MOTOR_ANGLE			            180				//电机旋转角度

#define           STEP_TIM                    TIM1
#define           STEP_TIM_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define           STEP_TIM_CLK                RCC_APB2Periph_TIM1
#define           STEP_TIM_IRQ                TIM1_UP_IRQn
#define           STEP_TIM_IRQHandler         TIM1_UP_IRQHandler

#define           STEP2_GPIO_CLK              RCC_APB2Periph_GPIOB
#define           STEP2_GPIO_PORT             GPIOB
#define           STEP2_GPIO_PIN_A            GPIO_Pin_15
#define           STEP2_GPIO_PIN_B            GPIO_Pin_14
#define           STEP2_GPIO_PIN_C            GPIO_Pin_13
#define           STEP2_GPIO_PIN_D            GPIO_Pin_12
#define           STEP2_A                     PBout(15)
#define           STEP2_B                     PBout(14)
#define           STEP2_C                     PBout(13)
#define           STEP2_D                     PBout(12)


/**********************************
函数声明
**********************************/
void Step_Motor_Init(void);			//步进电机初始化


#endif

