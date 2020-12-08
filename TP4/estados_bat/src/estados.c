/**
 * @file estados.c
 * 
 * @author Felipe A. Calcavecchia
 * 
 * @date 06/12/2020 
 *
 * 
 * -------------------------- Descripción ---------------------------------
 * 
 * Este módulo de software controla la transición de los estados por los 
 * que pasa la carga de una batería. Estos estados van a depender de la 
 * tensión medida, la corriente suministrada, el tiempo transcurrido 
 * y la cantidad de cargas realizadas.
 * 
 * Dichos estados son:
 *  NO_BATTERY: No detecta una batería conectada al cargador
 *  BULK: primera etapa de carga ( CARGA A FONFO )
 *  ABS: segunda etapa de carga ( CARGA POR ABSORCIÓN )
 *  FLOAT: tercera etapa de carga ( CARGA A FLOTE )
 *  ECU: cuarta etapa de carga ( ECUALIZACION )
 * 
 */

#include "estados.h"

stateCharge_t *stateCharge;

/* Función que inicializa la etapa de carga */
void state_init ( stateCharge_t *stateCharge )
{
    stateCharge = NO_BATTERY;
}

/* Función que determina la etapa de carga */
stateCharge_t state_battery( data_t *data )
{
    /* selección de la nueva etapa de carga de acuerdo a la anterior */
    switch ( data->charge_state )
    {
    
        case NO_BATTERY:
            /* sale de NO_BATTERY si la tensión medida alcanzó V_MIN */
            if( data->voltage >= V_MIN )
            {
                data->charge_state = BULK;
                data->time = 0;
            }
            break;
        
        case BULK:
            /* sale de BULK si la tensión llegó a V_MAX o el tiempo expiro */
            if( data->voltage >= V_MAX || data->voltage >= T_MAX )
            {
                data->charge_state = ABS;
                data->time = 0;
            }
            break;

        case ABS:
            /* sale de ABS si la corriente es menor a I_MIN o si el tiempo expiro */
            if(( data->current < I_MIN || data->time >= T_MAX ) && data->voltage >= V_MAX )
            {
                /* si el contador de cargas es menor a COUNT_ECU, va a ABS, sino a ECU */
                if( data->count < COUNT_ECU )
                {
                    data->charge_state = FLOAT;
                    data->count ++;
                }                
                else
                {
                    data->charge_state = ECU;
                    data->count = 0;
                }
            }
            
            /* vuele a BULK si la tensión medida cae al 90% de V_MAX */
            if( data->voltage <= (0.9 * V_MAX ))
            {
                data->charge_state = BULK;
                data->time = 0;
            } 

            break;

        case FLOAT:
            /* vuele a BULK si la corriente supera I_MIN */
            if( data->current > I_MIN )
            {
                data->charge_state = BULK;
                data->time = 0;
            }

            break;    
        
        default:
            break;
    }

    return (data->charge_state);   
}