/*! @mainpage Guia 1 - Ejercicio 2 - Blinking Switch Car
 *
 * \section 
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 20/09/2025 | Document creation		                         |
 *
 * @author Carmela Dominguez
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "switch.h"
/*==================[macros and definitions]=================================*/
#define CONFIG_BLINK_PERIOD 1000
/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/
void app_main(void){
	uint8_t teclas;
	LedsInit();
	SwitchesInit();
    while(1)    {
    	teclas  = SwitchesRead();
    	switch(teclas){
    		case SWITCH_1:
    			LedToggle(LED_1);
    		break;
    		case SWITCH_2:
    			LedToggle(LED_2);
    		break;
			case (SWITCH_1 | SWITCH_2):  // el valor constante que representa ambos a la vez
    			LedToggle(LED_3);
    		break;
		
    	}
		vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
		// if ((teclas & SWITCH_1) && (teclas & SWITCH_2)) {
		// 	LedToggle(LED_3);
		// 	vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);   otra opcion

		// }
	}
}
