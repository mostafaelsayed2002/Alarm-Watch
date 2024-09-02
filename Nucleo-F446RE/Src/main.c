#include <stdint.h>
#include "Login.h"
#include "MainMenu.h"
#include "SystemInitialization.h"

#include "SYSTICK_interface.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "STM32F466xx.h"
#include "CommonMacros.h"

SPI_RegDef_t *SPIx[3] = {SPI1, SPI2, SPI3};

void initMaster()
{
  // 8bit data frame format
  CLEAR_BIT(SPI2->CR1, DFF);

  // CPOL: Zero or One start
  CLEAR_BIT(SPI2->CR1, CPOL);

  // CPHA: First or Second edge
  CLEAR_BIT(SPI2->CR1, CPHA);

  // MSB or LSB first
  CLEAR_BIT(SPI2->CR1, LSBFIRST);

  // Software slave management
  CLEAR_BIT(SPI2->CR1, SSM);
  SET_BIT(SPI2->CR2, SSOE);

  // Baud rate
  SPI2->CR1 &= ~(0b111 << BR);
  SPI2->CR1 |= (0b111 << BR);

  // Master or Slave
  SET_BIT(SPI2->CR1, MSTR);

  // Enable SPI
  SET_BIT(SPI2->CR1, SPE);
}

int main(void)
{
  SYS_Initialization();
  initMaster();

  uint8_t value[4] = {0x41, 0x42, 0x43, 0x44};
  SPI_u8Transmit_IT(1, value, 4);

  while (1)
  {
  }
}
