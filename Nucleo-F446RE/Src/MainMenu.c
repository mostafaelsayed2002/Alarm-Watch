#include "UART_interface.h"
#include "I2C_interface.h"
#include "DS1307_interface.h"
#include "GPIO_interface.h"
#include "MainMenu.h"
#include <stdio.h>

DS1307_Time_t Alarm[5];
DS1307_Time_t Time;
DS1307_Time_t CurrentTime;

static void DisplayTimeDate()
{
    uint8_t DateStr[2];
    uint8_t MonthStr[2];
    uint8_t YearStr[2];
    uint8_t HoursStr[2];
    uint8_t MinutesStr[2];
    uint8_t SecondsStr[2];
    sprintf(DateStr, "%d", Time.Date);
    sprintf(MonthStr, "%d", Time.Month);
    sprintf(YearStr, "%d", Time.Year);
    sprintf(HoursStr, "%d", Time.Hours);
    sprintf(MinutesStr, "%d", Time.Minutes);
    sprintf(SecondsStr, "%d", Time.Seconds);

    UART_u8Transmit(UART2, (uint8_t *)"\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"\n-----------Time & Date------------\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"The Date is: ");
    UART_u8Transmit(UART2, DateStr);
    UART_u8Transmit(UART2, (uint8_t *)"/");
    UART_u8Transmit(UART2, MonthStr);
    UART_u8Transmit(UART2, (uint8_t *)"/");
    UART_u8Transmit(UART2, YearStr);
    UART_u8Transmit(UART2, (uint8_t *)"\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"The Time is: ");
    UART_u8Transmit(UART2, HoursStr);
    UART_u8Transmit(UART2, (uint8_t *)":");
    UART_u8Transmit(UART2, MinutesStr);
    UART_u8Transmit(UART2, (uint8_t *)":");
    UART_u8Transmit(UART2, SecondsStr);
    UART_u8Transmit(UART2, (uint8_t *)"\r\n");
}

static uint8_t CheckAlarm()
{
    for (uint8_t i = 0; i < 5; i++)
    {
        if (Alarm[i].Seconds == CurrentTime.Seconds && Alarm[i].Minutes == CurrentTime.Minutes && Alarm[i].Hours == CurrentTime.Hours && Alarm[i].Date == CurrentTime.Date && Alarm[i].Month == CurrentTime.Month && Alarm[i].Year == CurrentTime.Year)
        {
            return 1;
        }
    }
    return 0;
}

static void RecivedCallBack(void)
{
    if (Time.Seconds == CurrentTime.Seconds && Time.Minutes == CurrentTime.Minutes && Time.Hours == CurrentTime.Hours && Time.Date == CurrentTime.Date && Time.Month == CurrentTime.Month && Time.Year == CurrentTime.Year)
        return;
    CurrentTime.Seconds = Time.Seconds;
    CurrentTime.Minutes = Time.Minutes;
    CurrentTime.Hours = Time.Hours;
    CurrentTime.Date = Time.Date;
    CurrentTime.Month = Time.Month;
    CurrentTime.Year = Time.Year;
    if (CheckAlarm())
    {
        UART_u8Transmit(UART2, (uint8_t *)"\r\nAlarm!\r\n"); // send to blue pill
    }
    else
    {
        // send to blue pill
    }
}

static void GetTimeDate()
{
    DS1307_u8GetTimeIT(&Time, RecivedCallBack);
}

static void SetTimeDate()
{
    UART_u8Transmit(UART2, (uint8_t *)"\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"\n-----------Set Time & Date--------\r\n");

    uint8_t Hours[3] = "HH";
    uint8_t Minutes[3] = "MM";
    uint8_t Seconds[3] = "SS";
    uint8_t Date[3] = "DD";
    uint8_t Month[3] = "MM";
    uint8_t Year[3] = "YY";

    UART_u8Transmit(UART2, (uint8_t *)"Enter the Day (DD): ");
    UART_u8Receive(UART2, Date);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Month (MM): ");
    UART_u8Receive(UART2, Month);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Year (YY): ");
    UART_u8Receive(UART2, Year);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Hours (HH): ");
    UART_u8Receive(UART2, Hours);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Minutes (MM): ");
    UART_u8Receive(UART2, Minutes);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Seconds (SS): ");
    UART_u8Receive(UART2, Seconds);

    DS1307_Time_t Time;
    DS1307_u8GetTime(&Time);

    Time.Date = atoi(Date);
    Time.Month = atoi(Month);
    Time.Year = atoi(Year);
    Time.Hours = atoi(Hours);
    Time.Minutes = atoi(Minutes);
    Time.Seconds = atoi(Seconds);
    DS1307_u8SetTime(&Time);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nTime & Date set successfully!\r\n");
}

static void SetAlarm()
{
    UART_u8Transmit(UART2, (uint8_t *)"\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"\n-----------Set Alarm--------------\r\n");

    uint8_t Hours[3] = "HH";
    uint8_t Minutes[3] = "MM";
    uint8_t Seconds[3] = "SS";
    uint8_t Date[3] = "DD";
    uint8_t Month[3] = "MM";
    uint8_t Year[3] = "YY";
    uint8_t AlarmNum[2] = "-";

    UART_u8Transmit(UART2, (uint8_t *)"Enter the Day (DD): ");
    UART_u8Receive(UART2, Date);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Month (MM): ");
    UART_u8Receive(UART2, Month);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Year (YY): ");
    UART_u8Receive(UART2, Year);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Hours (HH): ");
    UART_u8Receive(UART2, Hours);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Minutes (MM): ");
    UART_u8Receive(UART2, Minutes);
    UART_u8Transmit(UART2, (uint8_t *)"\r\nEnter the Seconds (SS): ");
    UART_u8Receive(UART2, Seconds);

    UART_u8Transmit(UART2, (uint8_t *)"\r\nPlease enter the alarm number (1-5): ");
    UART_u8Receive(UART2, AlarmNum);
    if (atoi(AlarmNum) > 5 || atoi(AlarmNum) < 1)
    {
        UART_u8Transmit(UART2, (uint8_t *)"\r\nInvalid alarm number!\r\n");
        return;
    }
    DS1307_Time_t Time;
    Time.Date = atoi(Date);
    Time.Month = atoi(Month);
    Time.Year = atoi(Year);
    Time.Hours = atoi(Hours);
    Time.Minutes = atoi(Minutes);
    Time.Seconds = atoi(Seconds);
    Alarm[0] = Time;
    UART_u8Transmit(UART2, (uint8_t *)"\r\nAlarm set successfully!\r\n");
}

void MainMenu()
{
    UART_u8Transmit(UART2, (uint8_t *)"\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"\n------------Main Menu------------\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"1) Display Time & Date\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"2) Set Time & Date\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"3) Set Alarm\r\n");
    UART_u8Transmit(UART2, (uint8_t *)"Enter your choice: ");

    uint8_t Choice[1] = "-";
    UART_u8Receive(UART2, Choice);
    if (Choice[0] == 49)
    {
        UART_u8Transmit(UART2, (uint8_t *)"\r\n3To stop the Clock and Return to Main Menu!\r\n");
        uint8_t PC13 = HIGH;
        GPIO_u8ReadPinValue(PORTC, PIN13, &PC13);
        while (PC13)
        {
            GetTimeDate();
            GPIO_u8ReadPinValue(PORTC, PIN13, &PC13);
        }
    }
    else if (Choice[0] == 50)
    {
        SetTimeDate();
    }
    else if (Choice[0] == 51)
    {
        SetAlarm();
    }
    else
    {
        UART_u8Transmit(UART2, (uint8_t *)"\nInvalid choice!\r\n");
    }
}
