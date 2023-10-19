#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define velMax 255		// Velocidad Máxima
#define velDiff 200		// Velocidad de Diferencial
#define velMid 127		// Velocidad Media
#define velSeg 230		// Velocidad de Seguridad

#define BOTON PORTD0

#define MA1 PORTB2
#define MA2 PORTB1
#define MB1 PORTB4
#define MB2 PORTB3

#define LED_V PORTD2
#define LED_R PORTD4

#define LUZ PORTD5

uint16_t fotores;

void configPORT(){
	DDRB = 0xFF;
	DDRD = 0xFE;
}

void configPWM(){
	TCCR0A = 0b11110011;
	
	TCCR0B = 0b00001001;
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


void ADELANTE(){
	OCR0B = velMax;
	OCR0A = velMax;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(100);
}

void IZQUIERDA(){
	OCR0A = velMax;
	OCR0B = velDiff;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(100);
}

void DERECHA(){
	OCR0A = velDiff;
	OCR0B = velMax;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(100);
}

void ATRAS(){
	OCR0B = velMid;
	OCR0A = velMid;
	
	PORTB &= ~(1 << MA1);
	PORTB |= (1 << MA2);

	PORTB &= ~(1 << MB1);
	PORTB |= (1 << MB2);
	
	PORTD &= ~(1 << LED_V);
	PORTD |= (1 << LED_R);
	_delay_ms(100);
}

void SAFETY_CAR(){
	OCR0B = velSeg;
	OCR0A = velSeg;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(100);
}

int main(void){
	
	configPORT();
	
	configADC();
	
	configPWM();
	
	while(1){
		DERECHA();
	}
}
