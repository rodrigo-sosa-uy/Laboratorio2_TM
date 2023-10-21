#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Const_Globales.h"
#include "fotorresistor.h"
#include "movimiento.h"

uint16_t fotores;

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
	
	if((PIND & (1 << BOTON)) != 0){
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
	
	return 0;
}

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