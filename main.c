/*
PORTC5 - PIN A5
PORTC4 - PIN A4
PORTC3 - PIN A3
PORTC2 - PIN A2
PORTC1 - PIN A1 - ADC 1
PORTC0 - PIN A0

PORTB5 - PIN 13
PORTB4 - PIN 12
PORTB3 - PIN 11 ~
PORTB2 - PIN 10 ~
PORTB1 - PIN 9 ~
PORTB0 - PIN 8

PORTD7 - PIN 7
PORTD6 - PIN 6 ~ / 980 Hz
PORTD5 - PIN 5 ~ / 980 Hz
PORTD4 - PIN 4
PORTD3 - PIN 3 ~
PORTD2 - PIN 2
*/

/*
PIN x - BOTON ON/OFF

PIN A1 - FOTORESISTOR

PIN x - MOTOR B2
PIN x - MOTOR B1

PIN x - MOTOR A2
PIN x - MOTOR A1

PIN x - ENABLE B (o PB1)
PIN x - ENABLE A (o PB0)

PIN x - LED ROJO
PIN x - LED VERDE
*/

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

void configPORT();
void configADC();
void configPWM();

uint16_t readADC(uint8_t);
void fotoresistor();

void ADELANTE();
void DERECHA();
void IZQUIERDA();
void ATRAS();
void SAFETY_CAR();

typedef enum{
OFF,
ON
} STATE;

void F_OFF();
void F_ON();

STATE estado = OFF;

void F_OFF(){
	PORTB &= ~(1 << MA1);
	PORTB &= ~(1 << MA2);
	
	PORTB &= ~(1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD &= ~(1 << LED_R);
	PORTD &= ~(1 << LED_V);
	
	if((PINC & (1 << BOTON)) != 0){
		estado = ON;
	}
}

void F_ON(){
	// comportamiento
}

int main(void){
	void (*Autito[2])();
	Autito[OFF] = F_OFF;
	Autito[ON] = F_ON;
	
	configPWM();
	
	configPORT();
	
	configADC();
	
	while(1){
		(*Autito[estado])();
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
	_delay_ms(50);
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
	_delay_ms(50);
	
	fotoresistor();
	
	if((PINC & (1 << BOTON)) != 0){
		estado = OFF;
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
	
	if((PINC & (1 << BOTON)) != 0){
		estado = OFF;
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
	
	if((PINC & (1 << BOTON)) != 0){
		estado = OFF;
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
	
	if((PINC & (1 << BOTON)) != 0){
		estado = OFF;
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
	
	if((PINC & (1 << BOTON)) != 0){
		estado = OFF;
	}
}