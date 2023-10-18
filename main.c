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

#define BOTON PORTBx

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
ADELANTE,
DERECHA,
IZQUIERDA,
ATRAS,
SAFETY_CAR
} STATE;

typedef struct{
void (*func)();
} FSM;

STATE estado = OFF;

FSM Autito[] = {
{F_OFF},
{F_ADELANTE},
{F_DERECHA},
{F_IZQUIERDA},
{F_ATRAS},
{F_SAFETY_CAR}
};

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
	fotores = readADC(x); // cambiar
	
	if(fotores > x){ // cambiar
		PORTB |= (1 << x); // cambiar
	} else{
		PORTB &= ~(1 << x); // cambiar
	}
	_delay_ms(100);
}

void F_OFF(){
	PORTx &= ~(1 << MA1);
	PORTx &= ~(1 << MA2);
	
	PORTx &= ~(1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx &= ~(1 << LED_R);
	PORTx &= ~(1 << LED_V);
	
	if((PINx & (1 << BOTON)){
		estado = ADELANTE;
	}
}

void F_ADELANTE(){
	OCR1A = velMax;
	
	PORTx |= (1 << MA1);
	PORTx &= ~(1 << MA2);

	PORTx |= (1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx |= (1 << LED_V);
	PORTX &= ~(1 << LED_R);
	
	fotoresistor();
	
	//tiempo :)
	
	if((PINx & (1 << BOTON)){
		estado = OFF;
	} else if(/* tiempo */){
		estado = x;
		tiempo = 0;
	}
}

void F_DERECHA(){
	OCR1A = velMax;
	
	PORTx |= (1 << MA1);
	PORTx &= ~(1 << MA2);

	OCR1A = velDiff;

	PORTx |= (1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx |= (1 << LED_V);
	PORTx &= ~(1 << LED_R);
	
	fotoresistor();
	
	//tiempo :)
	
	if((PINx & (1 << BOTON)){
		estado = OFF;
	} else if(/* tiempo */){
		estado = x;
		tiempo = 0;
	}
}

void F_IZQUIERDA(){
	OCR1A = velDiff;
	
	PORTx |= (1 << MA1);
	PORTx &= ~(1 << MA2);

	OCR1A = velMax;

	PORTx |= (1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx |= (1 << LED_V);
	PORTx &= ~(1 << LED_R);
	
	fotoresistor();
	
	//tiempo :)
	
	if((PINx & (1 << BOTON)){
		estado = OFF;
	} else if(/* tiempo */){
		estado = x;
		tiempo = 0;
	}
}

void F_ATRAS(){
	OCR1A = velMid;
	
	PORTx &= ~(1 << MA1);
	PORTx |= (1 << MA2);

	PORTx &= ~(1 << MB1);
	PORTx |= (1 << MB2);
	
	PORTx &= ~(1 << LED_V);
	PORTx |= (1 << LED_R);
	
	fotoresistor();
	
	//tiempo :)
	
	if((PINx & (1 << BOTON)){
		estado = OFF;
	} else if(/* tiempo */){
		estado = x;
		tiempo = 0;
	}
}

void F_SAFETY_CAR(){
	OCR1A = velSeg;
	
	PORTx |= (1 << MA1);
	PORTx &= ~(1 << MA2);

	PORTx |= (1 << MB1);
	PORTx &= ~(1 << MB2);
	
	PORTx |= (1 << LED_V);
	PORTX &= ~(1 << LED_R);
	
	fotoresistor();
	
	//tiempo :)
	
	if((PINx & (1 << BOTON)){
		estado = OFF;
	} else if(/* tiempo */){
		estado = x;
		tiempo = 0;
	}
}

int main(void){
	
    configPWM();
	
	configPORT();
	
	configADC();
	
    while(1){
		(*Autito[estado].func)();
    }
}