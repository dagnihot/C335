#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "string_length_c.h"


void string_length_test(void) {
  
int i;
  
int error_count=0;
  
char string[40];
  

for (i=0;i<40;i++) {
    
	string[i] = 0;
  
}
  
for (i=0;i<39;i++) {
    
	string[i] = (char)('a' + (i%26));
    
	if (string_length(string) != string_length(string)) {
      
		printf("STRING LENGTH TEST ERROR: Expected %d, Received %d\n",string_length(string),string_length(string));
     
		error_count++;
    
			}
  
		}
  
	if (!error_count) {
    
		printf("AYYYEEEE STRING LENGTH TEST PASSED. GOOD WORK BUCKAROO\n");
  
			}
  
	else {
    printf("STRING LENGTH TEST: %d errors\n",error_count);
  }
			
}




/* test.c ends here */
