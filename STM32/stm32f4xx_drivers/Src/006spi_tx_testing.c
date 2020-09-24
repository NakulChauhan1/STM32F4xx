
#include <string.h>
#include "stm32f4xx.h"


/*
 * PB14 -------> SPI2_MISO
 * PB15 -------> SPI2_MOSI
 * PB13 -------> SPI2_SCLK
 * PB12 -------> SPI2_NSS
 * ALT function mode : 5
 *
 */

void SPI2_GPIOInits ()
{
		GPIO_Handle_t SPIPins;										//common variable for all pins
		
		// Common attributes for all pins (ie MOSI, MISO, SCLK )
		SPIPins.pGPIOx = GPIOB ;
		SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN ;								//selecting alternate functionality mode
		SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5 ;
		SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP ;
		SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD ;
		SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST ;
	
		// SCLK
		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13 ;
		GPIO_Init ( &SPIPins ) ;
	
		// MOSI
		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15 ;
		GPIO_Init ( &SPIPins );
	
		// MISO
		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14 ;
		GPIO_Init ( &SPIPins );
	
		// NSS
		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12 ;
		GPIO_Init ( &SPIPins );
}

void SPI2_Inits ()
{
		SPI_Handle_t spi2Handle;
	
		spi2Handle.pSPIx = SPI2 ;
		spi2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER ;
		spi2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2 ;																			//genrates clock of 8 MHz
		spi2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS ;
		spi2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW ;
		spi2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW ;
		spi2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD ;
		spi2Handle.SPIConfig.SPI_SSM = SPI_SSM_EN ;																							// Software Slave Management Enabled for NSS pin
		
		SPI_Init ( &spi2Handle ) ;
	
}

int main (void)
{
		
		char user_data[] = "Hello Wolrd";
	
		SPI2_GPIOInits ();					// This function is used to initialize GPIO pins to behave as Serial Peripheral Interface 2 (SPI2) pins
		
		SPI2_Inits ();							// This function does the SPI related Configuration
	
		// this makes NSS internally high ie make SSI = 1, and avoid MODEF error
		SPI_SSIConfig ( SPI2, ENABLE ) ;
	
		//enbaling the SPI2 peripheral
		SPI_PeripheralControl ( SPI2, ENABLE ) ;
	
		SPI_SendData ( SPI2, (uint8_t *) user_data, strlen(user_data) ) ;
	
		//disabling the SPI2 peripheral
		SPI_PeripheralControl ( SPI2, DISABLE ) ;
	
		while ( 1 ) ;
	
		return 0;
}
