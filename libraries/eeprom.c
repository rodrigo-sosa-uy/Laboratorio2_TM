#include "eeprom.h"

void writeEEPROM(uint8_t choques, uint16_t addr){
	// Escribimos en la EEPROM //
	while(EECR & (1<<EEPE));

	EEAR = addr;
	EEDR = choques;

	EECR |= (1<<EEMPE);

	EECR |= (1<<EEPE);
	// ----------------------- //
}

void CRASH(){
	// Evaluamos el choque //
	if((PINB & (1 << CHOKE)) != 0){
		choques++;
	}
	// ------------------- //
}