/*******************************************************************************
* @file     main.c                                                               
* @brief    主函数                                                   
* @author   xxxlzjxxx                                                          
* @version  V1.0                                                              
* @date     2018-08-02                                                        
* @license  GNU General Public License (GPL)                                                                                                               
*******************************************************************************/
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "oled.h"
#include "usmart.h"
#include "adc.h"

u16 adcx;
float USB_CURR,USB_VOLT,USB_WATT;
float BAT_CURR,BAT_VOLT,BAT_WATT;

void oled_task(void);

int main(void)
{	
 	u8 t = 0;
//	u16 i = 99;
 
	delay_init();	     //延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(115200);	 	//串口初始化为115200
    LED_Init();
	Adc_Init();
    delay_ms(1000);
    LED0 = !LED0;
	OLED_Init();			//初始化OLED
	usmart_dev.init(72);	//初始化USMART	

	OLED_ShowString(0,0,"USB:",16);
    OLED_ShowString(30,52,"V",12);
    OLED_ShowString(73,52,"A",12);
    OLED_ShowString(122,52,"W",12);
	OLED_ShowString(0,34,"BAT:",16);
    OLED_ShowString(30,18,"V",12);
    OLED_ShowString(73,18,"A",12);
    OLED_ShowString(122,18,"W",12);

	while(1){		  
		delay_ms(10);
		oled_task();
        
        t++;
        if(t >= 5){
            LED0 = !LED0;
            t = 0;
        }
	}	  
}
/*******************************************************************************
* @param		参数
* @brief		摘要
* @arg			列表说明参数
* @return       返回值说明
* @retval		返回值类型说明
* @see			参看
* @attention	注意
* @note			注解	
* @author   	作者                                                                                                       *                                                            
* @date     	日期            				
*******************************************************************************/
void oled_task(void){
    char aa[6];	
//display BAT_VOLT    
	adcx = Get_Adc_Average(ADC_Channel_0,20);
    BAT_VOLT=(float)adcx*(3.34/4096)*2;//实际电压值
    BAT_WATT= BAT_VOLT;
    sprintf(aa,"%2.2f",BAT_VOLT);//浮点型数据转为指定格式的字符串
    OLED_ShowString(0,52,(u8 *)aa,12);	
//display BAT_CURR    
	adcx = Get_Adc_Average(ADC_Channel_1,20);
    BAT_CURR = (float)adcx*3.34/4096;
    if(BAT_CURR >= 1.67){
        BAT_CURR=(BAT_CURR - 1.67) * 1000 / 132;
    }
    else{
        BAT_CURR=(1.67 - BAT_CURR) * 1000 / 132;
    }
    sprintf(aa,"%2.2f",BAT_CURR);//浮点型数据转为指定格式的字符串
    OLED_ShowString(43,52,(u8 *)aa,12);		
//display BAT_WATT    
	BAT_WATT = BAT_WATT * BAT_CURR;
    sprintf(aa,"%2.2f",BAT_WATT);//浮点型数据转为指定格式的字符串
    OLED_ShowString(92,52,(u8 *)aa,12);
    
//display USB_VOLT    
	adcx = Get_Adc_Average(ADC_Channel_3,20);
    USB_VOLT=(float)adcx*(3.34/4096)*4;//实际电压值
    USB_WATT= USB_VOLT;
    sprintf(aa,"%2.2f",USB_VOLT);//浮点型数据转为指定格式的字符串
    OLED_ShowString(0,18,(u8 *)aa,12);	
//display USB_CURR    
	adcx = Get_Adc_Average(ADC_Channel_2,20);
    USB_CURR = (float)adcx*3.34/4096;
    if(USB_CURR >= 1.67){
        USB_CURR=(USB_CURR - 1.67) * 1000 / 132;
    }
    else{
        USB_CURR=(1.67 - USB_CURR) * 1000 / 132;
    }
    sprintf(aa,"%2.2f",USB_CURR);//浮点型数据转为指定格式的字符串
    OLED_ShowString(43,18,(u8 *)aa,12);		
//display BAT_WATT    
	USB_WATT = USB_WATT * USB_CURR;
    sprintf(aa,"%2.2f",USB_WATT);//浮点型数据转为指定格式的字符串
    OLED_ShowString(92,18,(u8 *)aa,12);

	
	OLED_Refresh_Gram();//更新显示到OLED
}



