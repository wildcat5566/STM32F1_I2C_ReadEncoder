#include "main.h"
#include "i2c_STX.h"
#include "collision.h"
#include "read_encoder.h"
int count;
int collide;

int main(void){
	count = 0;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	i2c_init();
	timer_init();
	
	XA_config();
	XB_config();
	XC_config();
	
	vars_initialize();
	
	while (1){
			int timerValue = TIM_GetCounter(TIM2);
        if (timerValue == 0)
            collision_detect();
	} // wait for interrupts
}
