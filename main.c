#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "libraries/Const_Globales.h"

void configPORT();
void configPWM();

uint16_t fotores;
uint8_t tiempo = 0;

typedef enum{
	OFF,
	ADELANTE,
	ATRAS,
	DERECHA,
	IZQUIERDA,
	SAFETY_CAR
} STATE;

typedef struct{
void (*func)();
}FSM;

STATE estado = OFF;

void F_OFF();
#include "libraries/fotorresistor.h"
#include "libraries/movimiento.h"

FSM Autito[] = {
{F_OFF},
{F_ADELANTE},
{F_ATRAS},
{F_DERECHA},
{F_IZQUIERDA},
{F_SAFETY_CAR}
};

void F_OFF(){
	PORTB &= ~(1 << MA1);
	PORTB &= ~(1 << MA2);
	
	PORTB &= ~(1 << MB1);
	PORTB &= ~(1 << MB2);
	
	PORTD &= ~(1 << LED_R);
	PORTD &= ~(1 << LED_V);
	
	fotoresistor();
	
	if((PINB & (1 << BOTON)) != 0){
		_delay_ms(500);
		estado = ADELANTE;
	}
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
	DDRB = 0b11011111;
	DDRD = 0b01111110;
	DDRC = 0x00;
}

void configPWM(){
	TCCR0A |= (1 << COM0B1) | (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	
	TCCR0A &= ~(1 << COM0B0);
	TCCR0A &= ~(1 << COM0A0);
	
	TCCR0B |= (1 << CS00);
}