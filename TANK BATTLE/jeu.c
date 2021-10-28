#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <pthread.h>
#include "Structures.h"
#include "jeu.h"
#include <windows.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

typedef struct{
    int **carte1;
    SDL_Surface *ecran1;
}listearg;
listearg liste;

SDL_Rect Player1Rect;
SDL_Rect Player2Rect;
SDL_Rect BlocRect;
SDL_Rect Rect1;SDL_Rect Rect2;
SDL_Rect RectMenu;

    SDL_Surface *text=NULL;
    SDL_Surface *ScorePlayer1;
    SDL_Surface *ScorePlayer2;

    int Play=1;

    TTF_Font *font=NULL;
    SDL_Color BLACK={0,0,0};
    SDL_Color Green={0,255,0};
    SDL_Color Blue={0,0,255};
    SDL_Color Red={255,0,0};
    char score[20]="";
    double compteurBombe=0;
    int nbOr=0;
    int scorePlayer1=0;
    int scorePlayer2=0;

void ModeMenu(SDL_Surface *ecran){
    SDL_Event event;
    int PlayMenu=1;
    SDL_Surface *MenuModeJeu=NULL;
    MenuModeJeu=IMG_Load("src/ModeMenu.png");

    RectMenu.x=0;
    RectMenu.y=0;
    Play=1;
    SDL_BlitSurface(MenuModeJeu,NULL,ecran,&RectMenu);
    SDL_Flip(ecran);
    while(PlayMenu){
           SDL_WaitEvent(&event);
            switch (event.type){
                case SDL_QUIT:
                    Play=0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_1:
                            Ennemy(ecran);
                            break;
                        case SDLK_2:
                            Jouer(ecran);
                            break;
                        case SDLK_ESCAPE:
                            PlayMenu=0;
                            return;
                        default:
                            break;
                    }
            }
    }
    SDL_FreeSurface(MenuModeJeu);

}

void updateClavier(Key *KeyState){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_KEYDOWN:
                KeyState->key[event.key.keysym.sym]=1;
                break;
            case SDL_KEYUP:
                KeyState->key[event.key.keysym.sym]=0;
                break;
            default:
                break;
        }
    }
}

int** allouerCarte(int n,int m){
    int**carte;
    carte = (int **)malloc(n * sizeof(int *));
    if(carte != NULL) {
        for(int i=0; i<n; i++){
            carte[i] = (int *)malloc(m * sizeof(int));
        }
        return carte;
    }
}
int** carte(){
    int **carte=allouerCarte();
    FILE *fichier;
    fichier = fopen("src/carte1.tx","r");
    if (fichier != NULL) if (fichier != NULL)
    {
    for(int j=0;j<15;j++){
        for(i=0;i<20;i++){
            fscanf(fichier,"%d\n",((carte+i)+j));
        }
    }
    fclose(fichier);
    }
    return carte;
}

