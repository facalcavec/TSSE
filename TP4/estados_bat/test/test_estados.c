/**
 * @file test_estados
 * 
 * @author Felipe A. Calcavecchia
 * 
 * @date 06/12/2020 
 *
 * 
 * ------------------- test a realizar ---------------------------
 * 
 * 1) Inicialización.
 * 2) Transición a carga a FONDO cuando se conecta una batería.
 * 3) Estando en carga a FONDO, probar la transición a carga por ABSORCION (por corriente).
 * 4) Estando en carga por ABSORCION, probar la transición a carga a FLOTE (por corriente).
 * 5) Estando en carga a FONDO, probar la transición a carga por ABSORCION (por tiempo).
 * 6) Estando en carga por ABSORCION, probar la transición a carga a FLOTE (por tiempo).
 * 7) Estando en carga por ABSORCION, probar la transición a ECUALIZACION (por corriente).
 * 8) Estando en carga por ABSORCION, probar el retorno a carga a FONDO (por corriente).
 * 9) Estando en carga a FLOTE, probar el retorno a carga a FONDO (por corriente).
 * 
 */

#include "unity.h"
#include "estados.h"

stateCharge_t estadoActual;
data_t data;

void setUp( void )
{
 
}

void tearDown( void )
{

}

/* 1.test de inicialización */
void test_inicializacion( void )
{    
    state_init( &estadoActual );
    TEST_ASSERT_EQUAL_HEX16( NO_BATTERY, estadoActual);
}

/* 2. test de transición a carga a FONDO cuando se conecta una batería */
void test_detectar_bateria( void )
{
    TEST_ASSERT_EQUAL_HEX16( 0, estadoActual);
    
    data_t datosVirtuales = { (V_MIN + 1), 0, 0, 0, NO_BATTERY };
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( 1, estadoActual);
}

/* 3. test de transición de carga a FONDO a carga por ABSORCION (por corriente). */
void test_fondo_a_absorcion( void )
{
    TEST_ASSERT_EQUAL_HEX16( BULK, estadoActual);
    
    data_t datosVirtuales = { V_MAX, I_MAX, (T_MAX - 1), 0, BULK };
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( ABS, estadoActual);
}

/* 4. test de transición a carga por ABSORCION a FLOTE (por corriente). */
void test_absorcion_a_flote( void )
{
    TEST_ASSERT_EQUAL_HEX16( ABS, estadoActual);
    
    data_t datosVirtuales = { V_MAX, 119, (T_MAX - 1), 0, ABS };
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( FLOAT, estadoActual);
}

/* 5. test de transición de carga a FONDO a carga por ABSORCION (por tiempo). */
void test_fondo_a_absorcion_por_tiempo( void )
{
    data_t datosVirtuales = { (V_MIN + 1), I_MAX, 0, 0, NO_BATTERY };
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( BULK, estadoActual);

    datosVirtuales.time = T_MAX;
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( ABS, estadoActual);
}

/* 6. test de transición de carga por ABSORCION a FLOTE (por tiempo). */
void test_abs_a_flote_por_tiempo( void )
{
    TEST_ASSERT_EQUAL_HEX16( ABS, estadoActual);

    data_t datosVirtuales = { V_MAX, I_MAX, T_MAX, (COUNT_ECU - 1), ABS };
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( FLOAT, estadoActual);
}

/* 7. test de transición de carga por ABSORCION a ECUALIZACION (por corriente). */
void test_abs_a_ecualizacion( void )
{
    data_t datosVirtuales = { V_MAX, I_MIN, (T_MAX - 1), COUNT_ECU, BULK };
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( ABS, estadoActual);

    datosVirtuales.current = I_MIN -1;
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( ECU, estadoActual);
}

/* 8. test de retorno de carga por ABSORCION a FONDO (por corriente).  */
void test_abs_a_fondo( void )
{
    data_t datosVirtuales = { V_MAX, I_MIN, (T_MAX - 1), 0, BULK };
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( ABS, estadoActual);

    datosVirtuales.voltage = V_MAX * 0.9;
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( BULK, estadoActual);
}

/* 9. test de retorno de carga a FLOTE a FONDO (por corriente). */
void test_flote_a_fondo( void )
{
    data_t datosVirtuales = { V_MAX, (I_MIN - 1), (T_MAX - 1), 0, ABS };
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( FLOAT, estadoActual);

    datosVirtuales.current = I_MIN +1;
    estadoActual = state_battery( &datosVirtuales );
    TEST_ASSERT_EQUAL_HEX16( BULK, estadoActual);
}