#include <REG51.H>
#include <absacc.h>
#include <stdio.h>

#define uchar unsigned char
unsigned char code led_table[] = { //七段数码表
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x76};

void delay(unsigned char p) //延时函数
{
   unsigned char i, j;
   for (; p > 0; p--)
      for (i = 181; i > 0; i--) //
         for (j = 181; j > 0; j--)
            ;
}

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

unsigned char key_scan()
{
   unsigned char xdata *P;
   uchar i, line;
   uchar key_value = 0;
   line = 0x01;
   P = 0x8000;
   *P = 0xFF; //赋值FF
   key_value = P0;
   if (key_value) //说明有按键按下
   {
      delay(10);
      for (i = 0; i < 4; i++)
      { //
         P = 0x8000;
         *P = line << i; //赋值行值
         P0 = 0xFF;
         key_value = P0;
         if (key_value)
            return (key_value + i * 4);
      }
      return 0;
   }
   else
      return 0;
}

void main(void)
{
   int i = 0;
   int k = 0;
   int l = 0;
   unsigned char xdata *P;

   while (1)
   {
      i = 0;
	  XBYTE[0x8000] = 0x01;
      delay(3);
      switch (getkeycode())
      {
      case 0x11:
      {
         while (getkeycode() != 0x82)
         {
            XBYTE[0x9000] = 0x00;

            for (i = 0; i < 9; i++)
            {
               delay(5);
               XBYTE[0x8000] = 0x01 << i;
               XBYTE[0x9000] = led_table[k];
            }
            XBYTE[0x9000] = 0x00;
         }
      };
      break; /*第一行第1列*/
      case 0x21:
      {
         while (getkeycode() != 0x82)
         {

            XBYTE[0x8000] = 0x80;
            for (i = 0; i < 9; i++)
            {
               delay(5);
               XBYTE[0x8000] = 0x80 >> i;
               XBYTE[0x9000] = led_table[k];
            }
         }
      };
      break; /*第一行第2列*/

      case 0x41:
      {
         l = 0;
         XBYTE[0x8000] = 0x01;
         while (getkeycode() != 0x82)
         {
            XBYTE[0x8000] = 0x01;
            while (getkeycode() == 0x41 && getkeycode() != 0x82)
            {
               l = (l + 1) % 10;
               XBYTE[0x8000] = 0x01;
               XBYTE[0x9000] = 0x00;
               XBYTE[0x9000] = led_table[l];
               XBYTE[0x8000] = 0x01;
               delay(8);
               XBYTE[0x9000] = 0x00;
            }
            XBYTE[0x8000] = 0x01;
            XBYTE[0x9000] = 0x00;
            XBYTE[0x8000] = 0x01;
            XBYTE[0x9000] = led_table[l];
            XBYTE[0x8000] = 0x01;
            XBYTE[0x9000] = 0x00;
         }
      };
      break; /*第一行第3列*/

      case 0x81:
      {
         while (getkeycode() != 0x82)
         {
            XBYTE[0x8000] = 0x01;
            for (k = 9; k >= 0; k--)
            {
               delay(5);
               XBYTE[0x8000] = 0x01;
               XBYTE[0x9000] = led_table[k];
            }
            XBYTE[0x8000] = 0x01;
            XBYTE[0x9000] = led_table[9];
         }
      };
      break; /*第一行第4列*/

      case 0x12:
         while (getkeycode() != 0x82)
         {
            i = 0;
            while (i <= 6000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[7];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x02;
               XBYTE[0x9000] = led_table[0];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x01;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;

            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[7];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[0];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x02;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x01;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 6000 && getkeycode() != 0x82)
            {

               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[7];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[0];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x02;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x01;
               XBYTE[0x9000] = led_table[7];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[7];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[0];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x02;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x01;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
         }
         break; /*第二行第1列*/

      case 0x22:
         while (getkeycode() != 0x82)
         {
            i = 0;
            while (i <= 6000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[5];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[5];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[5];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x02;
               XBYTE[0x9000] = led_table[7];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[5];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x02;
               XBYTE[0x9000] = led_table[7];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x01;
               XBYTE[0x9000] = led_table[8];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[5];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x02;
               XBYTE[0x9000] = led_table[7];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[5];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x04;
               XBYTE[0x9000] = led_table[6];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x08;
               XBYTE[0x9000] = led_table[5];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x10;
               XBYTE[0x9000] = led_table[4];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x20;
               XBYTE[0x9000] = led_table[3];
               XBYTE[0x9000] = 0x00;
               i++;
            }
            i = 0;
            while (i <= 3000 && getkeycode() != 0x82)
            {
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x80;
               XBYTE[0x9000] = led_table[1];
               XBYTE[0x9000] = 0x00;
               XBYTE[0x8000] = 0x40;
               XBYTE[0x9000] = led_table[2];
               XBYTE[0x9000] = 0x00;
               i++;
            }
         }
         break; /*第二行第2列*/

      case 0x42:
         k = 0;
         break; /*第二行第3列*/

      case 0x82:
         k = 0;
         break; /*第二行第4列*/

      case 0x14:
         k = 1;
         break; /*第三行第1列*/
      case 0x24:
         k = 2;
         break; /*第三行第2列*/
      case 0x44:
         k = 3;
         break; /*第三行第3列*/
      case 0x84:
         k = 4;
         ;
         break; /*第三行第4列*/
      case 0x18:
         k = 5;
         break; /*第四行第1列*/
      case 0x28:
         k = 6;
         break; /*第四行第2列*/
      case 0x48:
         k = 7;
         break; /*第四行第3列*/
      case 0x88:
         k = 8;
         break; /*第四行第4列*/
      default:
         break;
      }

      XBYTE[0x8000] = 0x01;
      XBYTE[0x9000] = led_table[k];
   }
}
