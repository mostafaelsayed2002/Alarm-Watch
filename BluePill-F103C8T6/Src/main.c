#include <stdint.h>
#include "SystemInitialization.h"
#include "SPI_interface.h"
#include "EXTI_interface.h"
#include "LCD_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

uint8_t res[4];

void ReceiveCallBack()
{

  if (res[0] == 0x41)
  {
    GPIO_u8SetPinValue(PORTA, PIN2, 1);
  }
  if (res[1] == 0x42)
  {
    GPIO_u8SetPinValue(PORTA, PIN1, 1);
  }
  if (res[2] == 0x43)
  {
    GPIO_u8SetPinValue(PORTC, PIN15, 1);
  }
  if (res[3] == 0x44)
  {
    GPIO_u8SetPinValue(PORTC, PIN14, 1);
  }
}

int main(void)
{
  SYS_Initialization();
  SPI_u8Receive_IT(SPI1, res, 4, ReceiveCallBack);

  while (1)
  {
  }
}
