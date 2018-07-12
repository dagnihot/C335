/* Hasan Y Ahmed
 * Dhruv Agnihotri
 * Lab 3
 * 9/8/17
 */
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
    f3d_led_init();

    f3d_user_btn_init();

    

  while(1){
      int i = 0;
      for(i; i < 8;){
btn_held:
          if(user_btn_read()){
              f3d_led_on(i);
              goto btn_held;
          }
          else{
              f3d_led_on(i);
              delay();
              i++;
              if(i != 0){
                f3d_led_off(i-1);
            }
          }
      }
      f3d_led_all_on();
btn_held_all:
      if(user_btn_read()){
          f3d_led_all_on();
          goto btn_held_all;
      }
      delay();
      f3d_led_all_off();
      delay();

      /*
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)){
        //f3d_led_on(8);
        f3d_led_all_on();
    }
    else{
        f3d_led_all_off();
        //f3d_led_off(8);
    }
    */
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




