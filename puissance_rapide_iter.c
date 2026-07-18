
#include<stdio.h>

long long puissance_rapide_iterative(long long a,int n) {

    long long resultat = 1;

    while(n>0){
        if(n%2 == 1){
            printf(" n impaire donc :\n");
            printf(" on calcule resultat=%lld*%lld\n",resultat,a);
            resultat *= a;
            printf(" a devient:%lld\n",a);
        }
        printf(" n paire donc :\n");
        printf(" on calcule a par lui meme: %lld*%lld\n",a,a);
        a*=a;
        printf(" a devient %lld :\n",a);

        printf(" On decrement n en %lld/2:\n",n);
        n/=2;
        printf(" n devient %lld:\n",n);
    }
    printf(" le resultat final est :" );
    return resultat;

}

int main (){
    printf("%lld\n", puissance_rapide_iterative(2,10));
    return 0;

}
