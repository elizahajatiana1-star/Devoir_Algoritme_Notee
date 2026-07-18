#include<stdio.h>
#include<math.h>


void move(char from , char to){

    printf("deplacer de %c vers %c\n",from , to);

}

void hanoi_iter(char A, char C, char B, int n){

    if(n%2 == 1)
        move(A,C);
    else
        move(A,B);
}


int main(){

    int n = 3 ;
    int total_moves = pow(2,n)-1;
    char A='A' , B='B' , C ='C';

    for (int i = 1; i<= total_moves;i++){
        if (i%3 == 1)
            move(A,C);
        else if (i%3==2)
            move(A,B);
        else
            move(B,C);
    }
    return 0;
}
