
#include<stdio.h>

long long factorielle(int n) {

if (n== 0){
    printf("quand n est égale à 0 ;\n la factorielle de %lld return 1 \n",n);
    return 1;
}
else{
    printf("on calcule %lld*%lld\n",n,n-1);
    return n*factorielle(n-1);
}
}

int main (){
    int n=5;
    printf("\n Donc Le factorielle de %lld est %lld\n",n,factorielle(n));
    return 0 ;


}
