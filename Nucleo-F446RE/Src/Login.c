#include "Login.h"
#include "UART_interface.h"
#include "SPI_interface.h"
#include <string.h>
#include <stdio.h>

uint8_t arr[8] = {0};

uint8_t Login()
{
    UART_u8Transmit(UART2, (uint8_t *)"----------------Login----------------\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"Username: ");
    uint8_t username[6] = "-----";
    UART_u8Receive(UART2, username);

    UART_u8Transmit(UART2, (uint8_t *)"\r\nPassword(3 Attempt(s) Left): ");

    uint8_t password[6] = "-----";
    uint8_t Attempt = 0;

    while (Attempt < 3)
    {
        UART_u8Receive(UART2, password);

        if (password[0] == username[4] && password[1] == username[3] && password[2] == username[2] && password[3] == username[1] && password[4] == username[0])
        {
            arr[0] = 1;
            SPI_u8Transmit_IT(SPI2, arr, 8, NULL);
            return NORMAL;
        }
        else
        {
            Attempt++;
            if (Attempt < 3)
            {
                char attemptMessage[60];
                snprintf(attemptMessage, 60, "\r\nWrong password, Please Try again %d Attempt(s) Left: ", 3 - Attempt);
                UART_u8Transmit(UART2, (uint8_t *)attemptMessage);
            }
            else
            {
                UART_u8Transmit(UART2, (uint8_t *)"\r\nNo attempts left. Access denied.\r\n");
                SPI_u8Transmit_IT(SPI2, arr, 8, NULL);
                return FAILD;
            }
        }
    }

    return 0;
}
