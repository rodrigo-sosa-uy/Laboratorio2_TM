#ifndef FOTORRESISTOR_H
#define FOTORRESISTOR_H

#include "fotorresistor.c"

void configADC();
uint16_t readADC(uint8_t canal);
void fotoresistor();

#endif