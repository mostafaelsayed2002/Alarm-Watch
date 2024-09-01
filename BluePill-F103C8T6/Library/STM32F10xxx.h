#include <stdint.h>
#ifndef STM32F10xxx_H
#define STM32F10xxx_H

/******************************* Memories Base Addresses *******************************/

#define FLASH_BASE_ADDRESS 0x08000000UL // Flash memory base address
#define SRAM_BASE_ADDRESS 0x20000000UL  // SRAM base address
#define ROM_BASE_ADDRESS 0x1FFFF000UL   // System memory base address

/****************************** AHB Peripheral Base Addresses *************************/

#define SDIO_BASE_ADDRESS 0x40018000UL            // SDIO base address
#define DMA1_BASE_ADDRESS 0x40020000UL            // DMA1 base address
#define DMA2_BASE_ADDRESS 0x40020400UL            // DMA2 base address
#define RCC_BASE_ADDRESS 0x40021000UL             // RCC base address
#define FLASH_INTERFACE_BASE_ADDRESS 0x40022000UL // Flash interface base address
#define CRC_BASE_ADDRESS 0x40023000UL             // CRC base address
#define ETHERNET_BASE_ADDRESS 0x40028000UL        // Ehternet base address
#define USB_OTG_FS_BASE_ADDRESS 0x50000000UL      // USB OTG FS base address
#define FSMC_BASE_ADDRESS 0xA0000000UL            // FSMC base address

/****************************** APB1 Peripheral Base Addresses *************************/

#define TIM2_BASE_ADDRESS 0x40000000UL     // TIM2 base address
#define TIM3_BASE_ADDRESS 0x40000400UL     // TIM3 base address
#define TIM4_BASE_ADDRESS 0x40000800UL     // TIM4 base address
#define TIM5_BASE_ADDRESS 0x40000C00UL     // TIM5 base address
#define TIM6_BASE_ADDRESS 0x40001000UL     // TIM6 base address
#define TIM7_BASE_ADDRESS 0x40001400UL     // TIM7 base address
#define TIM12_BASE_ADDRESS 0x40001800UL    // TIM12 base address
#define TIM13_BASE_ADDRESS 0x40001C00UL    // TIM13 base address
#define TIM14_BASE_ADDRESS 0x40002000UL    // TIM14 base address
#define RTC_BASE_ADDRESS 0x40002800UL      // RTC base address
#define WWDG_BASE_ADDRESS 0x40002C00UL     // WWDG base address
#define IWDG_BASE_ADDRESS 0x40003000UL     // IWDG base address
#define SPI2_BASE_ADDRESS 0x40003800UL     // SPI2 base address
#define SPI3_BASE_ADDRESS 0x40003C00UL     // SPI3 base address
#define USART2_BASE_ADDRESS 0x40004400UL   // USART2 base address
#define USART3_BASE_ADDRESS 0x40004800UL   // USART3 base address
#define UART4_BASE_ADDRESS 0x40004C00UL    // UART4 base address
#define UART5_BASE_ADDRESS 0x40005000UL    // UART5 base address
#define I2C1_BASE_ADDRESS 0x40005400UL     // I2C1 base address
#define I2C2_BASE_ADDRESS 0x40005800UL     // I2C2 base address
#define USB_FS_BASE_ADDRESS 0x40005C00UL   // USB FS base address
#define CAN_SRAM_BASE_ADDRESS 0x40006000UL // CAN SRAM base address
#define CAN2_BASE_ADDRESS 0x40006800UL     // CAN2 base address
#define CAN1_BASE_ADDRESS 0x40006400UL     // CAN1 base address
#define BKP_BASE_ADDRESS 0x40006C00UL      // BKP base address
#define PWR_BASE_ADDRESS 0x40007000UL      // PWR base address
#define DAC_BASE_ADDRESS 0x40007400UL      // DAC base address

/****************************** APB2 Peripheral Base Addresses *************************/

#define AFIO_BASE_ADDRESS 0x40010000UL   // AFIO base address
#define EXTI_BASE_ADDRESS 0x40010400UL   // EXTI base address
#define GPIOA_BASE_ADDRESS 0x40010800UL  // GPIOA base address
#define GPIOB_BASE_ADDRESS 0x40010C00UL  // GPIOB base address
#define GPIOC_BASE_ADDRESS 0x40011000UL  // GPIOC base address
#define GPIOD_BASE_ADDRESS 0x40011400UL  // GPIOD base address
#define GPIOE_BASE_ADDRESS 0x40011800UL  // GPIOE base address
#define GPIOF_BASE_ADDRESS 0x40011C00UL  // GPIOF base address
#define GPIOG_BASE_ADDRESS 0x40012000UL  // GPIOG base address
#define ADC1_BASE_ADDRESS 0x40012400UL   // ADC1 base address
#define ADC2_BASE_ADDRESS 0x40012800UL   // ADC2 base address
#define TIM1_BASE_ADDRESS 0x40012C00UL   // TIM1 base address
#define SPI1_BASE_ADDRESS 0x40013000UL   // SPI1 base address
#define TIM8_BASE_ADDRESS 0x40013400UL   // TIM8 base address
#define USART1_BASE_ADDRESS 0x40013800UL // USART1 base address
#define ADC3_BASE_ADDRESS 0x40013C00UL   // ADC3 base address
#define TIM9_BASE_ADDRESS 0x40014C00UL   // TIM9 base address
#define TIM10_BASE_ADDRESS 0x40015000UL  // TIM10 base address
#define TIM11_BASE_ADDRESS 0x40015400UL  // TIM11 base address

/****************************** Core Peripherals Base Addresses   *********************/

