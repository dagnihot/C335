#include <stdio.h>

int main(){

	int line_count;
	int word_count;
	int character_count;
	int c; //current character

	while((c = getchar()) != EOF){
		character_count++;
		if ((c== ' ' || c== '\t' || c== '\r' || c== '\n' || c=='\f' || c== '\v')){
			word_count++;
			}
		if (c == '\n'){
			word_count++;
			line_count++;
			}
	}
	printf("%d %d %d/n", line_count, word_count, character_count);
	return(0);
}
