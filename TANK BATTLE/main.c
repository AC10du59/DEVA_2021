#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "jeu.h"


int main(int argc,char* argv[]){
    SDL_Surface *ecran=NULL;
    SDL_Surface *Menu=NULL;

    SDL_Rect MenuRect={0,0,LargeurFenetre,HauteurFenetre};
    if (SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_GetError();
    }

    ecran=SDL_SetVideoMode(LargeurFenetre,HauteurFenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("TANK BATTLE",NULL);

    Menu =IMG_Load("src/TANK BATTLE.bmp");
    SDL_Surface *About=NULL;
    About=IMG_Load("src/About.png");
    int Play=1,wait;
    SDL_Event event;
    while(Play){
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_QUIT:
                Play=0;
                break;
            case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_1:
                            ModeMenu(ecran);
                            break;
                        case SDLK_2:
                            SDL_BlitSurface(About,NULL,ecran,&MenuRect);
                            SDL_Flip(ecran);
                            SDL_Event event;
                            wait=1;
                            while(wait){
                                SDL_WaitEvent(&event);
                                switch (event.type){
                                    case SDL_QUIT:
                                        Play=0;
                                        break;
                                    case SDL_KEYDOWN:
                                            switch(event.key.keysym.sym){
                                                case SDLK_ESCAPE:
                                                    wait=0;
                                                    break;
                                                default:
                                                    break;
                                            }
                                }
                            }
                            break;
                        case SDLK_ESCAPE:
                            Play=0;
                            break;
                        default:
                            break;
                    }
        }
        SDL_BlitSurface(Menu,NULL,ecran,&MenuRect);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(Menu);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(About);
    SDL_Quit();
    return EXIT_SUCCESS;

}
