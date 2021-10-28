#ifndef jeu.h
#define jeu.h
#include "Structures.h"
    typedef struct{
        int key[SDLK_LAST];
    }Key;

    void Jouer(SDL_Surface *ecran);
    void Deplacement(int **carte,SDL_Rect *rect,int sens,int *ScorePlayer);
    int** allouerCarte(int n,int m);
    void updateClavier(Key *KeyState);
    void Bombes(int**carte,SDL_Surface *ecran,int Player);
    void* gestionBombes(void*arg );
    void* gestionBombes2(void*arg );
    void ModeMenu(SDL_Surface *ecran);
    void Ennemy(SDL_Surface *ecran);
    void MouvementEnnemy(int**carte,SDL_Surface *ecran);
    void* gestionMouvementEnnemy(void *arg);
    int placementOr(int **carte);
#endif
