/*! @mainpage Template
 *
 * @section genDesc General Description
 *
 * This section describes how the program works.
 *
 * <a href="https://drive.google.com/...">Operation Example</a>
 *
 * @section hardConn Hardware Connection
 *
 * |    Peripheral  |   ESP32   	|
 * |:--------------:|:--------------|
 * | 	PIN_X	 	| 	GPIO_X		|
 *
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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "switch.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/
enum{ON, OFF, TOGGLE};
struct my_leds{
	uint8_t mode;            //ON, OFF, TOGGLE
	uint8_t n_led;          //indica el número de led a controlar   
	uint8_t n_ciclos;      //indica la cantidad de ciclos de encendido/apagado
	uint16_t periodo;     //indica el tiempo de cada ciclo
};



void manejar_leds(struct my_leds *led){
		switch (led->mode){
			case ON:
				LedOn(led->n_led);
			break;
			case OFF:
				LedOff(led->n_led);
			break;
			case TOGGLE:
				int i;
				for (i=1; i < (led->n_ciclos)*2; i++) {
					LedToggle(led->n_led);
					vTaskDelay(led->periodo / portTICK_PERIOD_MS);
				}
				LedOff(led->n_led);
				break;
			}		


	};

void app_main(void){
	LedsInit();
		struct my_leds led1 = {ON,LED_3,10,500};
		manejar_leds(&led1);

		led1.mode = TOGGLE;
		led1.n_led= LED_1;
		led1.n_ciclos = 10;
		led1.periodo = 500;
		
		manejar_leds(&led1);
		
		while(1){

 
		}
}
/*==================[end of file]============================================*/