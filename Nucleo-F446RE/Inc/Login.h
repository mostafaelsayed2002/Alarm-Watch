#ifndef LOGIN_H
#define LOGIN_H

#include <stdint.h>

typedef enum
{
    FAILD,
    LOGED,
    NORMAL,
    ALARM
} APPState_t;

uint8_t Login();

#endif