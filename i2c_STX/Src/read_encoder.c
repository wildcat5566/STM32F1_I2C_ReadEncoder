#include "main.h"
#include "read_encoder.h"

int stt, dstt, stt_prev;
int xa, xb;

void XA_config(void){
		
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_A;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_Port, &GPIO_InitStruct);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_LineA;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannelA;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void XB_config(void){
		
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_B;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_Port, &GPIO_InitStruct);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_LineB;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannelB;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
}

void vars_initialize(void) {
	xa = ((GPIO_Port->IDR & GPIO_Pin_A) != (uint32_t)Bit_RESET);
	xb = ((GPIO_Port->IDR & GPIO_Pin_B) != (uint32_t)Bit_RESET);
	stt_prev = (xa != xb) + 2 * xb;
}

void EXTI0_IRQHandler(void) {
    FlagStatus f = ((EXTI->PR & EXTI_LineA) != (uint32_t)RESET);
		if (f!= RESET){
      xa = ((GPIO_Port->IDR & GPIO_Pin_A) != (uint32_t)Bit_RESET);
			xb = ((GPIO_Port->IDR & GPIO_Pin_B) != (uint32_t)Bit_RESET);
			stt = (xa != xb) + 2 * xb;
			dstt = (stt - stt_prev + 4) % 4;
			count += (dstt % 2)*(dstt - 2);
			stt_prev = stt;
			EXTI->PR = EXTI_LineA; // Clear interrupt flag
    }
}
 
void EXTI1_IRQHandler(void) {
    FlagStatus f = ((EXTI->PR & EXTI_LineB) != (uint32_t)RESET);
		if (f!= RESET){
			xa = ((GPIO_Port->IDR & GPIO_Pin_A) != (uint32_t)Bit_RESET);
			xb = ((GPIO_Port->IDR & GPIO_Pin_B) != (uint32_t)Bit_RESET);
			stt = (xa != xb) + 2 * xb;
			dstt = (stt - stt_prev + 4) % 4;
			count += (dstt % 2)*(dstt - 2);
			stt_prev = stt;
			EXTI->PR = EXTI_LineB;  
    }
}
