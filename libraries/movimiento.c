#include "movimiento.h"

#include "fotorresistor.h"

void F_ADELANTE(){
	OCR0B = velMax;
	OCR0A = velMax;
	
	PORTB |= (1 << MA2);
	PORTB &= ~(1 << MA1);

	PORTB |= (1 << MB2);
	PORTB &= ~(1 << MB1);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PINB & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
	} else if(tiempo >= 50){
		tiempo = 0;
		estado = DERECHA;
	}
}

void F_DERECHA(){
	OCR0B = velMax;
	OCR0A = velDiff;
	
	PORTB |= (1 << MA2);
	PORTB &= ~(1 << MA1);

	PORTB |= (1 << MB2);
	PORTB &= ~(1 << MB1);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PINB & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
	} else if(tiempo >= 20){
		tiempo = 0;
		estado = SAFETY_CAR;
	}
}

void F_IZQUIERDA(){
	OCR0B = velDiff;
	OCR0A = velMax;
	
	PORTB |= (1 << MA2);
	PORTB &= ~(1 << MA1);

	PORTB |= (1 << MB2);
	PORTB &= ~(1 << MB1);
	
	PORTD |= (1 << LED_V);
	PORTD &= ~(1 << LED_R);
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PINB & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
	} else if(tiempo >= 20){
		tiempo = 0;
		estado = ATRAS;
	}
}

void F_ATRAS(){
	OCR0B = velMid;
	OCR0A = velMid;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD &= ~(1 << LED_V);
	PORTD |= (1 << LED_R);
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PINB & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
	} else if(tiempo >= 40){
		tiempo = 0;
		estado = ADELANTE;
	}
}

void F_SAFETY_CAR(){
	OCR0B = velSeg;
	OCR0A = velSeg;
	
	PORTB |= (1 << MA2);
	PORTB &= ~(1 << MA1);

	PORTB |= (1 << MB2);
	PORTB &= ~(1 << MB1);
	
	PORTD |= (1 << LED_V);
	PORTD |= (1 << LED_R);
	_delay_ms(50);
	
	fotoresistor();
	
	tiempo++;
	
	if((PINB & (1 << BOTON)) != 0){
		tiempo = 0;
		_delay_ms(500);
		estado = OFF;
	} else if(tiempo >= 60){
		tiempo = 0;
		estado = IZQUIERDA;
	}
}