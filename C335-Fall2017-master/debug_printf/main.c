/* Partners: Sander Altman Dhruv Agnihotri
 * Lab 6 Debug Printf
 */

//The libraries to include
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_led.h>
#include <stdio.h> 
#include <stdint.h>
//The arrays that store the bits

//runs some test on our program
int main(){
  f3d_uart_init();
  f3d_user_btn_init();
  f3d_led_init();

  int debug = 0;
  //Turn led on and off, and print debug info when the user button is being held down
  while (1) {
    if (debug) printf("Turning on the north led\n");
    f3d_led_on(1);
    if (debug) printf("Turning off the north led\n");
    f3d_led_off(1);
    if (debug) printf("Checking for user button press to toggle prints\n");
    debug = user_btn_read();
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
