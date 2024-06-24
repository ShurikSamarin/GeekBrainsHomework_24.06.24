// STM32 Nucleo-L031K6 traffic light with button example
// Simulation: https://wokwi.com/projects/401576505871981569

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stm32l0xx_hal.h>

#define LED_PORT                GPIOA
#define RED_PIN                 GPIO_PIN_0
#define YELLOW_PIN              GPIO_PIN_1
#define GREEN_PIN               GPIO_PIN_3

#define LED_PORT2                GPIOB
#define RED_PIN2                 GPIO_PIN_1
#define YELLOW_PIN2              GPIO_PIN_6
#define GREEN_PIN2               GPIO_PIN_7

#define BUTTON_PORT                GPIOB
#define BUTTON_PIN                 GPIO_PIN_0

#define LED_PORT_CLK_ENABLE     __HAL_RCC_GPIOB_CLK_ENABLE
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_RX_Pin GPIO_PIN_15

void initGPIO(int port,int led)
{
  GPIO_InitTypeDef GPIO_Config;

  GPIO_Config.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Config.Pull = GPIO_NOPULL;
  GPIO_Config.Speed = GPIO_SPEED_FREQ_HIGH;

  //GPIO_Config.Pin = LED_PIN;
   GPIO_Config.Pin = led;

  LED_PORT_CLK_ENABLE();
  HAL_GPIO_Init(port, &GPIO_Config);

  __HAL_RCC_GPIOB_CLK_ENABLE();
}


int main(void)
{
  HAL_Init();
  SystemClock_Config();

  initGPIO(LED_PORT ,RED_PIN);
  initGPIO(LED_PORT ,YELLOW_PIN);
  initGPIO(LED_PORT ,GREEN_PIN);

  initGPIO(LED_PORT2 ,RED_PIN2);
  initGPIO(LED_PORT2 ,YELLOW_PIN2);
  initGPIO(LED_PORT2 ,GREEN_PIN2);

  while (1)
  {
      HAL_GPIO_WritePin(LED_PORT ,RED_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_PORT ,YELLOW_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_PORT ,GREEN_PIN, GPIO_PIN_SET);

      HAL_GPIO_WritePin(LED_PORT2 ,RED_PIN2, GPIO_PIN_SET);
      HAL_GPIO_WritePin(LED_PORT2 ,YELLOW_PIN2, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(LED_PORT2 ,GREEN_PIN2, GPIO_PIN_RESET);

      if (HAL_GPIO_ReadPin(BUTTON_PORT,BUTTON_PIN)==GPIO_PIN_SET)
      {
        HAL_GPIO_WritePin(LED_PORT ,GREEN_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PORT ,YELLOW_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PORT2 ,RED_PIN2, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PORT2 ,YELLOW_PIN2, GPIO_PIN_SET);
        HAL_Delay(2000);

        HAL_GPIO_WritePin(LED_PORT ,YELLOW_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PORT ,RED_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PORT2 ,YELLOW_PIN2, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PORT2 ,GREEN_PIN2, GPIO_PIN_SET);
        HAL_Delay(2000);

        HAL_GPIO_WritePin(LED_PORT ,YELLOW_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PORT ,RED_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_PORT2 ,YELLOW_PIN2, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_PORT2 ,GREEN_PIN2, GPIO_PIN_RESET);
        HAL_Delay(2000);
      };
  };

  return 0;
}
