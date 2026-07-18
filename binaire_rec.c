#include<stdio.h>

void binaire_rec(int n){
    if (n>1){
        printf("On appelle le binaire_rec(%d) et le binaire_rec(%d) attend\n",n/2,n);
        binaire_rec(n/2);
    }

    printf("%d",n%2);


}


int main(){

    int n;
    printf("Entrez le nombre:");
    scanf("%d",&n);
    binaire_rec(n);

}
