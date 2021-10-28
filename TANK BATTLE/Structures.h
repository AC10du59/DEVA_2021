/**
 * @author ABDELLAH EL ASRI
 *Groupe 5
*/

/**
    Structures.h
    Rôle : Contient toutes les Structures utilisées par le programme et les constantes.
*/

#ifndef Structures.h
#define Structures.h

#include <windows.h>
    #define LargeurFenetre 800
    #define HauteurFenetre 600
    #define FALSE 0
    #define TRUE 1
    #define FPS 30
    #define Frame_time (1000/FPS)
    #define SizePlayer 40
    #define SizeBloc 40

    enum{Up,Down,Right,Left};
    enum{Vide,Mur,Joueur1,Joueur2,Bombe,TNT,FeuBombe,BombeHaut,BombeBas,BombeDroite,BombeGauche,EnnemiHaut,EnnemiBas,EnnemiDroite,EnnemiGauche,MurOr,Or};


#endif

