//Dhruv Agnihotri
//Homework #3
//10-28-2017

#include <stdio.h>


#define types(x) (((x) >> 10) & 0x1f)
#define opc(x) (((x) >> 9) & 0x1)
#define rd(x) (((x) >> 0) & 0x7)
#define rn(x) (((x) >> 3) & 0x7)
#define rm(x) (((x) >> 6) & 0x7)
#define opcode(x) (((x) >> 6) & 0xf)



char *regnames[] = {"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15","lr","pc"};
char *opname[]   = {"ands","eors","lsls","lsrs","asrs","cmps","cmns","orrs","bics","mvns"};


void assembly(int i){

//addition and subtraction
  if(types(i) == 6) {
    if(opc(i) == 0) {
      printf("adds %s, %s, %s\n", regnames[rd(i)], regnames[rn(i)], regnames[rm(i)]);
    } else if (opc(i) == 1) {
      printf("subs %s, %s, %s\n", regnames[rd(i)], regnames[rn(i)], regnames[rm(i)]);
    }

    //data proccessing
  } else if (types(i) == 16){
    printf("%s %s, %s\n", opname[opcode(i)],regnames[rd(i)], regnames[rn(i)]);
  } else {
    printf(".hword 0x%x\n", i);
  }



}


int main(){
  int i;
  printf("HW3: Enter the test hexadecimal string to generate the legal Thumb-2 assembly code\n.text\n.syntax unified\n.thumb\n");
  while (scanf("%x", &i)==1){
    assembly(i);
  }

}
