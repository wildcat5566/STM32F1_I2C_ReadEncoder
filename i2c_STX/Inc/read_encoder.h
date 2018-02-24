#define GPIO_Port  GPIOA
#define GPIO_Pin_A GPIO_Pin_0
#define GPIO_Pin_B GPIO_Pin_1
#define EXTI_LineA EXTI_Line0
#define EXTI_LineB EXTI_Line1
#define NVIC_IRQChannelA EXTI0_IRQn;
#define NVIC_IRQChannelB EXTI1_IRQn;

void XA_config(void);
void XB_config(void);
void vars_initialize(void);

