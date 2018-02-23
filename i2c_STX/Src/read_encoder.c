#include "stm32f10x.h"          
#include "stm32f10x_gpio.h"     // Pins Interface
#include "stm32f10x_rcc.h"      // Enable peripheral clock
#include "stm32f10x_exti.h"     // External interruption
#include "misc.h"     // Connect exti and gpio
#include "read_encoder.h"

int xa, xb;                     // Encoder channel A 
int stt, dstt, stt_prev;
int count = 0;

void XA_config(void){ //A0
		
	GPIO_InitTypeDef GPIO_InitStruct;                  // GPIO Struct oobject
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;             // Use pin#0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;          // Pinmode = In
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;     // 50 MHZ (max) clock freq
	GPIO_Init(GPIOA, &GPIO_InitStruct);                // Init pin A0
	
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;         // #0 pins connected to line #0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;    // Choose priority among 0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void XB_config(void){ //A3
		
	GPIO_InitTypeDef GPIO_InitStruct;                  // GPIO Struct oobject
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;             // Use pin#0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;          // Pinmode = In
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;     // 50 MHZ (max) clock freq
	GPIO_Init(GPIOA, &GPIO_InitStruct);                // Init pin A0
	
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);
	
	EXTI_InitTypeDef EXTI_InitStructure2;
	EXTI_InitStructure2.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure2.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure2.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure2.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure2);
	
	NVIC_InitTypeDef NVIC_InitStructure2;
	NVIC_InitStructure2.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure2.NVIC_IRQChannelSubPriority        = 2;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure2);
}

void vars_initialize(void) {
	xa = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	xb = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
	stt_prev = (xa != xb) + 2 * xb;
}

void EXTI9_5_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) { // interrupt flag set
        xa = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
				xb = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
				stt = (xa != xb) + 2 * xb;
				dstt = (stt - stt_prev + 4) % 4;
				count += (dstt % 2)*(dstt - 2);
				stt_prev = stt;
				EXTI_ClearFlag(EXTI_Line0); 
        EXTI_ClearITPendingBit(EXTI_Line0);      // Clear interrupt flag
    }
}
 
void EXTI15_10_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
        xa = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
				xb = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
				stt = (xa != xb) + 2 * xb;
				dstt = (stt - stt_prev + 4) % 4;
				count += (dstt % 2)*(dstt - 2);
				stt_prev = stt;
				EXTI_ClearFlag(EXTI_Line3); 
        EXTI_ClearITPendingBit(EXTI_Line3); 
    }
}
