

/**********************************
包含头文件
**********************************/
#include "sys.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "delay.h"
#include "gpio.h"
#include "key.h"
#include "oled.h"
#include "usart.h"
#include "rtc.h"
#include "dht11.h"
#include "adc.h"
#include "motor_bujin.h"

/**********************************
变量定义
**********************************/
uint8_t key_num = 0;									//按键扫描标志位	
uint8_t flag_display = 0;							//显示界面标志位
uint32_t time_num = 0;								//10ms计时
char display_buf[32];									//显示缓存区

_Bool flag_time_write = 0;						//修改时间写入标志位
_Bool flag_time_on = 0;               //是否到达定时时间之内标志位
int time_shi_begin = 22;						  //区间定时开始时
int time_fen_begin = 0;						    //区间定时开始分
int time_shi_end = 6;						    	//区间定时结束时
int time_fen_end = 00;						    //区间定时结束分

_Bool flag_mode = 0;                  //模式标志位

u16 humi_value = 0;										//衣柜湿度值
u16 humi_max = 60;										//衣柜湿度最大值
u16 temp_value = 0;										//衣柜温度值
u16 temp_min = 10;							      //最小温度变量

u16 light_value = 0;									//光照值
u16 light_min = 50;									  //光照最小值

u16 smog_value = 0;                   //烟雾值
u16 smog_max = 80;                    //烟雾最大值

extern uint8_t usart1_buf[256];				//串口1接收数组


extern _Bool flag_bujin_foreward;						//步进电机正转标志位
extern _Bool flag_bujin_reversal;						//步进电机反转标志位
extern _Bool flag_bujin_state;               //步进电机状态标志位
/**********************************
函数声明
**********************************/ 
void Display_function(void);					//显示函数
void Manage_function(void);						//处理函数


/****
*******	主函数 
*****/
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //配置中断优先分组
	Delay_Init();	    	 								//延时初始化	  
	Gpio_Init();		  									//IO初始化
	Key_Init();		  										//按键初始化
	 
  while(DHT11_Init());								//DHT11初始化
//	DHT11_Init();
	while(1)
	{
	 
		Display_function();								//显示函数
		Manage_function();								//处理函数

		time_num++;												//计时变量+1
		Delay_ms(10);
		if(time_num %10 == 0)
			LED_SYS = ~LED_SYS;
		if(time_num >= 5000)
		{
			time_num = 0;
		}
	}
}
  
