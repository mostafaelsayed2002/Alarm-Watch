/***********************************************************************/
/* @file   GPIO_program.c
 * @author Mostafa Elsayed
 * @brief  The GPIO main source file, includes the implementation of the functions
 * @date   29/6/2024
 */
#include <stdint.h>
#include "STM32F10xxx.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "ErrType.h"

static GPIO_RegDef_t *GPIOx[GPIO_PERIPHERAL_NUM] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};

/***********************************************************************/
/* @fn     GPIO_u8InitPin
 * @brief  Initialize a pin with the given configuration
 * @param[in]  pinConfig: A pointer to the configuration structure
 * @retval Error status
 */

uint8_t GPIO_u8InitPin(const GPIO_PinConfig_t *pinConfig)
{

    uint8_t Local_u8ErrorState = OK;
    if (pinConfig != NULL)
    {
        if (pinConfig->port <= PORTE && pinConfig->pin <= PIN15)
        {
            uint8_t Local_u8CRIndex = pinConfig->pin / 8;
            uint8_t Local_u8CRPin = pinConfig->pin % 8;
            /*Select GPIO mode:   INPUT  OUTPUT_10MHZ, OUTPUT_2MHZ, OUTPUT_50MHZ*/
            /*Select GPIO configration: ANALOG ,FLOATING, INPUT_PULL_UP_DOWN, OUTPUT_PUSH_PULL, OUTPUT_OPEN_DRAIN, AF_PUSH_PULL, AF_OPEN_DRAIN*/
            GPIOx[pinConfig->port]->CR[Local_u8CRIndex] &= ~(CR_MASK << (Local_u8CRPin * CR_PIN_ACCESS));
            uint8_t Local_u8Config = pinConfig->config;
            if (pinConfig->mode > INPUT)
            {
                Local_u8Config -= 4;
            }
            Local_u8Config = (Local_u8Config << 2);
            Local_u8Config = (Local_u8Config | pinConfig->mode);
            GPIOx[pinConfig->port]->CR[Local_u8CRIndex] |= (Local_u8Config << (Local_u8CRPin * CR_PIN_ACCESS));
        }
        else
        {
            Local_u8ErrorState = NOK;
        }
    }
    else
    {
        Local_u8ErrorState = NULL_POINTER;
    }
    return Local_u8ErrorState;
}

/***********************************************************************/
/* @fn     GPIO_u8SetPinValue
 * @brief  Set the value of a pin
 * @param[in]   port: The port of the pin
 * @param[in]   pin: The pin number
 * @param[in]   state: The state of the pin
 * @retval Error status
 */

uint8_t GPIO_u8SetPinValue(Port_t port, Pin_t pin, PinState_t state)
{
    uint8_t Local_u8ErrorState = OK;
    if (port <= PORTE && pin <= PIN15)
    {
        if (state == LOW)
        {
            GPIOx[port]->BSRR = (1 << (16 + pin));
        }
        else if (state == HIGH)
        {
            GPIOx[port]->BSRR = (1 << pin);
        }
        else
        {
            Local_u8ErrorState = NOK;
        }
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}

/***********************************************************************/
/* @fn     GPIO_u8TogglePinValue
 * @brief  Toggle the value of a pin
 * @param[in]   port: The port of the pin
 * @param[in]   pin: The pin number
 * @retval Error status
 */

uint8_t GPIO_u8TogglePinValue(Port_t port, Pin_t pin)
{
    uint8_t Local_u8ErrorState = OK;
    if (port <= PORTE && pin <= PIN15)
    {
        GPIOx[port]->ODR ^= (1 << pin);
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}

/***********************************************************************/
/* @fn     GPIO_u8ReadPinValue
 * @brief  Read the value of a pin
 * @param[in]   port: The port of the pin
 * @param[in]   pin: The pin number
 * @param[out]  state: The state of the pin
 * @retval Error status
 */

uint8_t GPIO_u8ReadPinValue(Port_t port, Pin_t pin, PinState_t *state)
{

    uint8_t Local_u8ErrorState = OK;
    if (port <= PORTE && pin <= PIN15)
    {
        if (GPIOx[port]->IDR & (1 << pin))
        {
            *state = HIGH;
        }
        else
        {
            *state = LOW;
        }
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}
