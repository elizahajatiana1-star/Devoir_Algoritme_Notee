#include<stdio.h>

void binaire_iter(int n) {

    int bits[32];
    int i =0 ;

    if(n == 0){
        printf("0");
        return;
    }

    while(n>0){
        bits[i++] = n%2;
        n/=2;
    }

    for (int j=i-1 ; j>=0;j--)
        printf("%d",bits[j]);
}

int main(){
    int n;
    printf("Entrez le nombre:");
    scanf("%d",&n);
    printf ("la forme binaire de %d est :",n);
    binaire_iter(n);

}
