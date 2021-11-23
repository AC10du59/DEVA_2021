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

int main(int argc, char *argv[]) {  
    int choix = 0;
    do{
        choix = menu();
        if(choix == 3){
            return 0;
        }
    } while(choix!=1 && choix!=2);
    
    if(choix == 2){
        clear();
        printf("Bienvenue dans le jeu BattleShip.\n");
        printf("Nous sommes ici pour vous aider et expliquez le jeu \n");
        printf("Le but de ce jeu est dans un premier temps de placer ses bateaux sur le plateau de jeu \n");
        printf("Vous aurez 5 bateaux de tailles différentes à placer \n") ;
        printf("Votre adversaire aura exactement les mêmes bateaux que vous \n") ;
        printf("Une fois vos bateaux placés, vous devrez couler les bateaux de votre adversaire \n") ;
        printf("Pour trouver les bateaux, il vous suffit de donner les coordonnées x et y \n");
        printf("Vous essaierez de toucher le bateau l'un aprés l'autre \n");
        printf("Si vous touchez le bateau, celà vous sera informé et vous pourrez rejouer immédiatement \n") ;
        printf("Si vous ne le touchez pas il ne se passera rien et ce sera à l'adversaire de jouer \n") ;
        printf("Le premier à éliminer tous les bateaux adverses a gagné \n") ;
        
        int test = 0;
        scanf("%d", &test);

    }

    int choixJ = menu_jouer();
    printf("%d\n", choixJ);
    return 0;
}
