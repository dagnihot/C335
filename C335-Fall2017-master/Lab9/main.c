/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */

/*    Name : David Gutsch
      Partner: Dhruv Agnihotri 
      uname: dgutsch
      date: 11/03/2017          */


#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;		/* File system object */
FIL Fil;		/* File object */
BYTE Buff[128];		/* File read buffer */

////////////////////////////////////////////
/*file to read *///
//char pictureFile[10];
//TCHAR* pictureFile = "apple.bmp";
//strcpy(pictureFile, pic);
//TCHAR* pictureFile= "pony.bmp";         //
TCHAR* pictureFile= "Karen_~1.bmp";
TCHAR* pictureFiles[3] =  {"Karen_~1.bmp", "pony.bmp", "mini.bmp"};                 
             
///////////////////////////////////////////

uint16_t pixel_struct_bmp_mask(bmppixel); 
int isFlipped();
int isPicChanged();

int main(void) { 
  char footer[20];
  int count=0;
  int i;

  FRESULT rc;			/* Result code */
  DIR dir;			/* Directory object */
  FILINFO fno;			/* File information object */
  UINT bw, br;
  unsigned int retval;

  // initializations
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  delay(100);
  f3d_lcd_init();
  delay(300);
  f3d_lcd_fillScreen(RED);
  f3d_delay_init();
  delay(100);
  f3d_rtc_init();
  delay(100);
  f3d_lcd_fillScreen(WHITE);
  delay(200);
  f3d_i2c1_init();
  delay(100);
  f3d_accel_init();
  delay(100);
  //f3d_mag_init();
  //delay(100);
  f3d_nunchuk_init();
  delay(100);
  f3d_gyro_init();
  delay(100);
  
  int change = 1;
  int picture_state = 0;
  int flip_case = 1;
  //////////////////////////////////////////////////////////////////////////////////////
  //                  GIVEN TEST CODE 
  //////////////////////////////////////////////////////////////////////////////////////
  f_mount(0, &Fatfs);		/* Register volume work area (never fails) */
  delay(400);
  f3d_lcd_fillScreen(BLUE);
  printf("\nNobody exists on purpose... nobody belongs anywhere... were all going to die\ncome watch tv\n");

  
  while(1) {


    if(change) {
      f3d_lcd_fillScreen(WHITE);
      printf("\nOpen an existing file (%s).\n",pictureFiles[picture_state]);
      rc = f_open(&Fil, pictureFiles[picture_state], FA_READ);
      printf("\nWeddings are basically funerals with cake\n");
      if (rc) die(rc);
      printf("\nFile Opened.\n");
      
    // variables used to read in header information (we just need to get rid of it)
      UINT* bytes_read;
      bmpfile_magic magic_junk;
      bmpfile_header header_junk;
      BITMAPINFOHEADER bitmap_junk;
      printf("\n Rise above, focus on science morty!\n");
      
      //actually read in and discard header information
      rc = f_read(&Fil, &magic_junk, sizeof(magic_junk), &br);
      printf("\nmbpfile_magic error: %u bmpfile_magic struct size= %u\n", rc, br);
      rc = f_read(&Fil, &header_junk, sizeof(header_junk), &br);
      printf("\nheader \n"); 
      rc = f_read(&Fil, &bitmap_junk, sizeof(bitmap_junk), &br);
      printf("\nBITMAPINFOHEADER error: %u struct size= %u\n", rc, br);
      
      
      //f3d_lcd_setAddrWindow(0, 0, 128, 160, MADCTLGRAPHICS); // 0x6 portrait
      //f3d_lcd_setAddrWindow(0,0,128,160, 0x2); // 0x2 portrait upside down
      //f3d_lcd_setAddrWindow(0,0,127,159, 0x3); 
      //f3d_lcd_setAddrWindow(0,0,127, 159, 0x5);
      
      printf("we're here\n");
      switch(flip_case) {
	case 1:
	  f3d_lcd_setAddrWindow(0,0,127,159, 0x3); 
	  //f3d_lcd_setAddrWindow(0, 0, 128, 160, MADCTLGRAPHICS); // 0x6 portrait
	  break;
	case 2:
	   f3d_lcd_setAddrWindow(0,0,127, 159, 0x5);
	   //f3d_lcd_setAddrWindow(0,0,128,160, 0x2); // 0x2 portrait upside down
	   break;
	case 3:
	  f3d_lcd_setAddrWindow(0, 0, 128, 160, MADCTLGRAPHICS); // 0x6 portrait
	  //f3d_lcd_setAddrWindow(0,0,127,159, 0x3); 
	  break;
	case 4:
	  f3d_lcd_setAddrWindow(0,0,128,160, 0x2); // 0x2 portrait upside down
	  //f3d_lcd_setAddrWindow(0,0,127, 159, 0x5);
	  break;
	  }
      
      bmppixel raw_data[128];
      uint16_t pixel_array[128];
      
      
      printf("\nC'mon rick don't talk about my parents like that!\n");
      int k;
      for (k = 0;k < 128;k++) {
	rc = f_read(&Fil, &raw_data, sizeof(raw_data), &br);	/* Read a chunk of file */
	
	// this loop converts pixel from 24 bits to 16
	for (i = 0; i < 128; i++) {  
	  // pixel_array[i] = pixel_struct_bmp_mask(raw_data[i]);
	  pixel_array[i] = ((raw_data[i].b >> 3) << 11) | ((raw_data[i].g >>2) << 5) | (raw_data[i].r >> 3);
	}
	f3d_lcd_pushColor(pixel_array, 128);// now push color onto screen    
	
	if (rc || !br) break;			/* Error or end of file */
      }
      if (rc) die(rc);
      
      
      printf("\nClose the file.\n");
      rc = f_close(&Fil);
      if (rc) die(rc);

      change = 0;
    }
    ///////////////////////////////////////////////////////////////////
    //while(1) {
    int pic_change_val; // 0 no change, 1 left, 2 right
    
    if(pic_change_val = isPicChanged()) {
      switch(pic_change_val) {
	////////////////////////////////
      case 1:
	switch(picture_state) {
	case 0:
	  picture_state = 2;
	  break;
	case 1:
	  picture_state--;
	  break;
	case 2: 
	  picture_state--;
	  break;
	}
	break;
	////////////////////////////////
      case 2: 
	switch(picture_state) {
	case 0:
	  picture_state++;
	  break;
	  case 1:
	    picture_state++;
	    break;
	case 2: 
	  picture_state = 0;
	  break;
	}
	break;
      }
      /////////////////////////////////
      change = 1;
      break;
    }
    
    if(flip_case = isFlipped()) {
      printf("we're here two    %d\n", flip_case);
      change = 1;
    }
    printf("change: %d  flip case: %d\n", change, flip_case);
    //isFlipped();
    //}
  }
}

