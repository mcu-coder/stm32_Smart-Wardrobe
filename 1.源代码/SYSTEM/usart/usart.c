

/**********************************
包含头文件
**********************************/
//硬件驱动
#include "usart.h"

//C库
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/*
extern uint8_t usart1_buf[256];				//串口1接收数组
extern uint8_t usart2_buf[256];				//串口2接收数组
extern uint8_t usart3_buf[256];				//串口3接收数组

	if(USART1_WaitRecive() == 0)
	{
		if(strstr((char*)usart1_buf,"+CMT:") != NULL)
		{

		}

		USART1_Clear();
	}
*/

/**********************************
变量定义
**********************************/
uint8_t usart1_buf[256];											//串口1接收数组
uint16_t usart1_cnt = 0, usart1_cntPre = 0;
uint8_t usart2_buf[256];											//串口2接收数组
uint16_t usart2_cnt = 0, usart2_cntPre = 0;

/*
************************************************************
*	函数名称：	Usart1_Init
*
*	函数功能：	串口1初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：			TX-PA9		RX-PA10
************************************************************
*/
void Usart1_Init(unsigned int baud)
{
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);														//GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);													//使能USART1时钟
	
	//USART1 PA9	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;																			//复用推挽输出
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//USART1 PA10	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;																//浮空输入
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//Usart1 NVIC 配置
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;																		//串口1中断
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;																			//IRQ通道使能
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;														//抢占优先级0
	nvicInitStruct.NVIC_IRQChannelSubPriority = 3;																	//子优先级3
	NVIC_Init(&nvicInitStruct);																											//根据指定的参数初始化VIC寄存器
	
	//USART1 初始化设置
	usartInitStruct.USART_BaudRate = baud;																					//串口波特率
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			//无硬件数据流控制
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;											//接收和发送模式
	usartInitStruct.USART_Parity = USART_Parity_No;																	//无奇偶校验位
	usartInitStruct.USART_StopBits = USART_StopBits_1;															//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;													//8位数据位
	
	USART_Init(USART1, &usartInitStruct); 																					//初始化串口1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);																	//使能接收中断
	
	USART_Cmd(USART1, ENABLE);																											//使能串口
}

/*
************************************************************
*	函数名称：	Usart2_Init
*
*	函数功能：	串口2初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：			TX-PA2		RX-PA3
************************************************************
*/
void Usart2_Init(unsigned int baud)
{
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);														//GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);													//使能USART2时钟
	
	//USART2 PA2	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;																			//复用推挽输出
	gpioInitStruct.GPIO_Pin = GPIO_Pin_2;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//USART2 PA3	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;																//浮空输入
	gpioInitStruct.GPIO_Pin = GPIO_Pin_3;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//Usart2 NVIC 配置
	nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;																		//串口2中断
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;																			//IRQ通道使能
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;														//抢占优先级1
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;																	//子优先级3
	NVIC_Init(&nvicInitStruct);																											//根据指定的参数初始化VIC寄存器
	
	//USART1 初始化设置
	usartInitStruct.USART_BaudRate = baud;																					//串口波特率
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;			//无硬件数据流控制
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;											//接收和发送模式
	usartInitStruct.USART_Parity = USART_Parity_No;																	//无奇偶校验位
	usartInitStruct.USART_StopBits = USART_StopBits_1;															//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;													//8位数据位
	
	USART_Init(USART2, &usartInitStruct); 																					//初始化串口2
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);																	//使能串口2接收中断
	
	USART_Cmd(USART2, ENABLE);																											//使能串口2
}

/*
************************************************************
*	函数名称：	Usart_SendString
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{
	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}

}

/*
************************************************************
*	函数名称：	UsartPrintf
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{
	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//格式化
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

/*
************************************************************
*	函数名称：	USART1_Clear
//
*	函数功能：	清空缓存
//
*	入口参数：	无
//
*	返回参数：	无
//
*	说明：		
************************************************************
*/
void USART1_Clear(void)
{
	memset(usart1_buf, 0, sizeof(usart1_buf));
	usart1_cnt = 0;
}

/*
************************************************************
*	函数名称：	USART1_WaitRecive
//
*	函数功能：	等待接收完成
//
*	入口参数：	无
//
*	返回参数：	0-接收完成		1-接收超时未完成
//
*	说明：		循环调用检测是否接收完成
************************************************************
*/
_Bool USART1_WaitRecive(void)
{
	if(usart1_cnt == 0) 								//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return 1;
		
	if(usart1_cnt == usart1_cntPre)			//如果上一次的值和这次相同，则说明接收完毕
	{
		usart1_cnt = 0;										//清0接收计数
			
		return 0;													//返回接收完成标志
	}
		
	usart1_cntPre = usart1_cnt;					//置为相同
	
	return 1;														//返回接收未完成标志
}

/*
************************************************************
*	函数名称：	USART2_Clear
//
*	函数功能：	清空缓存
//
*	入口参数：	无
//
*	返回参数：	无
//
*	说明：		
************************************************************
*/
void USART2_Clear(void)
{
	memset(usart2_buf, 0, sizeof(usart2_buf));
	usart2_cnt = 0;
}

/*
************************************************************
*	函数名称：	USART2_WaitRecive
//
*	函数功能：	等待接收完成
//
*	入口参数：	无
//
*	返回参数：	0-接收完成		1-接收超时未完成
//
*	说明：		循环调用检测是否接收完成
************************************************************
*/
_Bool USART2_WaitRecive(void)
{

	if(usart2_cnt == 0) 								//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return 1;
		
	if(usart2_cnt == usart2_cntPre)			//如果上一次的值和这次相同，则说明接收完毕
	{
		usart2_cnt = 0;										//清0接收计数
			
		return 0;													//返回接收完成标志
	}
		
	usart2_cntPre = usart2_cnt;					//置为相同
	
	return 1;														//返回接收未完成标志
}


/*
************************************************************
*	函数名称：	USART1_IRQHandler
*
*	函数功能：	串口1收发中断
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 		//接收中断
	{
		if(usart1_cnt >= sizeof(usart1_buf))	usart1_cnt = 0; 	//防止串口被刷爆
		usart1_buf[usart1_cnt++] = USART1->DR;
		
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
}

/*
************************************************************
*	函数名称：	USART1_IRQHandler
*
*	函数功能：	串口2收发中断
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 		//接收中断
	{
		if(usart2_cnt >= sizeof(usart2_buf))	usart2_cnt = 0; 	//防止串口被刷爆
		usart2_buf[usart2_cnt++] = USART2->DR;
		
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
}


