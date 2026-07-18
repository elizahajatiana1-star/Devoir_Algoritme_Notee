#include<stdio.h>

int arrangement(int n , int p){

    if(p==0){
        printf(" == arrangement(%d,%d) est egale a  1 \n Donc ", n,p);
        return 1;
    }else{
    printf("On calcule %d*arrangement(%d,%d)\n",n,n-1,p-1);

    return n*arrangement(n-1,p-1);
}
}


int main(){
    int n=5;
    int p=2;

    printf(" l'arrangement(%d,%d) est :%d\n",n,p,arrangement(n,p));
    return 0;




}
