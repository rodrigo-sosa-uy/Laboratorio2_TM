#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LUZ PORTD5

void configPORT(){
	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0xFF;
}

void configADC() {
	ADMUX |= (1 << REFS0);

	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t readADC(uint8_t canal){
	ADMUX = (ADMUX & 0xF0) | (canal & 0x0F);

	ADCSRA |= (1 << ADSC);

	while (ADCSRA & (1 << ADSC));
	
	return ADC;
}

void fotoresistor(){
	fotores = readADC(0);
	
	if(fotores > 0){
		PORTB |= (1 << LUZ);
	} else{
		PORTB &= ~(1 << LUZ);
	}
	_delay_ms(100);
}

int main(void){
	
	configPORT();
	
	configADC();
	
	while(1){
		fotoresistor();
	}
}