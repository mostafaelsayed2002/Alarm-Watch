#include <stdint.h>
#include "Login.h"
#include "MainMenu.h"
#include "SystemInitialization.h"

int main(void)
{
  SYS_Initialization();
  uint8_t LoginStatus = Login();
  if (!LoginStatus)
    return 0;

  while (1)
  {
    MainMenu();
  }
}
