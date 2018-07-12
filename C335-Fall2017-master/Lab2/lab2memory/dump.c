//Dhruv Agnihotri
//dagnihot
//Lab 2
// Partner - Joe Hodson



void dump_memory(void *p, int len)
{
	int i;
	
	printf("address		char 		hexCh 		short     	integer         float      doubleFloat\n");
	
	for (i=0; i < len; i++) {
	printf("%8p: ", p + i); //address

	int j = *(unsigned char*)(p + i);
	if (j > 32 && j < 127){
		printf("%c\t", j);//char
		}
	else {
		printf("?\t");
		}
	printf("0x%02x\t", *(unsigned char *)(p + i));//hexCh
	if (i % 2 == 0){
		printf("%+d\t", *(short int *)(p + i));//short
		if (i % 4 == 0) {
			 printf("%+d\t", *(unsigned int *)(p + i));//int
			 printf("%+e\t", *(float *)(p + i));//float
			 if (i % 8 == 0){
				 printf("%+e\t", *(double *)(p + i));//doubleFloat
					}
				}
			}
	printf("\n");

	}
}
