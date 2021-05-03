#include "stm32f4xx.h"

GPIO_InitTypeDef  GPIO_InitStructure;

void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}

int main(void) {
  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure PF4, PD5 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  while (1) {
    // orange und rote LED des STM32F469 Discovery Boards abwechseln blinken lassen
    GPIOD->BSRRL = GPIO_Pin_4;
    GPIOD->BSRRH = GPIO_Pin_5;
    Delay(5000000L);

    GPIOD->BSRRL = GPIO_Pin_5;
    GPIOD->BSRRH = GPIO_Pin_4;
    Delay(5000000L);
  }
}
