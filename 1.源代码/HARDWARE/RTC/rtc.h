

#ifndef __RTC_H_
#define __RTC_H_   


/**********************************
包含头文件
**********************************/
#include "sys.h"



/**********************************
时间结构体
**********************************/
typedef struct 
{
	vs8 hour;
	vs8 min;
	vs8 sec;			
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;
	vu8  week;		 
}_calendar_obj;

extern _calendar_obj calendar;					//日历结构体，供其他文件调用


/**********************************
函数声明
**********************************/
uint8_t RTC_Init(void);        					//RTC初始化函数
uint8_t RTC_Set(uint16_t syear,uint8_t smon,uint8_t sday,uint8_t hour,uint8_t min,uint8_t sec);		//设置时间

#endif

