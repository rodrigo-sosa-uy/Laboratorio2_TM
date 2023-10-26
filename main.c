#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "libraries/Const_Globales.h"

void configPORT();
void configPWM();

uint16_t fotores;
uint8_t tiempo = 0;
uint8_t choques = 0;

// Definici�n de estados //
typedef enum{
	OFF,
	ADELANTE,
	ATRAS,
	DERECHA,
	IZQUIERDA,
	SAFETY_CAR
} STATE;
// --------------------- //

// Definici�n de m�quina de estados //
typedef struct{
void (*func)();
}FSM;

STATE estado = OFF;
// -------------------------------- //

// Inclusi�n de librer�as //
/* Las librer�as se incluyen en �sta parte del
   c�digo para evitar errores, debido a la
   declaraci�n de las variables utilizadas. */
void F_OFF();
#include "libraries/fotorresistor.h"
#include "libraries/eeprom.h"
#include "libraries/movimiento.h"

// Implementaci�n de m�quina de estados //
FSM Autito[] = {
{F_OFF},
{F_ADELANTE},
{F_ATRAS},
{F_DERECHA},
{F_IZQUIERDA},
{F_SAFETY_CAR}
};
// ------------------------------------- //

void F_OFF(){
	// Seteamos direcci�n //
	PORTB &= ~(1 << MA1);
	PORTB &= ~(1 << MA2);
	
	PORTB &= ~(1 << MB1);
	PORTB &= ~(1 << MB2);
	// ------------------ //
	
	// Luces de indicaci�n //
	PORTD &= ~(1 << LED_R);
	PORTD &= ~(1 << LED_V);
	// ------------------- //
	
	fotoresistor(); // Evaluamos la fotorresistencia
	
	// Cambio de estado //
	if((PINB & (1 << BOTON)) != 0){
		_delay_ms(500);
		writeEEPROM(choques, 10); // *
		estado = ADELANTE;
	}
	// ---------------- //
/*  * Se escribe en la EEPROM cada vez que se inicia el programa
	para evitar utilizarla cada vez que se registra un choque. */
}

int main(void){

	// Inicializamos configuraciones //
	configPWM();
	configPORT();
	configADC();
	// ----------------------------- //
	
	while(1){
		// M�quina de estado //
		(*Autito[estado].func)();
		// ----------------- //
	}
	
	return 0;
}

void configPORT(){
	// Definimos entradas y salidas //
	DDRB = 0b11011111;
	DDRD = 0b01111110;
	DDRC = 0x00;
	// ---------------------------- //
}

void configPWM(){
	// Configuraci�n del Timer 0 //
	TCCR0A |= (1 << COM0B1) | (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	
	TCCR0A &= ~(1 << COM0B0);
	TCCR0A &= ~(1 << COM0A0);
	
	TCCR0B |= (1 << CS00);
	// ------------------------- //
}