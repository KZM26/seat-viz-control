/*
 * input.c
 *
 *  Created on: 27 Aug 2018
 *      Author: KZM
 */

#include "input.h"

// Define column and row arrays based on pins
uint16_t ColArray[3] = {COL_SELECT_PIN_0, COL_SELECT_PIN_1, COL_SELECT_PIN_2};
uint16_t RowArray[3] = {ROW_SELECT_PIN_0, ROW_SELECT_PIN_1, ROW_SELECT_PIN_2};

#define BUTTON_GPIO 			GPIOB

/**
 * @brief  Initialize the GPIO on pins PB1, PB11, PB13, PB15 for push button input
 * @param  None
 * @retval None
 */
void Input_GPIO_Setup(void) {

	 GPIO_InitTypeDef GPIO_InitStructure;

	 GPIO_InitStructure.GPIO_Pin = ADC_INPUT_PIN;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	 //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	 GPIO_Init(ADC_GPIO, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = COL_SELECT_PIN_0 | COL_SELECT_PIN_1 | COL_SELECT_PIN_2 | ROW_SELECT_PIN_0 | ROW_SELECT_PIN_1 | ROW_SELECT_PIN_2;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	 //Output type push-pull
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	 GPIO_Init(ARRAY_GPIO, &GPIO_InitStructure);
}

/**
 * @brief  Setup ADC1 to use pin PB1
 * @param  None
 * @retval None
 */
void Input_ADC_Setup(void) {
	// Put ADCs in default state
	ADC_DeInit();

	// Configure the ADC
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; // provides smallest range greater than the range of volumes available
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_NbrOfConversion=1;

	// perform setup and enable
	ADC_Init(ADC_NUMBER, &ADC_InitStructure);
	ADC_Cmd(ADC_NUMBER, ENABLE);
	ADC_RegularChannelConfig(ADC_NUMBER, ADC_CHANNEL, 1, ADC_SampleTime_3Cycles);
}

/**
  * @brief  RCC Setup
  * @param  None
  * @retval None
  */
void Input_RCC_Setup(void){
	// ADC interface clock
	RCC_APB2PeriphClockCmd(ADC_NUMBER_RCC, ENABLE);
	// GPIO clock
	RCC_AHB1PeriphClockCmd(ADC_GPIO_RCC | RCC_AHB1Periph_GPIOD, ENABLE);

}
/**
  * @brief  Cycle through array of col/row and toggle pin with delay
  * @param  None
  * @retval None
  */
void Input_Pin_Cycle(void){

	uint32_t i,j;

	for (i = 0; i < 3; i++)
	{
		GPIO_ToggleBits(ARRAY_GPIO, ColArray[i]);

		for (j = 0; j < 3; j++)
		{
			GPIO_ToggleBits(ARRAY_GPIO, RowArray[j]);
			delay_ms(200);
			GPIO_ToggleBits(ARRAY_GPIO, RowArray[j]);
		}

		GPIO_ToggleBits(ARRAY_GPIO, ColArray[i]);
	}
}

/**
  * @brief  Get ADC value
  * @param  None
  * @retval ADC 16 bit value
  */
uint16_t Input_getADC(void){

	delay_ms(1);
	ADC_SoftwareStartConv(ADC_NUMBER);

	// Wait for the value
	while(!ADC_GetFlagStatus(ADC_NUMBER, ADC_FLAG_EOC));

	return ADC_GetConversionValue(ADC_NUMBER);
}

/**
  * @brief  Get Pin value
  * @param  Pin ID
  * @retval ADC 16 bit value
  */
uint16_t Input_PinReq(uint8_t pin){

	uint8_t col = pin % 6; //+ 1;
	uint8_t row = 0;
	int i = 0;

	if (0 <= pin && pin < 6)
		row = 0;
	else if (6 <= pin && pin < 12)
		row = 1;
	else if (12 <= pin && pin < 18)
		row = 2;
	else if (18 <= pin && pin < 24)
		row = 3;
	else if (24 <= pin && pin < 30)
		row = 4;
	else if (30 <= pin && pin < 33)
		row = 5;
	else
		return 0;

	//row += 1;

	GPIO_Write(ARRAY_GPIO, 0);

	for (i = 0; i < 3; i++)
	{
		if  (col & (1 << i))
			GPIO_ToggleBits(ARRAY_GPIO, ColArray[i]);

		if  (row & (1 << i))
			GPIO_ToggleBits(ARRAY_GPIO, RowArray[i]);
	}

	// Wait a bit before reading

	return Input_getADC();
}
/**
  * @brief  Delay in ms
  * @param  integer amount of milliseconds
  * @retval None
  */
void delay_ms(uint32_t milli)
{
	uint32_t delay = milli * 17612;              // approximate loops per ms at 168 MHz, Debug config
	for(; delay != 0; delay--);
}
