#include "AFIO_interface.h"
#include "CommonMacros.h"
#include "STM32F10xxx.h"
#include "ErrType.h"

uint8_t AFIO_EXTI_Enable(AFIO_EXTI_Line_t line, AFIO_Port_t port)
{
    if (line < AFIO_EXTI_LINE0 || line > AFIO_EXTI_LINE15)
    {
        return NOK;
    }
    if (port < AFIO_PORTA || port > AFIO_PORTG)
    {
        return NOK;
    }
    uint8_t RegNum = line / 4;
    uint8_t PinNum = line % 4;
    AFIO->EXTICR[RegNum] |= (port << (4 * PinNum));
    return OK;
}
