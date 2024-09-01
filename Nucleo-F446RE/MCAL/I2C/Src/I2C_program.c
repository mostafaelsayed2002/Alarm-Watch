#include "I2C_interface.h"
#include "I2C_private.h"
#include "CommonMacros.h"
#include "STM32F466xx.h"
#include "ErrType.h"

static I2C_RegDef_t *I2Cx[] = {I2C1, I2C2, I2C3};

volatile uint8_t I2CxSlaveAddress[3];
volatile uint8_t *I2CxData[3];
volatile uint8_t I2CxDataSize[3];
static uint8_t I2CxStatus[3] = {I2C_READY, I2C_READY, I2C_READY};
static void (*I2CxCallback[3])(void);

static void Start(I2C_t num)
{
    I2Cx[num]->CR1 |= (1 << START);
    while (!READ_BIT(I2Cx[num]->SR1, SB))
        ;
}

static void StartIT(I2C_t num)
{
    I2Cx[num]->CR1 |= (1 << START);
}

static void Stop(I2C_t num)
{
    I2Cx[num]->CR1 |= (1 << STOP);
}

static void SendSlaveAddress(I2C_t num, uint8_t SlaveAddress)
{
    // Send Slave Address with R/W bit
    I2Cx[num]->DR = SlaveAddress;

    while (!READ_BIT(I2Cx[num]->SR1, ADDR))
        ; // Wait for address to be sent

    // Clear ADDR by reading SR1 followed by SR2
    (void)I2Cx[num]->SR1;
    (void)I2Cx[num]->SR2;
}

static void SendData(I2C_t num, uint8_t *Data, uint8_t DataSize)
{
    for (uint8_t i = 0; i < DataSize; i++)
    {
        I2Cx[num]->DR = Data[i];

        while (!(READ_BIT(I2Cx[num]->SR1, TXE)))
        {
        };
    }
}

static void ReadData(I2C_t num, uint8_t *Data, uint8_t DataSize)
{
    // Enable ACK for all bytes except the last one
    SET_BIT(I2Cx[num]->CR1, ACK);

    for (uint16_t i = 0; i < DataSize; i++)
    {
        if (i == DataSize - 1)
        {
            // For the last byte, disable ACK to send a NACK
            CLEAR_BIT(I2Cx[num]->CR1, ACK);
        }

        // Wait until the data is received (RXNE flag is set)
        while (!(READ_BIT(I2Cx[num]->SR1, RXNE)))
            ;

        // Read the received data
        Data[i] = I2Cx[num]->DR;
    }
}

uint8_t I2C_Init(I2C_Config_t *I2C_Config)
{
    if (I2C_Config == NULL)
        return NULL_POINTER;

    if (I2C_Config->ClockSpeed > 50 || I2C_Config->ClockSpeed < 2)
        return NOK;

    // Disable the I2C peripheral
    CLEAR_BIT(I2Cx[I2C_Config->I2C]->CR1, PE);

    // FREQ[5:0] Set the peripheral clock frequency
    I2Cx[I2C_Config->I2C]->CR2 &= ~(0x3F);
    I2Cx[I2C_Config->I2C]->CR2 |= I2C_Config->ClockSpeed;

    // CCR
    I2Cx[I2C_Config->I2C]->CCR = I2C_Config->CCRValue;

    // Mode: SM, FM
    CLEAR_BIT(I2Cx[I2C_Config->I2C]->CCR, F_S);
    I2Cx[I2C_Config->I2C]->CCR |= (I2C_Config->Mode << F_S);

    // Trise
    I2Cx[I2C_Config->I2C]->TRISE = I2C_Config->TRISEValue;

    // Enable the I2C peripheral
    SET_BIT(I2Cx[I2C_Config->I2C]->CR1, PE);
    return OK;
}

uint8_t I2C_Write(I2C_t num, uint8_t SlaveAddress, uint8_t *Data, uint8_t DataSize)
{
    Start(num);
    SendSlaveAddress(num, (SlaveAddress << 1) | 0); // Write
    SendData(num, Data, DataSize);
    Stop(num);
    return OK;
}

uint8_t I2C_Read(I2C_t num, uint8_t SlaveAddress, uint8_t *Data, uint8_t DataSize)
{
    Start(num);
    SendSlaveAddress(num, (SlaveAddress << 1) | 1); // Read
    ReadData(num, Data, DataSize);
    Stop(num);
    return OK;
}

uint8_t I2C_WriteIT(I2C_t num, uint8_t SlaveAddress, uint8_t *Data, uint8_t DataSize, void (*Callback)(void))
{
    if (I2CxStatus[num] == I2C_BUSY)
        return NOK;

    I2Cx[num]->CR2 |= (1 << ITEVTEN);
    I2Cx[num]->CR2 |= (1 << ITBUFEN);
    I2CxSlaveAddress[num] = SlaveAddress << 1 | 0;
    I2CxData[num] = Data;
    I2CxDataSize[num] = DataSize;
    I2CxStatus[num] = I2C_BUSY;
    I2CxCallback[num] = Callback;
    StartIT(num);
    return OK;
}

