/*
 * Connect an external button to PD5 pin and toggle the led whenever interrupt
 * is triggered by the button press. Interrupt should be triggered during falling
 * edge of button press.
 */


#include<stm32f4xx.h>


void delay()
{
	for ( uint32_t i = 0; i<50000/2; i++ );
}

void button_config()
{
	GPIO_Handle_t * button;
	button->pGPIOx = GPIOD;
	button->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	button->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;						//means gpio is used to trigger an interrupt during falling edge
	button->GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	button->GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	GPIO_Init( button );

}
void led_config()
{
	GPIO_Handle_t * led;
	led->pGPIOx = GPIOD;
	led->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	led->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	led->GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	led->GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	led->GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Init( led );
}

int main()
{
	button_config();
	led_config();

	//note: peripheral side initialization for interrupt like setting Edge detection, selecting port, enabling interrupt delivery ie demasking, is done in GPIO_Init().


	//priority configuration is required when many interrupts are required. Since here only one interrupt is there, so no Interrupt Config is required
	GPIO_IRQPriorityConfig ( IRQ_NO_EXTI9_5, NVIC_IRQ_PRI15 );


	//Interrupt related configurations ie irq config.
	GPIO_InterruptConfig ( IRQ_NO_EXTI9_5, ENABLE );

	return 0;
}

void EXTI9_5_IRQHandler ()								//interrupt does not accept anything and doesnot return anyhting
{
	delay();											//to avoid button de bouncing
	GPIO_IRQHandling(GPIO_PIN_NO_5);					//clear the pending event in EXTIx line
	GPIO_ToggleOutputPin ( GPIOD, GPIO_PIN_NO_12 );

}