#define STK_BASE_ADDRESS 0xE000E010    // SysTick base address
#define NVIC_BASE_ADDRESS 0xE000E100UL // NVIC base address
#define SCB_BASE_ADDRESS 0xE000ED00UL  // SCB base address
#define MPU_BASE_ADDRESS 0xE000ED90UL  // MPU base address
// #define NVIC_BASE_ADDRESS 0xE000EF00UL // NVIC base address

/****************************** GPIO Register Definition Structures ******************/

typedef struct
{
    volatile uint32_t CR[2]; // GPIO port configuration register low/high
    volatile uint32_t IDR;   // GPIO port input data register
    volatile uint32_t ODR;   // GPIO port output data register
    volatile uint32_t BSRR;  // GPIO port bit set/reset register
    volatile uint32_t BRR;   // GPIO port bit reset register
    volatile uint32_t LCKR;  // GPIO port configuration lock register

} GPIO_RegDef_t;

/****************************** RCC Register Definition Structures ******************/

typedef struct
{
    volatile uint32_t CR;       // RCC clock control register
    volatile uint32_t CFGR;     // RCC clock configuration register
    volatile uint32_t CIR;      // RCC clock interrupt register
    volatile uint32_t APB2RSTR; // RCC APB2 peripheral reset register
    volatile uint32_t APB1RSTR; // RCC APB1 peripheral reset register
    volatile uint32_t AHBENR;   // RCC AHB peripheral clock enable register
    volatile uint32_t APB2ENR;  // RCC APB2 peripheral clock enable register
    volatile uint32_t APB1ENR;  // RCC APB1 peripheral clock enable register
    volatile uint32_t BDCR;     // RCC backup domain control register
    volatile uint32_t CSR;      // RCC control/status register
} RCC_RegDef_t;

/****************************** SysTick Register Definition Structures ******************/

typedef struct
{
    volatile uint32_t CTRL;  // SysTick control and status register
    volatile uint32_t LOAD;  // SysTick reload value register
    volatile uint32_t VAL;   // SysTick current value register
    volatile uint32_t CALIB; // SysTick calibration value register
} STK_RegDef_t;

/****************************** SPI Register Definition Structures ******************/

typedef struct
{
    volatile uint32_t CR1;     // SPI control register 1
    volatile uint32_t CR2;     // SPI control register 2
    volatile uint32_t SR;      // SPI status register
    volatile uint32_t DR;      // SPI data register
    volatile uint32_t CRCPR;   // SPI CRC polynomial register
    volatile uint32_t RXCRCR;  // SPI RX CRC register
    volatile uint32_t TXCRCR;  // SPI TX CRC register
    volatile uint32_t I2SCFGR; // SPI_I2S configuration register
    volatile uint32_t I2SPR;   // SPI_I2S prescaler register
} SPI_RegDef_t;

/****************************** EXIT Register Definition Structures ******************/

typedef struct
{
    volatile uint32_t IMR;   // Interrupt mask register
    volatile uint32_t EMR;   // Event mask register
    volatile uint32_t RTSR;  // Rising trigger selection register
    volatile uint32_t FTSR;  // Falling trigger selection register
    volatile uint32_t SWIER; // Software interrupt event register
    volatile uint32_t PR;    // Pending register
} EXIT_RegDef_t;

/****************************** NVIC Register Definition Structures ******************/

typedef struct
{
    volatile uint32_t ISER[8]; // Interrupt set-enable registers
    volatile uint32_t RESERVED0[24];
    volatile uint32_t ICER[8]; // Interrupt clear-enable registers
    volatile uint32_t RESERVED1[24];
    volatile uint32_t ISPR[8]; // Interrupt set-pending registers
    volatile uint32_t RESERVED2[24];
    volatile uint32_t ICPR[8]; // Interrupt clear-pending registers
    volatile uint32_t RESERVED3[24];
    volatile uint32_t IABR[8]; // Interrupt active bit registers
    volatile uint32_t RESERVED4[56];
    volatile uint8_t IP[240]; // Interrupt priority registers
} NVIC_RegDef_t;

/****************************** AFIO Register Definition Structures ******************/

typedef struct
{
    volatile uint32_t EVCR;      // Event control register
    volatile uint32_t MAPR;      // AF remap and debug I/O configuration register
    volatile uint32_t EXTICR[4]; // External interrupt configuration registers
    volatile uint32_t MAPR2;     // AF remap and debug I/O configuration register 2
} AFIO_RegDef_t;

/****************************** GPIO Definitions **************************************/

#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASE_ADDRESS)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASE_ADDRESS)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASE_ADDRESS)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASE_ADDRESS)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASE_ADDRESS)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASE_ADDRESS)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASE_ADDRESS)

/****************************** RCC Definitions **************************************/

#define RCC ((RCC_RegDef_t *)RCC_BASE_ADDRESS)

/****************************** STK Definitions **************************************/

#define STK ((STK_RegDef_t *)STK_BASE_ADDRESS)

/****************************** SPI Definitions **************************************/

#define SPI1 ((SPI_RegDef_t *)SPI1_BASE_ADDRESS)
#define SPI2 ((SPI_RegDef_t *)SPI2_BASE_ADDRESS)

/****************************** NVIC Definitions **************************************/

#define NVIC ((NVIC_RegDef_t *)NVIC_BASE_ADDRESS)

/****************************** EXIT Definitions **************************************/

#define EXIT ((EXIT_RegDef_t *)EXTI_BASE_ADDRESS)

/****************************** AFIO Definitions **************************************/

#define AFIO ((AFIO_RegDef_t *)AFIO_BASE_ADDRESS)

#endif