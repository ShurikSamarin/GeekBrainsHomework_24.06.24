// STM32 Nucleo-L031K6 traffic light simple example
// Simulation: https://wokwi.com/projects/401574087289289729

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stm32l0xx_hal.h>

#define LED_PORT                GPIOA
#define LED_PIN                 GPIO_PIN_0
#define YELLOW_PIN              GPIO_PIN_1
#define GREEN_PIN               GPIO_PIN_3
#define LED_PORT_CLK_ENABLE     __HAL_RCC_GPIOB_CLK_ENABLE
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_RX_Pin GPIO_PIN_15


void initGPIO(int led)
{
  GPIO_InitTypeDef GPIO_Config;

  GPIO_Config.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Config.Pull = GPIO_NOPULL;
  GPIO_Config.Speed = GPIO_SPEED_FREQ_HIGH;

  //GPIO_Config.Pin = LED_PIN;
   GPIO_Config.Pin = led;

  LED_PORT_CLK_ENABLE();
  HAL_GPIO_Init(LED_PORT, &GPIO_Config);

  __HAL_RCC_GPIOB_CLK_ENABLE();
}

void SwitchLight(int led,int time)
{
    HAL_GPIO_WritePin(LED_PORT, led,GPIO_PIN_SET); 
    HAL_Delay(time);
    HAL_GPIO_WritePin(LED_PORT, led,GPIO_PIN_RESET);
}

void ToggleLight(int led, int time)
{
    for(int i =1; i<4; i++)
    {
      HAL_Delay(time);
      HAL_GPIO_WritePin(LED_PORT, led,GPIO_PIN_SET); 
      HAL_Delay(time);
      HAL_GPIO_WritePin(LED_PORT, led,GPIO_PIN_RESET);
    }
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  initGPIO(LED_PIN);
  initGPIO(YELLOW_PIN);
  initGPIO(GREEN_PIN);

  while (1)
  {
      SwitchLight(LED_PIN,3000);
      SwitchLight(YELLOW_PIN,1500);
      SwitchLight(GREEN_PIN,3000);
      ToggleLight(GREEN_PIN,500);
      SwitchLight(YELLOW_PIN,1500);
  };

  return 0;
}
