#include<stdio.h>

int tri_selection(int n , int tab){

    for(int i=0; i<n-1 ; i++){
        int valeur_min = tab[i];
        int indice_min = i;


        for(int j=i+1 ; j<n ; j++){
            if(tab[j]<tab[i]){
                valeur_min=tab[j];
                indice_min=j;


            }
        int temp= tab[i];
        tab[i]=tab[indice_min];
        tab[indice_min]=temp;
        }
    }


}

int main(){
int n;
scanf("%d", &n)

}
