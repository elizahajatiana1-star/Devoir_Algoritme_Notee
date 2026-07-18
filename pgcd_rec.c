#include<stdio.h>


int pgcd(int a,int b){

    if(b==0){
        printf("Si b=0 , a est la pgcd de a et b\n");
        return a;
    }else{
        printf("On calcule pgcd(%d,%d)\n",b,a%b);

        return pgcd(b,a%b);
}

}

int main(){

    int a = 48, b=18;

    printf("le PGCD est  egale a : %d\n",pgcd(a,b));

    return 0;

}
