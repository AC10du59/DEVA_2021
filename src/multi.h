#ifndef MULTI_H
#define MULTI_H

#include "arbre.h"
#define TAILLE 10

typedef struct navire {
    char *nom;
    int sens; /*1 haut 2 droite 3 bas 4 gauche*/
    int x;
    int y;
    int taille;
} Navire;

typedef struct joueur {
    int id;
    int plateau[TAILLE][TAILLE];
    int tir[TAILLE][TAILLE];
    Navire *bateaux[5];
    BinTree *bt;
} Joueur;

void clear();
void initialiser_grille(int grille[TAILLE][TAILLE]);
Navire *creerNavire(char *nom, int posX, int posY, int taille, int s);
void initBateau(Navire *bat[5]);
Joueur *creerJoueur(int id);
void affiche_grille(int grille[TAILLE][TAILLE]);
int est_valide(int x, int y, int direction, int taille, int grille[TAILLE][TAILLE]);
void prochainTour(Joueur *j);
int nbBateauEnVie(Joueur *j1);

#endif
