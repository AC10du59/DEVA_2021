#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "multi.h"
#include "ordi.h"

const char * MESSAGE_AIDE = "Bienvenue dans le jeu BattleShip !\n\nVoici les règles du jeu :\n\nAu début du jeu, chaque joueur place à sa guise tous les bateaux sur sa grille de façon stratégique. Le but étant de compliquer au maximum la tache de son adversaire, c’est-à-dire détruire tous vos navires. Bien entendu, le joueur ne voit pas la grille de son adversaire.\n\nVoici les symboles sur la grille :\n\n   ~ <==> eau\n   x <==> touché\n   o <==> plouf\n\nUne fois tous les bateaux en jeu, la partie peut commencer. Un à un, les joueurs se tirent dessus pour détruire les navires ennemis. Le premier joueur à couler les bateaux de l'ennemi remporte la partie.\n\nA la fin de la partie, vous pourrez consulter l'historique des tirs de la partie.\n\nBonne chance !!!\n\n\n";

void menu(){
    clear();

    int choix = 0;
    printf("Bienvenue dans BattleShip !\n\n");
    printf("1. Jouer\n");
    printf("2. Aide\n");
    printf("3. Quitter\n\n");
    printf("Entrer votre choix : ");

    scanf("%d", &choix);

    if(choix == 1) menu_jouer();
    if(choix == 2) menu_aide();
    if(choix == 3) exit(EXIT_SUCCESS);

    menu();
}

void menu_jouer(){
    clear();

    int choix = 0;
    printf("Bienvenue dans le menu de jeu !\n\n");
    printf("1. Contre l'ordi\n");
    printf("2. 2 joueurs\n");
    printf("3. Menu principal\n");
    printf("4. Quitter\n\n");
    printf("Entrer votre choix : ");

    scanf("%d", &choix);

    if(choix == 1) jouerPartieOrdi();
    if(choix == 2) jouerPartie();
    if(choix == 3) menu();
    if(choix == 4) exit(EXIT_SUCCESS);

    menu_jouer();
}

void menu_aide(){
    clear();
    printf("%s", MESSAGE_AIDE);

    int choix = 0;
    printf("1. Menu principal\n");
    printf("2. Menu de jeu\n");
    printf("3. Quitter\n\n");
    printf("Entrer votre choix : ");

    scanf("%d", &choix);

    if(choix == 1) menu();
    if(choix == 2) menu_jouer();
    if(choix == 3) exit(EXIT_SUCCESS);

    menu_aide();
}
