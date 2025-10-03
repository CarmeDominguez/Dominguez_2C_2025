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
#include "timer_mcu.h"
#include "uart_mcu.h"

/*==================[macros and definitions]=================================*/

//Cree un nuevo proyecto en el que modifique la actividad del punto 2 agregando 
//ahora el puerto serie. Envíe los datos de las mediciones para poder observarlos 
//en un terminal en la PC, siguiendo el siguiente formato:


// Umbrales de distancia (en cm)
#define DIST_MIN     10
#define DIST_MEDIO   20
#define DIST_ALTO    30

// Período de actualización (ms)
#define SENSOR_PERIOD_MS   500

#define CONFIG_BLINK_PERIOD_LED_1 1000

#define CONFIG_TIMER_US 1000000 //1s

/*==================[internal data definition]===============================*/

TaskHandle_t led_task_handle = NULL;


/*==================[global variables]===============================*/
volatile bool hold = false;  // Flag para pausar/reanudar medición
volatile bool HCRS_ON = true;

/*==================[internal functions declaration]=========================*/


// Función de interrupción del timer
void FuncTimerA(void* param){ 
    vTaskNotifyGiveFromISR(led_task_handle, pdFALSE);    /* Envía una notificación a la tarea asociada al LED_1 */
}
//Cuando el timer vence, desde interrupción manda una notificación a la tarea LedTask.
//Reemplaza el vTaskDelay por la espera de notificación

timer_config_t timer_lector = {				
    .timer   = TIMER_A,        
    .period  = CONFIG_TIMER_US,     
    .func_p  = FuncTimerA,   //callback
    .param_p = NULL            
};


static void LedTask(void *pvParameter){
    while(true){
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);   /*espera en este punto hasta recibir una notificación */
        
        if (!hold && HCRS_ON) {  
		    uint16_t distancia=HcSr04ReadDistanceInCentimeters();
			
			
            
            // Enviar por UART: "DDD cm\r\n"
            UartSendString(UART_PC,(char *) UartItoa(distancia, 10));    // valor numérico
            UartSendString(UART_PC, " cm\r\n");   // unidad y salto de línea

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
		
    }
	
}


static void Apagador(void *args) {
    HCRS_ON = !HCRS_ON;
}
static void Mantenedor(void *args) {
    hold = !hold;
}



/*==================[external functions definition]==========================*/
void app_main(void){
	// Inicializar hardware
	LedsInit();
	HcSr04Init(GPIO_3, GPIO_2);
	LcdItsE0803Init();
    SwitchesInit();
    TimerInit(&timer_lector);

	serial_config_t uart_config = {
    .port = UART_PC,        // puerto conectado a la PC
    .baud_rate = 9600,    // velocidad de transmisión
    .func_p = UART_NO_INT,  // no necesitamos interrupción para leer
    .param_p = NULL
	};

	UartInit(&uart_config);

    //Comienzo a contar timer A
    TimerStart(TIMER_A);


    // Activar interrupciones de teclas
    SwitchActivInt(SWITCH_1, Apagador, NULL);
    SwitchActivInt(SWITCH_2, Mantenedor, NULL);


	// Crear tareas
	xTaskCreate(&LedTask, "LED_Task", 2048, NULL, 5, &led_task_handle);
}
/*==================[end of file]============================================*/