/****
*******显示函数
*****/
void Display_function(void)
{
	switch(flag_display)									//根据不同的显示模式标志位，显示不同的界面
	{
		case 0:									      			//界面0：
			sprintf(display_buf,"%d-%d%d-%d%d",calendar.w_year,calendar.w_month/10,calendar.w_month%10,calendar.w_date/10,calendar.w_date%10);
			Oled_ShowString(1, 2, display_buf);
			sprintf(display_buf,"%d%d:%d%d:%d%d",calendar.hour/10,calendar.hour%10,calendar.min/10,calendar.min%10,calendar.sec/10,calendar.sec%10);
			Oled_ShowString(2, 3, display_buf);
		
			Oled_ShowString(3,0,"T:");
			sprintf(display_buf,"%d.%dC ",temp_value/10,temp_value%10);
			Oled_ShowString(3,2,display_buf);
			Oled_ShowString(3,8,"H:");
			sprintf(display_buf,"%d.%dC ",humi_value/10,humi_value%10);
			Oled_ShowString(3,10,display_buf);
			Oled_ShowString(4,0,"L:");
			sprintf(display_buf,"%dlux ",light_value);
			Oled_ShowString(4,2,display_buf);
			Oled_ShowString(4,8,"S:");
			sprintf(display_buf,"%dppm  ",smog_value);
			Oled_ShowString(4,10,display_buf);
		
		break;
		
		case 1:																					//界面1：显示设置时间年
			Oled_ShowCHinese(1,2,"设置时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d-%d%d-%d%d",calendar.w_year,calendar.w_month/10,calendar.w_month%10,calendar.w_date/10,calendar.w_date%10);
				Oled_ShowString(2, 2, display_buf);
				sprintf(display_buf,"%d%d:%d%d:%d%d",calendar.hour/10,calendar.hour%10,calendar.min/10,calendar.min%10,calendar.sec/10,calendar.sec%10);
				Oled_ShowString(3, 3, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 2, "    ");
			}
		break;
			
		case 2:																					//界面2：显示设置时间月
			Oled_ShowCHinese(1,2,"设置时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d-%d%d-%d%d",calendar.w_year,calendar.w_month/10,calendar.w_month%10,calendar.w_date/10,calendar.w_date%10);
				Oled_ShowString(2, 2, display_buf);
				sprintf(display_buf,"%d%d:%d%d:%d%d",calendar.hour/10,calendar.hour%10,calendar.min/10,calendar.min%10,calendar.sec/10,calendar.sec%10);
				Oled_ShowString(3, 3, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 7, "  ");
			}
		break;

		case 3:																						//界面3：显示设置时间日
			Oled_ShowCHinese(1,2,"设置时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d-%d%d-%d%d",calendar.w_year,calendar.w_month/10,calendar.w_month%10,calendar.w_date/10,calendar.w_date%10);
				Oled_ShowString(2, 2, display_buf);
				sprintf(display_buf,"%d%d:%d%d:%d%d",calendar.hour/10,calendar.hour%10,calendar.min/10,calendar.min%10,calendar.sec/10,calendar.sec%10);
				Oled_ShowString(3, 3, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 10, "  ");
			}
		break;				
			
		case 4:																						//界面4：显示设置时间时
			Oled_ShowCHinese(1,2,"设置时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d-%d%d-%d%d",calendar.w_year,calendar.w_month/10,calendar.w_month%10,calendar.w_date/10,calendar.w_date%10);
				Oled_ShowString(2, 2, display_buf);
				sprintf(display_buf,"%d%d:%d%d:%d%d",calendar.hour/10,calendar.hour%10,calendar.min/10,calendar.min%10,calendar.sec/10,calendar.sec%10);
				Oled_ShowString(3, 3, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(3, 3, "  ");
			}
		break;	

		case 5:																						//界面5：显示设置时间分
			Oled_ShowCHinese(1,2,"设置时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d-%d%d-%d%d",calendar.w_year,calendar.w_month/10,calendar.w_month%10,calendar.w_date/10,calendar.w_date%10);
				Oled_ShowString(2, 2, display_buf);
				sprintf(display_buf,"%d%d:%d%d:%d%d",calendar.hour/10,calendar.hour%10,calendar.min/10,calendar.min%10,calendar.sec/10,calendar.sec%10);
				Oled_ShowString(3, 3, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(3, 6, "  ");
			}
		break;				
			
		case 6:																						//界面6：显示设置时间秒
			Oled_ShowCHinese(1,2,"设置时间");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d-%d%d-%d%d",calendar.w_year,calendar.w_month/10,calendar.w_month%10,calendar.w_date/10,calendar.w_date%10);
				Oled_ShowString(2, 2, display_buf);
				sprintf(display_buf,"%d%d:%d%d:%d%d",calendar.hour/10,calendar.hour%10,calendar.min/10,calendar.min%10,calendar.sec/10,calendar.sec%10);
				Oled_ShowString(3, 3, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(3, 9, "  ");
			}
		break;
		
			case 7:															         	 			//界面7：显示设置区间定时开始时
			Oled_ShowCHinese(1,0,"设置定时开始时");
			if(time_num % 5 == 0)
			{
				Oled_ShowNum_2(2,5,time_shi_begin);
				Oled_ShowNum_2(2,8,time_fen_begin);
				Oled_ShowString(2,7,":");
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2,5,"  :");
			}
		break;

		case 8:															         	 			//界面8：显示设置区间定时开始分
			Oled_ShowCHinese(1,0,"设置定时开始分");
			if(time_num % 5 == 0)
			{
				Oled_ShowNum_2(2,5,time_shi_begin);
				Oled_ShowNum_2(2,8,time_fen_begin);
				Oled_ShowString(2,7,":");
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2,7,":  ");
			}
		break;

		case 9:															         	 			//界面9：显示设置区间定时结束时
			Oled_ShowCHinese(1,0,"设置定时结束时");
			if(time_num % 5 == 0)
			{
				Oled_ShowNum_2(2,5,time_shi_end);
				Oled_ShowNum_2(2,8,time_fen_end);
				Oled_ShowString(2,7,":");
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2,5,"  :");
			}
		break;

		case 10:															         	 		//界面10：显示设置区间定时结束分
			Oled_ShowCHinese(1,0,"设置定时结束分");
			if(time_num % 5 == 0)
			{
				Oled_ShowNum_2(2,5,time_shi_end);
				Oled_ShowNum_2(2,8,time_fen_end);
				Oled_ShowString(2,7,":");
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2,7,":  ");
			}
		break;
			
		case 11:																						//界面11：显示设置温度最小值
			Oled_ShowCHinese(1,0,"设置温度最小值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d  ",temp_min);
				Oled_ShowString(2, 7, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 7, "    ");
			}
		break;

		case 12:																						//界面12：显示设置湿度最大值
			Oled_ShowCHinese(1,0,"设置湿度最大值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d  ",humi_max);
				Oled_ShowString(2, 7, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 7, "    ");
			}
		break;

		case 13:																						//界面13：显示设置光照最小值
			Oled_ShowCHinese(1,0,"设置光照最小值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d  ",light_min);
				Oled_ShowString(2, 7, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 7, "    ");
			}
		break;

		case 14:																						//界面14：显示设置烟雾最大值
			Oled_ShowCHinese(1,0,"设置烟雾最大值");
			if(time_num % 5 == 0)
			{
				sprintf(display_buf,"%d  ",smog_max);
				Oled_ShowString(2, 7, display_buf);
			}
			if(time_num % 10 == 0)
			{
				Oled_ShowString(2, 7, "    ");
			}
		break;
		default:
			
		break;
	}
}

