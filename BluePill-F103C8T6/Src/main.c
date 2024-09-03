#include <stdint.h>
#include "SystemInitialization.h"
#include "SPI_interface.h"
#include "EXTI_interface.h"
#include "LCD_interface.h"
#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

typedef enum
{
  FAILD,
  LOGED,
  NORMAL,
  ALARM
} APPState_t;

typedef struct
{
  uint8_t type;
  uint8_t Seconds;
  uint8_t Minutes;
  uint8_t Hours;
  uint8_t Day;
  uint8_t Date;
  uint8_t Month;
  uint8_t Year;
} Time_t;

Time_t time;

void DisplayNumber(uint8_t number)
{
  uint8_t firstDigit = number / 10;
  uint8_t secondDigit = number % 10;
  LCD_voidWrite(firstDigit + '0');
  LCD_voidWrite(secondDigit + '0');
}

void DisplayDataTime()
{
  LCD_voidCmd(0x80);
  DisplayNumber(time.Hours);
  LCD_voidWrite(':');
  DisplayNumber(time.Minutes);
  LCD_voidWrite(':');
  DisplayNumber(time.Seconds);
  LCD_voidCmd(0xC0);
  DisplayNumber(time.Date);
  LCD_voidWrite('/');
  DisplayNumber(time.Month);
  LCD_voidWrite('/');
  DisplayNumber(time.Year);
}

void ReceiveCallBack()
{
  if (time.type == NORMAL)
  {
    DisplayDataTime();
  }
  else if (time.type == ALARM)
  {
    GPIO_u8SetPinValue(PORTC, PIN14, HIGH);
    LCD_voidCmd(0x01);
    LCD_voidWrite('A');
    LCD_voidWrite('L');
    LCD_voidWrite('A');
    LCD_voidWrite('R');
    LCD_voidWrite('M');
  }
  else if (time.type == LOGED)
  {
    LCD_voidCmd(0x01);
    GPIO_u8SetPinValue(PORTC, PIN15,HIGH);
  }
  else if (time.type == FAILD)
  {
    GPIO_u8SetPinValue(PORTA, PIN1, HIGH);
  }
}

int main(void)
{
  SYS_Initialization();

  while (1)
  {
    SPI_u8Receive_IT(SPI1, (uint8_t *)&time, 8, ReceiveCallBack);
  }
}