// this function does the bit masking for the bmp files
uint16_t pixel_struct_bmp_mask(bmppixel pixel) {
  // bit shift r,g,b to fit in uint16_t and or components together
  uint16_t color = ((pixel.b >> 3) << 11) | ((pixel.g >>2) << 5) | (pixel.r >> 3);
  return color;
}

int isFlipped() {
  // return 0 - 4 depending on the board orientation
  // this will use pitch and roll from board accelerometer/magnetometer
  //float mag[3];
  float accel[3];
  f3d_accel_read(accel);
  if(accel[0] > 0.5) {
    return 3;
  }
  else if(accel[0] < -0.5) {
    return 4;
  }
  else if(accel[1] > 0.5) {
    return 1;
  }
  else if(accel[1] < -0.5) {
    return 2;
  }

  printf("x accel: %f   y accel: %f\n\n", accel[0], accel[1]); 
  return 0;
}

int isPicChanged() {
  //returns 0 is no change, 1 is left , or 2 is right
  // this function will read information from the nunchuk
  int left = 0;
  int right = 0;
  nunchuk_t nunchukData;
  f3d_nunchuk_read(&nunchukData);

  if(nunchukData.z == 1 && nunchukData.c == 1) return 0;
  if(nunchukData.z == 1 || nunchukData.jx > 180) return 1;
  else if (nunchukData.c == 1 || nunchukData.jx < 100)  return 2;
  else return 0;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
