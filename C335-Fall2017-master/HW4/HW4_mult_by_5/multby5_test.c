//Dhruv Agnihotri
//C335
//HW 4

#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "multby5_c.h"

void multby5_test(void) {
  int i;
  int error_count=0;
  for (i=0;i<=46;i++) {
    if (multby5(i) != mult_by_5(i)) {
      printf("Mult by 5 Error: Input %d, Expected %d, Received %d\n",i,mult_by_5(i),multby5(i));
      error_count++;
    }
  }
  if (!error_count) {
    printf("Mult by 5 Tests Passed\n");
  }
  else {
    printf("Mult by 5 Test: %d errors\n",error_count);
  }
}
