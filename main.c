#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void configPORT();
void configPWM();

uint16_t fotores;
uint8_t tiempo = 0;

typedef enum{
	OFF,
	ON
} STATE;

typedef struct{
void (*func)();
}FSM;

STATE estado = OFF;

void F_OFF();
void F_ON();

FSM Autito[] = {
{F_OFF},
{F_ON}	
};

#include "libraries/Const_Globales.h"
#include "libraries/fotorresistor.h"
#include "libraries/movimiento.h"

void F_OFF(){
	PORTB &= ~(1 << MA1);
	PORTB &= ~(1 << MA2);
	
	PORTB &= ~(1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD &= ~(1 << LED_R);
	PORTD &= ~(1 << LED_V);
	
	if((PIND & (1 << BOTON)) == 1){
		estado = ON;
	}
}

void F_ON(){
	ADELANTE();
	DERECHA();
}

int main(void){

	configPWM();
	configPORT();
	configADC();
	
	while(1){
		(*Autito[estado].func)();
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