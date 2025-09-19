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
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "hc_sr04.h"
#include "lcditse0803.h"
#include "switch.h"

/*==================[macros and definitions]=================================*/
// 1)Mostrar distancia medida utilizando los leds de la siguiente manera:

//a) Si la distancia es menor a 10 cm, apagar todos los LEDs.
//b) Si la distancia está entre 10 y 20 cm, encender el LED_1.
//c) Si la distancia está entre 20 y 30 cm, encender el LED_2 y LED_1.
//d) Si la distancia es mayor a 30 cm, encender el LED_3, LED_2 y LED_1.

// 2) Mostrar la distancia medida en el display LCD de 3 dígitos.
// 3) Usar TEC1 para activar y detener la medición.


// Umbrales de distancia (en cm)
#define DIST_MIN     10
#define DIST_MEDIO   20
#define DIST_ALTO    30

// Período de actualización (ms)
#define SENSOR_PERIOD_MS   500

#define CONFIG_BLINK_PERIOD_LED_1 1000
/*==================[internal data definition]===============================*/

TaskHandle_t led_task_handle = NULL;
TaskHandle_t switches_handle = NULL;

/*==================[global variables]===============================*/
volatile bool hold = false;  // Flag para pausar/reanudar medición
volatile bool HCRS_ON = true;
/*==================[internal functions declaration]=========================*/
static void LedTask(void *pvParameter){
    while(true){
        if (!hold && HCRS_ON) {  
		uint16_t distancia=HcSr04ReadDistanceInCentimeters();

        if (distancia < DIST_MIN) {
            LedOff(LED_1);
            LedOff(LED_2);
            LedOff(LED_3);

        } else if (distancia < DIST_MEDIO) {
            LedOn(LED_1);
            LedOff(LED_2);
            LedOff(LED_3);

        } else if (distancia < DIST_ALTO) {
            LedOn(LED_1);
            LedOn(LED_2);
            LedOff(LED_3);

        } else {
            LedOn(LED_1);
            LedOn(LED_2);
            LedOn(LED_3);
        }

            // Mostrar distancia en el LCD
            LcdItsE0803Write(distancia);
        }
        if (!HCRS_ON) {  
            LedOff(LED_1);
            LedOff(LED_2);
            LedOff(LED_3);
            LcdItsE0803Write(0);
        }

        // Esperar un tiempo antes de la próxima iteración
        vTaskDelay(pdMS_TO_TICKS(SENSOR_PERIOD_MS));
    }
}

static void Switches (void *pvParameter){
    while(true){
        uint8_t teclas = SwitchesRead();

        switch(teclas){
    		case SWITCH_2:
                hold=true;
    		break;
    		case SWITCH_1:
    			HCRS_ON=false;
    		break;
            case 0:
                hold=false;
                HCRS_ON=true;
    		break;
    }
        // Anti-rebote simple
        vTaskDelay(pdMS_TO_TICKS(100));
}}

/*==================[external functions definition]==========================*/
void app_main(void){
	// Inicializar hardware
	LedsInit();
	HcSr04Init(GPIO_3, GPIO_2);
	LcdItsE0803Init();
    SwitchesInit();

	// Crear tareas
	xTaskCreate(&LedTask, "LED_Task", 2048, NULL, 5, &led_task_handle);
	xTaskCreate(&Switches, "SWITCHES", 2048, NULL, 5, &switches_handle);
}
/*==================[end of file]============================================*/