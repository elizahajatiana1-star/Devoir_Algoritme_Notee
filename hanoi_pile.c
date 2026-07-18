#include<stdio.h>
#define MAX 1025


int stack_n[MAX];

char stack_A[MAX], stack_B[MAX],stack_C[MAX];

int top = -1;

void push(int n ,char A, char B , char C){

    stack_n[++top]=n;
    stack_A[top]=A;
    stack_B[top]=B;
    stack_C[top]=C;
}

int empty(){

    return top == -1;
}

void hanoi_pile(int n ,char A, char B , char C){

    push(n,A,B,C);

    while(!empty()){

        int n =stack_n[++top]=n;
        char A = stack_A[top]=A;
        char B = stack_B[top]=B;
        char C = stack_C[top]=C;

        top--;

        if(n==1){
            printf("Deplacer de %c vers %c \n",A,C);
        }else{
            push(n-1,B,A,C);
            push(1,A,B,C);
            push(n-1,A,C,B);
        }
    }

}

int main (){

    hanoi_pile(3,'A','B','C');
    return 0;



}
