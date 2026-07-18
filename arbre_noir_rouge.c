#include <stdio.h>
#include <stdlib.h>

// ============================================================================
// 1. DÉFINITION DES STRUCTURES ET ENUMS
// ============================================================================

// Énumération pour gérer proprement les deux couleurs de l'arbre
typedef enum { ROUGE, NOIR } Couleur;

// Structure d'un nœud de l'arbre Rouge-Noir
typedef struct Noeud {
    int valeur;             // La donnée stockée (ici un entier)
    Couleur couleur;        // ROUGE ou NOIR
    struct Noeud* gauche;   // Pointeur vers le sous-arbre gauche
    struct Noeud* droite;   // Pointeur vers le sous-arbre droit
    struct Noeud* parent;   // Pointeur vers le père (crucial pour les rotations)
} Noeud;

// Structure de contrôle de l'arbre
typedef struct {
    Noeud* racine;          // Point d'entrée de l'arbre
} ArbreRN;

// La Sentinelle NIL : nœud factice noir représentant toutes les feuilles vides
// Déclaré en global pour être accessible par toutes les fonctions
Noeud* NIL;

// ============================================================================
// 2. PROTOTYPES DES FONCTIONS
// ============================================================================
void initNIL();
void initArbre(ArbreRN* arbre);
Noeud* creerNoeud(int valeur);

// Fonctions de parcours (Exigence du sujet)
void parcoursInfixe(Noeud* n);
void parcoursPrefixe(Noeud* n);
void parcoursPostfixe(Noeud* n);
void afficherArbre2D(Noeud* racine, int espace);

// Fonctions de restructuration (Rotations)
void rotationGauche(ArbreRN* arbre, Noeud* x);
void rotationDroite(ArbreRN* arbre, Noeud* x);

// Fonctions d'insertion
void corrigerInsertion(ArbreRN* arbre, Noeud* n);
void insert(ArbreRN* arbre, int valeur);

// Fonctions de suppression
Noeud* minimum(Noeud* n);
void translaterArbre(ArbreRN* arbre, Noeud* u, Noeud* v);
void corrigerSuppression(ArbreRN* arbre, Noeud* x);
void supprimer(ArbreRN* arbre, int valeur);

// Fonction de recherche
Noeud* rechercher(ArbreRN* arbre, int valeur);

// Fonctions de nettoyage (Amélioration pour éviter les fuites de mémoire)
void libererNoeuds(Noeud* n);
void libererArbre(ArbreRN* arbre);

// ============================================================================
// 3. INITIALISATION ET FONCTIONS DE PARCOURS
// ============================================================================

// Alloue et configure le nœud sentinelle NIL global
void initNIL() {
    NIL = malloc(sizeof(Noeud));
    NIL->couleur = NOIR;
    NIL->droite = NULL;
    NIL->gauche = NULL;
    NIL->parent = NULL;
}

// Initialise un arbre vide en faisant pointer sa racine vers NIL
void initArbre(ArbreRN* arbre) {
    arbre->racine = NIL;
}

// Crée un nouveau nœud rouge (propriété de départ lors d'une insertion)
Noeud* creerNoeud(int valeur) {
    Noeud* n = malloc(sizeof(Noeud));
    n->valeur = valeur;
    n->couleur = ROUGE;
    n->gauche = NIL;
    n->droite = NIL;
    n->parent = NIL;
    return n;
}

// Parcours Infixe : Gauche -> Racine -> Droite (Affiche les éléments triés)
void parcoursInfixe(Noeud* n) {
    if (n == NIL) return;
    parcoursInfixe(n->gauche);
    printf("%d(%s) ", n->valeur, n->couleur == ROUGE ? "R" : "N");
    parcoursInfixe(n->droite);
}

// Parcours Préfixe / Suffixe : Racine -> Gauche -> Droite
void parcoursPrefixe(Noeud* n) {
    if (n == NIL) return;
    printf("%d(%s) ", n->valeur, n->couleur == ROUGE ? "R" : "N");
    parcoursPrefixe(n->gauche);
    parcoursPrefixe(n->droite);
}

// Parcours Post-fixe : Gauche -> Droite -> Racine
void parcoursPostfixe(Noeud* n) {
    if (n == NIL) return;
    parcoursPostfixe(n->gauche);
    parcoursPostfixe(n->droite);
    printf("%d(%s) ", n->valeur, n->couleur == ROUGE ? "R" : "N");
}

// Affichage visuel textuel de l'arbre en 2D (vue de profil inversée)
void afficherArbre2D(Noeud* racine, int espace) {
    if (racine == NIL) return;
    espace += 7;
    afficherArbre2D(racine->droite, espace);
    printf("\n");
    for (int i = 7; i < espace; i++) printf(" ");
    printf("%d(%s)\n", racine->valeur, racine->couleur == ROUGE ? "R" : "N");
    afficherArbre2D(racine->gauche, espace);
}

