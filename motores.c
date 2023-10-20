#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define velMax 255		// Velocidad Máxima
#define velDiff 200		// Velocidad de Diferencial
#define velMid 127		// Velocidad Media
#define velSeg 230		// Velocidad de Seguridad

#define MA1 PORTB2
#define MA2 PORTB1
#define MB1 PORTB4
#define MB2 PORTB3

void configPORT();
void configPWM();

void ADELANTE();
void DERECHA();
void IZQUIERDA();
void ATRAS();
void SAFETY_CAR();

int main(void){
	configPWM();
	
	configPORT();
	
	while(1){
		// comportamiento
	}
}

void configPORT(){
	DDRB = 0xFF;
	DDRD = 0xFE;
	DDRC = 0x00;
}

void configPWM(){
	TCCR0A = 0b11110011;
	
	TCCR0B = 0b00001001;
}

void ADELANTE(){
	OCR0B = velMax;
	OCR0A = velMax;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);

	_delay_ms(50);
}

void DERECHA(){
	OCR0B = velMax;
	OCR0A = velDiff;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);

	_delay_ms(50);
}

void IZQUIERDA(){
	OCR0B = velDiff;
	OCR0A = velMax;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);

	_delay_ms(50);
}

void ATRAS(){
	OCR0B = velMid;
	OCR0A = velMid;
	
	PORTB &= ~(1 << MA1);
	PORTB |= (1 << MA2);

	PORTB &= ~(1 << MB1);
	PORTB |= (1 << MB2);

	_delay_ms(50);
}

void SAFETY_CAR(){
	OCR0B = velSeg;
	OCR0A = velSeg;
	
	PORTB |= (1 << MA1);
	PORTB &= ~(1 << MA2);

	PORTB |= (1 << MB1);
	PORTB &= ~(1 << MB2);

	_delay_ms(50);
}