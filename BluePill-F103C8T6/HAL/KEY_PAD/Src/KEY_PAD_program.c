/***********************************************************************/
/* @file   KEY_PAD_program.c
 * @author Mostafa Elsayed
 * @brief This file contains the implementation of the functions used to control the 16x2 LCD
 * @date   3/7/2024
 */

#include "KEY_PAD_interface.h"
#include "KEY_PAD_config.h"
#include "GPIO_interface.h"

static GPIO_PinConfig_t KEYPAD_pins[NUM_ROWS + NUM_COLS] = {
    {ROW1_PORT, ROW1_PIN, OUTPUT_2MHZ, OUTPUT_PUSH_PULL},
    {ROW2_PORT, ROW2_PIN, OUTPUT_2MHZ, OUTPUT_PUSH_PULL},
    {ROW3_PORT, ROW3_PIN, OUTPUT_2MHZ, OUTPUT_PUSH_PULL},
    {ROW4_PORT, ROW4_PIN, OUTPUT_2MHZ, OUTPUT_PUSH_PULL},
    {Col1_PORT, Col1_PIN, INPUT, FLOATING},
    {Col2_PORT, Col2_PIN, INPUT, FLOATING},
    {Col3_PORT, Col3_PIN, INPUT, FLOATING},
    {Col4_PORT, Col4_PIN, INPUT, FLOATING}};

static char keys[NUM_ROWS][NUM_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

void KEYPAD_voidInit(void)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        GPIO_u8InitPin(&KEYPAD_pins[i]);
    }
}

uint8_t KEYPAD_voidRead(void)
{
    uint8_t in = ~(0b0001);

    for (uint8_t i = 0; i < NUM_ROWS; i++)
    {
        for (uint8_t k = 0; k < 4; k++)
        {
            GPIO_u8SetPinValue(KEYPAD_pins[k].port, KEYPAD_pins[k].pin, (in >> k) & 1);
        }

        for (uint8_t j = 0; j < NUM_COLS; j++)
        {
            uint8_t val;
            GPIO_u8ReadPinValue(KEYPAD_pins[j + NUM_ROWS].port, KEYPAD_pins[j + NUM_ROWS].pin, &val);
            if (val == LOW)
            {
                return keys[i][j];
            }
        }
        in = (~((~in) << 1));
    }

    return '-';
}
