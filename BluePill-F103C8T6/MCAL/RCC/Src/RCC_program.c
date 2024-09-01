/***********************************************************************/
/* @file   RCC_program.c
 * @author Mostafa Elsayed
 * @brief  This file contains the implementation for RCC driver
 * @date   2/7/2024
 */

#include <stdint.h>
#include "STM32F10xxx.h"

#include "RCC_interface.h"
#include "RCC_private.h"

void RCC_voidAPB2EnablePeripheralClock(uint8_t peripheral)
{
    RCC->APB2ENR |= (1 << peripheral);
}