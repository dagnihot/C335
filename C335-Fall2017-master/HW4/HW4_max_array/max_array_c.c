//Dhruv Agnihotri
//C335-HW4


#include <stdio.h>

unsigned int max_array_c(unsigned int *list, int size){
  int i = 0;
  int max = 0;
  for (i=0;i<size;i++)
    if(list[i]>max) max=list[i];
    return max;
}
