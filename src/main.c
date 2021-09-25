/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.0.1   2018-08-27

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "main.h"
#include <stdio.h>

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  uint8_t c;
  uint8_t i = 0;
  uint8_t br = 0; // bytes received

  uint16_t pin = 0;
  uint16_t proximity = 0;
  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used. 
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates 
  *  SCB->VTOR register.
  *  E.g.  SCB->VTOR = 0x20000000;  
  */

  Input_RCC_Setup();
  Input_GPIO_Setup();
  Input_ADC_Setup();

  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Initialize LEDs */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);

  /* Turn on LEDs */
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);

  /* Initialize USB VCP */
  TM_USB_VCP_Init();
  uint16_t doggo, catto;

/*  while(1){

//	  int j = 0;
//	  for (j =0; j< 33; j++){
//		  doggo = Input_PinReq(0);
//		  delay_ms(250);
//		  catto = Input_PinReq(7);
//		  int k = 0;
//	  }
	  //doggo = (int)(doggo + Input_getADC())/2;
	  for (int k = 0; k < 15; ++k){
		  delay_ms(20);
		  doggo = Input_PinReq(i);
	  }

	  float conv = doggo*(3.0/4095);
	  if (STM_EVAL_PBGetState(BUTTON_USER))
		  i++;

	  if (i == 33)
		  i = 0;
  }*/

	while (1) {
		/* USB configured OK, drivers OK */
		if (TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED) {
			/* Turn on GREEN led */
			STM_EVAL_LEDOn(LED4);
			STM_EVAL_LEDOff(LED3);

			/**
			 * Data sent/received left to right. eg: 12 sent	. "1" received first then "2"
			 * Data is always 2 bytes thus two loops to receive & two sends required
			 * Only digits being sent.
			 */

			/* If something arrived at VCP */
			if (TM_USB_VCP_Getc(&c) == TM_USB_VCP_DATA_OK) {
				++br;

				/* Return data back */
				//TM_USB_VCP_Putc(c);

				// Check if first or second byte received
				if (br == 1){
					pin = (c - '0') * 10;
				}
				else if (br == 2){
					// Convert char to number & add to pin
					pin = (c - '0') + pin;

					proximity = Input_PinReq(pin);

					// Convert char to number
					// 01110111 = 119
					// 00001111 = 15
					//proximity = 30479;
					br = 0;
					pin = 0;

					// Send lower & upper 8 bits with a rest
					// + '0' to convert back to char
					TM_USB_VCP_Putc((proximity >> 8));
					delay_ms(100);
					TM_USB_VCP_Putc((proximity << 8) >> 8);
				}

			}
		} else {
			/* USB not OK */
			STM_EVAL_LEDOn(LED3);
			STM_EVAL_LEDOff(LED4);
		}
	}

  /* Infinite loop
  while (1)
  {
	// Input_Pin_Cycle();
	proximity = Input_getADC();

	i++;
  }*/
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}