/**
 * file: leds.h
 *  
 * autor: Felipe A. Calcavecchia
 * 
 * fecha :19/11/2020
 * 
 */ 

#include <stdint.h>
#include <stdbool.h>

void Leds_Create(uint16_t *puerto);
void Leds_On( uint8_t );
void Leds_Off( uint8_t );
void Led_TurnAllOn(void);
void Led_TurnAllOff(void);
bool Led_State (uint8_t led);