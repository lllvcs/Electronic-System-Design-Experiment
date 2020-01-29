#include <reg52.h>
#include <absacc.h>
#include <stdio.h>

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

uchar code table[] = {
    0x3f, 0x06, 0x5b, 0x4f,
    0x66, 0x6d, 0x7d, 0x07,
    0x7f, 0x6f, 0x77, 0x7c,
    0x39, 0x5e, 0x79, 0x71};

uchar code FREQH[] = {
    0x9E, 0xF8, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFC, 0x00, 0x00,
    0x00, 0xFC, 0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, 0x00, 0x00,
    0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0x00, 0x00};
uchar code FREQL[] = {
    0x58, 0x8B, 0x5B, 0x14, 0x67, 0x04, 0x8F, 0x0B, 0x00, 0x00,
    0x00, 0x43, 0xAC, 0x09, 0x34, 0x82, 0xC7, 0x05, 0x00, 0x00,
    0x00, 0x22, 0x56, 0x84, 0x9A, 0xC1, 0xE3, 0x02, 0x00, 0x00};

/* 梁祝*/
code uchar music_score0[] = {3, 5, 6, 11, 12, 6, 11, 5, 15, 21, 16, 15, 13, 15, 12, 12, 13, 7, 6, 5, 6, 11, 12, 13, 11, 6, 5, 6, 11, 5, 13, 15, 7, 12, 6, 11, 5, 3, 5, 3, 5, 6, 7, 12, 6, 5, 6, 11, 12, 15, 13, 12, 13, 13, 11, 6, 5, 3, 11, 6, 11, 6, 5, 3, 5, 6, 11, 5, 10};
code uchar play_time0[] = {4, 3, 1, 3, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 8, 3, 1, 2, 2, 3, 1, 2, 2, 2, 2, 1, 1, 1, 1, 8, 3, 1, 2, 2, 1, 1, 4, 1, 2, 1, 1, 1, 1, 1, 6, 1, 1, 3, 1, 2, 2, 2, 1, 1, 2, 1, 1, 4, 4, 2, 1, 1, 1, 1, 1, 1, 1, 6, 0};

/*天空之城*/
code uchar music_score1[] = {16, 17, 21, 17, 21, 23, 17, 13, 13, 16, 15, 16, 21, 15, 13, 13, 14, 13, 14, 21, 13, 21, 21, 21, 17, 14, 14, 17, 17, 16, 17, 21, 17, 21, 23, 17, 13, 13, 16, 15, 16, 21, 15, 13, 14, 21, 17, 17, 21, 22, 22, 23, 21, 21, 17, 16, 16, 17, 15, 16, 10};
code uchar play_time1[] = {1, 1, 3, 1, 2, 2, 6, 1, 1, 3, 1, 2, 2, 4, 1, 1, 3, 1, 1, 3, 4, 1, 1, 1, 3, 1, 2, 2, 4, 1, 1, 3, 1, 2, 2, 4, 1, 1, 3, 1, 2, 2, 6, 1, 2, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 4, 0};

/*美丽的神话*/
code uchar music_score2[] = {6, 13, 7, 6, 11, 12, 11, 13, 6, 16, 15, 16, 15, 12, 14, 13, 13, 6, 16, 15, 12, 13, 14, 13, 11, 6, 13, 12, 6, 7, 6, 6, 7, 11, 12, 13, 11, 7, 5, 6, 11, 12, 13, 13, 6, 7, 11, 12, 13, 11, 7, 5, 6, 11, 12, 11, 11, 6, 7, 11, 12, 13, 11, 7, 5, 6, 11, 12, 11, 13, 13, 6, 7, 11, 12, 13, 11, 7, 5, 6, 11, 12, 11, 11, 10};
code uchar play_time2[] = {2, 2, 4, 1, 1, 1, 1, 4, 2, 2, 1, 1, 1, 1, 1, 1, 6, 2, 2, 1, 1, 1, 1, 4, 4, 2, 2, 2, 1, 1, 8, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 4, 0};

