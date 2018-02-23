#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "i2c_STX.h"
#include "read_encoder.h"

int main(void){
	i2c_init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	XA_config();
	XB_config();
	vars_initialize();

	while (1){} // wait for interrupts
}
