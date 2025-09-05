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
#include "gpio_mcu.h" /*donde están las definiciones de gpio_t, io_t, gpioConf_t, y funciones como GPIOWrite()/GPIOInit().*/
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "switch.h"


/*==================[macros and definitions]=================================*/

// 4.Escriba una función que reciba un dato de 32 bits,  la cantidad de dígitos 
// de salida y un puntero a un arreglo donde se almacene los n dígitos. La función 
// deberá convertir el dato recibido a BCD, guardando cada uno de los dígitos de 
// salida en el arreglo pasado como puntero.

// 5. Escribir una función que reciba como parámetro un dígito BCD y un vector 
// de estructuras del tipo gpioConf_t. Incluya el archivo de cabecera gpio_mcu.h



/*==================[internal data definition]===============================*/

void app_main(void){
	
	typedef struct  /* Define un tipo de dato nuevo llamado gpioConf_t.*/
	{
		gpio_t pin;			/*!guarda qué pin físico del micro vas a usar */
		io_t dir;			/*!indica la dirección del pin: entrada (IN) o salida (OUT), '0' IN;  '1' OUT*/
	} gpioConf_t;
	
	gpioConf_t b0 = {GPIO_20,GPIO_OUTPUT};
	gpioConf_t b1 = {GPIO_21,GPIO_OUTPUT};
	gpioConf_t b2 = {GPIO_22,GPIO_OUTPUT};
	gpioConf_t b3 = {GPIO_23,GPIO_OUTPUT};

	gpioConf_t vector_GPIO[4];
	vector_GPIO[0]=b0;
	vector_GPIO[1]=b1;
	vector_GPIO[2]=b2;
	vector_GPIO[3]=b3;


	void func_on_off(uint8_t bcd_number, gpioConf_t *vector_GPIO){
		uint8_t i;
		for (i=0; i<4; i++){
			
		}

	};


};



/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/

/*BCD_to_Array recibe un numero entero, la cantidad de digitos de dicho entero y un puntero que apunta a un arreglo que voy a modificar*/

void BCD_to_Array (uint32_t int_ingresado, uint8_t cant_digitos, uint8_t *array_salida){

	cant_digitos = cant_digitos - 1; //para que el índice del array vaya de 0 a 2
	for ( int i=cant_digitos; i>=0; i--){
		array_salida[i] = int_ingresado % 10; //obtengo el dígito menos significativo y lo guardo en el array
		int_ingresado = int_ingresado / 10; //elimino el dígito menos significativo
};
}

/*==================[end of file]============================================*/