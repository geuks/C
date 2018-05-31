#include "list.h"

void initialisation (Liste * liste)
{
        liste->debut = NULL;
        liste->fin = NULL;
        liste->taille = 0;
}

//insertion dans une liste vide
int insListeVide (Liste * liste, Point donnee){
        Element *nouveau_element;

        if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
                return -1;
        /*if ((nouveau_element->donnee = (char *) malloc (50 * sizeof (char)))== NULL)
                return -1;

        strcpy (nouveau_element->donnee, donnee);*/

        nouveau_element->donnees=donnee;
        nouveau_element->suivant = NULL;
        liste->debut = nouveau_element;
        liste->fin = nouveau_element;
        liste->taille++;

        return 0;
}

//insertion au début de la liste
int insDebutListe (Liste * liste, Point donnee){
        Element *nouveau_element;

        if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
                return -1;

        nouveau_element->donnees=donnee;
        nouveau_element->suivant = liste->debut;
        liste->debut = nouveau_element;
        liste->taille++;

        return 0;
}

//insertion à la fin de la liste
int insFinListe (Liste * liste, Element * courant, Point donnee){
        Element *nouveau_element;
        if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
                return -1;

        nouveau_element->donnees=donnee;
        courant->suivant = nouveau_element;
        nouveau_element->suivant = NULL;
        liste->fin = nouveau_element;
        liste->taille++;

        return 0;
}

//insertion à la position demandée
int insListe (Liste * liste, Point donnee, int pos){
        int i;
        if (liste->taille < 2)
                return -1;
        if (pos < 1 || pos >= liste->taille)
                return -1;

        Element *courant;
        Element *nouveau_element;

        if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
                return -1;

        courant = liste->debut;
        for (i = 1; i < pos; ++i)
                courant = courant->suivant;

        if (courant->suivant == NULL)
                return -1;

        nouveau_element->donnees=donnee;
        nouveau_element->suivant = courant->suivant;
        courant->suivant = nouveau_element;
        liste->taille++;

        return 0;
}

//suppression au début de la liste
        int suppDebut (Liste * liste){

        if (liste->taille == 0)
                return -1;

        Element *supp_element;
        supp_element = liste->debut;
        liste->debut = liste->debut->suivant;

        if (liste->taille == 1)
                liste->fin = NULL;

        free (supp_element);
        liste->taille--;

        return 0;
}

//supprimer un element après la position demandée
int suppDansListe (Liste * liste, int pos){
        int i;

        if (liste->taille <= 1 || pos < 1 || pos >= liste->taille)
                return -1;

        Element *courant;
        Element *supp_element;
        courant = liste->debut;

        for (i = 1; i < pos; ++i)
                courant = courant->suivant;

        supp_element = courant->suivant;
        courant->suivant = courant->suivant->suivant;

        if(courant->suivant == NULL)
                liste->fin = courant;

        free (supp_element);
        liste->taille--;

        return 0;
}

//affichage de la liste
void affiche (Liste * liste){
        Element *courant;
        courant = liste->debut;

        while (courant != NULL){
                printf ("%p - %d, %d, %d\n", courant, courant->donnees.x, courant->donnees.y ,courant->donnees.z);
                courant = courant->suivant;
        }
}

//detruire la liste
void detruire (Liste * liste){
        while (liste->taille > 0)
                suppDebut (liste);
}

int menu (Liste *liste,int *k){
        int choix;

        printf("********** MENU **********\n");

        if (liste->taille == 0){
                printf ("1. Ajout du 1er element\n");
                printf ("2. Quitter\n");
        }else if(liste->taille == 1 || *k == 1){
                printf ("1. Ajout au debut de la liste\n");
                printf ("2. Ajout a la fin de la liste\n");
                printf ("4. Suppression au debut de la liste\n");
                printf ("6. Detruire la liste\n");
                printf ("7. Quitter\n");
        }else {
                printf ("1. Ajout au debut de la liste\n");
                printf ("2. Ajout a la fin de la liste\n");
                printf ("3. Ajout apres la position specifie\n");
                printf ("4. Suppression au debut de la liste\n");
                printf ("5. Suppression apres la position specifie\n");
                printf ("6. Detruire la liste\n");
                printf ("7. Quitter\n");
        }
        printf ("\n\nFaites votre choix : ");
        scanf ("%d", &choix);

        getchar();

        if(liste->taille == 0 && choix == 2)
                choix = 7;
        return choix;
}
/* -------- FIN liste_function.h --------- */
