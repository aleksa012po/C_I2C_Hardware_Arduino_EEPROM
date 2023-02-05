/*
 * C_I2C_Hardware_EEPROM.c
 *
 * Created: 10.1.2023. 22:50:07
 * Author : Aleksandar Bogdanovic
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t eepromadress;					// EEPROM address initial 0
volatile uint8_t i;								// string array index initial 0
uint8_t message[] = "Aleksandar";				// message to be written to EEPROM

iSR(EE_READY_vect)
{
	if((message[i]) && (eepromadress <= E2END))	// E2END = 0x3FF
	{
		EEAR = eepromadress++;					// loads address and increments for next load
		EEDR = message[i++];					// loads current byte and increments index for next load
		EECR |= (1 << EEMPE);					// master write enable
		EECR |= (1 << EEPE);					// strobe eeprom write
	}
	else
	{
		EECR &= ~(1 << EERIE);					// disable eeprom ready interrupt
	}
}

int main(void)
{
	EECR |= (1 << EERIE);						// Enable eeprom ready interrupt
	sei();										// enable global interrupts
	
	while(1)
	{
		
	}
}
