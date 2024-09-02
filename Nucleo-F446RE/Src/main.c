#include <stdint.h>
#include "Login.h"
#include "MainMenu.h"
#include "SystemInitialization.h"
#include "DS1307_interface.h"
#include "ErrType.h"

int main(void)
{
  SYS_Initialization();
  uint8_t loginStatus = Login();
  while (loginStatus == FAILD)
    ;
  while (1)
  {
    MainMenu();
  }
}
