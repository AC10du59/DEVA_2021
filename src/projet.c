#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

typedef struct navire {
    char *nom;
    int sens; /*1 haut 2 droite 3 bas 4 gauche*/
    int x;
    int y;
    int taille;
    int coule; /*0 non 1 oui*/
} Navire;

typedef struct joueur {
    int id;
    int plateau[TAILLE][TAILLE];
    int tir[TAILLE][TAILLE];
    Navire *bateaux[5];
} Joueur;

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

Navire *creerNavire(char *nom, int posX, int posY, int taille, int s) {
	Navire *a = NULL;
    a = (Navire *)malloc(sizeof(Navire));
    a->nom = nom;
    a->sens = s;
    a->x = posX;
    a->y = posY;
    a->taille = taille;
    a->coule = 0;
    return a;
}

void initBateau(Navire *bat[5]){
    bat[0] = creerNavire("Torpilleur", 0, 0, 2, 0);
    bat[1] = creerNavire("Sous-marin", 0, 0, 3, 0);
    bat[2] = creerNavire("Contre-torpilleur", 0, 0, 3, 0);
    bat[3] = creerNavire("Croiseur", 0, 0, 4, 0);
    bat[4] = creerNavire("Porte-avion", 0, 0, 5, 0);
}

Joueur *creerJoueur(int id) {
	Joueur *j = NULL;
    j = (Joueur *)malloc(sizeof(Joueur));
    j->id = id;
    initialiser_grille(j->plateau);
    initialiser_grille(j->tir);
    initBateau(j->bateaux);
    return j;
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

int nbalea(int borneD, int limite){
    int nombre = 0;
    const int MIN = borneD, MAX = limite;
    srand(time(NULL)); // Initialisation de la donnée seed

    nombre = (rand() % (MAX + 1 - MIN)) + MIN;// MIN <= nombre <= MAX
    return nombre ;
}

int est_valide(int x, int y, int direction, int taille, int grille[TAILLE][TAILLE]){
    int i;
    if(direction < 1 || direction > 4) return 0;
    if(x>=0 && x<=9 && y>=0 && y<=9){
        for(i = 0; i < taille; i++){
            if(direction==1){
            /*haut*/
                //printf("x=%d / y=%d / case=%d\n",x-i,y,grille[x-i][y]);
                if(grille[x-i][y] != 0 || x-i < 0) return 0;
            }
            else if(direction==2){
            /*droite*/
                //printf("x=%d / y=%d / case=%d\n",x,y+i,grille[x+i][y]);
                if(grille[x][y+i] != 0 || y+i > 9) return 0;
            }
            else if(direction==3){
            /*bas*/
                //printf("x=%d / y=%d / case=%d\n",x+i,y,grille[x][y+i]);
                if(grille[x+i][y] != 0 || x+i > 9) return 0;
            }
            else if(direction==4){
            /*gauche*/
                //printf("x=%d / y=%d / case=%d\n",x,y-i,grille[x-i][y]);
                if(grille[x][y-i] != 0 || y-i < 0) return 0;
            }
        }
        return 1;

    }
    return 0;
}

void prochainTour(Joueur *j){
    int choix = -1;
    while(choix<0 || choix>9){
        clear();
        printf("JOUEUR %d\n", j->id);
        printf("Voici votre grille : \n\n", j->id);
        affiche_grille(j->plateau);
        printf("\n\nAppuyer sur une touche numérique et entrée pour continuer : ");
        scanf("%d", &choix);
    }  
    clear();
}

int * couler(Joueur *j1){
    static int res[5];
    int index = 0;
    for(int bat = 0; bat < 5; bat++){
        int isBateauTouche = 0;
        for(int i = 0; i < j1->bateaux[bat]->taille; i++){
            if(j1->bateaux[bat]->sens==1){
                /*haut*/
                if(j1->tir[j1->bateaux[bat]->x-i][j1->bateaux[bat]->y] == 0){
                    isBateauTouche = -1;                
                }
            }
            else if(j1->bateaux[bat]->sens==2){
                /*droite*/
                if(j1->plateau[j1->bateaux[bat]->x][j1->bateaux[bat]->y+i] == 0){
                    isBateauTouche = -1;      
                }
            }   
            else if(j1->bateaux[bat]->sens==3){
                /*bas*/
                if(j1->plateau[j1->bateaux[bat]->x+i][j1->bateaux[bat]->y] == 0){
                    isBateauTouche = -1;      
                }
            }
            else if(j1->bateaux[bat]->sens==4){
                /*gauche*/
                if(j1->plateau[j1->bateaux[bat]->x][j1->bateaux[bat]->y-i] == 0){
                    isBateauTouche = -1;      
                }
            }
        }
        if(isBateauTouche==-1){
            res[bat] = -1;
        } else {
            res[bat] = 0;
        }
    }
    return res;
}

void prochainTourTir(Joueur *j){
    int choix = -1;
    while(choix<0 || choix>9){
        clear();
        printf("JOUEUR %d\n", j->id);
        printf("Voici votre grille de tirs : \n\n", j->id);
        affiche_grille(j->tir);
        printf("\n");

        int *p;
        p = couler(j);

        if(p[0]==0){
            printf("- Torpilleur (2 cases)             FLOTTE\n");
        } else {
            printf("- Torpilleur (2 cases)             COULÉ\n");
        }

        if(p[1]==0){
            printf("- Sous-marin (3 cases)             FLOTTE\n");
        } else {
            printf("- Sous-marin (3 cases)             COULÉ\n");
        }

        if(p[2]==0){
            printf("- Contre-torpilleur (3 cases)      FLOTTE\n");
        } else {
            printf("- Contre-torpilleur (3 cases)      COULÉ\n");
        }

        if(p[3]==0){
            printf("- Croiseur (4 cases)               FLOTTE\n");
        } else {
            printf("- Croiseur (4 cases)               COULÉ\n");
        }

        if(p[4]==0){
            printf("- Porte-avion (5 cases)            FLOTTE\n");
        } else {
            printf("- Porte-avion (5 cases)            COULÉ\n");
        }
        printf("\nAppuyer sur une touche numérique et entrée pour continuer : ");
        scanf("%d", &choix);
    }  
    clear();
}


void placer_bateau(Joueur *j){
    int currentBateau;
    for(currentBateau = 0; currentBateau < 5; currentBateau++){
        Navire *n = j->bateaux[currentBateau];
        int choix_X = -1;
        int choix_Y = -1;
        int direction = -1;
        do{
            clear();
            printf("JOUEUR %d\n\n", j->id);
            affiche_grille(j->plateau);
            printf("\nPlacez le %s sur le plateau (%d cases).\n\n", n->nom, n->taille);
            printf("Coordonnés de début du navire.\n");
            printf("-   Ligne : ");
            scanf("%d", &choix_X);
            printf("- Colonne : ");
            scanf("%d", &choix_Y);
            printf("\nDirection du navire.\n");
            printf(" 1. Haut\n");
            printf(" 2. Droite\n");
            printf(" 3. Bas\n");
            printf(" 4. Gauche\n");
            printf("-   Choix : ");
            scanf("%d", &direction);
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
    prochainTour(j);
}

void placerBateauOrdi(int taille, int grille2[TAILLE][TAILLE]){
    int choix_X = -1;
    int choix_Y = -1;
    int direction = -1;
    do{
        choix_X=nbalea(0,9);
        choix_Y=nbalea(0,9);
        direction=nbalea(1,4);
    } while(est_valide(choix_X, choix_Y, direction, taille, grille2)==0);

    int i;
    for(i = 0; i < taille; i++){
        if(direction==1){
        /*haut*/
            grille2[choix_X-i][choix_Y] = 1;
        }
        else if(direction==2){
        /*droite*/
            grille2[choix_X][choix_Y+i] = 1;
        }
        else if(direction==3){
        /*bas*/
            grille2[choix_X+i][choix_Y] = 1;
        }
        else if(direction==4){
        /*gauche*/
            grille2[choix_X][choix_Y-i] = 1;
        }
    }
}

// 0 -> touche | 1 -> plouf
int touche(int x, int y, Joueur *j){
    if(j->plateau[x][y] == 1){
        return 0;
    }
    return 1;
}

void jouer(Joueur *j1, Joueur *j2){
    int choix_X = -1;
    int choix_Y = -1;
    do{
        clear();
        printf("JOUEUR %d\n\n", j1->id);
        affiche_grille(j1->tir);
        printf("Coordonnés du tir\n");
        printf("-   Ligne : ");
        scanf("%d", &choix_X);
        printf("- Colonne : ");
        scanf("%d", &choix_Y);
    } while(choix_X<0 || choix_X>9 || choix_Y<0 || choix_Y>9);

    if(touche(choix_X, choix_Y, j2)==0) j1->tir[choix_X][choix_Y] = 1;
    else j1->tir[choix_X][choix_Y] = 2;

    //vérifier si le bateau est coulé

    //vérifier si la partie est terminé
    prochainTourTir(j1);
}


/*------------------------------ FONCTION MAIN -------------------------------*/
int main(int argc, char *argv[]) {
    //menu();
    Joueur *j1 = creerJoueur(1);
    placer_bateau(j1);
    Joueur *j2 = creerJoueur(2);
    placer_bateau(j2);
    jouer(j1,j2);
    jouer(j1,j2);    
    jouer(j1,j2);
    jouer(j1,j2);
    jouer(j1,j2);
    return 0;
}
