#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Point{
        int x,y,z;
}Point;

typedef struct ElementListe
{
        Point donnees;
        struct ElementListe *suivant;
} Element;

typedef struct ListeRepere
{
        Element *debut;
        Element *fin;
        int taille;
} Liste;

//initialisation de la liste
extern void initialisation (Liste * liste);

/* INSERTION
insertion dans une liste vide */
extern int insListeVide (Liste * liste, Point donnee);
//insertion au début de la liste */
extern int insDebutListe (Liste * liste, Point donnee);
//nsertion Ã a fin de la liste */
extern int insFinListe (Liste * liste, Element * courant, Point donnee);
//insertition ailleurs */
extern int insListe (Liste * liste, Point donnee, int pos);
//SUPPRESSION
extern int suppDebut (Liste * liste);
extern int suppDansListe (Liste * liste, int pos);
extern int menu (Liste *liste,int *k);
extern void affiche (Liste * liste);
extern void detruire (Liste * liste);
/* -------- FIN liste.h --------- */
#endif // LIST_H_INCLUDED
