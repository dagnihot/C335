//Dhruv Agnihotri & Will Ollo
// lab 5
//main.c for lab5
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>


//X + 177, Y + 220, Z - 144

void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void){
  f3d_uart_init();
  delay();
  printf("UART initialized! \n");
  f3d_led_init();
  delay();
  printf("Dem LEDS tho. \n");
  f3d_gyro_init();
  delay();
  printf("SPI works yay. \n");
  f3d_user_btn_init();
  delay();
  printf("User button init. \n");

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  delay();
  
  float test[3] = {0.0,0.0,0.0};
  int count = 0;
  printf("Inits done.\n");


  char X[] = "X";
  char Y[] = "Y";
  char Z[] = "Z";
  
  int c;
  
 
  
  

  while(1){
    f3d_gyro_getdata(test);
    
    //c = getchar();
    printf("X:%f, Y:%f, Z:%f\n" , test[0], test[1], test[2]);
      
    delay();
    f3d_led_all_off();
    if(user_btn_read()){
      count = count + 1;
    }
    switch(count%3){
    case 0:
      if(test[0] >= 90){
	GPIOE->BSRR = GPIO_Pin_9;
	GPIOE->BSRR = GPIO_Pin_10;
	delay();
	if(test[0] >= 190){
	  GPIOE->BSRR = GPIO_Pin_11;
	  GPIOE->BSRR = GPIO_Pin_12;
	  delay();
	  if(test[0] >= 240){
	    GPIOE->BSRR = GPIO_Pin_13;
	    GPIOE->BSRR = GPIO_Pin_14;
	    GPIOE->BSRR = GPIO_Pin_15;
	    GPIOE->BSRR = GPIO_Pin_8;
	    delay();
	  }
	}
      }
      if(test[0] <= -90){
	GPIOE->BSRR = GPIO_Pin_9;
	GPIOE->BSRR = GPIO_Pin_8;
	delay();
	if(test[0] <= -190){
	  GPIOE->BSRR = GPIO_Pin_15;
	  GPIOE->BSRR = GPIO_Pin_14;
	  delay();
	  if(test[0] <= -260){
	    GPIOE->BSRR = GPIO_Pin_13;
	    GPIOE->BSRR = GPIO_Pin_12;
	    GPIOE->BSRR = GPIO_Pin_11;
	    GPIOE->BSRR = GPIO_Pin_10;
	    delay();
	  }
	}
      }
    case 1:	
      if(test[1] >= 90){
	GPIOE->BSRR = GPIO_Pin_9;
	GPIOE->BSRR = GPIO_Pin_10;
	delay();
	if(test[1] >= 190){
	  GPIOE->BSRR = GPIO_Pin_11;
	  GPIOE->BSRR = GPIO_Pin_12;
	  delay();
	  if(test[1] >= 240){
	    GPIOE->BSRR = GPIO_Pin_13;
	    GPIOE->BSRR = GPIO_Pin_14;
	    GPIOE->BSRR = GPIO_Pin_15;
	    GPIOE->BSRR = GPIO_Pin_8;
	    delay();
	  }
	}
      }
      if(test[1] <= -90){
	GPIOE->BSRR = GPIO_Pin_9;
	GPIOE->BSRR = GPIO_Pin_8;
	delay();
	if(test[1] <= -190){
	  GPIOE->BSRR = GPIO_Pin_15;
	  GPIOE->BSRR = GPIO_Pin_14;
	  delay();
	  if(test[1] <= -260){
	    GPIOE->BSRR = GPIO_Pin_13;
	    GPIOE->BSRR = GPIO_Pin_12;
	    GPIOE->BSRR = GPIO_Pin_11;
	    GPIOE->BSRR = GPIO_Pin_10;
	    delay();
	  }
	}
      }
    case 2:	
      if(test[2] >= 90){
	GPIOE->BSRR = GPIO_Pin_9;
	GPIOE->BSRR = GPIO_Pin_10;
	delay();
	if(test[2] >= 190){
	  GPIOE->BSRR = GPIO_Pin_11;
	  GPIOE->BSRR = GPIO_Pin_12;
	  delay();
	  if(test[2] >= 240){
	    GPIOE->BSRR = GPIO_Pin_13;
	    GPIOE->BSRR = GPIO_Pin_14;
	    GPIOE->BSRR = GPIO_Pin_15;
	    GPIOE->BSRR = GPIO_Pin_8;
	    delay();
	  }
	}
      }
      if(test[2] <= -90){
	GPIOE->BSRR = GPIO_Pin_9;
	GPIOE->BSRR = GPIO_Pin_8;
	delay();
	if(test[2] <= -190){
	  GPIOE->BSRR = GPIO_Pin_15;
	  GPIOE->BSRR = GPIO_Pin_14;
	  delay();
	  if(test[2] <= -260){
	    GPIOE->BSRR = GPIO_Pin_13;
	    GPIOE->BSRR = GPIO_Pin_12;
	    GPIOE->BSRR = GPIO_Pin_11;
	    GPIOE->BSRR = GPIO_Pin_10;
	    delay();
	  }
	}
      }
    }
  }
}


void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
