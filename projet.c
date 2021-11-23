#include <stdio.h>
#include <stdlib.h>

void clear(){
    system("@cls||clear");

}

int menu(){
    int choix;
    clear();
    printf("Bienvenue dans BattleShip !\n\n");
    printf("1. Jouer\n");
    printf("2. Aide\n");
    printf("3. Quitter\n\n");
    printf("Entrer votre choix : ");
    scanf("%d", &choix);
    return choix;
}

int menu_jouer(){
    int choix;
    clear();
    printf("Bienvenue dans le menu de jeu !\n\n");
    printf("1. Contre l'ordi\n");
    printf("2. 2 joueurs\n");
    printf("3. Quitter\n\n");
    printf("Entrer votre choix : ");
    scanf("%d", &choix);
    return choix;
}

void aide(){
    clear();
    printf("Appuyer pour retourner au menu.");.




}




int main(int argc, char *argv[]) {  
    int choix = 0;
    do{
        choix = menu();
        if(choix == 2){
            aide();

        }
        if(choix == 3){
            return 0;
        }
    } while(choix!=1);
    

    int choixJ = menu_jouer();
    printf("%d\n", choixJ);
    return 0;
}