// ============================================================================
// 4. LOGIQUE DES ROTATIONS MECHANISQUES
// ============================================================================

// Pivote le sous-arbre vers la gauche autour du nœud x
void rotationGauche(ArbreRN* arbre, Noeud* x) {
    Noeud* y = x->droite;
    x->droite = y->gauche;

    if (y->gauche != NIL) y->gauche->parent = x;
    y->parent = x->parent;

    if (x->parent == NIL) arbre->racine = y;
    else if (x == x->parent->gauche) x->parent->gauche = y;
    else x->parent->droite = y;
    y->gauche = x;
    x->parent = y;
}

// Pivote le sous-arbre vers la droite autour du nœud x
void rotationDroite(ArbreRN* arbre, Noeud* x) {
    Noeud* y = x->gauche;
    x->gauche = y->droite;

    if (y->droite != NIL) y->droite->parent = x;
    y->parent = x->parent;

    if (x->parent == NIL) arbre->racine = y;
    else if (x == x->parent->droite) x->parent->droite = y;
    else x->parent->gauche = y;
    y->droite = x;
    x->parent = y;
}

// ============================================================================
// 5. PROCESSUS D'INSERTION
// ============================================================================

// Rétablit les règles bicolores après l'ajout d'un nœud rouge
void corrigerInsertion(ArbreRN* arbre, Noeud* n) {
    while (n->parent->couleur == ROUGE) {
        Noeud* grandParent = n->parent->parent;

        if (n->parent == grandParent->gauche) {
            Noeud* oncle = grandParent->droite;

            // Cas 1 : L'oncle est ROUGE -> Recoloriage simple
            if (oncle->couleur == ROUGE) {
                n->parent->couleur = NOIR;
                oncle->couleur = NOIR;
                grandParent->couleur = ROUGE;
                n = grandParent;
            } else {
                // Cas 2 : L'oncle est NOIR et n est fils droit (Triangle)
                if (n == n->parent->droite) {
                    n = n->parent;
                    rotationGauche(arbre, n);
                }
                // Cas 3 : L'oncle est NOIR et n est fils gauche (Ligne droite)
                n->parent->couleur = NOIR;
                grandParent->couleur = ROUGE;
                rotationDroite(arbre, grandParent);
            }
        } else { // Cas symétrique : le parent est le fils droit
            Noeud* oncle = grandParent->gauche;

            // Cas 1 symétrique : L'oncle est ROUGE
            if (oncle->couleur == ROUGE) {
                n->parent->couleur = NOIR;
                oncle->couleur = NOIR;
                grandParent->couleur = ROUGE;
                n = grandParent;
            } else {
                // Cas 2 symétrique : L'oncle est NOIR et n est fils gauche
                if (n == n->parent->gauche) {
                    n = n->parent;
                    rotationDroite(arbre, n);
                }
                // Cas 3 symétrique : L'oncle est NOIR et n est fils droit
                n->parent->couleur = NOIR;
                grandParent->couleur = ROUGE;
                rotationGauche(arbre, grandParent);
            }
        }
    }
    arbre->racine->couleur = NOIR; // La racine doit impérativement rester noire
}

// Insertion standard BST suivie de la correction des propriétés
void insert(ArbreRN* arbre, int valeur) {
    Noeud* nouveau = creerNoeud(valeur);
    Noeud* parcours = arbre->racine;
    Noeud* parentTrouve = NIL;

    // Phase 1 : Recherche de la position d'accueil du nœud
    while (parcours != NIL) {
        parentTrouve = parcours;
        if (nouveau->valeur < parcours->valeur)
            parcours = parcours->gauche;
        else
            parcours = parcours->droite;
    }

    nouveau->parent = parentTrouve;

    if (parentTrouve == NIL) {
        arbre->racine = nouveau;
    } else if (nouveau->valeur < parentTrouve->valeur) {
        parentTrouve->gauche = nouveau;
    } else {
        parentTrouve->droite = nouveau;
    }

    // Si c'est le premier nœud, il devient racine noire et on quitte
    if (arbre->racine == nouveau) {
        nouveau->couleur = NOIR;
        return;
    }

    // Phase 2 : Rééquilibrage
    corrigerInsertion(arbre, nouveau);
}

// ============================================================================
// 6. PROCESSUS DE SUPPRESSION
// ============================================================================

// Trouve le plus petit nœud d'un sous-arbre (utile pour le successeur)
Noeud* minimum(Noeud* n) {
    while (n->gauche != NIL) n = n->gauche;
    return n;
}

