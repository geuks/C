#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 20       //taille pour les chaines
#define MIN0 0
#define MIN1 1

typedef struct ddn{
        int j,m,a;
}ddn;

typedef struct cid{
        int NumeroCarte;
        char *Nom,*Prenom,*Ville, Sexe;
        ddn Naissance;
}cid;

//PROTOTYPES
void getPresentation();
void setCarteIdentite(cid *);
void setFile(FILE *, cid *);
void getFile(FILE *,cid *);


int main()
{
        cid *carteIdentite=NULL;
        FILE *pFile = NULL;
        int choix;
        //allocation de memoire pour chaque pointeur
        carteIdentite = malloc(sizeof(cid));
        carteIdentite->Nom = malloc(TAILLE*sizeof(char*));
        carteIdentite->Prenom = malloc(TAILLE*sizeof(char*));
        carteIdentite->Ville = malloc(TAILLE*sizeof(char*));

        //affiche la pr�sentation
        getPresentation();
        //recup�re le choix de l'utilisateur
        scanf("%d",&choix);
        switch (choix){
                case 1:
                                setCarteIdentite(carteIdentite);
                                setFile(pFile,carteIdentite);
                        break;
                case 2:
                                getFile(pFile,carteIdentite);
                        break;
        }

        //on lib�re la m�moire
        free(carteIdentite->Nom);
        free(carteIdentite->Prenom);
        free(carteIdentite->Ville);
        free(carteIdentite);

        return 0;
}


void getFile(FILE *pFile, cid *carteIdentite){
        cid *tmpCarteIdentite = NULL;
        long lSize;
        int i,nbrElem=MIN0;

        //on ouvre le fichier
        pFile = fopen ("CarteIdentite.bin","rb");
        if (pFile==NULL){       //si il est vide
                printf("Aucun fichier existant.");
        }else{ //sinon s'il n'ai pas vide

                //lSize=sizeof(pFile);
                fseek(pFile ,0,SEEK_END);
                lSize=ftell(pFile);
                rewind(pFile);
                //nbrElem=lSize/sizeof(cid);

                tmpCarteIdentite = malloc(sizeof(cid));

                tmpCarteIdentite->Nom = calloc(TAILLE,sizeof(char));
                tmpCarteIdentite->Prenom = calloc(TAILLE,sizeof(char));
                tmpCarteIdentite->Ville = calloc(TAILLE,sizeof(char));

                fread(tmpCarteIdentite,sizeof(cid),MIN1,pFile);
                //while(fread(tmpCarteIdentite,sizeof(cid),MIN1,pFile)==1)

                printf("Numero: %d\n",tmpCarteIdentite->NumeroCarte);
                printf("Sexe: %c\n",tmpCarteIdentite->Sexe);
                printf("Nom: %s\n",tmpCarteIdentite->Nom);
                printf("Prenom: %s\n",tmpCarteIdentite->Prenom);
                printf("DDN: %d-%d-%d\n",tmpCarteIdentite->Naissance.j,tmpCarteIdentite->Naissance.m,tmpCarteIdentite->Naissance.a);
                printf("VDN: %s\n\n",tmpCarteIdentite->Ville);

                /*
                for(i=MIN0;i<nbrElem;i++){
                        printf("Numero: %d\n",tmpCarteIdentite[i].NumeroCarte);
                        printf("Sexe: %c\n",tmpCarteIdentite[i].Sexe);
                        printf("Nom: %s\n",tmpCarteIdentite[i].Nom);
                        printf("Prenom: %s\n",tmpCarteIdentite[i].Prenom);
                        printf("DDN: %d-%d-%d\n",tmpCarteIdentite[i].Naissance.j,tmpCarteIdentite[i].Naissance.m,tmpCarteIdentite[i].Naissance.a);
                        printf("VDN: %s\n\n",tmpCarteIdentite[i].Ville);
                }
                */
                fclose (pFile);
        }

        //on lib�re la m�moire
        free(tmpCarteIdentite->Nom);
        free(tmpCarteIdentite->Prenom);
        free(tmpCarteIdentite->Ville);
        free(tmpCarteIdentite);
}


void setFile(FILE *pFile, cid *carteIdentite){
        size_t test;
        //on ouvre le fichier en mode lecture
        pFile = fopen ("CarteIdentite.bin","ab");
        if (pFile==NULL){       //si la variable est vide
                //alors on change le mode et on cr�er le fichier
                printf("Erreur aucun fichier trouver!");
        }
        else
        {
                //fwrite (carteIdentite, sizeof(cid),sizeof(carteIdentite), pFile);
                fwrite(carteIdentite, sizeof(cid), sizeof(carteIdentite), pFile);
                fclose (pFile); //on ferme le fichier
        }
}


void setCarteIdentite(cid *carteIdentite){
        //on alloue et cr�e les m�moires aux pointeurs
        char *nom = malloc(TAILLE*sizeof(char));
        char *prenom = malloc(TAILLE*sizeof(char));
        char *ville = malloc(TAILLE*sizeof(char));

        printf("Entrez votre numero de CI.\n");
        printf("- ");
        scanf("%d",&carteIdentite -> NumeroCarte);
        fflush(stdin);

        printf("Entrez votre sexe F ou M.\n");
        printf("- ");
        scanf("%c",&carteIdentite -> Sexe);
        fflush(stdin);

        printf("Entrez votre nom.\n");
        printf("- ");
        scanf("%s", nom);
        strcpy(carteIdentite->Nom,nom);
        fflush(stdin);

        printf("Entrez votre prenom.\n");
        printf("- ");
        scanf("%s", prenom);
        strcpy(carteIdentite->Prenom,prenom);
        fflush(stdin);

        printf("Entrez votre date de naissance 'JJ MM AAAA'.\n");
        printf("- ");
        scanf("%d%d%d",&carteIdentite -> Naissance.j,&carteIdentite -> Naissance.m,&carteIdentite -> Naissance.a);
        fflush(stdin);

        printf("Entrez votre ville de naissance.\n");
        printf("- ");
        scanf("%s", ville);
        strcpy(carteIdentite->Ville,ville);
        fflush(stdin);

        //on vide la m�moire
        free(nom);
        free(prenom);
        free(ville);
}


void getPresentation(){
        printf("Bonjour et bienvenue dans notre systeme d'enregistrement de carte d'identite.\n");
        printf("Entrez l'option choisis.\n");
        printf("1 - Ajouter une fiche de CI.\n");
        printf("2 - Parcourir le fichier et l'afficher.\n");
        printf("- ");
}
