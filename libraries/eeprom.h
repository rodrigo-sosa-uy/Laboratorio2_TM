#ifndef EEPROM_H
#define EEPROM_H

#include "eeprom.c"

void writeEEPROM(uint8_t choques, uint16_t addr);
void CRASH();

#endif