void delayms(uint);
void keyscan();
void display_point(uint);
void display_time(uint, uint, uint);
void display_day(uint, uint, uint);
void display_day_play(uint, uint, uint);
void display_clock(uint, uint);
void display_stopwatch(uint, uint, uint);
void music_delay(uchar);
void music();
void play_music();

uint second_decade, second_unit, minute_decade, minute_unit, hour_decade, hour_unit;
uint day_decade, day_unit, month_decade, month_unit, year_thousand, year_hundred, year_decade, year_unit;
uint clock_hour_unit, clock_hour_decade, clock_minute_unit, clock_minute_decade;
uint ms_decade, ms_unit, sec_decade, sec_unit, min_decade, min_unit;
uint ms, second, minute, hour, clock_minute, clock_hour, day = 1, month = 1, year = 2017, mbms, sec, min, ds_ms;
uint ds_miao, ds_fen, ds_hour, ds_miao1, en_stopwatch, en_timer, en_clock, en_music, music_play_num;
uchar timer0h, timer0l, time;
ulong a;

sbit beep = P1 ^ 6;

unsigned char getkeycode(void) /*键盘扫描函数，返回获得键码*/
{
    unsigned char line = 0x00;     /*行码*/
    unsigned char col = 0x00;      /*列码*/
    unsigned char scancode = 0x01; /*行扫描码*/
    unsigned char keycode;         /*键号*/

    XBYTE[0x8000] = 0xff;
    col = XBYTE[0x8000] & 0x0f; /*从列端口读入四位列码*/
    if (col == 0x00)
        keycode = 0x00;
    else
    {
        while ((scancode & 0x0f) != 0) /*取scancode的低四位，没变为全0，循环*/
        {
            line = scancode;                   /*行号*/
            XBYTE[0x8000] = scancode;          /*给行赋扫描码，第一行为0x01*/
            if ((XBYTE[0x8000] & 0x0f) == col) /*检测按键所在的行跳出循环*/
                break;
            scancode = scancode << 1; /*行扫描码左移一位，转下一行*/
        }
        col = col << 4; /*把行码移到高四位*/
        keycode = col | line;
    }
    return keycode;
}

void main()
{
    TMOD = 0x11;
    TH0 = (65536 - 45872) / 256;
    TL0 = (65536 - 45872) % 256;
    TH1 = (65536 - 9174) / 256;
    TL1 = (65536 - 9174) % 256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    ET1 = 0;
    TR1 = 0;
    while (1)
    {
        keyscan();
    }
}

