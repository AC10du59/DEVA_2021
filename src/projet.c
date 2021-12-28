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

/*---------------------------------- ARBRE -----------------------------------*/

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}BinTree, Node;

BinTree *empty_bintree(){
    return NULL;
}

Node *create_node(int data){
    Node *node = malloc(sizeof(Node));
    if(!node) return NULL;
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BinTree *insert(BinTree *bt, int data){
    BinTree *prec;
    BinTree *head = bt;

    if(!bt) return create_node(data);

    while(bt){
        prec = bt;
        if(data < bt->data){
            bt = bt->left;
        } else {
            bt = bt->right;
        }
    }

    if(data < prec->data){
        prec->left = create_node(data);
    } else {
        prec->right = create_node(data);
    }

    return head;
}

BinTree *search(BinTree *bt, int data){
    while(bt){
        if(data < bt->data){
            bt = bt->left;
        } else {
            if(data > bt->data){
                bt = bt->right;
            } else {
                return bt;
            }
        }
    }

    return NULL;
}

void printBT(BinTree *bt){
    if(bt){
        printBT(bt->left);
        if(bt->data < 10){
            printf("Ligne : 0 | Colonne : %d\n", bt->data);
        } else {
            int l = bt->data / 10;
            int c = bt->data % 10;
            printf("Ligne : %d | Colonne : %d\n", l, c);
        }
        printBT(bt->right);
    }
}

BinTree *freeBT(BinTree *bt){
    if(bt){
        bt->left = freeBT(bt->left);
        bt->right = freeBT(bt->right);
        free(bt);
    }
    return NULL;
}

int lenBT(BinTree *bt){
    if(!bt) return 0;
    return 1 + lenBT(bt->left) + lenBT(bt->right);
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
    BinTree *bt;
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
    j->bt = empty_bintree();
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
    return rand() % (limite+1) + borneD;
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

int nbBateauEnVie(Joueur *j1){
    int compteur = 0;

    for(int i = 0; i < TAILLE; i++){
        for(int j = 0; j < TAILLE; j++){
            if(j1->tir[i][j] == 1) compteur++;
        }
    }

    return compteur;
}

void prochainTourTir(Joueur *j){
    int choix = -1;
    while(choix<0 || choix>9){
        clear();
        printf("JOUEUR %d\n", j->id);
        printf("Voici votre grille de tirs : \n\n", j->id);
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
    } while(choix_X<0 || choix_X>9 || choix_Y<0 || choix_Y>9 || j1->tir[choix_X][choix_Y] != 0);

    int caseNB = choix_X * 10 + choix_Y;
    j1->bt = insert(j1->bt, caseNB);

    if(touche(choix_X, choix_Y, j2)==0) j1->tir[choix_X][choix_Y] = 1;
    else j1->tir[choix_X][choix_Y] = 2;
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

int partieTerminee(Joueur *j1, Joueur *j2){
    if(nbBateauEnVie(j1)==17) return 1;
    if(nbBateauEnVie(j2)==17) return 2;

    return 0;
}

void jouerPartie(){
    clear();
    Joueur *j1 = creerJoueur(1);
    placer_bateau(j1);
    Joueur *j2 = creerJoueur(2);
    placer_bateau(j2);
    
    int joueur = 0; 

    while(partieTerminee(j1, j2)==0){
       if(joueur%2==0){
            jouer(j1,j2);
            prochainTourTir(j1);
        } else {
            jouer(j2,j1);
            prochainTourTir(j2);
        }
        joueur++;
    }
    int gagnant = partieTerminee(j1, j2);

    clear();

    if(gagnant==1){
        printf("Félicitation au Joueur 1 qui a remporté la partie !!!\n\n");
        affiche_grille(j1->tir);
    } else{
        printf("Félicitation au Joueur 2 qui a remporté la partie !!!\n\n");
        affiche_grille(j2->tir);
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
        printf("Chercher une case (taper 1) ou passer aux tirs du joueur 2 (taper 2) : ");
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

    printf("%d cases coulés par le joueur 2 :\n", lenBT(j2->bt));
    printBT(j2->bt);
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

            if(search(j2->bt, caseTest2) == NULL) {
                printf("--> Case non touchée\n");
            } else {
                printf("--> Case touchée\n");
            }
        }

    } while(choix3 != 2); 

    j1->bt = freeBT(j1->bt);
    j2->bt = freeBT(j2->bt);
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
            //jouer(j1,ordi);
            //prochainTourTir(j1);
            jouerOrdi(j1,ordi);
            prochainTourTirOrdi(j1);
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

/*------------------------------ FONCTION MAIN -------------------------------*/
int main(int argc, char *argv[]) {
    menu();
    return 0;
}
