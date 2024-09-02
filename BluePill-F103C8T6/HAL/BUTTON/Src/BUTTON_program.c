/***********************************************************************/
/* @file   BUTTON_program.c
 * @author Mostafa Elsayed
 * @brief This file contains the implementation for the BUTTON driver
 * @date   3/7/2024
 */

#include <stdint.h>
#include "STM32F10xxx.h"

#include "BUTTON_interface.h"

void BUTTON_voidInit(Port_t port, Pin_t pin, Config_t config)
{
    GPIO_PinConfig_t pininit = {.port = port, .pin = pin, .mode = INPUT, .config = config};
    GPIO_u8InitPin(&pininit);
}
uint8_t BUTTON_voidRead()
{
    if (GPIO_u8ReadPin(PORTA, PIN0))
    {
        // update this line when write timer driver
        for (uint8_t i = 0; i < 100000; i++)
        {
        }
        if (GPIO_u8ReadPin(PORTA, PIN0))
        {
            return 1;
        }
    }
    return 0;
}
