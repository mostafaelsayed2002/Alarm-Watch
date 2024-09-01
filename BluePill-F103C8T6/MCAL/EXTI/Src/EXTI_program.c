#include "EXTI_interface.h"
#include "CommonMacros.h"
#include "STM32F10xxx.h"
#include "ErrType.h"

static void (*EXTI_Callbacks[20])(void);

uint8_t EXTI_Enable(EXTI_Line_t line, EXTI_Trigger_t trigger, void (*callback)(void))
{
    if (line < EXTI_LINE0 || line > EXTI_LINE19)
    {
        return NOK;
    }
    if (trigger < EXTI_RISING_EDGE || trigger > EXTI_RISING_FALLING_EDGE)
    {
        return NOK;
    }
    EXIT->IMR |= (1 << line);
    if (trigger == EXTI_RISING_EDGE)
    {
        EXIT->RTSR |= (1 << line);
    }
    else if (trigger == EXTI_FALLING_EDGE)
    {
        EXIT->FTSR |= (1 << line);
    }
    else if (trigger == EXTI_RISING_FALLING_EDGE)
    {
        EXIT->RTSR |= (1 << line);
        EXIT->FTSR |= (1 << line);
    }
    EXTI_Callbacks[line] = callback;
    return OK;
}

uint8_t EXTI_Disable(EXTI_Line_t line)
{
    if (line < EXTI_LINE0 || line > EXTI_LINE19)
    {
        return NOK;
    }
    EXIT->IMR &= ~(1 << line);
    return OK;
}

uint8_t EXTI_ClearPending(EXTI_Line_t line)
{
    if (line < EXTI_LINE0 || line > EXTI_LINE19)
    {
        return NOK;
    }
    EXIT->PR |= (1 << line);
    return OK;
}

uint8_t EXTI_SetPending(EXTI_Line_t line)
{
    if (line < EXTI_LINE0 || line > EXTI_LINE19)
    {
        return NOK;
    }
    EXIT->SWIER |= (1 << line);
    return OK;
}

uint8_t EXTI_GetPending(EXTI_Line_t line, uint8_t *value)
{
    if (line < EXTI_LINE0 || line > EXTI_LINE19)
    {
        return NOK;
    }
    *value = (EXIT->PR >> line) & 1;
    return OK;
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_Callbacks[0] != NULL)
    {
        EXTI_Callbacks[0]();
    }
    EXTI_ClearPending(EXTI_LINE0);
}

void EXTI1_IRQHandler(void)
{
    if (EXTI_Callbacks[1] != NULL)
    {
        EXTI_Callbacks[1]();
    }
    EXTI_ClearPending(EXTI_LINE1);
}

void EXTI2_IRQHandler(void)
{
    if (EXTI_Callbacks[2] != NULL)
    {
        EXTI_Callbacks[2]();
    }
    EXTI_ClearPending(EXTI_LINE2);
}

void EXTI3_IRQHandler(void)
{
    if (EXTI_Callbacks[3] != NULL)
    {
        EXTI_Callbacks[3]();
    }
    EXTI_ClearPending(EXTI_LINE3);
}

void EXTI4_IRQHandler(void)
{
    if (EXTI_Callbacks[4] != NULL)
    {
        EXTI_Callbacks[4]();
    }
    EXTI_ClearPending(EXTI_LINE4);
}

void EXTI9_5_IRQHandler(void)
{
    for (uint8_t i =
             EXTI_LINE5;
         i < EXTI_LINE10; i++)
    {
        uint8_t pending;
        EXTI_GetPending(i, &pending);
        if (pending)
        {
            if (EXTI_Callbacks[i] != NULL)
            {
                EXTI_Callbacks[i]();
            }
            EXTI_ClearPending(i);
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    for (uint8_t i =
             EXTI_LINE10;
         i < EXTI_LINE15; i++)
    {
        uint8_t pending;
        EXTI_GetPending(i, &pending);
        if (pending)
        {
            if (EXTI_Callbacks[i] != NULL)
            {
                EXTI_Callbacks[i]();
            }
            EXTI_ClearPending(i);
        }
    }
}
