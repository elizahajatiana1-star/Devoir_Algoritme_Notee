#include<stdio.h>

void afficher(int tab[], int n){
    for (int i=0 ; i<n;i++){
        printf(" %d",tab[i]);
    }
    printf("\n");

}

void permuter_element_tableau(int tab[], int indice1 , int indice2) {

    int temp = tab[indice1];

    tab[indice1] = tab[indice2];

    tab[indice1]=temp;
}


void lister_permutation(int tab[], int debut , int etat) {

    if(debut == etat){
        afficher(tab,etat);
        return;
    }
    for(int i=debut;i<etat;i++){
        permuter_element_tableau(tab,debut,i);
        lister_permutation(tab , debut+1 , etat);
        permuter_element_tableau(tab,debut,i);
    }

}

int main(){
    int tab[]={1,2,3};
    int n=sizeof(tab)/sizeof(tab[0]);
    printf("l' etat est egale a %d\n",n);
    printf(" les Permutation sont :\n");
    lister_permutation(tab,0,n);
    return 0;
}