void keyscan()
{
    uint status, time_set, clock_set, timer_set;
    WR = 0;
    P0 = 0x00;
    P2 = 0x80;
    P0 = 0x02;
    RD = 1;
    WR = 1;
    P0 = 0x00;
    RD = 0;

    if (P0 == 0x01) //?????????,key1++
    {
        delayms(20);
        if (P0 == 0x01)
        {
            delayms(20);
            while (P0 == 0x01)
                ;
            status++;
            time_set = 0;
            clock_set = 0;
            timer_set = 0;
            if (status >= 6)
                status = 0;
        }
    }

    if (status == 0) //时间功能
    {

        RD = 1;
        display_time(second, minute, hour);
    }

    if (status == 1) //日期
    {
        if (P0 == 0x02)
        {
            delayms(20);
            if (P0 == 0x02)
                ;
            {
                while (P0 == 0x02)
                    ;
                RD = 1;
                display_day_play(year, month, day);
            }
        }
        else
        {
            RD = 1;
            display_day(year, month, day);
        }
    }

    if (status == 2) //时间日期设置
    {
        if (P0 == 0x02)
        {
            delayms(20);
            if (P0 == 0x02)
            {
                while (P0 == 0x02)
                    ;
                time_set++;
                if (time_set == 5)
                    time_set = 0;
            }
        }
    }

    if (status == 2 && time_set == 0 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            minute++;
            if (minute >= 60)
            {
                minute = 0;
            }
        }
    }

    if (status == 2 && time_set == 0 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;

            if (minute <= 0)
            {
                minute = 60;
            }
            minute--;
        }
    }

    if (status == 2 && time_set == 1 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            hour++;
            if (hour >= 24)
            {
                hour = 0;
            }
        }
    }
    if (status == 2 && time_set == 1 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;

            if (hour <= 0)
            {
                hour = 24;
            }
            hour--;
        }
    }

    if (status == 2 && time_set == 2 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            day++;
            if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day >= 32)
                day = 1;
            else if ((month == 4 || month == 6 || month == 9 || month == 11) && day >= 31)
                day = 1;
            else if (month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) && day >= 30)
                day = 1;
            else if (((month == 2 && year % 400 != 0 && year % 4 != 0) || (month == 2 && year % 100 == 0)) && day >= 29)
                day = 1;
        }
    }
    if (status == 2 && time_set == 2 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            day--;
            if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 0)
                day = 31;
            else if ((month == 4 || month == 6 || month == 9 || month == 11) && day <= 0)
                day = 30;
            else if ((month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) && day <= 0))
                day = 29;
            else if (((month == 2 && year % 400 != 0 && year % 4 != 0) || (month == 2 && year % 100 == 0)) && day <= 0)
                day = 28;
        }
    }

    if (status == 2 && time_set == 3 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            month++;
            if (month >= 13)
            {
                month = 1;
            }
        }
    }
    if (status == 2 && time_set == 3 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            month--;
            if (month <= 0)
            {
                month = 12;
            }
        }
    }

    if (status == 2 && time_set == 4 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            year++;
        }
    }
    if (status == 2 && time_set == 4 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            year--;
        }
    }

    if (status == 3) //闹钟
    {
        if (P0 == 0x02)
        {
            delayms(20);
            if (P0 == 0x02)
            {
                while (P0 == 0x02)
                    ;
                clock_set++;
                if (clock_set == 3)
                    clock_set = 0;
            }
        }
    }
    if (status == 3 && clock_set == 0 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            en_clock = ~en_clock;
        }
    }
    if (status == 3 && clock_set == 0 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            clock_minute = 0;
            clock_hour = 0;
        }
    }

    if (status == 3 && clock_set == 1 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            clock_minute++;
            if (clock_minute >= 60)
                clock_minute = 0;
        }
    }

    if (status == 3 && clock_set == 1 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            if (clock_minute <= 0)
                clock_minute = 60;
            clock_minute--;
        }
    }

    if (status == 3 && clock_set == 2 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            clock_hour++;
            if (clock_hour >= 24)
                clock_hour = 0;
        }
    }
    if (status == 3 && clock_set == 2 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            if (clock_hour <= 0)
                clock_hour = 24;
            clock_hour--;
        }
    }

    if (en_clock && clock_minute == minute && clock_hour == hour && second == 0)
    {
        en_clock = ~en_clock;
        beep = 0;
        delayms(500);
        beep = 1;
        delayms(200);
        beep = 0;
        delayms(500);
        beep = 1;
        delayms(200);
        beep = 0;
        delayms(500);
        beep = 1;
        delayms(200);
        beep = 0;
        delayms(500);
        beep = 1;
        delayms(200);
    }

    if (status == 4)
    {
        if (P0 == 0x04)
        {
            delayms(20);
            if (P0 == 0x04)
            {
                while (P0 == 0x04)
                    ;
                en_stopwatch = ~en_stopwatch;
                ET1 = 1;
                TR1 = ~TR1;
            }
        }
        if (~en_stopwatch && P0 == 0x08)
        {
            mbms = 0;
            sec = 0;
            min = 0;
        }
    }

    if (status == 5) //定时器
    {
        if (P0 == 0x02)
        {
            delayms(20);
            if (P0 == 0x02)
                ;
            {
                while (P0 == 0x02)
                    ;
                timer_set++;
                if (timer_set == 5)
                    timer_set = 0;
            }
        }
    }
    if (status == 5 && timer_set == 0 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            en_timer = ~en_timer;
            ET1 = 1;
            TR1 = ~TR1;
        }
    }
    if (status == 5 && timer_set == 0 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            ds_miao = 0;
            ds_fen = 0;
            ds_hour = 0;
        }
    }

    if (status == 5 && timer_set == 1 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            ds_miao++;
            if (ds_miao >= 60)
            {
                ds_miao = 0;
            }
        }
    }
    if (status == 5 && timer_set == 1 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            if (ds_miao <= 0)
            {
                ds_miao = 60;
            }
            ds_miao--;
        }
    }

    if (status == 5 && timer_set == 2 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            ds_fen++;
            if (ds_fen >= 60)
            {
                ds_fen = 0;
            }
        }
    }
    if (status == 5 && timer_set == 2 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            if (ds_fen <= 0)
            {
                ds_fen = 60;
            }
            ds_fen--;
        }
    }

    if (status == 5 && timer_set == 3 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            ds_hour++;
            if (ds_hour >= 100)
            {
                ds_hour = 0;
            }
        }
    }
    if (status == 5 && timer_set == 3 && P0 == 0x08)
    {
        delayms(20);
        if (P0 == 0x08)
        {
            while (P0 == 0x08)
                ;
            if (ds_hour <= 0)
            {
                ds_hour = 100;
            }
            ds_hour--;
        }
    }

    if (status == 5 && timer_set == 4 && P0 == 0x04)
    {
        delayms(20);
        if (P0 == 0x04)
        {
            while (P0 == 0x04)
                ;
            music_play_num++;
            if (music_play_num >= 3)
            {
                music_play_num = 0;
            }
        }
    }

    if (en_timer)
    {
        ds_miao = ds_miao - ds_miao1;
        ds_miao1 = 0;
        if (ds_miao == -1)
        {
            ds_miao = 59;
            ds_fen--;
        }
        if (ds_fen == -1)
        {
            ds_fen = 59;
            ds_hour--;
        }
        if (ds_hour == 0 && ds_fen == 0 && ds_miao == 0)
        {
            en_timer = ~en_timer;
            play_music();
            beep = 1;
        }
    }
    switch (status)
    {
    case 2:
        RD = 1;
        switch (time_set)
        {
        case 0:
            display_point(0x18);
            display_time(second, minute, hour);
            break;
        case 1:
            display_point(0xc0);
            display_time(second, minute, hour);
            break;
        case 2:
            display_point(0x03);
            display_time(day, month, year);
            break;
        case 3:
            display_point(0x18);
            display_time(day, month, year);
            break;
        case 4:
            display_point(0xc0);
            display_time(day, month, year);
            break;
        case 5:
            display_point(0xc0);
            display_time(day, month, year);
        }
        break;
    case 3:
        RD = 1;
        switch (clock_set)
        {
        case 0:
            if (en_clock)
            {
                display_point(0x03);
                display_point(0x18);
            }
            break;
        case 1:
            display_point(0x03);
            break;
        case 2:
            display_point(0x18);
            break;
        }
        display_clock(clock_minute, clock_hour);
        break;
    case 4:
        RD = 1;
        display_stopwatch(mbms, sec, min);
        break;
    case 5:
        RD = 1;
        switch (timer_set)
        {
        case 1:
            display_point(0x03);
            break;
        case 2:
            display_point(0x18);
            break;
        case 3:
            display_point(0xc0);
            break;
        case 4:
            display_point(0x03);
            display_point(0x18);
            display_point(0xc0);
            break;
        }
        display_time(ds_miao, ds_fen, ds_hour);
        break;
    }
}

