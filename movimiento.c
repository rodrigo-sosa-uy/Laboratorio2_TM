#include "movimiento.h"

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

void DERECHA(){
	OCR0B = velMax;
	OCR0A = velDiff;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(100);
}

void IZQUIERDA(){
	OCR0B = velDiff;
	OCR0A = velMax;
	
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