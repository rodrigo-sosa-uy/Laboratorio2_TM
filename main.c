/*
PORTC5 - PIN A5
PORTC4 - PIN A4
PORTC3 - PIN A3
PORTC2 - PIN A2
PORTC1 - PIN A1 - ADC 1
PORTC0 - PIN A0

PORTD7 - PIN 7
PORTD6 - PIN 6 ~ / 980 Hz
PORTD5 - PIN 5 ~ / 980 Hz
PORTD4 - PIN 4
PORTD3 - PIN 3 ~
PORTD2 - PIN 2
*/

/*
PIN A5 - FOTORESISTOR

PIN A4 - BOTON ON/OFF

PIN A3 - MOTOR B2
PIN A2 - MOTOR B1

PIN A1 - MOTOR A2
PIN A0 - MOTOR A1

PIN 6 - ENABLE B (o PB1)
PIN 5 - ENABLE A (o PB0)

PIN 7 - LED ROJO
PIN 4 - LED VERDE
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define PWM_Frec 1500	// Frecuencia de PWM (Hz)
#define Top 666			// Top
#define velMax 666		// Velocidad Máxima
#define velDiff 200		// Velocidad de Diferencial
#define velMid 333		// Velocidad Media
#define velSeg 100		// Velocidad de Seguridad

#define BOTON PINXx

#define MA1 PORTBx
#define MA2 PORTBx
#define MB1 PORTBx
#define MB2 PORTBx

#define LED_V PORTx
#define LED_R PORTx

unsigned short fotores;
unsigned int tiempo = 0;

typedef enum{
OFF,
ON
} STATE;

STATE estado = OFF;


void configPORT(){
	DDRC = 0x0F;	// STANDBY
	DDRD = 0xF0;	// STANDBY
}

void configPWM(){
	ICR1 = 666;
	
	TCCR1A = 0b11110010;
	
	TCCR1B = 0b00011001;
}

void configADC() {
	ADMUX |= (1 << REFS0);

	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

unsigned short readADC(unsigned char canal){
	ADMUX = (ADMUX & 0xF0) | (canal & 0x0F);

	ADCSRA |= (1 << ADSC);

	while (ADCSRA & (1 << ADSC));
	
	return ADC;
}

void fotoresistor(){
	fotores = readADC(1);
	
	if(fotores > x){ // cambiar
		PORTB |= (1 << x); // cambiar
	} else{
		PORTB &= ~(1 << x); // cambiar
	}
	_delay_ms(100);
}

void ADELANTE(){
	OCR1A = velMax;
	
	PORTx |= (1 << MA1);
	PORTx &= ~(1 << MA2);

	PORTx |= (1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx |= (1 << LED_V);
	PORTX &= ~(1 << LED_R);
	
	fotoresistor();
	
	if((PINx & (1 << BOTON)) != 0){
		estado = OFF;
	}
}

void DERECHA(){
	OCR1A = velMax;
	
	PORTx |= (1 << MA1);
	PORTx &= ~(1 << MA2);

	OCR1A = velDiff;

	PORTx |= (1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx |= (1 << LED_V);
	PORTx &= ~(1 << LED_R);
	
	fotoresistor();
	
	if((PINx & (1 << BOTON)) != 0){
		estado = OFF;
	}
}

void IZQUIERDA(){
	OCR1A = velDiff;
	
	PORTx |= (1 << MA1);
	PORTx &= ~(1 << MA2);

	OCR1A = velMax;

	PORTx |= (1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx |= (1 << LED_V);
	PORTx &= ~(1 << LED_R);
	
	fotoresistor();
	
	if((PINx & (1 << BOTON)) != 0){
		estado = OFF;
	}
}

void ATRAS(){
	OCR1A = velMid;
	
	PORTx &= ~(1 << MA1);
	PORTx |= (1 << MA2);

	PORTx &= ~(1 << MB1);
	PORTx |= (1 << MB2);
	
	PORTx &= ~(1 << LED_V);
	PORTx |= (1 << LED_R);
	
	fotoresistor();
	
	if((PINx & (1 << BOTON)) != 0){
		estado = OFF;
	}
}

void SAFETY_CAR(){
	OCR1A = velSeg;
	
	PORTx |= (1 << MA1);
	PORTx &= ~(1 << MA2);

	PORTx |= (1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx |= (1 << LED_V);
	PORTX &= ~(1 << LED_R);
	
	fotoresistor();
	
	if((PINx & (1 << BOTON)) != 0){
		estado = OFF;
	}
}

void F_OFF(){
	PORTx &= ~(1 << MA1);
	PORTx &= ~(1 << MA2);
	
	PORTx &= ~(1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx &= ~(1 << LED_R);
	PORTx &= ~(1 << LED_V);
	
	if((PINx & (1 << BOTON)) != 0){
		estado = ON;
	}
}

void F_ON(){
	ADELANTE();
	_delay_ms(2000);
	DERECHA();
	_delay_ms(1000);
	ADELANTE();
	_delay_ms(2000);
	IZQUIERDA();
	_delay_ms(1000);
	ATRAS();
	_delay_ms(2000);
	SAFETY_CAR();
	_delay_ms(4000);
}

int main(void){
	
	void (*Autito[2])();
	Autito[OFF] = F_OFF;
	Autito[ON] = F_ON;
	
    configPWM();
	
	configPORT();
	
	configADC();
	
    while(1){
		Autito[estado]();
    }
}