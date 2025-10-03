/*! @mainpage Blinking
 *
 * \section genDesc General Description
 *
 * This example makes LED_1 blink.
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
#include <stdio.h> /*printf*/
#include <stdint.h> /*tipos de enteros como uint32_t*/
#include "freertos/FreeRTOS.h"/*para tareas y temporizaacion como vTaskDelay*/
#include "freertos/task.h" /*para tareas y temporizaacion como vTaskDelay*/
#include "led.h"/*para cosas de los leds*/
/*==================[macros and definitions]=================================*/
#define CONFIG_BLINK_PERIOD 300 /**< blink period in ms */
/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]========funciones visibles==================*/
void app_main(void){
    LedsInit(); /*inicializa los leds, sin esto ledon podria fallar*/
    while(true){ /*bucle infinito*/
        printf("LED ON\n"); 
        LedOn(LED_1); /*enciende led 1*/
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS); /*espera el periodo de parpadeo*/
        printf("LED OFF\n");
        LedOff(LED_1); /*apaga led 1*/
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
/*==================[end of file]============================================*/
