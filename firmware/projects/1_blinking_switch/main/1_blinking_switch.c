/*! @mainpage Blinking switch
 *
 * \section genDesc General Description
 *
 * This example makes LED_1 and LED_2 blink if SWITCH_1 or SWITCH_2 are pressed.
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 12/09/2023 | Document creation		                         |
 *
 * @author Albano Peñalva (albano.penalva@uner.edu.ar)
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> /*para true o false */
#include "freertos/FreeRTOS.h" /*API de FreeRTOS (delays, tareas,etc)*/
#include "freertos/task.h" /*API de FreeRTOS (delays, tareas,etc)*/
#include "led.h"
#include "switch.h" /*control de SW*/
/*==================[macros and definitions]=================================*/
#define CONFIG_BLINK_PERIOD 1000
/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/
void app_main(void){
	uint8_t teclas; //variable para guardar el estado de los SW (entera sin signo y de 8 bits)
	LedsInit();
	SwitchesInit();
    while(1)    {
    	teclas  = SwitchesRead(); //leo el estado de los SW
    	switch(teclas){
    		case SWITCH_1:
    			LedToggle(LED_1); //cambia el estado actual del led por el opuesto
    		break;
    		case SWITCH_2:
    			LedToggle(LED_2);
    		break;
    	}
	    LedToggle(LED_3);
		vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
	}
}
