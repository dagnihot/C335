//Dhruv Agnihotri
//C335-HW4

#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "max_array_c.h"

void max_array_test(void) {
  int i;
  int error_count=0;
  unsigned int list[10] = {0, 9, 1, 8, 2, 7, 3, 6, 4, 5};
  for (i=0;i<10;i++) {
    if (max_array_c(list, i) != max_array(list, i)) {
      printf("MAX ARRAY ERROR: Expected %d, Received %d\n",max_array_c(list, i),max_array(list, i));
      error_count++;
    }
  }
  if (!error_count) {
    printf("MAX ARRAY TESTS PASSED. GOOD WORK BUCKAROO\n");
  }
  else {
    printf("MAX ARRAY TEST: %d errors\n",error_count);
  }
}