/****
*******处理函数
*****/
void Manage_function(void)
{
	u8 time_shi,time_fen;              //当前时间

	if(flag_display == 0)																			//测量界面
	{
		if(flag_mode == 0)
		{
			time_shi = calendar.hour;												        //获取当前时间
			time_fen = calendar.min;
			if(time_shi_begin*60+time_fen_begin > time_shi_end*60+time_fen_end)						//开始时间>结束时间
			{
				if((time_shi_end*60+time_fen_end <= time_shi*60+time_fen) && (time_shi*60+time_fen < time_shi_begin*60+time_fen_begin))		//当前时间不在设置的时间内
					flag_time_on = 0;
				else																																				//否则
					flag_time_on = 1;
			}
			else if(time_shi_begin*60+time_fen_begin < time_shi_end*60+time_fen_end)			//开始时间<结束时间
			{
				if((time_shi_begin*60+time_fen_begin <= time_shi*60+time_fen) && (time_shi*60+time_fen < time_shi_end*60+time_fen_end))		//当前时间在设置的时间内
					flag_time_on = 1;
				else																																				//否则
					flag_time_on = 0;
			}
		 
      if(smog_value > smog_max)	//烟雾值大于设置的最大值，声光报警
      {
        if(time_num % 3 == 0)
        {
          LED=~LED;
          BEEP=~BEEP;
        }
      }
      else
      {
        LED = 1;
        BEEP = 0;
      }
		}
	}
	else																											//设置界面，关闭所有继电器
	{
		LED = 1;
    BEEP = 0;
		RELAY_ZM = 0;
    RELAY_TF = 0;
    RELAY_JR = 0;
    RELAY_XD = 0;
	}
}

