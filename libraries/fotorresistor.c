#include "fotorresistor.h"

void configADC() {
	// Configuración del conversor analógico //
	ADMUX |= (1 << REFS0);

	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	// ------------------------------------- //
}

uint16_t readADC(uint8_t canal){
	// Conversión del ADC //
	ADMUX = (ADMUX & 0xF0) | (canal & 0x0F);

	ADCSRA |= (1 << ADSC);

	while (ADCSRA & (1 << ADSC));
	
	return ADC;
	// ------------------ //
}

void fotoresistor(){
	fotores = readADC(1);
	
	if(fotores > LUZ_NATURAL){
		PORTD |= (1 << LUZ);
	} else{
		PORTD &= ~(1 << LUZ);
	}
	_delay_ms(50);
}