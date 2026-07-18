#include<stdio.h>

int comb_rec(int n ,int k,int i,int res){

    if(i>k){
        printf("Si i=%d est superieur a k=%d\n  on prend la valeur de res = %d\n",i,k,res);

        return res;
    }else{
        printf("Puis on appel comb_rec(%d,%d,%d,%d)\n",n,k,i+1,res*(n-k+i)/i);
        return comb_rec(n,k,i+1,res*(n-k+i)/i);
}

}

int comb(int n ,int k) {

    if(k>n-k){
        printf("si %d superieur a (%d-%d) \n On calcule %d\n",k,n,k,n-k);
        k=n-k;
        printf("donc k devient %d",n-k);

    }else{
        printf("On appel comb_rec(%d,%d,1,1)\n",n,k);
        return comb_rec(n,k,1,1);
}

}

int main (){

    printf("la combinaison est egale a :%d\n",comb(5,2));
    return 0;

}
