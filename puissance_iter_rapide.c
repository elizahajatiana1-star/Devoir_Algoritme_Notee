#include<stdio.h>

long long puissance_rapide(long long a , int n){
    long long result =1;

    while (n != 0){
        if (n%2 == 0){
            printf(" n est paire donc :\n");

            printf("On calule le double de la valeur de a=%lld*%lld\n" , a,a);
            a=a*a;
            printf("Donne %lld:\n",a);

            printf("On decrimente n en %lld/2 \n ",n);
            n=n/2;
            printf(" n devient:%lld\n",n);
        }
        else{
            printf("n impaire donc: \n On calcule resultat = %lld*%lld :\n",result , a);
            result = result *a;
            printf("le resultat devient: %lld\n",result);

            printf("On decrimente n en %lld/2 \n ",n);
            n =n-1 ;
            printf(" n devient:%lld\n",n);
        }
    }
    printf("le resultat final est:");
    return result;
}

int main () {
    printf("%lld\n",puissance_rapide(2,10));
    return 0 ;
}


