#include<stdio.h>

int somme_rec(int t[], int n){

    if(n==0){
        printf("Or somme_rec(t,%d) devient 0 \n",n);
        return 0;
    }
    printf("On appelle somme_rec(t,%d) et on attend somme_rec(t,%d)\n",n-1,n);
    return t[n-1]+somme_rec(t,n-1);
}
int main() {
    int t[5]={8,5,6,32};


    printf("DONC la somme des nombres dans le tableau est %d",somme_rec(t,5));
    return 0;


}