void Jouer(SDL_Surface *ecran){
    Key State_Keyword;
    memset(&State_Keyword,0,sizeof(State_Keyword));
    int i,j;
    int **carte=carte();
    SDL_Surface *Player1[4]={NULL};
    SDL_Surface *Player1Now=NULL;

    SDL_Surface *Player2[4]={NULL};
    SDL_Surface *Player2Now=NULL;

    SDL_Surface *BombUp=NULL;
    SDL_Surface *BombDown=NULL;
    SDL_Surface *BombRight=NULL;
    SDL_Surface *BombLeft=NULL;
    SDL_Surface *BombBox=NULL;
    SDL_Surface *BombBlast=NULL;
    SDL_Surface *Player1Wins=NULL;
    SDL_Surface *Player2Wins=NULL;

    SDL_Surface *Brike=NULL;
    SDL_Surface *Terre=NULL;
    SDL_Surface *LingotOr=NULL;

    Player1Rect.x=7;
    Player1Rect.y=1;

    Player2Rect.x=6;
    Player2Rect.y=1;

    Player1[Up]=IMG_Load("src/Up.png");
    Player1[Down]=IMG_Load("src/Down.png");
    Player1[Right]=IMG_Load("src/Right.png");
    Player1[Left]=IMG_Load("src/Left.png");
    Brike=IMG_Load("src/Wall.jpg");
    Terre=IMG_Load("src/Ground.jpg");
    LingotOr=IMG_Load("src/Gold.png");


    Player2[Up]=IMG_Load("src/Up2.png");
    Player2[Down]=IMG_Load("src/Down2.png");
    Player2[Right]=IMG_Load("src/Right2.png");
    Player2[Left]=IMG_Load("src/Left2.png");
    Player1Now=Player1[Up];
    Player2Now=Player2[Down];

    BombUp=IMG_Load("src/BombUp.png");
    BombDown=IMG_Load("src/BombDown.png");
    BombRight=IMG_Load("src/BombRight.png");
    BombLeft=IMG_Load("src/BombLeft.png");
    BombBlast=IMG_Load("src/BombBlast.png");
    BombBox=IMG_Load("src/Bomb.png");

    Player1Wins=IMG_Load("src/Player1.png");
    Player2Wins=IMG_Load("src/Player2.png");

    nbOr=placementOr(carte);

    TTF_Init();

    while(Play==1){
        updateClavier(&State_Keyword);
        if (State_Keyword.key[SDLK_UP]){
            Player1Now=Player1[Up];
            Deplacement(carte,&Player1Rect,Up,&scorePlayer1);
        }
        if (State_Keyword.key[SDLK_DOWN]){
            Player1Now=Player1[Down];
            Deplacement(carte,&Player1Rect,Down,&scorePlayer1);
        }
        if (State_Keyword.key[SDLK_RIGHT]){
            Player1Now=Player1[Right];
            Deplacement(carte,&Player1Rect,Right,&scorePlayer1);
        }
        if (State_Keyword.key[SDLK_LEFT]){
            Player1Now=Player1[Left];
            Deplacement(carte,&Player1Rect,Left,&scorePlayer1);
        }
        if (State_Keyword.key[SDLK_w]){
            Player2Now=Player2[Up];
            Deplacement(carte,&Player2Rect,Up,&scorePlayer2);
        }
        if (State_Keyword.key[SDLK_s]){
            Player2Now=Player2[Down];
            Deplacement(carte,&Player2Rect,Down,&scorePlayer2);
        }
        if (State_Keyword.key[SDLK_d]){
            Player2Now=Player2[Right];
            Deplacement(carte,&Player2Rect,Right,&scorePlayer2);
        }
        if (State_Keyword.key[SDLK_a]){
            Player2Now=Player2[Left];
            Deplacement(carte,&Player2Rect,Left,&scorePlayer2);
        }
        if (State_Keyword.key[SDLK_SPACE]){
                Bombes(carte,ecran,1);
        }
        if (State_Keyword.key[SDLK_f]){
                Bombes(carte,ecran,2);
        }
        if (State_Keyword.key[SDLK_ESCAPE]){
            Play=0;
            return;
        }

        for (i=0;i<LargeurFenetre/SizeBloc;i++){
            for(j=0;j<HauteurFenetre/SizeBloc;j++){
                BlocRect.x=i*SizeBloc;
                BlocRect.y=j*SizeBloc;
                switch (carte[i][j]){
                    case Mur:
                        SDL_BlitSurface(Brike,NULL,ecran,&BlocRect);
                        break;
                    case Vide:
                        SDL_BlitSurface(Terre,NULL,ecran,&BlocRect);
                        break;
                    case MurOr:
                        SDL_BlitSurface(Brike,NULL,ecran,&BlocRect);
                        break;
                    case Or:
                        SDL_BlitSurface(LingotOr,NULL,ecran,&BlocRect);
                        break;
                    case TNT:
                        SDL_BlitSurface(BombBox,NULL,ecran,&BlocRect);
                        break;
                    case FeuBombe:
                        SDL_BlitSurface(BombBlast,NULL,ecran,&BlocRect);
                        break;
                    case BombeHaut:
                        SDL_BlitSurface(BombUp,NULL,ecran,&BlocRect);
                        break;
                    case BombeBas:
                        SDL_BlitSurface(BombDown,NULL,ecran,&BlocRect);
                        break;
                    case BombeDroite:
                        SDL_BlitSurface(BombRight,NULL,ecran,&BlocRect);
                        break;
                    case BombeGauche:
                        SDL_BlitSurface(BombLeft,NULL,ecran,&BlocRect);
                        break;
                    default:
                        break;
                }
            }
        }

        Rect1.x = Player1Rect.x * SizeBloc;
        Rect1.y = Player1Rect.y * SizeBloc;
        Rect2.x = Player2Rect.x * SizeBloc;
        Rect2.y = Player2Rect.y * SizeBloc;

        SDL_BlitSurface(Player1Now,NULL,ecran,&Rect1);
        SDL_BlitSurface(Player2Now,NULL,ecran,&Rect2);
        font=TTF_OpenFont("data/font.ttf",26);
        sprintf(score,"%d: GOLD INGOTS",nbOr);
        text=TTF_RenderText_Blended(font,score,Green);
        sprintf(score,"%d: PLAYER 1",scorePlayer1);
        ScorePlayer1=TTF_RenderText_Blended(font,score,Blue);
        sprintf(score,"%d: PLAYER 2",scorePlayer2);
        ScorePlayer2=TTF_RenderText_Blended(font,score,Red);
        BlocRect.x=300;
        BlocRect.y=3;
        SDL_BlitSurface(text,NULL,ecran,&BlocRect);
        BlocRect.x=5;
        BlocRect.y=570;
        SDL_BlitSurface(ScorePlayer1,NULL,ecran,&BlocRect);
        BlocRect.x=560;
        BlocRect.y=570;
        SDL_BlitSurface(ScorePlayer2,NULL,ecran,&BlocRect);
        SDL_Flip(ecran);
        Sleep(80);
    }
    RectMenu.x=0;
    RectMenu.y=0;
    if(Play==2){
        SDL_BlitSurface(Player1Wins,NULL,ecran,&RectMenu);
        SDL_Flip(ecran);
        Sleep(10);
        Play=0;
    }
    if(Play==3){
        SDL_BlitSurface(Player2Wins,NULL,ecran,&RectMenu);
        SDL_Flip(ecran);
        Sleep(10);
        Play=0;
    }

    SDL_FreeSurface(Brike);
    SDL_FreeSurface(Terre);
    SDL_FreeSurface(BombDown);
    SDL_FreeSurface(BombUp);
    SDL_FreeSurface(BombBox);
    SDL_FreeSurface(BombRight);
    SDL_FreeSurface(BombLeft);
    SDL_FreeSurface(BombBlast);
    SDL_FreeSurface(LingotOr);
    SDL_FreeSurface(text);
    SDL_FreeSurface(Player1Wins);
    SDL_FreeSurface(Player2Wins);
    for(int i=0;i<4;i++){
        SDL_FreeSurface(Player1[i]);
        SDL_FreeSurface(Player2[i]);
    }
}

