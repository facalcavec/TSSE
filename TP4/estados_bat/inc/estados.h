/**
 * @file estados.h
 * 
 * @author Felipe A. Calcavecchia
 * 
 * @date 06/12/2020 
 */


#include <stdint.h>
#include <stdbool.h>

#define V_MIN       3600
#define V_MAX       5880
#define I_MIN       120
#define I_MAX       1200
#define T_MAX       360
#define COUNT_ECU   5

typedef enum { NO_BATTERY, BULK, ABS, FLOAT, ECU }stateCharge_t;

typedef struct
{
    uint16_t voltage;
    uint16_t current;
    uint16_t time;
    uint16_t count;
    stateCharge_t charge_state;
}data_t;

/**
 * @brief Rutina de inicialización del estado de carga
 * 
 * @param stateCharge puntero que determina la etapa de carga
 */
void state_init( stateCharge_t * );

/**
 * @brief Rutina que selecciona la nueva etapa de carga
 * 
 * @details devueve un stateCharge_t con el valor del nuevo estado
 * dependiendo de los parámetros medidos como la tensión , la corriente
 * el tiempo y el nro de cargas.
 * 
 * @param [in] data puntero a una extructura con todos los valores medibles
 * @param [out] valor del tipo stateCharge_t
 */
stateCharge_t state_battery( data_t * );
