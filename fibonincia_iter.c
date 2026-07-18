#include<stdio.h>

int fib_iter(int n){

    int i;

    if(n == 0){
        printf("la fib_iter(%d) est 0\n",i);
        return 0;
    }
    if(n == 1){
        printf("la fib_iter(%d) est 0\n",i);
        return 1;
    }

    int a=0;
    int b =1 ;
    int c;

    for (int i=2 ; i<= n ; i++){
        printf("On appel fib_rec(%d) et fib_rec(%d) attend \n",i-1,i);
        c=a+b;
        a=b;
        b=c;
    }

    return b;
}

int main(){

    printf(" la valeur de fibonincia est %d\n",fib_iter(10));
    return 0;

}