void Deplacement(int **carte,SDL_Rect *rect,int sens,int *ScorePlayer){

        switch(sens){
            case Up:
                if(carte[rect->x][(rect->y)-1]==Mur||carte[rect->x][(rect->y)-1]==TNT)
                break;
                rect->y-=1;
                if (carte[rect->x][rect->y]==Or){
                    carte[rect->x][rect->y]=Vide;
                    nbOr--;
                    ScorePlayer++;
                }
                break;
            case Down:
                if(carte[rect->x][(rect->y)+1]==Mur||carte[rect->x][(rect->y)+1]==TNT)
                break;
                rect->y+=1;
                if(carte[rect->x][rect->y]==Or){
                    carte[rect->x][(rect->y)]=Vide;
                    nbOr--;
                    ScorePlayer++;
                }
                break;
            case Right:
                if(carte[(rect->x)+1][(rect->y)]==Mur||carte[(rect->x)+1][(rect->y)]==TNT)
                break;
                rect->x+=1;
                if(carte[rect->x][rect->y]==Or){
                    carte[rect->x][rect->y]=Vide;
                    nbOr--;
                    ScorePlayer++;
                }
                break;
            case Left:
                if(carte[(rect->x)-1][(rect->y)]==Mur||carte[(rect->x)-1][(rect->y)]==TNT)
                break;
                rect->x-=1;
                if(carte[rect->x][rect->y]==Or){
                    carte[rect->x][rect->y]=Vide;
                    nbOr--;
                    ScorePlayer++;
                }
                break;
            default:
                break;

        }
}

