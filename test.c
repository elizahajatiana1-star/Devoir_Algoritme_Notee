#include<stdio.h>

long long somme_nombre(int n){

    long long res = 0;

    for (int i=0;i<=n;i+=2){
        printf("on calcule %lld+%lld\n",res,i);
        res+=i;
    }
    return res ;
}

int main(){
    int n=9;
    printf("La somme du nombre %d est %lld",n ,somme_nombre(n));
    return 0;
}
