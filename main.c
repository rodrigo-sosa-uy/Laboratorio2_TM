/*
PORTC5 - PIN A5 - ADC 5
PORTC4 - PIN A4
PORTC3 - PIN A3
PORTC2 - PIN A2
PORTC1 - PIN A1
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

void configPORT(){
	DDRC = 0x0F;
	DDRD = 0xF0;
}

void configPWM(){
	ICR1 = 666;
	
	TCCR1A = 0b11110010;
	
	TCCR1B = 0b00011001;
}

int main(void){
    configPWM();
	
	configPORT();
	
    while(1){
		//
    }
}

