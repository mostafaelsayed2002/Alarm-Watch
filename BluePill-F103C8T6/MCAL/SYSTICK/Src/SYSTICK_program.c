/***********************************************************************/
/* @file   SYSTICK_program.c
 * @author Mostafa Elsayed
 * @brief  This file contains the implementation for the SYSTICK driver
 * @date   29/6/2024
 */
#include <stdint.h>
#include "STM32F10xxx.h"
#include "SYSTICK_interface.h"
#include "SYSTICK_private.h"

void SYSTICK_voidDelayms(uint32_t timems)
{
    uint32_t Ftick = SYSTICK_AHB_CLOCK / 8;
    STK->VAL = 0;
    // AHB/8
    STK->CTRL &= ~(1 << 2);
    STK->LOAD = (timems / 1000.0) * Ftick;
    STK->CTRL |= 1 << 0;

    while (((STK->CTRL >> 16) & 1) == 0)
        ;
    STK->CTRL &= ~(1 << 0);
    STK->VAL = 0;
}
void SYSTICK_voidDelayus(uint32_t timeus)
{
    uint32_t Ftick = SYSTICK_AHB_CLOCK / 8;

    STK->VAL = 0;
    // AHB/8
    STK->CTRL &= ~(1 << 2);
    STK->LOAD = (timeus / 1000000.0) * Ftick;
    STK->CTRL |= 1 << 0;

    while (((STK->CTRL >> 16) & 1) == 0)
        ;
    STK->CTRL &= ~(1 << 0);
    STK->VAL = 0;
}