// Remplace le sous-arbre u par le sous-arbre v (gestion des liens de parenté)
void translaterArbre(ArbreRN* arbre, Noeud* u, Noeud* v) {
    if (u->parent == NIL) arbre->racine = v;
    else if (u == u->parent->gauche) u->parent->gauche = v;
    else u->parent->droite = v;
    v->parent = u->parent;
}

// Corrige le problème du "Double Noir" provoqué par la perte d'un nœud noir
void corrigerSuppression(ArbreRN* arbre, Noeud* x) {
    while (x != arbre->racine && x->couleur == NOIR) {
        if (x == x->parent->gauche) { // x est fils gauche
            Noeud* frere = x->parent->droite;

            // Cas 1 : Le frère est ROUGE
            if (frere->couleur == ROUGE) {
                frere->couleur = NOIR;
                x->parent->couleur = ROUGE;
                rotationGauche(arbre, x->parent);
                frere = x->parent->droite;
            }

            // Cas 2 : Le frère est NOIR et ses deux enfants sont NOIRS
            if (frere->gauche->couleur == NOIR && frere->droite->couleur == NOIR) {
                frere->couleur = ROUGE;
                x = x->parent; // Le double noir remonte d'un étage
            } else {
                // Cas 3 : Le frère est NOIR, son enfant droit est NOIR (Triangle)
                if (frere->droite->couleur == NOIR) {
                    frere->gauche->couleur = NOIR;
                    frere->couleur = ROUGE;
                    rotationDroite(arbre, frere);
                    frere = x->parent->droite;
                }
                // Cas 4 : Le frère est NOIR, son enfant droit est ROUGE (Ligne droite)
                frere->couleur = x->parent->couleur;
                x->parent->couleur = NOIR;
                frere->droite->couleur = NOIR;
                rotationGauche(arbre, x->parent);
                x = arbre->racine; // Fin de boucle forcée
            }
        } else { // Cas symétrique : x est fils droit
            Noeud* frere = x->parent->gauche;

            // Cas 1 symétrique
            if (frere->couleur == ROUGE) {
                frere->couleur = NOIR;
                x->parent->couleur = ROUGE;
                rotationDroite(arbre, x->parent);
                frere = x->parent->gauche;
            }

            // Cas 2 symétrique
            if (frere->droite->couleur == NOIR && frere->gauche->couleur == NOIR) {
                frere->couleur = ROUGE;
                x = x->parent;
            } else {
                // Cas 3 symétrique
                if (frere->gauche->couleur == NOIR) {
                    frere->droite->couleur = NOIR;
                    frere->couleur = ROUGE;
                    rotationGauche(arbre, frere);
                    frere = x->parent->gauche;
                }
                // Cas 4 symétrique
                frere->couleur = x->parent->couleur;
                x->parent->couleur = NOIR;
                frere->gauche->couleur = NOIR;
                rotationDroite(arbre, x->parent);
                x = arbre->racine;
            }
        }
    }
    x->couleur = NOIR;
}

// Fonction maîtresse de suppression
void supprimer(ArbreRN* arbre, int valeur) {
    Noeud* z = rechercher(arbre, valeur);
    if (z == NIL) {
        printf("\n[Erreur] Valeur %d absente de l'arbre.\n", valeur);
        return;
    }

    Noeud* x;
    Noeud* y = z;
    Couleur couleur_origine_y = y->couleur;

    // Cas d'élimination physique (0 ou 1 enfant)
    if (z->gauche == NIL) {
        x = z->droite;
        translaterArbre(arbre, z, z->droite);
    } else if (z->droite == NIL) {
        x = z->gauche;
        translaterArbre(arbre, z, z->gauche);
    } else {
        // Cas complexe : 2 enfants (on extrait le successeur)
        y = minimum(z->droite);
        couleur_origine_y = y->couleur;
        x = y->droite;

        if (y->parent == z) {
            x->parent = y;
        } else {
            translaterArbre(arbre, y, y->droite);
            y->droite = z->droite;
            y->droite->parent = y;
        }

        translaterArbre(arbre, z, y);
        y->gauche = z->gauche;
        y->gauche->parent = y;
        y->couleur = z->couleur;
    }

    free(z); // Destruction définitive du conteneur en mémoire

    // Si le nœud retiré du système était noir, équilibre rompu -> on lance le correcteur
    if (couleur_origine_y == NOIR) {
        corrigerSuppression(arbre, x);
    }
    printf("[Succes] Valeur %d supprimee.\n", valeur);
}

// ============================================================================
// 7. FONCTION DE RECHERCHE BINAIRE
// ============================================================================
Noeud* rechercher(ArbreRN* arbre, int valeur) {
    Noeud* n = arbre->racine;
    while (n != NIL && valeur != n->valeur) {
        if (valeur < n->valeur) n = n->gauche;
        else n = n->droite;
    }
    return n;
}

