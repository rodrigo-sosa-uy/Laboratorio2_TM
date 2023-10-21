#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define velMax 255		// Velocidad M�xima (7,5v)
#define velDiff 130		// Velocidad de Diferencial (3,2v)
#define velMid 140		// Velocidad Media (3,75v)
#define velSeg 125 		// Velocidad de Seguridad (2,85v)

#define BOTON PORTD0

#define MA1 PORTB2
#define MA2 PORTB1
#define MB1 PORTB4
#define MB2 PORTB3

#define LED_V PORTD2
#define LED_R PORTD4

void configPORT(){
	DDRB = 0xFF;
	DDRD = 0xFE;
	DDRC = 0x00;
}

void configPWM(){
	TCCR0A |= (1 << COM0B1) | (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	
	TCCR0A &= ~(1 << COM0B0);
	TCCR0A &= ~(1 << COM0A0);
	
	TCCR0B |= (1 << CS00);
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

int main(void){
	
	configPORT();
	
	configPWM();
	
	while(1){
		ADELANTE();
		_delay_ms(3000);
		DERECHA();
		_delay_ms(3000);
		IZQUIERDA();
		_delay_ms(3000);
		ATRAS();
		_delay_ms(3000);
		SAFETY_CAR();
		_delay_ms(3000);
	}
}
