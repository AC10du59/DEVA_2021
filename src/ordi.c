#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordi.h"
#include "multi.h"
#include "arbre.h"

int nbalea(int borneD, int limite){
    return rand() % (limite+1) + borneD;
}

void prochainTourTirOrdi(Joueur *j){
    int choix = -1;
    while(choix<0 || choix>9){
        clear();
        printf("ORDI\n", j->id);
        printf("Voici la grille de tirs de l'ordi : \n\n");
        affiche_grille(j->tir);
        printf("\n");

        int cases = 17 - nbBateauEnVie(j);
        
        if(cases == 0 || cases == 1){
            printf("Il reste %d case à couler pour remporter la partie.\n", cases);
        } else {
            printf("Il reste %d cases à couler pour remporter la partie.\n", cases);
        }
       
        printf("\nAppuyer sur une touche numérique et entrée pour continuer : ");
        scanf("%d", &choix);
    }  
    clear();
}

void placerBateauOrdi(Joueur *j){
    int currentBateau;
    for(currentBateau = 0; currentBateau < 5; currentBateau++){
        Navire *n = j->bateaux[currentBateau];
        int choix_X = -1;
        int choix_Y = -1;
        int direction = -1;
        do{
            choix_X = nbalea(0,9);
            choix_Y = nbalea(0,9);
            direction = nbalea(1,4);
        } while(est_valide(choix_X, choix_Y, direction, n->taille, j->plateau)==0);
    
        j->bateaux[currentBateau]->x = choix_X; 
        j->bateaux[currentBateau]->y = choix_Y; 
        j->bateaux[currentBateau]->sens = direction; 

        int i;
        for(i = 0; i < n->taille; i++){
            if(direction==1){
                /*haut*/
                j->plateau[choix_X-i][choix_Y] = 1;
            }
            else if(direction==2){
                /*droite*/
                j->plateau[choix_X][choix_Y+i] = 1;
            }
            else if(direction==3){
                /*bas*/
                j->plateau[choix_X+i][choix_Y] = 1;
            }
            else if(direction==4){
                /*gauche*/
                j->plateau[choix_X][choix_Y-i] = 1;
            }
        }
    }
}

void jouerOrdi(Joueur *j1, Joueur *j2){
    int choix_X = -1;
    int choix_Y = -1;
    do{
        choix_X = nbalea(0,9);
        choix_Y = nbalea(0,9);
    } while(choix_X<0 || choix_X>9 || choix_Y<0 || choix_Y>9 || j1->tir[choix_X][choix_Y] != 0);

    int caseNB = choix_X * 10 + choix_Y;
    j1->bt = insert(j1->bt, caseNB);

    if(touche(choix_X, choix_Y, j2)==0) j1->tir[choix_X][choix_Y] = 1;
    else j1->tir[choix_X][choix_Y] = 2;
}

void jouerPartieOrdi(){
    clear();
    Joueur *j1 = creerJoueur(1);
    placer_bateau(j1);
    Joueur *ordi = creerJoueur(2);
    placerBateauOrdi(ordi);
    
    int joueur = 0; 

    while(partieTerminee(j1, ordi)==0){
       if(joueur%2==0){
            jouer(j1,ordi);
            prochainTourTir(j1);
        } else {
            jouerOrdi(ordi,j1);
            prochainTourTirOrdi(ordi);
        }
        joueur++;
    }
    int gagnant = partieTerminee(j1, ordi);

    clear();

    if(gagnant==1){
        printf("Félicitation au Joueur 1 qui a remporté la partie !!!\n\n");
        affiche_grille(j1->tir);
    } else{
        printf("Félicitation à l'ordi qui a remporté la partie !!!\n\n");
        affiche_grille(ordi->tir);
    }

    int choix;
    printf("\nAppuyer sur une touche numérique pour voir l'historique des tirs de la partie : ");
    scanf("%d", &choix);

    clear();

    printf("%d cases coulés par le joueur 1 :\n", lenBT(j1->bt));
    printBT(j1->bt);
    printf("\n");

    int choix2 = 0;
    int choix_X1 = -1;
    int choix_Y1 = -1;
    do{
        printf("\n");
        printf("Chercher une case (taper 1) ou passer aux tirs de l'ordi (taper 2) : ");
        scanf("%d", &choix2);
        if(choix2 == 1){
            do {            
                printf("-   Ligne : ");
                scanf("%d", &choix_X1);
                printf("- Colonne : ");
                scanf("%d", &choix_Y1);
            } while(choix_X1<0 || choix_X1>9 || choix_Y1<0 || choix_Y1>9);

            int caseTest = choix_X1 * 10 + choix_Y1;

            if(search(j1->bt, caseTest) == NULL) {
                printf("--> Case non touchée\n");
            } else {
                printf("--> Case touchée\n");
            }
        }

    } while(choix2 != 2);

    clear();

    printf("%d cases coulés par l'ordi :\n", lenBT(ordi->bt));
    printBT(ordi->bt);
    printf("\n");

    int choix3 = 0;
    int choix_X2 = -1;
    int choix_Y2 = -1;
    do{
        printf("\n");
        printf("Chercher une case (taper 1) ou revenir au menu (taper 2) : ");
        scanf("%d", &choix3);
        if(choix3 == 1){
            do {            
                printf("-   Ligne : ");
                scanf("%d", &choix_X2);
                printf("- Colonne : ");
                scanf("%d", &choix_Y2);
            } while(choix_X2<0 || choix_X2>9 || choix_Y2<0 || choix_Y2>9);

            int caseTest2 = choix_X2 * 10 + choix_Y2;

            if(search(ordi->bt, caseTest2) == NULL) {
                printf("--> Case non touchée\n");
            } else {
                printf("--> Case touchée\n");
            }
        }

    } while(choix3 != 2); 

    j1->bt = freeBT(j1->bt);
    ordi->bt = freeBT(ordi->bt);
}
