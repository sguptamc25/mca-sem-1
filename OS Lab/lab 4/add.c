#include<stdio.h>

void add(int a ,int b){
    int sum ;
    sum = a + b ;
    printf("sum is %d", sum);
}

int main(){
 int a;
 printf("enter a number 1: ");
 scanf("%d", &a);
 int b;
 printf("enter a number 2: ");
 scanf("%d", &b);
 add(a,b);
 return 0;
}

