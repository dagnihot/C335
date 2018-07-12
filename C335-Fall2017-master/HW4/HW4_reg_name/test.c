//Dhruv Agnihotri
//C335-HW4

#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "reg_name_c.h"

void reg_name_test(void) {
  int i;
  int error_count=0;
  for (i=0;i<10;i++) {
    if (reg_name(i) != regName(i)) {
      printf("REGISTER TEST ERROR: Expected %d, Received %d\n",reg_name(i),regName(i));
      error_count++;
    }
  }
  if (!error_count) {
    printf("REGISTER TESTS PASSED. GOOD WORK BUCKAROO\n");
  }
  else {
    printf("REGISTER TEST: %d errors\n",error_count);
  }
}
