#ifndef MAINMENU_H
#define MAINMENU_H

#include "DS1307_interface.h"
typedef struct
{
    uint8_t type;
    DS1307_Time_t Time;
} PacketDef_t;

typedef enum
{
    LOGED_PACKET = 1,
    DATE_TIME_PACKET,
    ALARM_PACKET,
} Packet_t;

void MainMenu();

#endif