uint8_t I2C_ReadIT(I2C_t num, uint8_t SlaveAddress, uint8_t *Data, uint8_t DataSize, void (*Callback)(void))
{
    if (I2CxStatus[num] == I2C_BUSY)
        return NOK;
    I2Cx[num]->CR2 |= (1 << ITEVTEN);
    I2Cx[num]->CR2 |= (1 << ITBUFEN);

    I2CxSlaveAddress[num] = (SlaveAddress << 1) | 1;
    I2CxData[num] = Data;
    I2CxDataSize[num] = DataSize;
    I2CxStatus[num] = I2C_BUSY;
    I2CxCallback[num] = Callback;
    SET_BIT(I2Cx[num]->CR1, ACK);
    StartIT(num);
    return OK;
}

void I2C1_EV_IRQHandler(void)
{
    if (READ_BIT(I2C1->SR1, SB))
    {
        // Send Slave Address with R/W bit
        I2C1->DR = I2CxSlaveAddress[0];
    }
    if (READ_BIT(I2C1->SR1, ADDR))
    {
        (void)I2C1->SR1;
        (void)I2C1->SR2;
    }
    if (READ_BIT(I2C1->SR1, TXE))
    {
        if (I2CxDataSize[0] > 0)
        {
            I2C1->DR = *I2CxData[0];
            I2CxData[0]++;
            I2CxDataSize[0]--;
        }
        else
        {
            Stop(0);
            I2CxStatus[0] = I2C_READY;
            if (I2CxCallback[0] != NULL)
                I2CxCallback[0]();
        }
    }
    if (READ_BIT(I2C1->SR1, RXNE))
    {
        *I2CxData[0] = I2C1->DR;

        if (I2CxDataSize[0] == 1)
        {
            Stop(0);
            I2CxStatus[0] = I2C_READY;
            if (I2CxCallback[0] != NULL)
                I2CxCallback[0]();
        }

        if (I2CxDataSize[0] == 2)
        {
            CLEAR_BIT(I2C1->CR1, ACK);
        }
        I2CxData[0]++;
        I2CxDataSize[0]--;
    }
}

// void I2C2_EV_IRQHandler(void)
// {
//     if (READ_BIT(I2C2->SR1, SB))
//     {
//         // Send Slave Address with R/W bit
//         I2C2->DR = I2CxSlaveAddress[1];
//     }
//     else if (READ_BIT(I2C2->SR1, ADDR))
//     {
//         (void)I2C2->SR1;
//         (void)I2C2->SR2;
//     }
//     else if (READ_BIT(I2C2->SR1, TXE))
//     {
//         if (I2CxDataSize[1] > 0)
//         {
//             I2C2->DR = *I2CxData[1];
//             I2CxData[1]++;
//             I2CxDataSize[1]--;
//         }
//         else
//         {
//             Stop(1);
//             I2CxStatus[1] = I2C_READY;
//             if (I2CxCallback[1] != NULL)
//                 I2CxCallback[1]();
//         }
//     }
//     else if (READ_BIT(I2C2->SR1, RXNE))
//     {
//         if (I2CxDataSize[1] > 0)
//         {
//             *I2CxData[1] = I2C2->DR;
//             I2CxData[1]++;
//             I2CxDataSize[1]--;
//         }
//         else
//         {
//             Stop(1);
//             I2CxStatus[1] = I2C_READY;
//             if (I2CxCallback[1] != NULL)
//                 I2CxCallback[1]();
//         }
//     }
// }

// void I2C3_EV_IRQHandler(void)
// {
//     if (READ_BIT(I2C3->SR1, SB))
//     {
//         // Send Slave Address with R/W bit
//         I2C3->DR = I2CxSlaveAddress[2];
//     }
//     else if (READ_BIT(I2C3->SR1, ADDR))
//     {
//         (void)I2C3->SR1;
//         (void)I2C3->SR2;
//     }
//     else if (READ_BIT(I2C3->SR1, TXE))
//     {
//         if (I2CxDataSize[2] > 0)
//         {
//             I2C3->DR = *I2CxData[2];
//             I2CxData[2]++;
//             I2CxDataSize[2]--;
//         }
//         else
//         {
//             Stop(1);
//             I2CxStatus[2] = I2C_READY;
//             if (I2CxCallback[2] != NULL)
//                 I2CxCallback[2]();
//         }
//     }
//     else if (READ_BIT(I2C3->SR1, RXNE))
//     {
//         if (I2CxDataSize[2] > 0)
//         {
//             *I2CxData[2] = I2C3->DR;
//             I2CxData[2]++;
//             I2CxDataSize[2]--;
//         }
//         else
//         {
//             Stop(1);
//             I2CxStatus[2] = I2C_READY;
//             if (I2CxCallback[2] != NULL)
//                 I2CxCallback[2]();
//         }
//     }
// }
