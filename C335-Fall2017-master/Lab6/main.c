//Partners: Sander Altman and Dhruv Agnihotri

//main.c for lab6
#include <f3d_uart.h>
#include <stdio.h>
#include <stdlib.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

//Graphical variables
int maxBarLength = 15;
int padding = 10;
int pixelsBetweenRows = 48;
int pixelsAboveBar = 15;
uint16_t backgroundColor = WHITE;
uint16_t textColor = BLACK;
uint16_t positiveBarColor = GREEN;
uint16_t negativeBarColor = RED;

//Make a bar for display to represent the given value
void makeBar(float value, char *bar) {
  int length = (int) (abs(value) / 2) + 1;
  if (length > maxBarLength) length = maxBarLength;
  bar[0] = value < 0 ? '-' : '+';
  int i;
  for (i = 1; i < length; ++i) {
    bar[i] = ' ';
  }
  bar[i] = '\0';
}


void main(void) {
  f3d_uart_init();
  f3d_gyro_init();
  f3d_lcd_init();

  float data[3];
  char axisLabels[] = { 'x', 'y', 'z' };
  int x = 0, y = 1, z = 2;
  int axis = x;

  char strings[3][128];
  char bar[maxBarLength + 1];

  while(1) {
    //Collect data
    f3d_gyro_getdata(data);

    //Set background
    f3d_lcd_fillScreen(backgroundColor);

    int i;
    for (i = 0; i < 3; ++i) {
      //Prepare string for lcd
      sprintf(strings[i], "%c: %+f", axisLabels[i], data[i]);
      //Print to serialT for debugging
      printf("%s\n",strings[i]);
      //Create bar
      makeBar(data[i], bar);
	      
      //Draw text
      f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, strings[i], textColor, backgroundColor);
      //Draw bar
      f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, data[i] < 0 ? negativeBarColor : positiveBarColor);
    }
    printf("\n");
    delay(1000);
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
