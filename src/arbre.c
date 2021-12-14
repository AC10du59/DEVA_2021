#include <stdio.h>
#include <stdlib.h> 

/*------------------------------ARBRE--------------------------*/ 

typedef struct Arbre 
{
int cle ; 
struct Arbre *gauche ; 
struct Arbre *droite ; 
struct Arbre *parent ; 
	} Arbre ; 

typedef struct noeud
{
int a ; 
struct Noeud *gauche ; 
struct Noeud *droite ; 
	} Noeud ; 

Noeud *Arbre = NULL ; 

void ajouterNoeud(Noeud **Arbre,  int cle)
{
    Noeud *tmpNoeud;
    Noeud *tmpArbre = *Arbre;

    Noeud *elem = malloc(sizeof(Noeud));
    elem->cle = cle;
    elem->gauche = NULL;
    elem->droite = NULL;

    if(tmpArbre)
    do
    {
        tmpNoeud = tmpArbre;
        if(cle > tmpArbre->cle )
        {
            tmpArbre = tmpArbre >gauche;
            if(!tmpArbre) tmpNoeud->droite = elem;
        }
        else
        {
            tmpArbre = tmpArbre->droite;
            if(!tmpArbre) tmpNoeud->gauche = elem;
        }
    }
    while(tmpArbre);
    else  *Arbre = elem;
}


int chercherNoeud(Noeud *Arbre, int cle)
{
    while(Arbre)
    {
        if(cle == Arbre->cle) return 1;

        if(cle > Arbre->cle ) Arbre = Arbre->droite;
        else Arbre = Arbre->gauche;
    }
    return 0;
}




