#include<stdio.h>
#include<unistd.h>

int main(){
  int i;
  for (i=20; i>=0; i--){
    printf("This message will self-destruct in %d seconds\n", i);
    printf("Hello World!\n");
    sleep(3);
  }

  return(0);
}
 
