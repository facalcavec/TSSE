/*--------- pruebas a realizar ------------------------------------- 

1 Después de la inicialización todos los LEDs deben quedar apagados.
2 Se puede prender un LED individual.
3 Se puede apagar un LED individual.
4 Se pueden prender y apagar múltiples LED’s.
5 Se pueden prender todos los LEDs de una vez.
6 Se pueden apagar todos los LEDs de una vez.
7 Se puede consultar el estado de un LED.

---------------------------------------------------------------------
*/

#include "unity.h"
#include "leds.h"

#define ON 0x0001
#define OFF 0

uint16_t ledsVirtuales;
uint16_t estadoLed;

void setUp( void )
{
    Leds_Create( &ledsVirtuales );
}

void tearDown( void )
{

}

// primer test despues de crear la tarea LEDs
void test_LedsOfAfterCreate( void )
{
    uint16_t ledsVirtuales = 0xFFFF;
    Leds_Create( &ledsVirtuales );
    TEST_ASSERT_EQUAL_HEX16( 0, ledsVirtuales);
}

// se prende un LED individual
void test_prender_led_individual( void )
{
    Leds_On(1);
    TEST_ASSERT_EQUAL_HEX16( 1, ledsVirtuales);
}

// se apaga un LED individual
void test_apagar_led_individual( void )
{
    Leds_On(1);
    Leds_Off(1);
    TEST_ASSERT_EQUAL_HEX16( 0, ledsVirtuales);
}

// se prende y apaga multiples LED's
void test_prender_apagar_multiple( void )
{
    Leds_On(3);
    Leds_On(4);
    Leds_Off(3);
    TEST_ASSERT_EQUAL_HEX16( 1 << 3, ledsVirtuales);
}

// se prende todos los LEDs
void test_prender_todos(void) 
{
    Led_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}

// se apagan todos los LEDs
void test_apagar_todos(void) 
{
    Led_TurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0, ledsVirtuales);
}

// se consulta el estado de un LED
void test_estado_led(void)
{
    Leds_On(12);
    estadoLed = Estado_de_un_Led(12);
    TEST_ASSERT_EQUAL_HEX( ON, estadoLed );
}