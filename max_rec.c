#include<stdio.h>

int max_rec(int t[], int n){

if (n==1){
    return t[0];
}else{
    int m = max_rec(t,n-1);

    return (t[n-1]>m)? t[n-1]:m;


}

}

int main (){

    int t[]={4,5,8,1,6};

    printf("le nombre maximale dans le tableau est %d", max_rec(t,5));

    return 0;


}


