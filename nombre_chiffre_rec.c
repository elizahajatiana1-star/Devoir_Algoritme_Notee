#include<stdio.h>

int nb_chiffre_rec(int n){

    if (n==0)
        return 0;

    return 1 + nb_chiffre_rec(n/10);

}

int main() {

int n=796 ;
printf("la nombre de chiffre de %d est %d ",n,nb_chiffre_rec(n));
}
