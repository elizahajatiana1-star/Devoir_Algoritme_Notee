#include<stdio.h>

int nb_chiffre_iter(int n){

int c = 0 ;

if (n == 0 ) return 1 ;

while (n>0){
    c++;
    n/=10;
}
return c;
}

int main() {

int n=7965 ;
printf("la nombre de chiffre de %d est %d ",n,nb_chiffre_iter(n));
}
