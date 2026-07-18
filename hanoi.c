#include<stdio.h>

void hanoi(int n , char A, char B , char C){

    if(n==1){

        printf("Deplacer disque 1 de %c vers %c \n" , A,C);
        return;
    }

    hanoi(n-1,A,C,B);
    printf("Deplacer disque %d de %c vers %c \n", n,A,C);

    hanoi(n-1,B,A,C);

}

int main(){

    hanoi(3,'A','B','C');
    return 0;


}
