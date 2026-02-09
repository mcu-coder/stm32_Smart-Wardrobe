

/**********************************
包含头文件
**********************************/
#include "motor_bujin.h"

/*
Step_Motor_Init();												//步进电机初始化
*/

/**********************************
变量定义
**********************************/
_Bool flag_bujin_foreward = 0;						//步进电机正转标志位
_Bool flag_bujin_reversal = 0;						//步进电机反转标志位
_Bool flag_bujin_state = 0;               //步进电机状态标志位


/****
*******步进电机控制引脚初始化函数
*****/
static void Step_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(STEP2_GPIO_CLK,ENABLE);				//使能端口时钟

	GPIO_InitStructure.GPIO_Pin  = STEP2_GPIO_PIN_A|STEP2_GPIO_PIN_B|STEP2_GPIO_PIN_C|STEP2_GPIO_PIN_D;		//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				//设置成推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 		//IO口速度为50MHz
 	GPIO_Init(STEP2_GPIO_PORT, &GPIO_InitStructure);				//根据设定参数初始化
	GPIO_ResetBits(STEP2_GPIO_PORT,STEP2_GPIO_PIN_A|STEP2_GPIO_PIN_B|STEP2_GPIO_PIN_C|STEP2_GPIO_PIN_D);	//输出低电平

}

/****
*******定时器初始化函数：
*****/
static void TIM1_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	STEP_TIM_APBxClock_FUN(STEP_TIM_CLK, ENABLE); 								//时钟使能
	
	//定时器初始化
	TIM_TimeBaseStructure.TIM_Period = 100; 											//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler = 720-1; 									//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM向上计数模式
	TIM_TimeBaseInit(STEP_TIM, &TIM_TimeBaseStructure); 					//根据指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(STEP_TIM,TIM_IT_Update,ENABLE ); 								//使能指定的定时器中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = STEP_TIM_IRQ;  					//定时器中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  		//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  					//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  															//初始化NVIC寄存器

	TIM_Cmd(STEP_TIM, ENABLE);  																	//使能定时器					 
}

/****
*******定时器中断服务函数
*****/
void STEP_TIM_IRQHandler(void)
{
	static u8 motor_bujin_count = 0;
	static u16 motor_step = 0;
	
	if(TIM_GetITStatus(STEP_TIM, TIM_IT_Update) != RESET)  						//检查定时器更新中断发生与否
	{
		TIM_ClearITPendingBit(STEP_TIM, TIM_IT_Update);  								//清除定时器更新中断标志

		switch(motor_step % 8)								//步进电机八步解析
		{
			case 0:	STEP2_A=1; STEP2_B=0; STEP2_C=0; STEP2_D=0; break;
			case 1:	STEP2_A=1; STEP2_B=1; STEP2_C=0; STEP2_D=0; break;
			case 2:	STEP2_A=0; STEP2_B=1; STEP2_C=0; STEP2_D=0; break;
			case 3:	STEP2_A=0; STEP2_B=1; STEP2_C=1; STEP2_D=0; break;
			case 4:	STEP2_A=0; STEP2_B=0; STEP2_C=1; STEP2_D=0; break;
			case 5:	STEP2_A=0; STEP2_B=0; STEP2_C=1; STEP2_D=1; break;
			case 6:	STEP2_A=0; STEP2_B=0; STEP2_C=0; STEP2_D=1; break;
			case 7:	STEP2_A=1; STEP2_B=0; STEP2_C=0; STEP2_D=1; break;	
		}

		if(flag_bujin_foreward == 1)					//步进电机正转过程
		{
			motor_bujin_count++;
			if(motor_bujin_count > MOTOR_SPEED)
			{
				motor_bujin_count = 0;
				if(motor_step < (MOTOR_ANGLE/180.0*256) * 8)
					motor_step++;
				else
				{
					flag_bujin_foreward = 0;
					flag_bujin_state = 1;
				}
			}
		}
		else if(flag_bujin_reversal == 1)			//步进电机反转过程
		{
			motor_bujin_count++;
			if(motor_bujin_count > MOTOR_SPEED)
			{
				motor_bujin_count = 0;
				if(motor_step > 0)
					motor_step--;
				else
				{
					flag_bujin_reversal = 0;
					flag_bujin_state = 0;
				}
			}
		}
		else																	//步进电机停止
		{
			motor_bujin_count = 0;
			STEP2_A=0; STEP2_B=0; STEP2_C=0; STEP2_D=0;
		}
	}
}

/****
*******步进电机初始化函数
*****/	
void Step_Motor_Init(void)
{
	TIM1_Init();
	Step_GPIO_Init();
}



