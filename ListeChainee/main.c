#include "list.h"
int main (void){
        char choix;
        Point nom;
        Liste *liste;

        if ((liste = (Liste *) malloc (sizeof (Liste))) == NULL)
                return -1;

        choix = 'o';
        initialisation (liste);
        int pos, k;

        while (choix != 7){
                choix = menu (liste, &k);

                switch (choix){
                        case 1:
                                printf ("Entrez un element x: ");
                                scanf ("%d", &nom.x);
                                printf ("Entrez un element y: ");
                                scanf ("%d", &nom.y);
                                printf ("Entrez un element z: ");
                                scanf ("%d", &nom.z);

                                if (liste->taille == 0)
                                        insListeVide(liste, nom);
                                else
                                        insDebutListe (liste, nom);

                                printf ("%d elements:deb=%d, %d, %d ,fin=%d, %d, %d\n", liste->taille,
                                liste->debut->donnees.x, liste->debut->donnees.y, liste->debut->donnees.z,
                                liste->fin->donnees.x, liste->fin->donnees.y, liste->fin->donnees.z);
                                affiche (liste);
                        break;

                        case 2:
                                printf ("Entrez un element x: ");
                                scanf ("%d", &nom.x);
                                printf ("Entrez un element y: ");
                                scanf ("%d", &nom.y);
                                printf ("Entrez un element z: ");
                                scanf ("%d", &nom.z);

                                insFinListe (liste, liste->fin, nom);
                                printf ("%d elements:deb=%d, %d, %d ,fin=%d, %d, %d\n", liste->taille,
                                liste->debut->donnees.x, liste->debut->donnees.y, liste->debut->donnees.z,
                                liste->fin->donnees.x, liste->fin->donnees.y, liste->fin->donnees.z);
                                affiche (liste);
                        break;

                        case 3:
                                printf ("Entrez un element x: ");
                                scanf ("%d", &nom.x);
                                printf ("Entrez un element y: ");
                                scanf ("%d", &nom.y);
                                printf ("Entrez un element z: ");
                                scanf ("%d", &nom.z);

                                do{
                                        printf ("Entrez la position : ");
                                        scanf ("%d", &pos);
                                }

                                while (pos < 1 || pos > liste->taille);
                                        getchar ();

                                if (liste->taille == 1 || pos == liste->taille){
                                        k = 1;
                                        printf("-----------------------------------------------\n");
                                        printf("Insertion echouée.Utilisez le menu {1|2} \n");
                                        printf("-----------------------------------------------\n");
                                        break;
                                }
                                insListe (liste, nom, pos);
                                printf ("%d elements:deb=%d, %d, %d ,fin=%d, %d, %d\n", liste->taille,
                                liste->debut->donnees.x, liste->debut->donnees.y, liste->debut->donnees.z,
                                liste->fin->donnees.x, liste->fin->donnees.y, liste->fin->donnees.z);
                                affiche (liste);
                        break;

                        case 4:
                                suppDebut (liste);
                                if (liste->taille != 0){
                                        printf ("%d elements:deb=%d, %d, %d ,fin=%d, %d, %d\n", liste->taille,
                                        liste->debut->donnees.x, liste->debut->donnees.y, liste->debut->donnees.z,
                                        liste->fin->donnees.x, liste->fin->donnees.y, liste->fin->donnees.z);
                                }
                                else
                                        printf ("liste vide\n");
                                affiche (liste);
                        break;

                        case 5:
                                do{
                                        printf ("Entrez la position : ");
                                        scanf ("%d", &pos);
                                }while (pos < 1 || pos > liste->taille);

                                getchar ();
                                suppDansListe (liste, pos);

                                if (liste->taille != 0){
                                        printf ("%d elements:deb=%d, %d, %d ,fin=%d, %d, %d\n", liste->taille,
                                        liste->debut->donnees.x, liste->debut->donnees.y, liste->debut->donnees.z,
                                        liste->fin->donnees.x, liste->fin->donnees.y, liste->fin->donnees.z);
                                }
                                else
                                        printf ("liste vide\n");
                                affiche (liste);
                        break;

                        case 6:
                                detruire (liste);
                                printf ("la liste a ete detruite : %d elements\n", liste->taille);
                        break;
                }
        }
        return 0;
}
