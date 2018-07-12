//Dhruv Agnihotri
//C335-HW4


#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "reg_name_c.h"

char *names[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"};
char *reg_name(unsigned int x){
  if (x > 15) {
    return 0;
  }
  return names[x];
}
