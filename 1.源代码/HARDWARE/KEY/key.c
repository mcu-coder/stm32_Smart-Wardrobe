
/**********************************
包含头文件
**********************************/
#include "key.h"
#include "delay.h"


/****
*******	KEY IO初始化
*****/
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK_ENABLE,ENABLE);								//使能端口时钟
	GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;														//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 											//设置成上拉输入
 	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);													//根据设定参数初始化
	GPIO_SetBits(KEY1_PORT,KEY1_PIN);						 												//IO口输出高
	
	RCC_APB2PeriphClockCmd(KEY2_GPIO_CLK_ENABLE,ENABLE);								//使能端口时钟
	GPIO_InitStructure.GPIO_Pin  = KEY2_PIN;														//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 											//设置成上拉输入
 	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);													//根据设定参数初始化
	GPIO_SetBits(KEY2_PORT,KEY2_PIN);						 												//IO口输出高
	
	RCC_APB2PeriphClockCmd(KEY3_GPIO_CLK_ENABLE,ENABLE);								//使能端口时钟
	GPIO_InitStructure.GPIO_Pin  = KEY3_PIN;														//引脚配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 											//设置成上拉输入
 	GPIO_Init(KEY3_PORT, &GPIO_InitStructure);													//根据设定参数初始化
	GPIO_SetBits(KEY3_PORT,KEY3_PIN);						 												//IO口输出高
}

/****
*******	按键处理函数
mode:0,不支持连续按;1,支持连续按;
*****/
u8 Chiclet_Keyboard_Scan(u8 mode)
{	 
	static u8 key_up=1;			//按键松开标志

	if(mode)  							//mode=1,支持连按
		key_up=1;

	if(key_up && (KEY1==0||KEY2==0||KEY3==0))
	{
		Delay_ms(10);					//去抖动 
		key_up=0;
		
		if(KEY1==0)						//按键1按下，返回1
			return 1;
		else if(KEY2==0)			//按键2按下，返回2
			return 2;
		else if(KEY3==0)			//按键3按下，返回3
			return 3;
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1)		//没有按键按下，松开标志位置1
	{
		key_up=1;
	}
	
	return 0;								// 无按键按下.返回0
}
