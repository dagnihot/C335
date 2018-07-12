/* main.c ---
 *
 * Filename: main.c
 * Description:
 * Author: Nick Root, Dhruv Agnihotri
 * Maintainer:
 * Created: Thu Jan 10 11:23:43 2013
 /* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <math.h>
#include <f3d_gyro.h>

#define TIMER 20000

float dataA[3];
float dataM[3];

float angleCalc(int b){
  float x = dataA[0];
  float y = dataA[1];
  float z = dataA[2];
  float pitch = atan2(x, (sqrt(pow(y, 2) + pow(z, 2))));
  float roll = atan2(y, (sqrt(pow(x, 2) + pow(z, 2))));
  float yaw = atan2(z, (sqrt(pow(x, 2) + pow(y, 2))));

  if (b == 0){
    return pitch;
  }
  else{
    return roll;
  }
}

float compassHeadingCalc (int b){
  float compassHead;
  float pitch = angleCalc(0);
  float roll = angleCalc(1);

  float accelX = dataA[0];
  float accelY = dataA[1];
  float accelZ = dataA[2];
  float magX = dataM[0];
  float magY = dataM[1];
  float magZ = dataM[2];
 
  float compassHeadX = (magX * cos(pitch)) + (magY * sin(pitch));
  float compassHeadY = (magX * sin(pitch) * sin(roll)) + (magY * cos(roll)) - (magZ * sin(roll) * cos(pitch));

  if (b) {
    compassHead = atan2(compassHeadY, compassHeadX) + M_PI;
  } else {
    compassHead = ( atan2(compassHeadY, compassHeadX) * (180 / M_PI) ) + 180;
  }
  return compassHead;
}


//stuff from lab 6

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


int main(void) {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // Set up your inits before you go ahead
  f3d_lcd_init();
  delay(100);
  f3d_user_btn_init();
  f3d_lcd_fillScreen(BLUE);
  delay(100);
  f3d_uart_init();
  f3d_lcd_fillScreen(RED);
  delay(100);
  f3d_i2c1_init();
  f3d_lcd_fillScreen(GREEN);
  delay(100);
  f3d_accel_init();
  f3d_lcd_fillScreen(BLACK);
  
  printf("hi");
  
  delay(100);
  f3d_mag_init();
  delay(100);
  f3d_lcd_fillScreen(RED);

  f3d_accel_read(dataA);
  f3d_mag_read(dataM);



  char axisLabels[] = { 'x', 'y', 'z' };
  int x = 0, y = 1, z = 2;
  int axis = x;
  char strings[3][128];
  char bar[maxBarLength + 1];

  int pointer[11][2] = { {40, 60},{40, 61},{40, 62},{40, 63},{40, 64},{40, 65},{40, 66},{40, 67},{40, 68},{40, 69},{40, 70} }; 


  int count = 0;
  int mod = 0;



  while(1){
    f3d_accel_read(dataA);
    while (user_btn_read()) {
      count++;
      mod = count%2;
      delay(1000);
    }

    if (count == 0 || count == 4) {
      //Set background
      f3d_lcd_fillScreen(backgroundColor);

      int i;
      for (i = 0; i < 1; ++i) {
	//Prepare string for lcd
	sprintf(strings[i], "%c: %+f", axisLabels[i], angleCalc(0));
	//Print to serialT for debugging
	printf("%s\n",strings[i]);
	//Create bar
	makeBar(angleCalc(0), bar);
	      
	//Draw text
	f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "pitch:", textColor, backgroundColor);
	//Draw bar
	f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, angleCalc(0) < 0 ? negativeBarColor : positiveBarColor);
      }
      for (i = 1; i < 2; ++i) {
	//Prepare string for lcd
	sprintf(strings[i], "%c: %+f", axisLabels[i], angleCalc(1));
	//Print to serialT for debugging
	printf("%s\n",strings[i]);
	//Create bar
	makeBar(angleCalc(1), bar);
	      
	//Draw text
	f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "roll:", textColor, backgroundColor);
	//Draw bar
	f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, angleCalc(1) < 0 ? negativeBarColor : positiveBarColor);
      }
      for (i = 2; i < 3; ++i) {
	//Prepare string for lcd
	sprintf(strings[i], "%c: %+f", axisLabels[i], angleCalc(2));
	//Print to serialT for debugging
	printf("%s\n",strings[i]);
	//Create bar
	makeBar(angleCalc(2), bar);
	      
	//Draw text
	f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "yaw:", textColor, backgroundColor);
	//Draw bar
	f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, angleCalc(2) < 0 ? negativeBarColor : positiveBarColor);
      }
      printf("\n");
      delay(10);
    } else if (count == 1 || count == -1) {
      f3d_lcd_fillScreen(RED);
      f3d_mag_read(dataM);

      int x;
      for (x = 0; x < 11; x++){
	float arrow1 = pointer[x][0];
	float arrow2 = pointer[x][1];
	float rotateArrowX = ((arrow1 * cos(compassHeadingCalc(1) + M_PI)) + ((arrow2 * sin(compassHeadingCalc(1) + M_PI)))) / 2;
	float rotateArrowY = ((arrow1 * sin(compassHeadingCalc(1) + M_PI) * -1) + ((arrow2 * cos(compassHeadingCalc(1) + M_PI)))) / 2;
	f3d_lcd_drawPixel(rotateArrowX + 40, rotateArrowY + 90, BLUE);
      }
    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
