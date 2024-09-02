#include "SPI_interface.h"
#include "CommonMacros.h"
#include "STM32F466xx.h"
#include "SPI_private.h"
#include "ErrType.h"

static SPI_RegDef_t *SPIx[3] = {SPI1, SPI2, SPI3};
static uint8_t TXState[3] = {SPI_READY, SPI_READY, SPI_READY};
static uint8_t RXState[3] = {SPI_READY, SPI_READY, SPI_READY};

static uint8_t *SPIx_TXData[3];
static uint8_t *SPIx_RXData[3];

static uint32_t SPIx_TXLen[3];
static uint32_t SPIx_RXLen[3];

static void (*SPI_TXCallback[3])(void);
static void (*SPI_RXCallback[3])(void);

uint8_t SPI_u8Init(SPI_Config_t *config)
{
    if (config == NULL)
        return NULL_POINTER;
    // 8 or 16 bit data frame format
    SPIx[config->SPI]->CR1 &= ~(1 << DFF);
    SPIx[config->SPI]->CR1 |= (config->DataFrameFormat << DFF);

    // CPOL: Zero or One start
    SPIx[config->SPI]->CR1 &= ~(1 << CPOL);
    SPIx[config->SPI]->CR1 |= (config->clockPolarity << CPOL);

    // CPHA: First or Second edge
    SPIx[config->SPI]->CR1 &= ~(1 << CPHA);
    SPIx[config->SPI]->CR1 |= (config->clockPhase << CPHA);

    // MSB or LSB first
    SPIx[config->SPI]->CR1 &= ~(1 << LSBFIRST);
    SPIx[config->SPI]->CR1 |= (config->LSBFirst << LSBFIRST);

    // Software slave management
    if (config->SoftwareSlaveManagement == HW)
    {
        CLEAR_BIT(SPIx[config->SPI]->CR1, SSM);
        if (config->Mode == MASTER)
            SET_BIT(SPIx[config->SPI]->CR2, SSOE);
        else
            CLEAR_BIT(SPIx[config->SPI]->CR2, SSOE);
    }
    else
    {
        SET_BIT(SPIx[config->SPI]->CR1, SSM);
        if (config->Mode == MASTER)
            SET_BIT(SPIx[config->SPI]->CR1, SSI);
        else
            CLEAR_BIT(SPIx[config->SPI]->CR1, SSI);
    }

    // Baud rate
    SPIx[config->SPI]->CR1 &= ~(0b111 << BR);
    SPIx[config->SPI]->CR1 |= (config->BaudRate << BR);

    // Master or Slave
    SPIx[config->SPI]->CR1 &= ~(1 << MSTR);
    SPIx[config->SPI]->CR1 |= (config->Mode << MSTR);

    // Enable SPI
    SET_BIT(SPIx[config->SPI]->CR1, SPE);
    return OK;
}

uint8_t SPI_u8Transmit_IT(SPI_t copy_SPI, uint8_t *pData, uint32_t Len, void (*callback)(void))
{
    if (TXState[copy_SPI] == SPI_BUSY)
        return NOK;

    TXState[copy_SPI] = SPI_BUSY;
    SPIx_TXData[copy_SPI] = pData;
    SPIx_TXLen[copy_SPI] = Len;
    SPI_TXCallback[copy_SPI] = callback;
    SPIx[copy_SPI]->DR = *pData;
    // Enable TXE interrupt
    SET_BIT(SPIx[copy_SPI]->CR2, TXEIE);
    return OK;
}

uint8_t SPI_u8Receive_IT(SPI_t copy_SPI, uint8_t *pData, uint32_t Len, void (*callback)(void))
{
    if (RXState[copy_SPI] == SPI_BUSY)
        return NOK;

    RXState[copy_SPI] = SPI_BUSY;
    SPIx_RXData[copy_SPI] = pData;
    SPIx_RXLen[copy_SPI] = Len;
    SPI_RXCallback[copy_SPI] = callback;
    // Enable RXNE interrupt
    SET_BIT(SPIx[copy_SPI]->CR2, RXNEIE);
    return OK;
}

void SPI1_IRQHandler(void)
{
    if (READ_BIT(SPI1->SR, TXE))
    {
        if (TXState[0] == SPI_BUSY)
        {
            SPIx_TXLen[0]--;
            if (SPIx_TXLen[0] > 0)
            {
                SPIx_TXData[0]++;
                SPI1->DR = *(SPIx_TXData[0]);
            }
            else
            {
                TXState[0] = SPI_READY;
                CLEAR_BIT(SPI1->CR2, TXEIE);
                if (SPI_RXCallback[0] != NULL)
                    SPI_RXCallback[0]();
            }
        }
    }
    if (READ_BIT(SPI1->SR, RXNE))
    {
        if (RXState[0] == SPI_BUSY)
        {
            *SPIx_RXData[0] = SPI1->DR;
            SPIx_RXLen[0]--;
            SPIx_RXData[0]++;
            if (SPIx_RXLen[0] == 0)
            {
                RXState[0] = SPI_READY;
                CLEAR_BIT(SPI1->CR2, RXNEIE);
                if (SPI_RXCallback[0] != NULL)
                    SPI_RXCallback[0]();
            }
        }
    }
}

void SPI2_IRQHandler(void)
{
    if (READ_BIT(SPI2->SR, TXE))
    {
        if (TXState[1] == SPI_BUSY)
        {
            SPIx_TXLen[1]--;
            if (SPIx_TXLen[1] > 0)
            {
                SPIx_TXData[1]++;
                SPI2->DR = *(SPIx_TXData[1]);
            }
            else
            {
                TXState[1] = SPI_READY;
                CLEAR_BIT(SPI2->CR2, TXEIE);
                if (SPI_RXCallback[1] != NULL)
                    SPI_RXCallback[1]();
            }
        }
    }
    if (READ_BIT(SPI2->SR, RXNE))
    {
        if (RXState[1] == SPI_BUSY)
        {
            *SPIx_RXData[1] = SPI2->DR;
            SPIx_RXLen[1]--;
            SPIx_RXData[1]++;
            if (SPIx_RXLen[1] == 0)
            {
                TXState[1] = SPI_READY;
                CLEAR_BIT(SPI2->CR2, RXNEIE);
                if (SPI_RXCallback[1] != NULL)
                    SPI_RXCallback[1]();
            }
        }
    }
}

void SPI3_IRQHandler(void)
{
    if (READ_BIT(SPI3->SR, TXE))
    {
        if (TXState[2] == SPI_BUSY)
        {
            SPIx_TXLen[2]--;
            if (SPIx_TXLen[2] > 0)
            {
                SPIx_TXData[2]++;
                SPI3->DR = *(SPIx_TXData[2]);
            }
            else
            {
                TXState[2] = SPI_READY;
                CLEAR_BIT(SPI3->CR2, TXEIE);
                if (SPI_RXCallback[2] != NULL)
                    SPI_RXCallback[2]();
            }
        }
    }
    if (READ_BIT(SPI3->SR, RXNE))
    {
        if (RXState[2] == SPI_BUSY)
        {
            *SPIx_RXData[2] = SPI3->DR;
            SPIx_RXLen[2]--;
            SPIx_RXData[2]++;
            if (SPIx_RXLen[2] == 0)
            {
                RXState[2] = SPI_READY;
                CLEAR_BIT(SPI3->CR2, RXNEIE);
                if (SPI_RXCallback[2] != NULL)
                    SPI_RXCallback[2]();
            }
        }
    }
}
