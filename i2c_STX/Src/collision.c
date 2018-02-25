#include "main.h"
#include "collision.h"

void XC_config(void){
		
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_C;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_Port, &GPIO_InitStruct);
	
	GPIO_InitTypeDef GPIO_InitStruct2;
	GPIO_InitStruct2.GPIO_Pin = GPIO_Pin_Led;
	GPIO_InitStruct2.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_Port, &GPIO_InitStruct2);

}

void timer_init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
    TIM_TimeBaseInitTypeDef timerInitStructure; 
    timerInitStructure.TIM_Prescaler = 40000;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 100; // Call for collision detect every 100 ms
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    TIM_Cmd(TIM2, ENABLE);
}

void collision_detect(void){
	collide = ((GPIO_Port->IDR & GPIO_Pin_C) != (uint32_t)Bit_RESET);
	if(collide)
		GPIO_Port->BRR=1<<13;
	else
		GPIO_Port->BSRR=1<<13;
}
