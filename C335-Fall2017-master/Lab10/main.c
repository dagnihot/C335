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

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_delay.h>
#include <f3d_systick.h>
#include <f3d_user_btn.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



void main(void){


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






while(1){

putchar(getchar());

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
