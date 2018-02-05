\
/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 1/31/2018
Author  : 
Company : 
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>
#include <delay.h>
#include <glcd.h>
#include <font5x7.h>
#include <stdio.h>
#include <stdlib.h>
#include "kashanu_logo.c"
#include "apple_logo.c"
//#include "rectangle.c"
#include "circle.c"

int delay = 10;
int delay_counter = 10;

bool reverse_flag = false;
bool stopped_flag = false;

char rows[] = {0x03, 0x06, 0x0C, 0x09};
char columns[] = {0x30, 0x60, 0xC0, 0x90};

eeprom int x = 0;
eeprom int y = 0;

void return_to_start()
{
    char strx[50];
    x = 0;
    y = 0;
    sprintf(strx, "(%2d, %2d)", x, y);
    glcd_outtextxy(75, 10, strx);
}

int calculate_pixel(int i, int j, flash unsigned char *a)
{
    int byte = (((i * 64) + j) / 8) + 4;
    int bitt = ((i * 64) + j) % 8;
    int pixel = (a[byte] & (1 << bitt)) >> bitt;
    return pixel;
}

void print_rectangle()
{
    int i = 17;
    int j = 7;
    char strx[50];
    glcd_clear();
    glcd_outtextxy(75, 0, "cor:");
    glcd_outtextxy(75, 20, "speed:");
    glcd_outtextxy(75, 30, "10");

    for (; j < 47; j++)
    {
        if (stopped_flag == true)
        {
            return_to_start();
            return;
        }
        PORTC &= 0xf0;
        PORTC |= rows[(j - 7) % 4];
        PORTD .6 = true;
        x++;
        glcd_setpixel(j, i);
        sprintf(strx, "(%2d, %2d)", x, y);
        glcd_outtextxy(75, 10, strx);
        delay_ms(delay);
    }
    for (; i < 47; i++)
    {
        if (stopped_flag == true)
        {
            return_to_start();
            return;
        }
        PORTC &= 0x0f;
        PORTC |= columns[(i - 17) % 4];
        PORTD .6 = true;
        y++;
        glcd_setpixel(j, i);
        sprintf(strx, "(%2d, %2d)", x, y);
        glcd_outtextxy(75, 10, strx);
        delay_ms(delay);
    }
    for (; j >= 7; j--)
    {
        if (stopped_flag == true)
        {
            return_to_start();
            return;
        }
        PORTC &= 0xf0;
        PORTC |= rows[(j - 7) % 4];
        PORTD .6 = true;
        x++;
        glcd_setpixel(j, i);
        sprintf(strx, "(%2d, %2d)", x, y);
        glcd_outtextxy(75, 10, strx);
        delay_ms(delay);
    }
    for (; i >= 17; i--)
    {
        if (stopped_flag == true)
        {
            return_to_start();
            return;
        }
        PORTC &= 0x0f;
        PORTC |= columns[(i - 17) % 4];
        PORTD .6 = true;
        y++;
        glcd_setpixel(j, i);
        sprintf(strx, "(%2d, %2d)", x, y);
        glcd_outtextxy(75, 10, strx);
        delay_ms(delay);
    }
}

void iteration_LCD(flash unsigned char *image)
{
    int i = 0;
    int j = 0;
    char strx[50];
    //glcd_clear();
    glcd_outtextxy(75, 0, "cor:");
    glcd_outtextxy(75, 20, "speed:");
    glcd_outtextxy(75, 30, "10");
    for (i = y; i < 64; i++)
    {
        if (i % 2 == 0)
        {
            for (j = x; j < 64 && x < 64; j++)
            {
                if (stopped_flag == true)
                {
                    return;
                }
                PORTC &= 0xf0;
                PORTC |= rows[j % 4];
                x++;
                if (reverse_flag == false)
                {
                    if (calculate_pixel(i, j, image) == 1)
                    {
                        PORTD .6 = true;
                        glcd_setpixel(j, i);
                    }
                    else
                    {
                        PORTD .6 = false;
                    }
                }
                else
                {
                    if (calculate_pixel(i, j, image) == 0)
                    {
                        PORTD .6 = true;
                        glcd_setpixel(j, i);
                    }
                    else
                    {
                        PORTD .6 = false;
                    }
                }

                sprintf(strx, "(%2d, %2d)", x, y);
                glcd_outtextxy(75, 10, strx);
                delay_ms(delay);
            }
        }
        else
        {
            for (j = x; j >= 0 && x >= 0; j--)
            {
                if (stopped_flag == true)
                {
                    return;
                }
                PORTC &= 0xf0;
                PORTC |= rows[j % 4];
                x--;
                if (reverse_flag == false)
                {
                    if (calculate_pixel(i, j, image) == 1)
                    {
                        PORTD .6 = true;
                        glcd_setpixel(j, i);
                    }
                    else
                    {
                        PORTD .6 = false;
                    }
                }
                else
                {
                    if (calculate_pixel(i, j, image) == 0)
                    {
                        PORTD .6 = true;
                        glcd_setpixel(j, i);
                    }
                    else
                    {
                        PORTD .6 = false;
                    }
                }

                sprintf(strx, "(%2d, %2d)", x, y);
                glcd_outtextxy(75, 10, strx);
                delay_ms(delay);
            }
        }
        if (stopped_flag == true)
        {
            return;
        }
        PORTC &= 0x0f;
        PORTC |= columns[i % 4];
        y++;
        delay_ms(delay);
    }
    sprintf(strx, "(%2d, %2d)", j, i);
    glcd_outtextxy(75, 10, strx);
    delay_ms(delay);
}

