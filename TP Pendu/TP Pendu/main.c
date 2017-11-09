/*BUT:L'utilisateur doit devin� le mot cach� en cherchant lettre par lettre et en faisant le moins de fautes possibles
//ENTREE:1 caractere
//SORTIE:joueur gagne ou non*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#define MOT "rachid"


//Prototype
void afficherPresentation();
void initmotTrouver(char[255],int);
void remplacemotTrouver(int,int*,char,char[strlen(MOT)],HANDLE);
int testLettre(char, char[255]);


int main()
{
        int tailleMot=strlen(MOT),i=0,erreur=3,cpt=0,test=0;
        char motTrouver[strlen(MOT)], lettreTester[255],lettre;

        //construit le tableau de caractere correctement pour �viter des erreurs
        motTrouver[tailleMot]='\0';

        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);   //cr�ation de la fen�tre
        SetConsoleTextAttribute(H,3);   //Couleur du texte turquoise

        //init du tableau de caractere motTrouver
        initmotTrouver(motTrouver,tailleMot);

        //PARTIE PRESENTATION DU JEU A L'UTILISATEUR
        afficherPresentation();

        SetConsoleTextAttribute(H,15);  //Couleur blanche

        printf("Le mot fait %d caractere :\n",tailleMot);

        //d�but de boucle de jeu
        do{

                do{
                        //demande � l'utilisateur d'entrer une lettre
                        SetConsoleTextAttribute(H,8);//couleur gris
                        puts("\nEntrez un caractere: ");
                        SetConsoleTextAttribute(H,15);//Couleur blanche
                        printf("- ");

                        /* Le buffer n'est pas vider au moment de la boucle donc elle fait
                        2 fois la boucle au lieu d'une (elle saute le getchar())
                        fflush n'a pas fonctionner */
                        do {
                                lettre=tolower(getchar());
                        }while (lettre == '\n');

                        //test de la lettre si elle a deja ete tapper
                        test=testLettre(lettre,lettreTester);

                        SetConsoleTextAttribute(H,12);//couleur rouge

                        if (test) {     //si le caractere � deja ete tapper
                                        printf("Le caractere '%c' a deja ete tapper !\n",lettre);
                                        erreur--;
                                        printf("Il vous rester %d chance(s)\n",erreur);
                        }

                        SetConsoleTextAttribute(H,15);//Couleur blanche

                }while ((test) && (erreur));

                if (erreur>0){
                        lettreTester[cpt]=lettre;
                        lettreTester[cpt+1]='\0';       //on indique la fin de la chaine avec un compteur
                        cpt++;

                        //verification de la lettre avec le mot + nbr erreur
                        remplacemotTrouver(tailleMot,&erreur,lettre,motTrouver,H);
                        printf("\n");

                        //affiche le mot trouver (ex: R _ C _ _ _ )
                        for (i=0;i<=tailleMot;i++){
                                printf("%c ",motTrouver[i]);
                        }
                        printf("\n");
                }

        }while((strcmp(motTrouver,MOT)) && (erreur>0));
        //fin de boucle de jeu

        //affiche a l'utilisateur si il a gagner ou perdu
        if (!erreur)
                printf("Le mot etais '%s', vous ferez mieux la prochaine fois !\n",MOT);
        else{
                printf("Le mot est bien '%s', bravo !\n",MOT);
                printf("Il vous rester %d chance(s)\n",erreur);
        }

    system("pause"); //en attente d'une touche de l'utilisateur

    return 0;
}

/*BUT:Affiche un texte � l'utilisateur
//ENTREE:
//SORTIE:texte afficher*/
void afficherPresentation(){
        //PARTIE PRESENTATION DU JEU A L'UTILISATEUR
        puts("Bonjour et bienvenue dans le jeu du pendu !");
        puts("Le but est de trouver le mot cacher en indiquant le caractere");
        puts("et en se trompant un minimum de fois,");
        puts("en sachant que le nombre d''erreur maximum est 3");
}


/*BUT:Initialise la valeur d'une chaine
//ENTREE:1 chaine 1 entier
//SORTIE:1 chaine*/
void initmotTrouver(char motTrouver[255], int tailleMot){
        int i=0;

        for (i=0;i<=tailleMot-1;i++){
                motTrouver[i]='_';
        }
}


/*BUT:Verifie si la lettre existe ou non et remplace la variable
//ENTREE:2 entier, 1 caractere 1 chaine
//SORTIE:*/
void remplacemotTrouver(int tailleMot,int* erreur,char lettre,char motTrouver[strlen(MOT)], HANDLE H){
        int i,test=0;

        for (i=0;i<=tailleMot-1;i++){
                if(lettre==MOT[i]){
                        motTrouver[i]=lettre;
                        SetConsoleTextAttribute(H,2);//couleur vert foncer
                        printf("Trouver !\n");
                        SetConsoleTextAttribute(H,15);//Couleur blanche
                        test=1;
                }
        }

        if (!test) {
                *erreur=*erreur-1;
                SetConsoleTextAttribute(H,12);//couleur rouge

                printf("Le caractere '%c' n'est pas dans le mot\n",lettre);

                if (*erreur>0)
                        printf("Il vous reste %d chance(s) de trouver le mot\n",*erreur);
                else
                        printf("C'etais votre derniere chance !\n");

                SetConsoleTextAttribute(H,15);//Couleur blanche
        }
}


/*BUT:verifie si un caractere existe dans une chaine
//ENTREE:1 caractere 1 chaine
//SORTIE:1 booleen*/
int testLettre(char lettre, char lettreTester[255]){
        int i=0,test=0;

        for (i=0;i<=strlen(lettreTester);i++){
                if (lettreTester[i]==lettre)
                        test=1;
        }

        return test;
}
