
#ifndef _USART_H_
#define _USART_H_


/**********************************
包含头文件
**********************************/
#include "sys.h"


/**********************************
函数声明
**********************************/
void Usart1_Init(unsigned int baud);			//串口1初始化
void USART1_Clear(void);									//串口1清除缓存
_Bool USART1_WaitRecive(void);						//串口1等待接收完成
void Usart2_Init(unsigned int baud);			//串口2初始化
void USART2_Clear(void);									//串口2清除缓存
_Bool USART2_WaitRecive(void);						//串口2等待接收完成
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);		//发送数据
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);		//发送数据


#endif
