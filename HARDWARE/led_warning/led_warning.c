#include "stm32f10x.h"
#include "led_warning.h"

unsigned char LED0_State=0;

int mian(void)
{
  while (1)
  {
		if(Key0_State==0xff)
		{
			LED0_State=!LED0_State;
			delay_ms(300);
			Key0_State=0;
     
		x}
		
		if(LED0_State==0)
		{
			 LED0_ON();//LEDÁÁ
			 delay_ms(200);
			 LED0_OFF();//LEDÃð
			 delay_ms(200); 
		 }
		
  }
}