#include<stdio.h>

long long factorielle_iterative(int n){

    long long res=1;

    for (int i=2; i<= n;i++){
        printf ("On calcule %lld*%d\n",res,i);

        res *=i;
    }
    return res;
}

int main (){
 int n=5;
 printf("\n le factorielle de %lld est %lld", n,factorielle_iterative(n));

}
