/*! @mainpage guia1 ej 3
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
 * | 20/09/2025 | Document creation		                         |
 *
 * @author Carmela Dominguez
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



void manejar_leds(struct my_leds *led){  //la funcion recibe un puntero a la estructura
		switch (led->mode){ //elijo el campo de la estructura
			case ON:
				LedOn(led->n_led); //enciende el n_led
			break;
			case OFF:
				LedOff(led->n_led);
			break;
			case TOGGLE:
				int i;
				for (i=0; i < (led->n_ciclos)*2; i++) {
					LedToggle(led->n_led); //cambia el estado actual del led por el opuesto
					vTaskDelay(led->periodo / portTICK_PERIOD_MS);
				}
				LedOff(led->n_led); //apaga el led al finalizar los ciclos aun q no sean pares
				break;
			}		


	};

void app_main(void){
	LedsInit();
		struct my_leds leds = {ON,LED_3,10,500};
		manejar_leds(&leds);

		leds.mode = TOGGLE; //reconfiguro leds
		leds.n_led= LED_1;
		leds.n_ciclos = 10;
		leds.periodo = 500;
		
		manejar_leds(&leds); //llamo la funcion y le paso la direccion de memoria de la variable estructura
		
		while(1){ //bucle infinito para que no termine el programa

 
		}
}
/*==================[end of file]============================================*/