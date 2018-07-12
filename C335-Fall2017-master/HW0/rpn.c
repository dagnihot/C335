//Dhruv Agnihotri
//Homework 0
//C335

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CELL *LIST;
struct CELL {
	int val;
	LIST next;
	};

LIST stack;

void push(int val){
	LIST c = (LIST) malloc(sizeof(struct CELL));
	if (c) {
		c->val = val;
		c->next = stack;
		stack = c;
	}
	else {
	printf("error\n");
	exit (0);
	 }
}


int pop(){
	LIST c = stack;
	if (c) {
	stack = stack->next;
	int val = c->val;
	free (c);
	return val;
	}
	else {
	printf("stack is empty\n");
	exit (0);
	}
}

int main(){

	LIST newList;
	stack = NULL;
	char newInput[200];
	
	while ((*newInput != EOF) && (*newInput != "q")){
	
		scanf("%s", newInput);
		int a, d;
		if ((atoi(newInput)) != 0){
			push(atoi(newInput));
				}
		else {

			switch(*newInput){
				
				case 'p': 
					if (stack != NULL) printf("%d\n", stack->val);
					else printf("stack is empty");
					break;
				case 'f':
					newList=stack;
					while (newList != NULL){ printf("%d\n", newList->val);
					newList = newList->next;
					}
					break;
				case 'c':
					while (stack != NULL){ pop();}
					break;
				case 'q':
					exit (0);
				case '+':
					if (stack != NULL && stack->next){
						d = pop();
						a = pop();
						push(a+d);
							}
					else if (stack == NULL) {printf("empty stack\n");}
						else (printf("integers"));
						break;
				case '-':
                                        if (stack != NULL && stack->next){
                                                d = pop();
                                                a = pop();
                                                push(a-d);
                                                        }
                                        else if (stack == NULL) {printf("empty stack\n");}
                                                else (printf("integers"));
                                                break;
				
				case '*':
                                        if (stack != NULL && stack->next){
                                                d = pop();
                                                a = pop();
                                                push(a*d);
                                                        }
                                        else if (stack == NULL) {printf("empty stack\n");}
                                                else (printf("integers"));
                                                break;
				case '/':
                                        if (stack != NULL && stack->next){
                                                d = pop();
                                                a = pop();
                                                push(a/d);
                                                        }
                                        else if (stack == NULL) {printf("empty stack\n");}
                                                else (printf("integers"));
                                                break;
				}
			}
		}

	return(0);

}
