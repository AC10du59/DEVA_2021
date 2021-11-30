#include <stdio.h>
#include <stdlib.h>

/*------------------------------------ MENU ----------------------------------*/

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


/*----------------------------- BATAILLE NAVALE ------------------------------*/

#define TAILLE 10

typedef struct une_case {
    int x;
    int y;
} Case;

typedef struct navire {
    char * nom;
    int sens; /*1 haut 2 droite 3 bas 4 gauche*/
    Case premiere_case;
    int taille;
} Navire;

/*
0 ---> rien
1 ---> tir non touché
2 ---> bateau touché
*/

void initialiser_grille(int grille[TAILLE][TAILLE]){
    for(int i = 0; i < TAILLE; i++){
        for(int j = 0; j < TAILLE; j++){
            grille[i][j] = 0;
        }
    }
}

void affiche_grille(int grille[TAILLE][TAILLE]){
    int i, j;
    printf("    0 1 2 3 4 5 6 7 8 9\n");

    for(i = 0; i < TAILLE; i++){
        printf(" %d  ", i);
        for(j = 0; j < TAILLE; j++){
            if(grille[i][j]==0) printf("~ ");
            else if(grille[i][j]==1) printf("x ");
            else if(grille[i][j]==2) printf("o ");
        }
    printf("\n");
    }
}

int est_valide(int x, int y, int direction, int taille, int grille[TAILLE][TAILLE]){
    int i;    
    if(x>=0 && x<=9 && y>=0 && y<=9){
        for(i = 0; i < taille; i++){
            if(direction==1){
            /*haut*/            
                if(grille[x][y-i] != 0 || x-i < 0) return 0; 
            }
            else if(direction==2){
            /*droite*/            
                if(grille[x+i][y] != 0 || y+i > 9) return 0; 
            }
            else if(direction==3){
            /*bas*/            
                if(grille[x][y+i] != 0 || x+i > 9) return 0; 
            }
            else if(direction==4){
            /*gauche*/            
                if(grille[x-i][y] != 0 || y-i < 0) return 0; 
            }
        }
        return 1;

    }
    return 0;
}


void placer_bateau(int taille, int grille[TAILLE][TAILLE]){ 
    int choix_X = -1;
    int choix_Y = -1;
    int direction = -1;    
    do{
        clear();
    
        affiche_grille(grille);

        printf("\nPlacez le bateau à %d cases.\n\n", taille);
        printf("Coordonnés de début du navire.\n");
        printf("-   Ligne : ");
        scanf("%d", &choix_X);
        printf("- Colonne : ");
        scanf("%d", &choix_Y);
        printf("\n\nDirection du navire.\n");
        printf(" 1. Haut\n");
        printf(" 2. Droite\n");
        printf(" 3. Bas\n");
        printf(" 4. Gauche\n");
        printf("Choix : ");
        scanf("%d", &direction);
    } while(est_valide(choix_X, choix_Y, direction, taille, grille)==0);


}



/*------------------------------ FONCTION MAIN -------------------------------*/
int main(int argc, char *argv[]) {  
    //menu();
    int plateau1[TAILLE][TAILLE];
    initialiser_grille(plateau1);
    placer_bateau(3,plateau1);
    affiche_grille(plateau1);
    return 0;
}
