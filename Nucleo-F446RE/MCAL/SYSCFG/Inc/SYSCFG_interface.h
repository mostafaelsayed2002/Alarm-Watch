#include <stdint.h>
#ifndef SYSCFG_INTERFACE_H
#define SYSCFG_INTERFACE_H

#include "EXTI_interface.h"
#include "GPIO_interface.h"

typedef enum
{
    SYSCFG_EXTI0,
    SYSCFG_EXTI1,
    SYSCFG_EXTI2,
    SYSCFG_EXTI3,
    SYSCFG_EXTI4,
    SYSCFG_EXTI5,
    SYSCFG_EXTI6,
    SYSCFG_EXTI7,
    SYSCFG_EXTI8,
    SYSCFG_EXTI9,
    SYSCFG_EXTI10,
    SYSCFG_EXTI11,
    SYSCFG_EXTI12,
    SYSCFG_EXTI13,
    SYSCFG_EXTI14,
    SYSCFG_EXTI15
} SYSCFG_Line_t;

typedef enum
{
    SYSCFG_PORTA = 0,
    SYSCFG_PORTB,
    SYSCFG_PORTC,
    SYSCFG_PORTD,
    SYSCFG_PORTE,
    SYSCFG_PORTF,
    SYSCFG_PORTG,
    SYSCFG_PORTH
} SYSCFG_Port_t;

/**
 * @fn     SYSCFG_u8SetExtiPort
 * @brief  Set the EXTI port for a specific line
 * @param[in]   line: The EXTI line
 * @param[in]   port: The EXTI port
 * @retval Error status
 */
uint8_t SYSCFG_u8SetExtiPort(SYSCFG_Line_t line, SYSCFG_Port_t port);

#endif