int placementOr(int **carte1){
    int a=0,b=0,compteur=0;
    srand(time(NULL));
    for(a=1;a<19;a++){
        for (b=1;b<14;b++){
            if(carte1[a][b]==Mur&&carte1[a+1][b]==Mur&&carte1[a-1][b]==Vide){
                int alea=(rand()%3);
                if(alea==0){
                    carte1[a][b]=MurOr;
                    compteur++;
                }
            }

        }
    }
    return compteur;
}

/**
    Bombes crée un Thread (un programme en parallèle du main).
*/
void Bombes(int**carte,SDL_Surface *ecran,int Player){
    pthread_t thread;
    liste.carte1=carte;
    liste.ecran1=ecran;
    if(Player==1)
        pthread_create(&thread,NULL,gestionBombes,(void*)&liste);
    if(Player==2)
        pthread_create(&thread,NULL,gestionBombes2,(void*)&liste);
}

void* gestionBombes(void *arg){
    listearg *args =(listearg*)arg;
    int Dead=0;
    int i=Player1Rect.x;
    int j=Player1Rect.y;
    int **carte1=args->carte1;
    /**
    *Pour empecher le joueur de poser une bombe tant qu'il y est une bombe sur la carte
    */
    for(int a=0;a<15;a++){
        for(int b=0;b<20;b++){
            if(carte1[b][a]==TNT){
                pthread_exit(NULL);
            }
        }
    }
    carte1[i][j]=TNT;
    Sleep(1000);
        if(carte1[i][j]==TNT){
                carte1[i][j]=FeuBombe;
        }
        if(carte1[i][j]==carte1[Player1Rect.x][Player1Rect.y]){
                Dead=2;
        }
        if(carte1[i][j]==carte1[Player2Rect.x][Player2Rect.y]){
                Dead=3;
        }
        if(carte1[i][j+1]==Vide){
                carte1[i][j+1]=BombeBas;
        }
        if(carte1[i][j+1]==MurOr){
                carte1[i][j+1]=Or;
        }
        if(carte1[i][j+1]==carte1[Player1Rect.x][Player1Rect.y]){
                carte1[i][j+1]=BombeBas;
                Dead=2;
        }
        if(carte1[i][j+1]==carte1[Player2Rect.x][Player2Rect.y]){
                carte1[i][j+1]=BombeBas;
                Dead=3;
        }

        if(carte1[i] [j-1]==Vide){
                carte1[i][j-1]=BombeHaut;
        }
        if(carte1[i][j-1]==MurOr){
                carte1[i][j-1]=Or;
        }
        if(carte1[i][j-1]==carte1[Player1Rect.x][Player1Rect.y]){
                carte1[i][j-1]=BombeHaut;
                Dead=2;
        }
        if(carte1[i][j-1]==carte1[Player2Rect.x][Player2Rect.y]){
                carte1[i][j-1]=BombeHaut;
                Dead=3;
        }

        if(carte1[i+1][j]==Vide){
                carte1[i+1][j]=BombeDroite;
            }
        if(carte1[i+1][j]==MurOr){
                carte1[i+1][j]=Or;
            }
        if(carte1[i+1][j]==carte1[Player1Rect.x][Player1Rect.y]){
                carte1[i+1][j]=BombeDroite;
                Dead=2;
            }
        if(carte1[i+1][j]==carte1[Player2Rect.x][Player2Rect.y]){
                carte1[i+1][j]=BombeDroite;
                Dead=3;
            }

        if(carte1[i-1][j]==Vide){
                carte1[i-1][j]=BombeGauche;
            }
        if(carte1[i-1][j]==MurOr){
                carte1[i-1][j]=Or;
            }
        if(carte1[i-1][j]==carte1[Player1Rect.x][Player1Rect.y]){
                carte1[i-1][j]=BombeGauche;
                Dead=2;
            }
        if(carte1[i-1][j]==carte1[Player2Rect.x][Player2Rect.y]){
                carte1[i-1][j]=BombeGauche;
                Dead=3;
        }
        Sleep(500);
        for(j=0;j<15;j++){
            for(i=0;i<20;i++){
                if(carte1[i][j]==TNT){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==BombeBas){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==FeuBombe){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==BombeHaut){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==BombeDroite){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==BombeGauche){
                    carte1[i][j]=Vide;
                }
            }
        }
        if (Dead==2)
            Play=3;
        if  (Dead==3)
            Play=2;
    pthread_exit(NULL);
}
void* gestionBombes2(void *arg){
    listearg *args =(listearg*)arg;
    int i=Player2Rect.x;
    int j=Player2Rect.y;
    int Dead;
    int **carte1=args->carte1;
    for(int a=0;a<15;a++){
        for(int b=0;b<20;b++){
            if(carte1[b][a]==TNT){
                pthread_exit(NULL);
            }
        }
    }
    carte1[i][j]=TNT;
    Sleep(100);
        if(carte1[i][j]==TNT){
                carte1[i][j]=FeuBombe;
            }
        if(carte1[i][j+1]!=Mur){
                carte1[i][j+1]=BombeBas;
            }
        if(carte1[i][j+1]==carte1[Player1Rect.x][Player1Rect.y]){
                carte1[i][j+1]=BombeBas;
                Dead=2;
            }
        if(carte1[i][j+1]==carte1[Player2Rect.x][Player2Rect.y]){
                carte1[i][j+1]=BombeBas;
                Dead=3;
            }

        if(carte1[i][j-1]!=Mur){
                carte1[i][j-1]=BombeHaut;
            }
        if(carte1[i][j-1]==carte1[Player1Rect.x][Player1Rect.y]){
                carte1[i][j-1]=BombeHaut;
                Dead=2;
            }
        if(carte1[i][j-1]==carte1[Player2Rect.x][Player2Rect.y]){
                carte1[i][j-1]=BombeHaut;
                Dead=3;
            }

        if(carte1[i+1][j]!=Mur){
                carte1[i+1][j]=BombeDroite;
            }
        if(carte1[i+1][j]==carte1[Player1Rect.x][Player1Rect.y]){
                carte1[i+1][j]=BombeDroite;
                Dead=2;
            }
        if(carte1[i+1][j]==carte1[Player2Rect.x][Player2Rect.y]){
                carte1[i+1][j]=BombeDroite;
                Dead=3;
            }

        if(carte1[i-1][j]!=Mur){
                carte1[i-1][j]=BombeGauche;
            }
        if(carte1[i-1][j]==carte1[Player1Rect.x][Player1Rect.y]){
                carte1[i-1][j]=BombeGauche;
                Dead=2;
            }
        if(carte1[i-1][j]==carte1[Player2Rect.x][Player2Rect.y]){
                carte1[i-1][j]=BombeGauche;
                Dead=3;
        }
        Sleep(500);
        for(j=0;j<15;j++){
            for(i=0;i<20;i++){
                if(carte1[i][j]==TNT){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==BombeBas){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==FeuBombe){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==BombeHaut){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==BombeDroite){
                    carte1[i][j]=Vide;
                }
                if(carte1[i][j]==BombeGauche){
                    carte1[i][j]=Vide;
                }
        }
    }
    if (Dead==2)
            Play=3;
    if  (Dead==3)
            Play=2;
    pthread_exit(NULL);
}
/*FILE *fichier;
    fichier = fopen("src/carte1.txt","r");
    if (fichier != NULL)
    {
        for(i=0;i<20;i++)
            for(i=0;i<20;i++)
                fscanf(fichier,"%d\n",((carte+i)+j));
        fclose(fichier);
    }
**/

