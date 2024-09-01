#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include <stdint.h>
typedef enum
{
    EXTI_LINE0,
    EXTI_LINE1,
    EXTI_LINE2,
    EXTI_LINE3,
    EXTI_LINE4,
    EXTI_LINE5,
    EXTI_LINE6,
    EXTI_LINE7,
    EXTI_LINE8,
    EXTI_LINE9,
    EXTI_LINE10,
    EXTI_LINE11,
    EXTI_LINE12,
    EXTI_LINE13,
    EXTI_LINE14,
    EXTI_LINE15,
    EXTI_LINE16,
    EXTI_LINE17,
    EXTI_LINE18,
    EXTI_LINE19
} EXTI_Line_t;

typedef enum
{
    EXTI_RISING_EDGE,
    EXTI_FALLING_EDGE,
    EXTI_RISING_FALLING_EDGE
} EXTI_Trigger_t;

uint8_t EXTI_Enable(EXTI_Line_t line, EXTI_Trigger_t trigger, void (*callback)(void));
uint8_t EXTI_Disable(EXTI_Line_t line);
uint8_t EXTI_ClearPending(EXTI_Line_t line);
uint8_t EXTI_SetPending(EXTI_Line_t line);
uint8_t EXTI_GetPending(EXTI_Line_t line, uint8_t *value);

#endif