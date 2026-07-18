
#include<stdio.h>

long long puissance_lineaire_iterative(long long a , int n){

    long long resultat = 1;
    int i ;

    for (i==0; i<n; i++){
        resultat = resultat*a ;
    }
    return resultat ;

}

int main(){

printf("%lld \n ", puissance_lineaire_iterative(2,10));
return 0 ;
}
