#include "Login.h"
#include "UART_interface.h"
#include <string.h>
#include <stdio.h>

uint8_t Login()
{
    UART_u8Transmit(UART2, (uint8_t *)"----------------Login----------------\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"Username: ");
    uint8_t username[6] = "-----";
    UART_u8Receive(UART2, username);

    if (username[0] == '1' && username[1] == '2' && username[2] == '3' && username[3] == '4' && username[4] == '5')
    {
        UART_u8Transmit(UART2, (uint8_t *)"\r\nPassword(3 Attempt(s) Left): ");

        uint8_t password[6] = "-----";
        uint8_t Attempt = 0;

        while (Attempt < 3)
        {
            UART_u8Receive(UART2, password);

            if (password[0] == '1' && password[1] == '2' && password[2] == '3' && password[3] == '4' && password[4] == '5')
            {

                return 1;
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
                    return 0;
                }
            }
        }
    }
    else
    {
        UART_u8Transmit(UART2, (uint8_t *)"\nWrong username!\r\n");
        return 0;
    }
    return 0;
}