// ============================================================================
// 8. FONCTIONS DE NETTOYAGE MÉMOIRE (INDISPENSABLE EN LOGIQUE AVANCÉE)
// ============================================================================

// Libère récursivement tous les nœuds de l'arbre en post-fixe
void libererNoeuds(Noeud* n) {
    if (n == NIL) return;
    libererNoeuds(n->gauche);
    libererNoeuds(n->droite);
    free(n);
}

// Nettoie l'arbre complet et réinitialise la racine
void libererArbre(ArbreRN* arbre) {
    libererNoeuds(arbre->racine);
    arbre->racine = NIL;
}

// ============================================================================
// 9. INTERFACE UTILISATEUR (MAIN COIN DE DÉMONSTRATION)
// ============================================================================
int main() {
    // 1. Initialisation obligatoire du framework de l'arbre
    initNIL();
    ArbreRN arbre;
    initArbre(&arbre);

    int choix, valeur;
    Noeud* recherche;

    // Injection automatique d'un jeu de données de test de départ

    for (int i = 0; i < 6; i++) {
        insert(&arbre, valeurs_defaut[i]);
    }

    // Boucle d'exécution de l'application interactive
    do {
        printf("\n=================================");
        printf("\n    MENU ARBRE ROUGE ET NOIR     ");
        printf("\n=================================");
        printf("\n 1. Inserer une nouvelle valeur");
        printf("\n 2. Supprimer une valeur existante");
        printf("\n 3. Rechercher une valeur");
        printf("\n 4. Afficher la structure 2D (Profil)");
        printf("\n 5. Executer les 3 Parcours (Sujet)");
        printf("\n 6. Quitter et Nettoyer la memoire");
        printf("\n=================================");
        printf("\nVotre choix : ");

        // Protection contre la saisie accidentelle de caractères/lettres
        if (scanf("%d", &choix) != 1) {
            printf("\n[Erreur] Veuillez entrer un entier numérique.\n");
            while (getchar() != '\n'); // Purge du tampon de saisie
            choix = 0;
            continue;
        }

        switch (choix) {
            case 1:
                printf("Entrez la valeur entiere a inserer : ");
                scanf("%d", &valeur);
                insert(&arbre, valeur);
                printf("[Succes] Valeur %d inseree.\n", valeur);
                break;

            case 2:
                printf("Entrez la valeur entiere a supprimer : ");
                scanf("%d", &valeur);
                supprimer(&arbre, valeur);
                break;

            case 3:
                printf("Entrez la valeur a rechercher : ");
                scanf("%d", &valeur);
                recherche = rechercher(&arbre, valeur);
                if (recherche != NIL) {
                    printf("[Trouve] Le noeud %d existe. Couleur : %s.\n",
                           recherche->valeur,
                           recherche->couleur == ROUGE ? "ROUGE" : "NOIRE");
                } else {
                    printf("[Absent] La valeur %d n'appartient pas a l'arbre.\n", valeur);
                }
                break;

            case 4:
                printf("\n--- Visualisation Structurale de l'Arbre (Racine a gauche) ---\n");
                if (arbre.racine == NIL) {
                    printf("L'arbre ne contient aucun element.\n");
                } else {
                    afficherArbre2D(arbre.racine, 0);
                }
                break;

            case 5:
                printf("\n=======================================================");
                printf("\n        DEMONSTRATION DES COMPORTEMENTS DE PARCOURS   ");
                printf("\n=======================================================");
                if (arbre.racine == NIL) {
                    printf("\nL'arbre est vide, parcours impossibles.\n");
                } else {
                    printf("\n1. Parcours Infixe (Tri croissant ordonne) :\n   ");
                    parcoursInfixe(arbre.racine);

                    printf("\n\n2. Parcours Suffixe / Prefixe (Racine d'abord) :\n   ");
                    parcoursPrefixe(arbre.racine);

                    printf("\n\n3. Parcours Post-fixe (Enfants d'abord) :\n   ");
                    parcoursPostfixe(arbre.racine);
                    printf("\n=======================================================\n");
                }
                break;

            case 6:
                printf("\nExecution du protocole de nettoyage de la memoire...\n");
                libererArbre(&arbre); // Vide proprement l'arbre
                free(NIL);            // Désalloue la sentinelle globale
                printf("Liberation terminee. Fermeture du programme. Au revoir !\n");
                break;

            default:
                printf("\n[Option non répertoriée] Saisissez un entier entre 1 et 6.\n");
                break;
        }
    } while (choix != 6);

    return 0;
}
