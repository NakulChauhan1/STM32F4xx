/* WAP to toggle the on board LED with some delay:
   1. Use push pull configuration for the output pin
   2. Use open drain configuration for the output pin
*/

#include<stm32f4xx.h>

void delay()
{
	for ( uint32_t i = 0; i<50000; i++ );
}

int main()
{

	GPIO_Handle_t led;
	led.pGPIOx = GPIOD;
	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;			//since Push pull is used no need of pull up/pull down resistors as PP is already having well defined stated.
	GPIO_Init( &led );

	while(1)
	{
		GPIO_ToggleOutputPin(led.pGPIOx, led.GPIO_PinConfig.GPIO_PinNumber );
		delay();
	}

	return 0;
}

