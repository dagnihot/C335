
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
#include <f3d_nunchuk.h>

#define TIMER 20000

nunchuk_t nunData;
int count = 0;
float data[3];
//Graphical variables
int maxBarLength = 15;
int padding = 10;
int pixelsBetweenRows = 48;
int pixelsAboveBar = 15;
uint16_t backgroundColor = WHITE;
uint16_t textColor = BLACK;
uint16_t positiveBarColor = GREEN;
uint16_t negativeBarColor = RED;
char axisLabels[] = { 'x', 'y', 'z' };
int x = 0, y = 1, z = 2;
int axis = 0;
int pointer[11][2] = { {40, 60},{40, 61},{40, 62},{40, 63},{40, 64},{40, 65},{40, 66},{40, 67},{40, 68},{40, 69},{40, 70} }; 

char strings[3][128];
char bar[15 + 1];

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


int countCheck(int cont){
  f3d_nunchuk_read(&nunData);
  if (nunData.c == 1 || nunData.jx == 0){
    while (nunData.c == 1 || nunData.jx == 0){
      f3d_nunchuk_read(&nunData);
    }
    f3d_lcd_fillScreen(backgroundColor);
    cont--;
    if (cont == -1){
      cont = 3;
    }
  }
  if (nunData.z == 1 || nunData.jx == 255){
    while (nunData.z == 1 || nunData.jx == 255){
      f3d_nunchuk_read(&nunData);
    }
    f3d_lcd_fillScreen(backgroundColor);
    cont++;
    if (cont == 4){
      cont = 0;
    }
  }
  return cont;
}






