#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include <stdint.h>

typedef enum
{
    PORTA = 0,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
} Port_t;

typedef enum
{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15
} Pin_t;

typedef enum
{
    INPUT = 0,
    OUTPUT_10MHZ,
    OUTPUT_2MHZ,
    OUTPUT_50MHZ
} Mode_t;

typedef enum
{
    ANALOG = 0,
    FLOATING,
    INPUT_PULL_UP_DOWN,
    OUTPUT_PUSH_PULL = 4,
    OUTPUT_OPEN_DRAIN,
    AF_PUSH_PULL,
    AF_OPEN_DRAIN
} Config_t;

typedef enum
{
    LOW = 0,
    HIGH
} PinState_t;

typedef struct
{
    Port_t port;
    Pin_t pin;
    Mode_t mode;
    Config_t config;
} GPIO_PinConfig_t;

uint8_t GPIO_u8InitPin(const GPIO_PinConfig_t *pinConfig);

uint8_t GPIO_u8SetPinValue(Port_t port, Pin_t pin, PinState_t state);

uint8_t GPIO_u8TogglePinValue(Port_t port, Pin_t pin);

uint8_t GPIO_u8ReadPinValue(Port_t port, Pin_t pin, PinState_t *state);