void Ennemy(SDL_Surface *ecran){
    int **carte=carte();
    int i,j;

    SDL_Surface *BombUp=NULL;
    SDL_Surface *BombDown=NULL;
    SDL_Surface *BombRight=NULL;
    SDL_Surface *BombLeft=NULL;
    SDL_Surface *BombBox=NULL;
    SDL_Surface *BombBlast=NULL;

    SDL_Surface *LingotOr=NULL;
    SDL_Surface *Brike=NULL;
    SDL_Surface *Terre=NULL;
    SDL_Surface *Playerwins=NULL;
    SDL_Surface *gameover=NULL;

    Player1Rect.x=7;
    Player1Rect.y=1;

    Player2Rect.x=6;
    Player2Rect.y=1;

    LingotOr=IMG_Load("src/Gold.png");
    Terre=IMG_Load("src/Ground.jpg");
    Brike=IMG_Load("src/Wall.jpg");

    BombUp=IMG_Load("src/BombUp.png");
    BombDown=IMG_Load("src/BombDown.png");
    BombRight=IMG_Load("src/BombRight.png");
    BombLeft=IMG_Load("src/BombLeft.png");
    BombBlast=IMG_Load("src/BombBlast.png");
    BombBox=IMG_Load("src/Bomb.png");

    SDL_Surface *Ennemies[4]={NULL};
    SDL_Surface *EnnemyNow=NULL;
    SDL_Surface *Player[4]={NULL};
    SDL_Surface *PlayerNow=NULL;
    SDL_Event event;

    Player[Up]=IMG_Load("src/Up.png");
    Player[Down]=IMG_Load("src/Down.png");
    Player[Right]=IMG_Load("src/Right.png");
    Player[Left]=IMG_Load("src/Left.png");
    PlayerNow=Player[Up];

    Ennemies[Up]=IMG_Load("src/EnnemyUp.png");
    Ennemies[Down]=IMG_Load("src/EnnemyDown.png");
    Ennemies[Right]=IMG_Load("src/EnnemyRight.png");
    Ennemies[Left]=IMG_Load("src/EnnemyLeft.png");
    EnnemyNow=Ennemies [Up];

    Playerwins=IMG_Load("src/Player1.png");
    gameover=IMG_Load("GAME OVER.png");

    nbOr=placementOr(carte);

    TTF_Init();
    font=TTF_OpenFont("data/font.ttf",26);

    while(Play==1)
    {
    MouvementEnnemy(carte,ecran);
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            Play=0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_UP:
                        PlayerNow=Player[Up];
                        Deplacement(carte,&Player1Rect,Up,&scorePlayer1);
                        break;
                case SDLK_DOWN:
                        PlayerNow=Player[Down];
                        Deplacement(carte,&Player1Rect,Down,&scorePlayer1);
                        break;
                case SDLK_RIGHT:
                        PlayerNow=Player[Right];
                        Deplacement(carte,&Player1Rect,Right,&scorePlayer1);
                        break;
                case SDLK_LEFT:
                        PlayerNow=Player[Left];
                        Deplacement(carte,&Player1Rect,Left,&scorePlayer1);
                        break;
                case SDLK_SPACE:
                        Bombes(carte,ecran,1);
                        break;
                case SDLK_ESCAPE:
                        Play=0;
                        break;
                default:
                        break;
            }
    }

    for (int i=0;i<LargeurFenetre/SizeBloc;i++){
            for(int j=0;j<HauteurFenetre/SizeBloc;j++){
                BlocRect.x=i*SizeBloc;
                BlocRect.y=j*SizeBloc;
                switch (carte[i][j]){
                    case Mur:
                        SDL_BlitSurface(Brike,NULL,ecran,&BlocRect);
                        break;
                    case Vide:
                        SDL_BlitSurface(Terre,NULL,ecran,&BlocRect);
                        break;
                    case TNT:
                        SDL_BlitSurface(BombBox,NULL,ecran,&BlocRect);
                        break;
                    case FeuBombe:
                        SDL_BlitSurface(BombBlast,NULL,ecran,&BlocRect);
                        break;
                    case BombeHaut:
                        SDL_BlitSurface(BombUp,NULL,ecran,&BlocRect);
                        break;
                    case BombeBas:
                        SDL_BlitSurface(BombDown,NULL,ecran,&BlocRect);
                        break;
                    case BombeDroite:
                        SDL_BlitSurface(BombRight,NULL,ecran,&BlocRect);
                        break;
                    case BombeGauche:
                        SDL_BlitSurface(BombLeft,NULL,ecran,&BlocRect);
                        break;
                    case MurOr:
                        SDL_BlitSurface(Brike,NULL,ecran,&BlocRect);
                        break;
                    case Or:
                        SDL_BlitSurface(LingotOr,NULL,ecran,&BlocRect);
                        break;
                    case EnnemiBas:
                        EnnemyNow=Ennemies[Down];
                        break;
                    case EnnemiHaut:
                        EnnemyNow=Ennemies[Up];
                        break;
                    case EnnemiDroite:
                        EnnemyNow=Ennemies[Right];
                        break;
                    case EnnemiGauche:
                        EnnemyNow=Ennemies[Left];
                        break;
                    default:
                        break;
                }
            }
    }
        Rect1.x = Player1Rect.x * SizeBloc;
        Rect1.y = Player1Rect.y * SizeBloc;
        Rect2.x = Player2Rect.x * SizeBloc;
        Rect2.y = Player2Rect.y * SizeBloc;
    SDL_BlitSurface(PlayerNow,NULL,ecran,&Rect1);
    SDL_BlitSurface(EnnemyNow,NULL,ecran,&Rect2);

    BlocRect.x=300;
    BlocRect.y=3;
    sprintf(score,"%d: Gold Ingot",nbOr);
    text=TTF_RenderText_Blended(font,score,Green);
    sprintf(score,"%d: PLAYER 1",scorePlayer1);
    ScorePlayer1=TTF_RenderText_Blended(font,score,Blue);
    sprintf(score,"%d: PLAYER 2",nbOr);
    ScorePlayer2=TTF_RenderText_Blended(font,score,Green);
    SDL_BlitSurface(text,NULL,ecran,&BlocRect);

    BlocRect.x=5;
    BlocRect.y=570;
    SDL_BlitSurface(ScorePlayer1,NULL,ecran,&BlocRect);
    BlocRect.x=560;
    BlocRect.y=570;
    SDL_BlitSurface(ScorePlayer2,NULL,ecran,&BlocRect);
    SDL_Flip(ecran);

    Sleep(100);
    for (int i=0;i<20;i++){
        for(int j=0;j<15;j++){
            if(carte[i][j]==EnnemiBas)
                carte[i][j]=Vide;
            if(carte[i][j]==EnnemiHaut)
                carte[i][j]=Vide;
            if(carte[i][j]==EnnemiDroite)
                carte[i][j]=Vide;
            if(carte[i][j]==EnnemiGauche)
                carte[i][j]=Vide;
        }
    }
    }
    RectMenu.x=0;
    RectMenu.y=0;
    if(Play==2){
        SDL_BlitSurface(Playerwins,NULL,ecran,&RectMenu);
        SDL_Flip(ecran);
        Sleep(10);
        Play=0;
    }
    if(Play==3){
        SDL_BlitSurface(gameover,NULL,ecran,&RectMenu);
        SDL_Flip(ecran);
        Sleep(10);
        Play=0;
    }
    SDL_FreeSurface(ScorePlayer1);
    SDL_FreeSurface(ScorePlayer2);
    SDL_FreeSurface(text);
    SDL_FreeSurface(BombBlast);
    SDL_FreeSurface(BombBox);
    SDL_FreeSurface(BombDown);
    SDL_FreeSurface(BombUp);
    SDL_FreeSurface(BombRight);
    SDL_FreeSurface(BombLeft);
    SDL_FreeSurface(Terre);
    SDL_FreeSurface(Brike);
    SDL_FreeSurface(LingotOr);
    SDL_FreeSurface(gameover);
    SDL_FreeSurface(Playerwins);
    for(int i=0;i<4;i++){
        SDL_FreeSurface(Ennemies[i]);
        SDL_FreeSurface(Player[i]);

    }
}
void MouvementEnnemy(int**carte,SDL_Surface *ecran){
    pthread_t thread;
    liste.carte1=carte;
    liste.ecran1=ecran;
    pthread_create(&thread,NULL,gestionMouvementEnnemy,(void*)&liste);
}
void* gestionMouvementEnnemy(void *arg){
    listearg *args =(listearg*)arg;
    int **carte1=args->carte1;
    int nbr =0;
    srand(time(NULL));
    nbr=rand() % 4 ;
    switch (nbr){
    case Up :
          if(carte1[Player2Rect.x][Player2Rect.y+1]==Vide){
                Player2Rect.y++ ;
                carte1[Player2Rect.x][Player2Rect.y]=EnnemiHaut;
          }
          if(carte1 [Player2Rect.x][Player2Rect.y+1]==MurOr){
                    Player2Rect.y-=2;
                    carte1 [Player2Rect.x][Player2Rect.y]=Or;
                    Player2Rect.y+=3;
                    nbOr--;
              }
           break ;
    case Down :
          if(carte1 [Player2Rect.x][Player2Rect.y-1]==Vide){
                Player2Rect.y-- ;
                carte1 [Player2Rect.x][Player2Rect.y]=EnnemiBas;
          }
          if(carte1 [Player2Rect.x][Player2Rect.y-1]==MurOr){
                    Player2Rect.y+=2;
                    carte1 [Player2Rect.x][Player2Rect.y]=Or;
                    Player2Rect.y-=3;
                    nbOr--;
              }
          break ;
    case Right  :
          if(Player2Rect.x +1!=20){
              if(carte1 [Player2Rect.x +1][Player2Rect.y]==Vide){
                    Player2Rect.x++ ;
                    carte1 [Player2Rect.x][Player2Rect.y]=EnnemiDroite;
              }
              if(carte1 [Player2Rect.x+1][Player2Rect.y]==MurOr){
                    Player2Rect.x-=2;
                    carte1 [Player2Rect.x][Player2Rect.y]=Or;
                    Player2Rect.x+=3;
                    nbOr--;
              }
          }
          break ;
    case Left :
          if(Player2Rect.x-1){
              if(carte1 [Player2Rect.x-1][Player2Rect.y]==Vide){
                    Player2Rect.x-- ;
                    carte1 [Player2Rect.x][Player2Rect.y]=EnnemiGauche;
              }
              if(carte1 [Player2Rect.x-1][Player2Rect.y]==MurOr){
                    Player2Rect.x+=2;
                    carte1 [Player2Rect.x][Player2Rect.y]=Or;
                    Player2Rect.x-=3;
                    nbOr--;
              }
          }
          break;
    }

    if(Player2Rect.x+1==Player1Rect.x&&Player2Rect.y==Player1Rect.y||
       Player2Rect.x-1==Player1Rect.x&&Player2Rect.y==Player1Rect.y||
       Player2Rect.x==Player1Rect.x&&Player2Rect.y-1==Player1Rect.y||
       Player2Rect.x==Player1Rect.x&&Player2Rect.y+1==Player1Rect.y){
        Bombes(carte1,args->ecran1,2);
    }
}