int get_key(void)
{
    DDRB = 0x00;
    PORTB &= 0b10000000;
    PORTB |= 0X0F;

    DDRB = 0b10010000; //اعمال ولتاژ صفر به ستون یک با خروجی کردن پایه مورد نظر
    if (PINB .0 == 0)
        return 1;
    if (PINB .1 == 0)
        return 4;
    if (PINB .2 == 0)
        return 7;
    if (PINB .3 == 0)
        return 10;

    DDRB = 0b10100000; //اعمال ولتاژ صفر به ستون دوم با خروجی کردن پایه مورد نظر
    if (PINB .0 == 0)
        return 2;
    if (PINB .1 == 0)
        return 5;
    if (PINB .2 == 0)
        return 8;
    if (PINB .3 == 0)
        return 0;

    DDRB = 0b11000000; //اعمال ولتاژ صفر به ستون سوم با خروجی کردن پایه مورد نظر
    if (PINB .0 == 0)
        return 3;
    if (PINB .1 == 0)
        return 6;
    if (PINB .2 == 0)
        return 9;
    if (PINB .3 == 0)
        return 11;

    return 255;
}

void decrease_speed()
{
    char buff[16];
    delay += 20;
    delay_counter--;
    sprintf(buff, "%d ", delay_counter);
    glcd_outtextxy(75, 30, buff);
}
void increase_speed()
{
    char buff[16];
    if (delay - 20 >= 10)
    {
        delay -= 20;
        delay_counter++;
        sprintf(buff, "%d ", delay_counter);
        glcd_outtextxy(75, 30, buff);
    }
}

// External Interrupt 0 service routine
interrupt[EXT_INT0] void ext_int0_isr(void)
{
    // Place your code here

    int key;
    key = get_key();
    DDRB |= 0b11110000;
#asm("sei")
    switch (key)
    {
    case 1: //print rectangle
        //iteration_LCD(rectangle);
        stopped_flag = false;
        print_rectangle();
        break;

    case 2: //print circle
        stopped_flag = false;
        iteration_LCD(circle);
        break;

    case 3: //print kashan logo
        stopped_flag = false;
        iteration_LCD(kashanu_logo);
        break;

    case 4: //print apple logo
        stopped_flag = false;
        iteration_LCD(apple_logo);
        break;

    case 5:
        reverse_flag = true;
        break;

    case 6:
        reverse_flag = false;
        break;

    case 7:
        stopped_flag = true;
        break;

    case 10:
        decrease_speed();
        break;
    case 11:
        increase_speed();
        break;
    }

    DDRB |= 0b11110000;
}

void main(void)
{
    GLCDINIT_t glcd_init_data;

    DDRC = 0XFF;
    DDRA = 0XFF;
    DDRD = 0XFB;
    DDRB = 0xF0;
    PORTB = 0X0F;

    // External Interrupt(s) initialization
    // INT0: On
    // INT0 Mode: Falling Edge
    // INT1: Off
    // INT2: Off
    GICR |= (0 << INT1) | (1 << INT0) | (0 << INT2);
    MCUCR = (0 << ISC11) | (0 << ISC10) | (1 << ISC01) | (0 << ISC00);
    MCUCSR = (0 << ISC2);
    GIFR = (0 << INTF1) | (1 << INTF0) | (0 << INTF2);

    return_to_start();

// Global enable interrupts
#asm("sei")

    glcd_init_data.font = font5x7;
    glcd_init_data.readxmem = NULL;
    glcd_init_data.writexmem = NULL;

    glcd_init(&glcd_init_data);

    glcd_outtext("please enter a key accourding to the box: ");
    delay_ms(100);
    glcd_clear();
    while (1)
    {
    }
}
