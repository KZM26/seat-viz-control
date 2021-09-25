/*
 * input.h
 *
 *  Created on: 27 Aug 2018
 *      Author: KZM
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4_discovery.h"

#define ARRAY_GPIO				GPIOD

// Define the column select pins & populate in array for the pins
#define COL_SELECT_PIN_0		GPIO_Pin_0 // Green
#define COL_SELECT_PIN_1		GPIO_Pin_1 // Purple
#define COL_SELECT_PIN_2 		GPIO_Pin_2 // Blue

// Define the row select pins & populate in array for the pins
#define ROW_SELECT_PIN_0		GPIO_Pin_3 // Orange
#define ROW_SELECT_PIN_1		GPIO_Pin_6 // Grey
#define ROW_SELECT_PIN_2 		GPIO_Pin_7 // Brown

// ADC Pin
#define ADC_GPIO				GPIOB
#define ADC_NUMBER				ADC1
#define ADC_NUMBER_RCC			RCC_APB2Periph_ADC1
#define ADC_INPUT_PIN			GPIO_Pin_1
#define ADC_CHANNEL				ADC_Channel_9
#define ADC_GPIO_RCC 			RCC_AHB1Periph_GPIOB

void Input_GPIO_Setup(void);
void Input_Pin_Cycle(void);
void Input_ADC_Setup(void);
void Input_RCC_Setup(void);

uint16_t Input_getADC(void);
uint16_t Input_PinReq(uint8_t pin);
void delay_ms(uint32_t milli);

#endif /* INPUT_H_ */
