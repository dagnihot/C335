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
 * Dhruv Agnihotri (dagnihot) & Joe Hodson (jthodson)
 */

/* Commentary: 
 * uses mywc from lab 2
 * 
 * 
 */

/* Change log:
 * implements putchar()
 * 
 */
/* Code: */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

void mywc() {
	int line_count = 0;
	int word_count = 0;
	int character_count = 0;
	char* str;
	int c; /* current character */

	while ((c = getchar()) != 0x1b) {
	  putchar(c);
	  character_count++;
	  if (c >= 9 && c <= 12 || c == 32) {
	    if (c == 10) {
	      line_count++;
	    }
	    word_count++;
	  }
	}
	printf("%d %d %d\n", line_count, word_count, character_count);
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  while (1){
    //putstring("Hello World!"); 
    mywc();
    //putchar(getchar());
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
