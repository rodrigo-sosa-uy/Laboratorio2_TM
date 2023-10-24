#include "movimiento.h"

#include "fotorresistor.h"

void ADELANTE(){
	OCR0B = velMax;
	OCR0A = velMax;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PIND & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
	} else if(tiempo >= 50){
		tiempo = 0;
		return;
	}
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
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PIND & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
		} else if(tiempo >= 50){
		tiempo = 0;
		return;
	}
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
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PIND & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
		} else if(tiempo >= 50){
		tiempo = 0;
		return;
	}
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
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PIND & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
	} else if(tiempo >= 50){
		tiempo = 0;
		return;
	}
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
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PIND & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
		} else if(tiempo >= 50){
		tiempo = 0;
		return;
	}
}