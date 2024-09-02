#include "SystemInitialization.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "UART_interface.h"
#include "I2C_interface.h"
#include "NVIC_interface.h"
#include "SPI_interface.h"
#include "DS1307_interface.h"

void SYS_Initialization()
{
    /************************** NVIC Initialization ******************/
    NVIC_u8Enable(I2C1_EV_IRQ);
    NVIC_u8Enable(I2C2_EV_IRQ);
    NVIC_u8Enable(SPI2_IRQ);

    /************************** GPIO Initialization ******************/

    RCC_voidAHB1EnablePeripheralClock(0); // GPIOA
    RCC_voidAHB1EnablePeripheralClock(1); // GPIOB
    RCC_voidAHB1EnablePeripheralClock(2); // GPIOC

    GPIO_PinConfig_t UserButton = {
        .mode = INPUT,
        .outputSpeed = LOW_SPEED,
        .outputType = PUSH_PULL,
        .pin = PIN13,
        .port = PORTC,
        .pullType = PULL_UP};

    GPIO_PinConfig_t TX = {
        .alternateFunction = AF7,
        .mode = ALTERNATE_FUNCTION,
        .outputSpeed = HIGH_SPEED,
        .outputType = PUSH_PULL,
        .pin = PIN2,
        .port = PORTA,
        .pullType = NO_PULL};

    GPIO_PinConfig_t RX = {
        .alternateFunction = AF7,
        .mode = ALTERNATE_FUNCTION,
        .outputSpeed = HIGH_SPEED,
        .outputType = PUSH_PULL,
        .pin = PIN3,
        .port = PORTA,
        .pullType = NO_PULL};

    GPIO_PinConfig_t SCL = {
        .alternateFunction = AF4,
        .mode = ALTERNATE_FUNCTION,
        .outputSpeed = HIGH_SPEED,
        .outputType = OPEN_DRAIN,
        .pin = PIN8,
        .port = PORTB,
        .pullType = NO_PULL};

    GPIO_PinConfig_t SDA = {
        .alternateFunction = AF4,
        .mode = ALTERNATE_FUNCTION,
        .outputSpeed = HIGH_SPEED,
        .outputType = OPEN_DRAIN,
        .pin = PIN9,
        .port = PORTB,
        .pullType = NO_PULL};

    GPIO_PinConfig_t NSS = {
        .alternateFunction = AF5,
        .mode = ALTERNATE_FUNCTION,
        .outputSpeed = HIGH_SPEED,
        .outputType = PUSH_PULL,
        .pin = PIN12,
        .port = PORTB,
        .pullType = NO_PULL};

    GPIO_PinConfig_t SCK = {
        .alternateFunction = AF5,
        .mode = ALTERNATE_FUNCTION,
        .outputSpeed = HIGH_SPEED,
        .outputType = PUSH_PULL,
        .pin = PIN13,
        .port = PORTB,
        .pullType = NO_PULL};

    GPIO_PinConfig_t MISO = {
        .alternateFunction = AF5,
        .mode = ALTERNATE_FUNCTION,
        .outputSpeed = HIGH_SPEED,
        .outputType = PUSH_PULL,
        .pin = PIN14,
        .port = PORTB,
        .pullType = NO_PULL};

    GPIO_PinConfig_t MOSI = {
        .alternateFunction = AF5,
        .mode = ALTERNATE_FUNCTION,
        .outputSpeed = HIGH_SPEED,
        .outputType = PUSH_PULL,
        .pin = PIN15,
        .port = PORTB,
        .pullType = NO_PULL};

    GPIO_u8InitPin(&UserButton);
    GPIO_u8InitPin(&TX);
    GPIO_u8InitPin(&RX);
    GPIO_u8InitPin(&SCL);
    GPIO_u8InitPin(&SDA);
    GPIO_u8InitPin(&NSS);
    GPIO_u8InitPin(&SCK);
    GPIO_u8InitPin(&MOSI);
    GPIO_u8InitPin(&MISO);

    /************************** MCAL Peripherals Initialization ******************/

    RCC_voidAPB1EnablePeripheralClock(17); // USART2
    RCC_voidAPB1EnablePeripheralClock(21); // I2C1
    RCC_voidAPB1EnablePeripheralClock(14); // SPI2

    UART_Config_t UART2_Config = {
        .BaudRate = 9600,
        .ClockFreq = 16000000,
        .num = UART2,
        .Over = UART_OVER16,
        .Parity = UART_PARITY_DISABLED,
        .Stop = UART_STOP_1BIT,
        .WordLength = UART_8BIT};
    I2C_Config_t I2C1_Config = {
        .ClockSpeed = 0b01000,
        .I2C = I2C1,
        .Mode = I2C_SM,
        .CCRValue = 0x28,
        .TRISEValue = 0x09};

    SPI_Config_t SPI2_Config = {
        .BaudRate = FPCLK_256,
        .DataFrameFormat = BIT8,
        .LSBFirst = MSB,
        .Mode = MASTER,
        .SPI = SPI2,
        .clockPolarity = ZERO_START,
        .clockPhase = FIRST_EDGE,
        .SoftwareSlaveManagement = HW};

    UART_u8Init(&UART2_Config);
    I2C_Init(&I2C1_Config);
    SPI_u8Init(&SPI2_Config);

    /************************** MCAL Peripherals Initialization ******************/

    DS1307_AttachI2C(I2C1);
    DS1307_u8EnableClock();
    DS1307_u8SetHourMode(DS1307_12H);
}
