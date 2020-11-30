/**
 * file: leds.c
 * 
 * archivo de produccion para encender LEDs
 * 
 * autor: Felipe A. Calcavecchia
 * 
 * fecha :19/11/2020
 * 
 */ 

#include "leds.h"

#define LEDS_ALL_OFF    0x0000
#define LEDS_ALL_ON     0xFFFF
#define LSB 1
#define LEDS_MASK 0x0001

static uint16_t estado;
static uint16_t *leds;

// mascara para setear un LED determinado
uint16_t LedToMask( uint8_t led )
{
    return (1 << (led - 1));
}

// actualizacion del puerto 
static void Leds_HardwareUpdate(void) 
{
   *leds = estado;
}

// inicializacion y definicion del puerto
void Leds_Create(uint16_t *puerto)
{
    leds = puerto;
    estado = LEDS_ALL_OFF;
    Leds_HardwareUpdate();
}

// funcion para encender un LED
void Leds_On( uint8_t led)
{
    estado |= LedToMask( led );
    Leds_HardwareUpdate();
}

// funcion para apagar un LED
void Leds_Off( uint8_t led)
{
    estado &= ~LedToMask( led );
    Leds_HardwareUpdate();
}

// funcion para prender todos los LEDs
void Led_TurnAllOn(void) 
{
   estado = LEDS_ALL_ON;
   Leds_HardwareUpdate();
}

// funcion para apagar todos los LEDs
void Led_TurnAllOff(void) 
{
   estado = LEDS_ALL_OFF; 
   Leds_HardwareUpdate();  
}

// consulta el estado de un LED
bool Led_State (uint8_t led)
{
    return ((*leds >> (led - LSB)) & LEDS_MASK);
}