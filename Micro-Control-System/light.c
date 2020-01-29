#include <REG51.H>
#include <absacc.h>
#include <stdio.h>

#define uchar unsigned char
unsigned char code led_table[] = { //�߶������
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x76};

void delay(unsigned char p) //��ʱ����
{
   unsigned char i, j;
   for (; p > 0; p--)
      for (i = 181; i > 0; i--) //
         for (j = 181; j > 0; j--)
            ;
}

unsigned char getkeycode(void) /*����ɨ�躯�������ػ�ü���*/
{
   unsigned char line = 0x00;     /*����*/
   unsigned char col = 0x00;      /*����*/
   unsigned char scancode = 0x01; /*��ɨ����*/
   unsigned char keycode;         /*����*/

   XBYTE[0x8000] = 0xff;
   col = XBYTE[0x8000] & 0x0f; /*���ж˿ڶ�����λ����*/
   if (col == 0x00)
      keycode = 0x00;
   else
   {
      while ((scancode & 0x0f) != 0) /*ȡscancode�ĵ���λ��û��Ϊȫ0��ѭ��*/
      {
         line = scancode;                   /*�к�*/
         XBYTE[0x8000] = scancode;          /*���и�ɨ���룬��һ��Ϊ0x01*/
         if ((XBYTE[0x8000] & 0x0f) == col) /*��ⰴ�����ڵ�������ѭ��*/
            break;
         scancode = scancode << 1; /*��ɨ��������һλ��ת��һ��*/
      }
      col = col << 4; /*�������Ƶ�����λ*/
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
   *P = 0xFF; //��ֵFF
   key_value = P0;
   if (key_value) //˵���а�������
   {
      delay(10);
      for (i = 0; i < 4; i++)
      { //
         P = 0x8000;
         *P = line << i; //��ֵ��ֵ
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
      break; /*��һ�е�1��*/
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
      break; /*��һ�е�2��*/

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
      break; /*��һ�е�3��*/

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
      break; /*��һ�е�4��*/

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
         break; /*�ڶ��е�1��*/

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
         break; /*�ڶ��е�2��*/

      case 0x42:
         k = 0;
         break; /*�ڶ��е�3��*/

      case 0x82:
         k = 0;
         break; /*�ڶ��е�4��*/

      case 0x14:
         k = 1;
         break; /*�����е�1��*/
      case 0x24:
         k = 2;
         break; /*�����е�2��*/
      case 0x44:
         k = 3;
         break; /*�����е�3��*/
      case 0x84:
         k = 4;
         ;
         break; /*�����е�4��*/
      case 0x18:
         k = 5;
         break; /*�����е�1��*/
      case 0x28:
         k = 6;
         break; /*�����е�2��*/
      case 0x48:
         k = 7;
         break; /*�����е�3��*/
      case 0x88:
         k = 8;
         break; /*�����е�4��*/
      default:
         break;
      }

      XBYTE[0x8000] = 0x01;
      XBYTE[0x9000] = led_table[k];
   }
}
