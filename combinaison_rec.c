#include<stdio.h>

int comb(int n , int k){

    if(k == 0 || k == n){
        printf("On return 1\n");
        return 1;
    }else{

    printf("On calcule comb(%d,%d) + comb(%d,%d)\n",n-1,k-1,n-1,k);
    return comb(n -1 , k-1)+comb(n-1,k);
}

}

int main (){

    printf(" la combinaison est egale a :%d\n",comb(5,3));
    return 0;


}
