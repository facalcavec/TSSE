/**
 * file: leds.h
 *  
 * autor: Felipe A. Calcavecchia
 * 
 * fecha :19/11/2020
 * 
 */ 

#include <stdint.h>

void Leds_Create(uint16_t *puerto);
void Leds_On( uint8_t );
void Leds_Off( uint8_t );
void Led_TurnAllOn(void);
void Led_TurnAllOff(void);
uint8_t Estado_de_un_Led (uint8_t led);