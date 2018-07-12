/* Hasan Y Ahmed
 * Dhruv Agnihotri
 * Lab 3
 * 9/8/17
 */
/**********************************
 *f3d_user_btn.c 
 *contains the init and read functions for the User Button
 *********************************/
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>


/*Initialization of the UserButton*/
void f3d_user_btn_init(void){
    GPIO_InitTypeDef button; 
    GPIO_StructInit(&button);
    button.GPIO_Pin = GPIO_Pin_0;
    button.GPIO_Mode = GPIO_Mode_IN;
    button.GPIO_PuPd = GPIO_PuPd_NOPULL;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_Init(GPIOA, &button);
}

/*reads the User Button*/
int user_btn_read(void){
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
}