void display_point(uint x) //display the point
{
    WR = 0;
    P2 = 0x81;
    P0 = x;
    P2 = 0x91;
    P0 = 0x80;
    delayms(1);
}

void display_time(uint second, uint minute, uint hour) //display the time
{
    second_decade = second / 10;
    second_unit = second % 10;
    minute_decade = minute / 10;
    minute_unit = minute % 10;
    hour_decade = hour % 100 / 10;
    hour_unit = hour % 10;
    WR = 0;
    P2 = 0x81; //??
    P0 = 0x80;
    P2 = 0x91; //??
    P0 = table[hour_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x40;
    P2 = 0x91;
    P0 = table[hour_unit];
    delayms(1);
    P2 = 0x81;
    P0 = 0x20;
    P2 = 0x91;
    P0 = 0x40;
    delayms(1);

    P2 = 0x81;
    P0 = 0x10;
    P2 = 0x91;
    P0 = table[minute_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x08;
    P2 = 0x91;
    P0 = table[minute_unit];
    delayms(1);
    P2 = 0x81;
    P0 = 0x04;
    P2 = 0x91;
    P0 = 0x40;
    delayms(1);

    P2 = 0x81;
    P0 = 0x02;
    P2 = 0x91;
    P0 = table[second_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x01;
    P2 = 0x91;
    P0 = table[second_unit];
    delayms(1);
}

void display_day_play(uint year, uint month, uint day) //display the date
{
    uint i, j;
    day_decade = day / 10;
    day_unit = day % 10;
    month_decade = month / 10;
    month_unit = month % 10;
    year_thousand = year / 1000;
    year_hundred = year % 1000 / 100;
    year_decade = year % 100 / 10;
    year_unit = year % 10;
    WR = 0;
    P0 = 0x00;
    j = 3;
    while (j)
    {
        i = 200;
        while (i > 0)
        {
            P2 = 0x80;
            P0 = 0x80;
            P2 = 0x91;
            P0 = table[year_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x40;
            P2 = 0x91;
            P0 = table[year_unit];
            delayms(1);
            P2 = 0x80;
            P0 = 0x20;
            P2 = 0x91;
            P0 = 0x40;
            delayms(1);
            P2 = 0x80;
            P0 = 0x10;
            P2 = 0x91;
            P0 = table[month_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x08;
            P2 = 0x91;
            P0 = table[month_unit];
            delayms(1);
            P2 = 0x80;
            P0 = 0x04;
            P2 = 0x91;
            P0 = 0x40;
            delayms(1);
            P2 = 0x80;
            P0 = 0x02;
            P2 = 0x91;
            P0 = table[day_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x01;
            P2 = 0x91;
            P0 = table[day_unit];
            delayms(1);
            i--;
        }
        i = 200;
        while (i > 0)
        {
            P2 = 0x80;
            P0 = 0x80;
            P2 = 0x91;
            P0 = table[month_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x40;
            P2 = 0x91;
            P0 = table[month_unit];
            delayms(1);
            P2 = 0x80;
            P0 = 0x20;
            P2 = 0x91;
            P0 = 0x40;
            delayms(1);
            P2 = 0x80;
            P0 = 0x10;
            P2 = 0x91;
            P0 = table[day_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x08;
            P2 = 0x91;
            P0 = table[day_unit];
            delayms(1);
            P2 = 0x80;
            P0 = 0x04;
            P2 = 0x91;
            P0 = 0;
            delayms(1);
            P2 = 0x80;
            P0 = 0x02;
            P2 = 0x91;
            P0 = 0;
            delayms(1);
            P2 = 0x80;
            P0 = 0x01;
            P2 = 0x91;
            P0 = table[year_thousand];
            delayms(1);
            i--;
        }
        i = 200;
        while (i > 0)
        {
            P2 = 0x80;
            P0 = 0x80;
            P2 = 0x91;
            P0 = table[day_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x40;
            P2 = 0x91;
            P0 = table[day_unit];
            delayms(1);
            P2 = 0x80;
            P0 = 0x20;
            P2 = 0x91;
            P0 = 0;
            delayms(1);
            P2 = 0x80;
            P0 = 0x10;
            P2 = 0x91;
            P0 = 0;
            delayms(1);
            P2 = 0x80;
            P0 = 0x08;
            P2 = 0x91;
            P0 = table[year_thousand];
            delayms(1);
            P2 = 0x80;
            P0 = 0x04;
            P2 = 0x91;
            P0 = table[year_hundred];
            delayms(1);
            P2 = 0x80;
            P0 = 0x02;
            P2 = 0x91;
            P0 = table[year_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x01;
            P2 = 0x91;
            P0 = table[year_unit];
            delayms(1);
            i--;
        }
        i = 200;
        while (i > 0)
        {
            P2 = 0x80;
            P0 = 0x80;
            P2 = 0x91;
            P0 = 0;
            delayms(1);
            P2 = 0x80;
            P0 = 0x40;
            P2 = 0x91;
            P0 = 0;
            delayms(1);
            P2 = 0x80;
            P0 = 0x20;
            P2 = 0x91;
            P0 = table[year_thousand];
            delayms(1);
            P2 = 0x80;
            P0 = 0x10;
            P2 = 0x91;
            P0 = table[year_hundred];
            delayms(1);
            P2 = 0x80;
            P0 = 0x08;
            P2 = 0x91;
            P0 = table[year_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x04;
            P2 = 0x91;
            P0 = table[year_unit];
            delayms(1);
            P2 = 0x80;
            P0 = 0x02;
            P2 = 0x91;
            P0 = 0x40;
            delayms(1);
            P2 = 0x80;
            P0 = 0x01;
            P2 = 0x91;
            P0 = table[month_decade];
            delayms(1);
            i--;
        }
        i = 200;
        while (i > 0)
        {
            P2 = 0x80;
            P0 = 0x80;
            P2 = 0x91;
            P0 = table[year_thousand];
            delayms(1);
            P2 = 0x80;
            P0 = 0x40;
            P2 = 0x91;
            P0 = table[year_hundred];
            delayms(1);
            P2 = 0x80;
            P0 = 0x20;
            P2 = 0x91;
            P0 = table[year_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x10;
            P2 = 0x91;
            P0 = table[year_unit];
            delayms(1);
            P2 = 0x80;
            P0 = 0x08;
            P2 = 0x91;
            P0 = 0x40;
            delayms(1);
            P2 = 0x80;
            P0 = 0x04;
            P2 = 0x91;
            P0 = table[month_decade];
            delayms(1);
            P2 = 0x80;
            P0 = 0x02;
            P2 = 0x91;
            P0 = table[month_unit];
            delayms(1);
            P2 = 0x80;
            P0 = 0x01;
            P2 = 0x91;
            P0 = 0x40;
            delayms(1);
            i--;
        }
        j--;
    }
    display_day(year, month, day);
}

void display_clock(uint clock_minute, uint clock_hour) //display the clock
{
    clock_minute_decade = clock_minute / 10;
    clock_minute_unit = clock_minute % 10;
    clock_hour_decade = clock_hour / 10;
    clock_hour_unit = clock_hour % 10;
    WR = 0;
    P2 = 0x81;
    P0 = 0x10;
    P2 = 0x91;
    P0 = table[clock_hour_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x08;
    P2 = 0x91;
    P0 = table[clock_hour_unit];
    delayms(1);
    P2 = 0x81;
    P0 = 0x04;
    P2 = 0x91;
    P0 = 0x40;
    delayms(1);
    P2 = 0x81;
    P0 = 0x02;
    P2 = 0x91;
    P0 = table[clock_minute_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x01;
    P2 = 0x91;
    P0 = table[clock_minute_unit];
    delayms(1);
}

void display_stopwatch(uint mbms, uint sec, uint min) //display the stopwatch
{
    ms_decade = mbms / 10;
    ms_unit = mbms % 10;
    sec_decade = sec / 10;
    sec_unit = sec % 10;
    min_decade = min / 10;
    min_unit = min % 10;
    WR = 0;
    P2 = 0x81;
    P0 = 0x20;
    P2 = 0x91;
    P0 = table[min_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x10;
    P2 = 0x91;
    P0 = table[min_unit];
    delayms(1);
    P0 = 0x80;
    delayms(1);

    P2 = 0x81;
    P0 = 0x08;
    P2 = 0x91;
    P0 = table[sec_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x04;
    P2 = 0x91;
    P0 = table[sec_unit];
    delayms(1);
    P0 = 0x80;
    delayms(1);

    P2 = 0x81;
    P0 = 0x02;
    P2 = 0x91;
    P0 = table[ms_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x01;
    P2 = 0x91;
    P0 = table[ms_unit];
    delayms(1);
}

void display_day(uint year, uint month, uint day) //display the timer
{
    day_decade = day / 10;
    day_unit = day % 10;
    month_decade = month / 10;
    month_unit = month % 10;
    year_thousand = year / 1000;
    year_hundred = year % 1000 / 100;
    year_decade = year % 100 / 10;
    year_unit = year % 10;
    WR = 0;

    P2 = 0x81;
    P0 = 0x80;
    P2 = 0x91;
    P0 = table[year_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x40;
    P2 = 0x91;
    P0 = table[year_unit];
    delayms(1);
    P2 = 0x81;
    P0 = 0x20;
    P2 = 0x91;
    P0 = 0x40;
    delayms(1);
    P2 = 0x81;
    P0 = 0x10;
    P2 = 0x91;
    P0 = table[month_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x08;
    P2 = 0x91;
    P0 = table[month_unit];
    delayms(1);
    P2 = 0x81;
    P0 = 0x04;
    P2 = 0x91;
    P0 = 0x40;
    delayms(1);
    P2 = 0x81;
    P0 = 0x02;
    P2 = 0x91;
    P0 = table[day_decade];
    delayms(1);
    P2 = 0x81;
    P0 = 0x01;
    P2 = 0x91;
    P0 = table[day_unit];
    delayms(1);
}

void delayms(uint xms) //delay50ms
{
    uint i, j;
    for (i = xms; i > 0; i--)
        for (j = 110; j > 0; j--)
            ;
}

void music_delay(uchar t)
{
    uchar t1;
    ulong t2;
    RD = 1;
    for (t1 = 0; t1 < 10 * t; t1++)
    {
        display_time(second, minute, hour);
        for (t2 = 0; t2 < 500; t2++)
            ;
    }
    TR1 = 0;
}

void music()
{
    TH1 = timer0h;
    TL1 = timer0l;
    TR1 = 1;
    music_delay(time);
}

void play_music()
{
    uchar i, k;
    en_music = 1;
    ET1 = 1;
    i = 0;
    time = 1;

    while (time)
    {

        {
            switch (music_play_num)
            {
            case 0:
                k = music_score0[i];
                time = play_time0[i];
                break;
            case 1:
                k = music_score1[i];
                time = play_time1[i];
                break;
            case 2:
                k = music_score2[i];
                time = play_time2[i];
                break;
            }
        }

        timer0h = FREQH[k];
        timer0l = FREQL[k];
        i++;
        music();

        WR = 0;
        P0 = 0x00;
        P2 = 0x81;
        P0 = 0x02;
        WR = 1;
        P0 = 0x00;
        RD = 0;

        if (k == 10)
        {
            time = 0;
            en_music = 0;
            beep = 1;
            break;
        }
        RD = 1;

        if (getkeycode() == 0x82)
        {
            delayms(10);
            if (getkeycode() == 0x82)
            {
                while (getkeycode() == 0x82)
                    ;
                time = 0;
                en_music = 0;
                beep = 1;
                break;
            }
        }
    }
    en_music = 0;
    beep = 1;
}

void T0_time() interrupt 1
{
    TH0 = (65536 - 45872) / 256;
    TL0 = (65536 - 45872) % 256;
    ms++;
    if (en_timer)
        ds_ms++;
    if (ds_ms >= 20)
    {
        ds_ms = 0;
        ds_miao1++;
    }
    if (ms >= 20)
    {
        ms = 0;
        second++;
    }
    if (second >= 60)
    {
        second = 0;
        minute++;
    }

    if (minute >= 60)
    {
        minute = 0;
        hour++;
    }
    if (hour >= 24)
    {
        hour = 0;
        day++;
    }
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 | month == 12) && day >= 32)
    {
        day = 1;
        month++;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day >= 31)
    {
        day = 1;
        month++;
    }
    if (month == 2)
    {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        {
            if (day >= 30)
            {
                day = 1;
                month++;
            }
        }
        else if (day >= 29)
        {
            day = 1;
            month++;
        }
    }
    if (month >= 13)
    {
        month = 1;
        year++;
    }
}

void T1_time() interrupt 3
{

    if (en_music)
    {
        TR1 = 0;
        beep = !beep;
        TH1 = timer0h;
        TL1 = timer0l;
        TR1 = 1;
    }
    else

    {
        TH1 = (65536 - 9174) / 256;
        TL1 = (65536 - 9174) % 256;
        if (en_stopwatch)
            mbms++;
        if (mbms >= 100)
        {
            mbms = 0;
            sec++;
            if (sec >= 60)
            {
                sec = 0;
                min++;
                if (min >= 60)
                    min = 0;
            }
        }
    }
}