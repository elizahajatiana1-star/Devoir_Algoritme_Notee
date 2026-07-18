#include<stdio.h>

int comb(int n , int k){
    int count = 0;

    if(k == 0 || k == n){
        count ++ ;
        printf("On a %d combinaison \n",count);

        return 1;
    }else{

    printf("On calcule comb(%d,%d) + comb(%d,%d)\n",n-1,k-1,n-1,k);
    return comb(n -1 , k-1)+comb(n-1,k);
}

}

int main (){

    printf(" la combinaison est egale a :%d\n",comb(5,2));
    return 0;


}

