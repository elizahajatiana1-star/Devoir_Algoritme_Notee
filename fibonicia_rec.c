#include<stdio.h>

int fib_rec(int n){
    printf("On appel fib_rec(%d) et fib_rec(%d) attend \n",n-2,n-1);
    if(n==0){
        printf(" la fib_rec(%d) est 0\n",n);
        return 0;
    }
    else if(n==1){
         printf(" la fib_rec(%d) est 1\n",n);
        return 1
    }
    else{

        return fib_rec(n-1)+fib_rec(n-2);
}
}

int main(){

    printf(" la valeur de la fibonincia est :%d\n",fib_rec(10));
    return 0;

}
