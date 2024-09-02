#include "SystemInitialization.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "SPI_interface.h"
#include "LCD_interface.h"

void SYS_Initialization()
{
    /************************** NVIC Initialization ******************************/
    NVIC_u8Enable(SPI1_IRQ); // SPI1
    NVIC_u8Enable(SPI2_IRQ); // SPI2

    /************************** GPIO Initialization ******************************/
    RCC_voidAPB2EnablePeripheralClock(2); // GPIOA
    RCC_voidAPB2EnablePeripheralClock(3); // GPIOB
    RCC_voidAPB2EnablePeripheralClock(4); // GPIOC

    GPIO_PinConfig_t RED = {
        .config = OUTPUT_PUSH_PULL,
        .mode = OUTPUT_10MHZ,
        .pin = PIN1,
        .port = PORTA};

    GPIO_PinConfig_t GREEN = {
        .config = OUTPUT_PUSH_PULL,
        .mode = OUTPUT_10MHZ,
        .pin = PIN15,
        .port = PORTC};

    GPIO_PinConfig_t SCK = {
        .config = FLOATING,
        .mode = INPUT,
        .pin = PIN5,
        .port = PORTA};

    GPIO_PinConfig_t MISO = {
        .config = AF_PUSH_PULL,
        .mode = OUTPUT_10MHZ,
        .pin = PIN6,
        .port = PORTA};
    GPIO_PinConfig_t MOSI = {
        .config = FLOATING,
        .mode = INPUT,
        .pin = PIN7,
        .port = PORTA};

    GPIO_PinConfig_t NSS = {
        .config = FLOATING,
        .mode = INPUT,
        .pin = PIN4,
        .port = PORTA};

    GPIO_u8InitPin(&SCK);
    GPIO_u8InitPin(&MOSI);
    GPIO_u8InitPin(&MISO);
    GPIO_u8InitPin(&NSS);
    GPIO_u8InitPin(&RED);
    GPIO_u8InitPin(&GREEN);

    /************************** MCAL Peripherals Initialization ******************/
    RCC_voidAPB2EnablePeripheralClock(12); // SPI1

    SPI_Config_t SPI1_Config = {
        .BaudRate = FPCLK_4,
        .DataFrameFormat = BIT8,
        .LSBFirst = MSB,
        .Mode = SLAVE,
        .SPI = SPI1,
        .clockPolarity = ZERO_START,
        .clockPhase = FIRST_EDGE,
        .SoftwareSlaveManagement = HW};

    SPI_u8Init(&SPI1_Config);
    /************************** HAL Peripherals Initialization ******************/
    LCD_voidInit();
}
