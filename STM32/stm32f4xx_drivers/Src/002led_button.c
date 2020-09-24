
#include "stm32f4xx.h"

int main()
{
	
	//led gpio configuration
		GPIO_Handle_t led;
		led.pGPIOx = GPIOD ;
		led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12 ;
		led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT  ;
		led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD ;
		led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD ;
		GPIO_PeriClockControl ( GPIOD, ENABLE );
	//button gpio configuration
		GPIO_Handle_t button;
		button.pGPIOx = GPIOA ;
		button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0 ;
	  button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INP ;
	  button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST ;
		button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD ;					//because by default on board button has pull up or pull down resistor
		GPIO_PeriClockControl ( GPIOA, ENABLE ) ;
	
		GPIO_Init ( &led);
	  GPIO_Init( &button );
	
	
		while( 1 )
		{
			if ( GPIO_ReadFromInputPin ( GPIOA, GPIO_PIN_NO_0 ) == SET ) 
			{
				GPIO_WriteToOutputPin ( GPIOD, GPIO_PIN_NO_12, SET);
			}
			else if ( GPIO_ReadFromInputPin ( GPIOA, GPIO_PIN_NO_0) == RESET )
			{
				GPIO_WriteToOutputPin ( GPIOD, GPIO_PIN_NO_12, RESET );
			}
		}
	
		return 0;
}
