#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

#include <stdint.h>

#define SYSTICK_AHB_CLOCK 8000000UL

void SYSTICK_voidDelayms(uint32_t timems);
void SYSTICK_voidDelayus(uint32_t timeus);

#endif
