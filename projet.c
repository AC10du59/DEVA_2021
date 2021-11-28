#include <stdio.h>
#include <stdlib.h>

const char * MESSAGE_AIDE = "Bienvenue dans le jeu BattleShip !\n\nNous sommes ici pour vous aider et expliquer le jeu.\nLe but de ce jeu est dans un premier temps de placer les bateaux sur le plateau de jeu.\nVous aurez 5 bateaux de tailles différentes à placer. \nVotre adversaire aura exactement les mêmes bateaux que vous.\nUne fois vos bateaux placés, vous devrez couler les bateaux de votre adversaire.\nPour trouver les bateaux, il vous suffira de donner les coordonnées X et Y par rapport au plateau.\nVous essaierez de toucher le bateau l'un aprés l'autre.\nSi vous touchez le bateau, vous serez informé et vous pourrez rejouer immédiatement.\nSi vous ne le touchez pas, ce sera à l'adversaire de jouer.\nLe premier à couler tous les bateaux adverses a gagné.\n\nBonne chance !!!\n\n\n";

void clear(){
    system("@cls||clear");
}

void menu(){
    clear();

    int choix = 0;
    printf("Bienvenue dans BattleShip !\n\n");
    printf("1. Jouer\n");
    printf("2. Aide\n");
    printf("3. Quitter\n\n");
   
    while(choix!=1 && choix!=2 && choix!=3){
        printf("Entrer votre choix : ");
        scanf("%d", &choix);
    }
    
    if(choix == 1) menu_jouer();
    if(choix == 2) menu_aide();
    if(choix == 3) exit(EXIT_SUCCESS);
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

    if(choix == 1 || choix == 2){
        printf("OK --> choix = %d\n", choix);
        exit(EXIT_SUCCESS);
    }
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

int main(int argc, char *argv[]) {  
    menu();
    return 0;
}
