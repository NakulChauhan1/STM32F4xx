
#include "stm32f4xx.h"
#include<string.h>


#define MY_ADDR 0x61;
#define SLAVE_ADDR  0x68

void delay(void)
{
		for ( uint32_t i=0; i<5000000/2;i++ );
}

/*
 * PB6-> SCL
 * PB7 -> SDA
 */

int main()
{
		uint8_t  mydata[] = "Nakul Chauhan";
		
		//Setting GPIO to behave as I2C, and doing all other configurations.
		GPIO_Handle_t * pGPIOx;
		pGPIOx->pGPIOx = GPIOB;																								//choosing Port B for the usage, GPIOB is pointer to GPIO register structure
		pGPIOx->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;								//using GPIO as Alternate Fxn (bcz we want to use selected port ie Port B as I2C1
		pGPIOx->GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;							//I2C need pull up resistor thats why we need to use Open Drain Conf, otherwise PP donot need PUPD resistor
		pGPIOx->GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;							//As I2C requires PU resitor
		pGPIOx->GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;								//deciding Speed of GPIO
		pGPIOx->GPIO_PinConfig.GPIO_PinAltFunMode = 4;												//as I2C1 belongs to AF4
	
		//SDA
		pGPIOx->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;								//as from Data Sheet PB7 can be used as SDA
		GPIO_Init (pGPIOx);																										//as all the conf. of SDA is done, so now sending handle pointer to initialse PB7 as SDA and doing other configurations
		
		//SCL
		pGPIOx->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;								//as from Data Sheet PB7 can be used as SCL
		GPIO_Init (pGPIOx);																										//as all the conf. of SCL is done, so now sending handle pointer to initialse PB6 as SCL and doing other configurations
		
		
		//Doing I2C configurations
		I2C_Handle_t * pI2Cpin;
		pI2Cpin->pI2Cx = I2C1;																								//selecting I2C1 out of it variants, I2C1 is pointer to I2C register structure
		pI2Cpin->I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
		pI2Cpin->I2C_Config.I2C_DeviceAddress = MY_ADDR;
		pI2Cpin->I2C_Config.I2C_FMDutyCycle  = I2C_FM_DUTY_2;
		pI2Cpin->I2C_Config.I2C_SCLSpeed  = I2C_SCL_SPEED_SM;
		I2C_Init ( pI2Cpin );
	
		//Doing Button Configurations
		GPIO_Handle_t * button;
		button->pGPIOx = GPIOA;
		button->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INP;
		button->GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		button->GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
		button->GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		button->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
		GPIO_Init ( button );
		
		//enable the i2c peripheral, note: Peripheral is Enabled after doing all configuration
		I2C_PeripheralControl ( pI2Cpin->pI2Cx, ENABLE );
		
		while ( 1 )
		{
				//when button will be pressed data will be sent
				while ( !GPIO_ReadFromInputPin ( button->pGPIOx, button->GPIO_PinConfig.GPIO_PinNumber ));
				//to avoid button de-bouncing related issues 200ms of delay
				delay();
				I2C_MasterSendData(pI2Cpin->pI2Cx, mydata, strlen((char*)mydata), SLAVE_ADDR, I2C_DISABLE_SR );
		}
		return 0;
}
