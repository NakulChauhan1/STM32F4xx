
#include "stm32f4xx.h"
#include<string.h>


#define MY_ADDR 0x61;
#define SLAVE_ADDR  0x68

extern void initialise_monitor_handles();


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
		uint8_t	receive_buffer[32];
		uint8_t command_code;
		uint8_t Len;
	
		initialise_monitor_handles();
	
		printf("Application is running\n");
		
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
		
		//ack bit is made 1 after PE=1
		I2C_ManageAcking( I2C1,	I2C_ACK_ENABLE );
		
	
		
		while ( 1 )
		{
				//When button will be pressed data will be sent
				while ( !GPIO_ReadFromInputPin ( button->pGPIOx, button->GPIO_PinConfig.GPIO_PinNumber ));
				
				//To avoid button de-bouncing related issues 200ms of delay
				delay();
				
			//1. I2C transactions to read 1 byte length information from the slave
				//Sending 0x51 command to Arduino, so that in the next transaction it sends us the number of bytes of data
				//Data Write: Master sending command to Slave
				command_code = 0x51;
				I2C_MasterSendData ( pI2Cpin->pI2Cx, &command_code, 1, SLAVE_ADDR, I2C_ENABLE_SR );				//we have more transactions after this transaction, thats why we are passing I2C_ENABLE_SR, this will enable repeated start and therefore another start will be generated for next transaction without STOP this current transaction
				
				//Data received will be stored in Len variable, therefore Len will have number of bytes of data to be received
				//Data Read: Master reading response from the Slave
				I2C_MasterReceiveData ( pI2Cpin->pI2Cx, &Len, 1, SLAVE_ADDR, I2C_ENABLE_SR );						//in place of rcvbuffer we are writing Len because we have sent 0x51, so data which will be received is going to be Len (ie number of bytes of data)
				//This length will be filled with the data which is received from the slave. So, the length a value will be stored in the length variable, as we have send 0x51 command, so whatever data slave is going to send will be Lenght of data (ie number of bytes of data)
			
			//2. I2C transactions to read 'Len' byte length information from the slave	
				//Sending 0x52 command to Arduino, so that Arduino is indicated to start sending 'Len' number of bytes
				//Data Write: Master sending command to Slave 
				command_code = 0x52;
				I2C_MasterSendData ( pI2Cpin->pI2Cx, &command_code, 1, SLAVE_ADDR, I2C_ENABLE_SR );
			
				// Data is being received at receive_buffer variable, increment and evrything is done inside the API
				//Data Read: Master reading response from the Slave
				I2C_MasterReceiveData ( pI2Cpin->pI2Cx, receive_buffer, Len, SLAVE_ADDR, I2C_DISABLE_SR );				//as this is last transaction therefore we dont need repeated start, therefore we can generate STOP here
				
				receive_buffer[Len++] = '\0';
				printf("Data : %s", receive_buffer);
		}
		return 0;
}
