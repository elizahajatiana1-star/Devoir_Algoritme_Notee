#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int nbJoueurs;
    int score1 = 0, score2 = 0, score3 = 0, score4 = 0;
    int cent1 = 0, cent2 = 0, cent3 = 0, cent4 = 0;
    int joueur = 1;
    int de;

    do {
        printf("Nombre de joueurs (2 à 4) : ");
        scanf("%d", &nbJoueurs);
    } while (nbJoueurs < 2 || nbJoueurs > 4);

    srand(time(NULL));

    while (1) {

        printf("\nTour du Joueur %d\n", joueur);
        printf("Appuyez sur Entrée pour lancer le dé...");
        getchar();
        getchar();

        de = rand() % 6 + 1;
        printf("Dé obtenu : %d\n", de);

        if (joueur == 1) {
            if (score1 + de <= 100)
                score1 += de;

            printf("Score Joueur 1 : %d\n", score1);

            if (score1 == 100) {
                cent1++;
                score1 = 0;

                if (cent1 == 4) {
                    printf("\nJoueur 1 a atteint 100 points 4 fois et gagne la partie !\n");
                    break;
                }
            }
        }

        else if (joueur == 2) {
            if (score2 + de <= 100)
                score2 += de;

            printf("Score Joueur 2 : %d\n", score2);

            if (score2 == 100) {
                cent2++;
                score2 = 0;

                if (cent2 == 4) {
                    printf("\nJoueur 2 a atteint 100 points 4 fois et gagne la partie !\n");
                    break;
                }
            }
        }

        else if (joueur == 3) {
            if (score3 + de <= 100)
                score3 += de;

            printf("Score Joueur 3 : %d\n", score3);

            if (score3 == 100) {
                cent3++;
                score3 = 0;

                if (cent3 == 4) {
                    printf("\nJoueur 3 a atteint 100 points 4 fois et gagne la partie !\n");
                    break;
                }
            }
        }

        else if (joueur == 4) {
            if (score4 + de <= 100)
                score4 += de;

            printf("Score Joueur 4 : %d\n", score4);

            if (score4 == 100) {
                cent4++;
                score4 = 0;

                if (cent4 == 4) {
                    printf("\nJoueur 4 a atteint 100 points 4 fois et gagne la partie !\n");
                    break;
                }
            }
        }

        printf("\nScores :\n");
        printf("J1=%d (%d fois)\n", score1, cent1);
        printf("J2=%d (%d fois)\n", score2, cent2);

        if (nbJoueurs >= 3)
            printf("J3=%d (%d fois)\n", score3, cent3);

        if (nbJoueurs == 4)
            printf("J4=%d (%d fois)\n", score4, cent4);

        joueur++;

        if (joueur > nbJoueurs)
            joueur = 1;
    }

    return 0;
}
