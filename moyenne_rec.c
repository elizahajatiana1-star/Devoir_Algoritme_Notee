#include<stdio.h>

double somme(double tab[] , int n){

    if(n==0)
        return 0.0;

    return tab[n-1] + somme(tab,n-1);

}

double moyenne_rec(double tab[],int n){

    return somme(tab , n)/n;

}

int main(){

    double tab[]={2.5,4.0,6.5,8.0};
    int n=4;
    printf("%f\n", moyenne_rec(tab ,n ));

    return 0;

}