int main(void) {


  // Set up your inits before you go ahead
  f3d_uart_init();
  delay(10);
  f3d_user_btn_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_gyro_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  int i, j;
  f3d_nunchuk_read(&nunData);
  
  float compassH;
  float compassPrev = 0.0;

  /*

    while(1){
    
    f3d_nunchuk_read(&nunData);
    
    printf("JX: %hu, JY: %hu\n", nunData.jx, nunData.jy);
    printf("\n");

    printf("AX: %hu, AY: %hu, AZ: %hu\n", nunData.ax, nunData.ay, nunData.az);
    printf("\n");


    printf("C: %hu, Z: %hu\n", nunData.c, nunData.z);
    printf("\n");
    }

  */


  
  while(1) {
    //Gyroscope
    if (count == 0){
      //int j = 0;
      f3d_lcd_fillScreen(backgroundColor);
      for (j = 0; j < 3; ++j) {
	sprintf(strings[j], "%c: %+f", axisLabels[j], data[j]);
	f3d_lcd_drawString(padding, padding + j*pixelsBetweenRows, strings[j], textColor, backgroundColor);
      }
      while(count == 0){
	//Collect data
	/*
	  printf("%d \n", count);
	  f3d_nunchuk_read(&nunData);
	  if (nunData.jx >= 0 && nunData.jx < 50) {
	  count--;
	  delay(100);
	  f3d_lcd_fillScreen(backgroundColor);
	  } else if (nunData.jx > 200) {
	  count++;
	  delay(100);
	  f3d_lcd_fillScreen(backgroundColor);
	  } else if (nunData.c == 1) {
	  count++;
	  delay(100);
	  f3d_lcd_fillScreen(backgroundColor);
	  } else if (nunData.z == 1) {
	  count--;
	  f3d_lcd_fillScreen(backgroundColor);
	  }*/
	count = countCheck(count);
	
	f3d_gyro_getdata(data);
	
	//Set background
	//f3d_lcd_fillScreen(backgroundColor);
	
	//int i;
	for (i = 0; i < 3; ++i) {
	  //Prepare string for lcd
	  //sprintf(strings[i], "%c: %+f", axisLabels[i], data[i]);
	  //Print to serialT for debugging
	  printf("%s\n",strings[i]);
	  //Create bar
	  makeBar(data[i], bar);
	  
	  //Draw text
	  //f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, strings[i], textColor, backgroundColor);
	  //Draw bar
	  f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, data[i] < 0 ? negativeBarColor : positiveBarColor);
	}
	printf("\n");
      }
    }


    

    //Accelerometer
    if (count == 1){
      //int j = 0;
      f3d_lcd_fillScreen(backgroundColor);
      for (j = 0; j < 3; ++j) {
	if (j == 0){
	  sprintf(strings[j], "%c: %+f", axisLabels[j], angleCalc(0));
	  f3d_lcd_drawString(padding, padding + j*pixelsBetweenRows, "pitch:", textColor, backgroundColor);
	} else if (j == 1){
	  sprintf(strings[j], "%c: %+f", axisLabels[j], angleCalc(1));
	  f3d_lcd_drawString(padding, padding + j*pixelsBetweenRows, "roll:", textColor, backgroundColor);
	} else {
	  sprintf(strings[j], "%c: %+f", axisLabels[j], angleCalc(2));
	  f3d_lcd_drawString(padding, padding + j*pixelsBetweenRows, "yaw:", textColor, backgroundColor);
	}
      }
      while (count == 1){
	count = countCheck(count);
		
	//display tilt angle
	f3d_accel_read(dataA);
	//f3d_lcd_fillScreen(backgroundColor);
	
	//int i;
	//for (i = 0; i < 1; ++i) {
	;
	//Prepare string for lcd
	//sprintf(strings[i], "%c: %+f", axisLabels[i], angleCalc(0));
	//Print to serialT for debugging
	//printf("%s\n",strings[i]);
	//Create bar
	makeBar(angleCalc(0), bar);
	  
	//Draw text
	//f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "pitch:", textColor, backgroundColor);
	//Draw bar
	f3d_lcd_drawString(padding, padding + 0*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, angleCalc(0) < 0 ? negativeBarColor : positiveBarColor);
	//}
	
	//for (i = 1; i < 2; ++i) {
	//Prepare string for lcd
	//sprintf(strings[i], "%c: %+f", axisLabels[i], angleCalc(1));
	//Print to serialT for debugging
	//printf("%s\n",strings[i]);
	//Create bar
	makeBar(angleCalc(1), bar);
	  
	//Draw text
	//f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "roll:", textColor, backgroundColor);
	//Draw bar
	f3d_lcd_drawString(padding, padding + 1*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, angleCalc(1) < 0 ? negativeBarColor : positiveBarColor);
	//}
	
	//for (i = 2; i < 3; ++i) {
	//Prepare string for lcd
	//sprintf(strings[i], "%c: %+f", axisLabels[i], angleCalc(2));
	//Print to serialT for debugging
	//printf("%s\n",strings[i]);
	//Create bar
	makeBar(angleCalc(2), bar);
	  
	//Draw text
	//f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "yaw:", textColor, backgroundColor);
	//Draw bar
	f3d_lcd_drawString(padding, padding + 2*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, angleCalc(2) < 0 ? negativeBarColor : positiveBarColor);
	//}
      }
    }
    
    //Magnetometer
    if (count == 2){
      count = countCheck(count);

      //f3d_lcd_fillScreen(backgroundColor);
      f3d_mag_read(dataM);

      compassH = compassHeadingCalc(1);
      
      int x;
      if (compassH != compassPrev){
	f3d_lcd_fillScreen(backgroundColor);
	for (x = 0; x < 11; x++){
	  float arrow1 = pointer[x][0];
	  float arrow2 = pointer[x][1];
	  float rotateArrowX = ((arrow1 * cos(compassH + M_PI)) + ((arrow2 * sin(compassH + M_PI)))) / 2;
	  float rotateArrowY = ((arrow1 * sin(compassH + M_PI) * -1) + ((arrow2 * cos(compassH + M_PI)))) / 2;
	  f3d_lcd_drawPixel(rotateArrowX + 40, rotateArrowY + 90, BLUE);
	}
	compassPrev = compassH;
      }
    }

    //Nunchuk
    if (count == 3){
      f3d_lcd_fillScreen(backgroundColor);
      sprintf(strings[0], "%c: %+f", axisLabels[0], nunData.ax);
      f3d_lcd_drawString(padding, padding + 0*pixelsBetweenRows, "AX:", textColor, backgroundColor);

      sprintf(strings[1], "%c: %+f", axisLabels[1], nunData.ay);
      f3d_lcd_drawString(padding, padding + 1*pixelsBetweenRows, "AY:", textColor, backgroundColor);

      sprintf(strings[2], "%c: %+f", axisLabels[2], nunData.az);
      f3d_lcd_drawString(padding, padding + 2*pixelsBetweenRows, "AZ:", textColor, backgroundColor);

      while(count == 3){
	count = countCheck(count);
	f3d_nunchuk_read(&nunData);
	//int i;
	for (i = 0; i < 1; ++i) {
	  //Prepare string for lcd
	  //sprintf(strings[i], "%c: %+f", axisLabels[i], nunData.ax);
	  //Print to serialT for debugging
	  //printf("%s\n",strings[i]);
	  //Create bar
	  makeBar(nunData.ax * 10000, bar);
	      
	  //Draw text
	  //f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "AX:", textColor, backgroundColor);
	  //Draw bar
	  f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, nunData.ax-350 < 0 ? negativeBarColor : positiveBarColor);
	}
	for (i = 1; i < 2; ++i) {
	  //Prepare string for lcd
	  //sprintf(strings[i], "%c: %+f", axisLabels[i], nunData.ay);
	  //Print to serialT for debugging
	  //printf("%s\n",strings[i]);
	  //Create bar
	  makeBar(nunData.ay, bar);
	      
	  //Draw text
	  //f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "AY:", textColor, backgroundColor);
	  //Draw bar
	  f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, nunData.ay-350 < 0 ? negativeBarColor : positiveBarColor);
	}
	for (i = 2; i < 3; ++i) {
	  //Prepare string for lcd
	  //printf(strings[i], "%c: %+f", axisLabels[i], nunData.az);
	  //Print to serialT for debugging
	  //printf("%s\n",strings[i]);
	  //Create bar
	  makeBar(nunData.az, bar);
	      
	  //Draw text
	  //f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows, "AZ:", textColor, backgroundColor);
	  //Draw bar
	  f3d_lcd_drawString(padding, padding + i*pixelsBetweenRows + pixelsAboveBar, bar, backgroundColor, nunData.az-350 < 0 ? negativeBarColor : positiveBarColor);
	}
	// }
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


