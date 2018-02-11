/* ***************************BUT****PRINCIPAL*************************************
	*
	 *_CREATEUR:UNALAN Gökhan
	 *
	 *_____POUR:Ludus Academie école de jeu vidéo
	 *
	 *______BUT:Le jeu du serpent, pour deplacer le serpent utilisez les touches flechés. Ramassez les pommes et former le plus grand serpent !
	 *
	 *___ENTREE:Utiliser les touches fléchés du clavier
	 *
	 *___SORTIE:Le serpent se déplace, et vous gagner ou perdu la partie
	 *
	*
***********************************************************************************/
#include "snake.h"

int main(int arc, char *argv[])
{
        //int nbrModeScreen;
        //SDL_DisplayMode displayMode;
        int screenHeight,screenWidth;
        SDL_Rect fondMenu, snakeRect[NBRLIGNES*NBRLIGNES],pommeRect,fondScore;
        Pos lignes[NBRLIGNES*NBRLIGNES];
        int statut = EXIT_FAILURE;
        int score=MIN0;
        int test=MIN0;
        Game *jeu;

        jeu = malloc(sizeof(Game));

        //init des sdls
        test=initSDL();
        if (test){
                //init du jeu
                jeu = initJeu();
                //recupere la taille de l'écran
                SDL_GetWindowSize(jeu -> screen, &screenWidth, &screenHeight);
                //init des tableaux et rect
                initAllRect(snakeRect,&fondMenu,&pommeRect,&fondScore,screenHeight, screenWidth);
                initTab(lignes,fondMenu);
                //init du random
                srand(time(NULL));
                //On lance la musique
                Mix_PlayMusic(jeu -> musique, -MIN1);
                //procedure du jeu
                boucleJeu(jeu,&score,lignes,&pommeRect,snakeRect,fondMenu,fondScore);
                statut = EXIT_SUCCESS;
                printf("Programme fonctionnel!\n");
        }
        freeAll(jeu);

        system("pause");
        return statut;
}
//***************************FIN****PRINCIPAL***************************************


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:Boucle du jeu
	 *__ENTREE:1 type Game, 1 pointeur d'entier, 1 tableau de type Pos, 3 SDL_Rect
	 *__SORTIE:
***********************************************************************************/
void boucleJeu(Game *jeu,int *score, Pos lignes[], SDL_Rect *pommeRect, SDL_Rect *snakeRect, SDL_Rect fondMenu, SDL_Rect fondScore){
        int i;
        int tempsActuel=MIN0,tempsPrecedent=MIN0;
        int tempsActuel2=MIN0,tempsPrecedent2=MIN0;
        int vitesseSnake = SECONDE;
        int directionSnake = MIN1; // 1 droite 2 gauche 3 haut 4 bas
        int angleTexture,pommeActive=MIN0;
        int perdu = NON, gagner=NON;
        int repeat = MIN0;
        int nbrCorpSnake=MIN0;
        Pos snake[NBRLIGNES*NBRLIGNES];
        TTF_Font *font = NULL;
        SDL_Color fontColor = { COLORFONT, COLORFONT, COLORFONT };
        char scoreInt[MAXCARACTERE];
        SDL_Texture *fontScoreTexture = NULL;
        SDL_Surface *fontScoreSurface = NULL;
        SDL_Event event;

        //init font
        font = TTF_OpenFont(FONT, TAILLEFONT);
        sprintf(scoreInt,"Score: %d",*score);
        fontScoreSurface=TTF_RenderText_Solid(font,scoreInt,fontColor);

        //creer la base du corp du snake
        setCorpSnake(snakeRect,snake,lignes[DEPARTSNAKE].x,lignes[DEPARTSNAKE].y,DEPARTSNAKE,DEPARTSNAKE,&nbrCorpSnake);
        setCorpSnake(snakeRect,snake,lignes[DEPARTSNAKE-MIN1].x,lignes[DEPARTSNAKE].y,DEPARTSNAKE-MIN1,DEPARTSNAKE,&nbrCorpSnake);

        /***********************************************************************************************************
        --------------------------------Boucle de jeu
        ***********************************************************************************************************/
        while (!repeat){
                sprintf(scoreInt,"Score: %d",*score);
                fontScoreSurface=TTF_RenderText_Solid(font,scoreInt,fontColor);
                fontScoreTexture = SDL_CreateTextureFromSurface(jeu -> renderer, fontScoreSurface);

                //en attente d'un event
                SDL_PollEvent(&event);
                //event du clavier par le joueur
                toucheJoueur(event,&repeat,&directionSnake,&angleTexture);

                //spawn de la pomme 1 seul fois
                if (pommeActive==MIN0){
                        randPomme(pommeRect,lignes,snakeRect,nbrCorpSnake);
                        pommeActive=MIN1;
                }

                //30fps affichage
                tempsActuel = SDL_GetTicks();
                if (tempsActuel - tempsPrecedent > FPS){
                         //copie la texture dans le rendu
                        SDL_RenderCopy(jeu -> renderer,jeu -> texture[IMGFOND1],NULL,NULL);
                        SDL_RenderCopy(jeu -> renderer,jeu -> texture[IMGFOND2],NULL,&fondMenu);
                        SDL_RenderCopy(jeu -> renderer,fontScoreTexture, NULL, &fondScore);

                        if (pommeActive==MIN1){
                                SDL_RenderCopy(jeu -> renderer, jeu -> texture[IMGPOMME], NULL, pommeRect);
                        }

                        SDL_SetRenderDrawColor(jeu -> renderer, COLORDRAWR, COLORDRAWG, COLORDRAWB, SDL_ALPHA_OPAQUE);
                        for (i=MIN0;i<NBRLIGNES;i++){
                                SDL_RenderDrawLine(jeu -> renderer,lignes[i].x,fondMenu.y,lignes[i].x,fondMenu.y+fondMenu.h);
                                SDL_RenderDrawLine(jeu -> renderer,fondMenu.x,lignes[i].y,fondMenu.x+fondMenu.w,lignes[i].y);
                        }

                        tempsPrecedent = tempsActuel;
                }
                else    //economisé le proc sinon tourne a 100%
                        SDL_Delay(FPS - (tempsActuel - tempsPrecedent));


                //jeux
                if ((!perdu) || (gagner)){
                        for (i=MIN0;i<nbrCorpSnake;i++){
                                if (i==MIN0)
                                        SDL_RenderCopyEx(jeu -> renderer, jeu -> texture[IMGSERPENDTETE], NULL, &snakeRect[i], angleTexture, NULL, SDL_FLIP_NONE );
                                else
                                        SDL_RenderCopy(jeu -> renderer, jeu -> texture[IMGSERPENDROND], NULL, &snakeRect[i]);

                                snakeRect[i].x = lignes[snake[i].x].x;
                                snakeRect[i].y = lignes[snake[i].y].y;

                                if ((testPerduCadre(snake[MIN0].x,snake[MIN0].y)) || (testPerduCollision(snake,nbrCorpSnake))){
                                        perdu=OUI;
                                        //joue le son de mort
                                        Mix_PlayChannel(-MIN1, jeu -> son[SONMORT], MIN0 );
                                }

                                //deplacement du snake
                                tempsActuel2 = SDL_GetTicks();
                                if (tempsActuel2 - tempsPrecedent2 > vitesseSnake){
                                        //joue le son de deplacement
                                        Mix_PlayChannel(-MIN1, jeu -> son[SONDEPLACEMENT], MIN0 );
                                        deplacementSnake(snake,nbrCorpSnake,directionSnake);

                                        if (testSnakePomme(snakeRect[MIN0],*pommeRect,nbrCorpSnake)==MIN1){
                                                pommeActive=MIN0;
                                                //joue le son de deplacement
                                                Mix_PlayChannel(-MIN1, jeu -> son[SONPOMME], MIN0 );
                                                *score+=MIN1;

                                                setCorpSnake(snakeRect,snake,lignes[snake[nbrCorpSnake-MIN1].x].x,lignes[snake[nbrCorpSnake-MIN1].y].y,snake[nbrCorpSnake-MIN1].x,snake[nbrCorpSnake-MIN1].y,&nbrCorpSnake);

                                                if (vitesseSnake>SECONDEMIN){
                                                        vitesseSnake-=REDUITSECONDE;
                                                }

                                                if (nbrCorpSnake==NBRLIGNES*NBRLIGNES){
                                                        gagner=OUI;
                                                }
                                        }
                                        tempsPrecedent2 = tempsActuel2;
                                }
                        }
                        SDL_RenderPresent(jeu -> renderer);
                }
        }
        SDL_FreeSurface(fontScoreSurface);
        SDL_DestroyTexture(fontScoreTexture);
        TTF_CloseFont(font);
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:initialisation de la SDL
	 *__ENTREE:
	 *__SORTIE:SDL initialisé
***********************************************************************************/
int initSDL(){

         /***********************************************************************************************************
        --------------------------------initialisation des SDL
        ***********************************************************************************************************/
        if (SDL_Init(SDL_INIT_EVERYTHING)){
                 fprintf(stderr,"Echec lors de l'initialisation de SDL_Init (%s)\n",SDL_GetError());
                 return MIN0;
        }
        if (!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG)){
                 fprintf(stderr,"Echec lors de l'initialisation de IMG_Init (%s)\n",SDL_GetError());
                return MIN0;
        }
        //Initialisation de SDL_mixer
        if(Mix_OpenAudio( FREQ, MIX_DEFAULT_FORMAT, MIN2, SAMPLE ) ){
                fprintf(stderr,"Echec lors de l'initialisation de MIXER_Init (%s)\n",Mix_GetError());
                return MIN0;
        }
        //Initialisation de SDL_TTF
	if(TTF_Init() < MIN0) {
		fprintf(stderr,"Echec lors de l'initialisation de TTF_Init (%s)\n",TTF_GetError());
                return MIN0;
	}

	return MIN1;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:initialisation de la fenetre et du rendu
	 *__ENTREE:
	 *__SORTIE:renvoie un pointeur d'un type Game
***********************************************************************************/
Game *initJeu(){
        Game *jeu=malloc (sizeof(Game));
        char nomImg[NBRTEXTURE][MAXCARACTERE]={IMAGES};
        char nomSon[NBRSON][MAXCARACTERE]={SONS};
        SDL_Surface *imgIcon=NULL;
        int i;

        /***********************************************************************************************************
        --------------------------------Initialisation de la fenetre/rendu
        ***********************************************************************************************************/
        //creation fenetre
        jeu -> screen = SDL_CreateWindow(NOMFENETRE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MIN0, MIN0, SDL_WINDOW_MAXIMIZED);
        if (jeu -> screen ==NULL){
                 fprintf(stderr,"Echec lors de l'initialisation SDL_CreateWindow (%s)\n",SDL_GetError());
                return MIN0;
        }

        //creer le rendu
        jeu -> renderer =  SDL_CreateRenderer(jeu -> screen, -MIN1, SDL_RENDERER_ACCELERATED);   //rendu écran
        if (jeu -> renderer==NULL){
                 fprintf(stderr,"Echec lors de l'initialisation SDL_CreateRenderer (%s)\n",SDL_GetError());
                return MIN0;
        }


       /***********************************************************************************************************
        --------------------------------Initialisation des images
        ***********************************************************************************************************/
        for (i=MIN0;i<NBRTEXTURE;i++)
                jeu -> texture[i] = getTexture(jeu->renderer,nomImg[i]);

        //charge l'icone
        imgIcon = getSurface(IMGICONE);

        //change l'icone
        SDL_SetWindowIcon(jeu -> screen, imgIcon);

        /***********************************************************************************************************
        --------------------------------Initialisation des sons musique
        ***********************************************************************************************************/
       jeu -> musique = getMusique(MUSIQUE);

       for (i=MIN0;i<NBRSON;i++)
                jeu -> son[i] = getSon(nomSon[i]);

        free(jeu);

        return jeu;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:initialise les valeurs d'un rect
	 *__ENTREE:4 entier
	 *__SORTIE:rect initialisé
***********************************************************************************/
SDL_Rect setRect(int h,int w,int x,int y){
        SDL_Rect rect;

        rect.h=h;
        rect.w=w;
        rect.x=x;
        rect.y=y;

        return rect;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:charge l'image du disque dans une variable de type Surface et renvoie le type
	 *__ENTREE:1 chaine
	 *__SORTIE:1 type SDL_Surface
***********************************************************************************/
SDL_Surface *getSurface(char name[]){
        SDL_Surface *img = NULL;

        img=IMG_Load(name);
        if (img==NULL){
                 fprintf(stderr,"Echec lors de l'initialisation IMG_Load (%s)\n",SDL_GetError());
                return MIN0;
        }
        return img;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:charge la musique du disque dans une variable de type Surface et renvoie le type
	 *__ENTREE:1 chaine
	 *__SORTIE:1 type Mix_Music
***********************************************************************************/
Mix_Music *getMusique(char name[]){
         //Chargement de la musique
        Mix_Music *musique = NULL;
        musique = Mix_LoadMUS(name);

        Mix_VolumeMusic(MIX_MAX_VOLUME/MIN2);
        if (musique==NULL){
                fprintf(stderr,"Echec lors de l'initialisation de la musique (%s)\n",Mix_GetError());
                return MIN0;
        }
        return musique;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:charge un son du disque dans une variable de type Surface et renvoie le type
	 *__ENTREE:1 chaine
	 *__SORTIE:1 type Mix_Chunk
***********************************************************************************/
Mix_Chunk *getSon(char name[]){
         //chargement son
        Mix_Chunk *son = NULL;
        son = Mix_LoadWAV(name);
        Mix_VolumeChunk(son,MIX_MAX_VOLUME/MIN3);

        if (son==NULL){
                fprintf(stderr,"Echec lors de l'initialisation des sons (%s)\n",Mix_GetError());
                return MIN0;
        }
        return son;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:renvoie un type texture depuis une image
	 *__ENTREE:1 chaine 1 Renderer
	 *__SORTIE:1 type SDL_Texture
***********************************************************************************/
SDL_Texture *getTexture(SDL_Renderer *renderer,char name[]){
        SDL_Surface *image =NULL;
        SDL_Texture *texture=NULL;

        image = IMG_Load(name);
        if (image==NULL){
                 fprintf(stderr,"Echec lors de l'initialisation IMG_Load (%s)\n",SDL_GetError());
                return MIN0;
        }

        texture = SDL_CreateTextureFromSurface(renderer, image);

        SDL_FreeSurface(image);

        return texture;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:remplace la valeur x y de 2 Rect (le snake)
	 *__ENTREE:1 SDL_Rect, 1 Pos, 5 entier
	 *__SORTIE:valeur initialisé
***********************************************************************************/
void setCorpSnake(SDL_Rect snakeRect[], Pos snake[], int xRect,int yRect,int xLignes,int yLignes,int *nbrCorpSnake){

        snakeRect[*nbrCorpSnake].x = xRect;
        snakeRect[*nbrCorpSnake].y = yRect;
        snake[*nbrCorpSnake].x = xLignes;
        snake[*nbrCorpSnake].y = yLignes;



        *nbrCorpSnake=*nbrCorpSnake+MIN1;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:test si il y a une colision entre les partie du corp du snake
	 *__ENTREE:1 type Pos, 1 entier
	 *__SORTIE:retourne 1 -0
***********************************************************************************/
int testPerduCollision(Pos snake[], int nbrCorpSnake){
        int i,test=MIN0;

        for (i=MIN1;i<nbrCorpSnake;i++){
                if ((snake[MIN0].x == snake[i].x) && (snake[MIN0].y == snake[i].y))
                        test= MIN1;
        }

        return test;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:test si la snake est sorti du cadre de la map
	 *__ENTREE:2 entier
	 *__SORTIE:1 ou 0
***********************************************************************************/
int testPerduCadre(int x, int y){
        int test=MIN0;

        if ((x < MIN0) || (x > NBRLIGNES-MIN2) || (y < MIN0) || (y > NBRLIGNES-MIN2))
                test=MIN1;

        return test;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:test si le snake touche la pomme
	 *__ENTREE:2 SDL_Rect 1 entier
	 *__SORTIE:1 - 0
***********************************************************************************/
int testSnakePomme(SDL_Rect snakeRect, SDL_Rect pommeRect, int nbrCorpSnake){
        int test=MIN0;
        if ((snakeRect.x == pommeRect.x) && (snakeRect.y == pommeRect.y))
                test=MIN1;
        return test;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:initialise la valeur de la pomme pour qu'il soit à l'interieur de la map
	 *__ENTREE:2 SDL_Rect 1 type Pos et 1 entier
	 *__SORTIE:
***********************************************************************************/
void randPomme(SDL_Rect *pommeRect,Pos lignes[], SDL_Rect snakeRect[], int nbrCorpSnake){
        int x,y;

        do{
                x = lignes[rand()%(NBRLIGNES-MIN1)].x;
                y = lignes[rand()%(NBRLIGNES-MIN1)].y;
        }while(testRandPomme(x,y,snakeRect,nbrCorpSnake));

        pommeRect -> x = x;
        pommeRect -> y = y;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:verifie si la valeur x et y de la pomme n'est pas la meme que le snake
	 *__ENTREE:3 entier 1 SDL_Rect
	 *__SORTIE:1-0
***********************************************************************************/
int testRandPomme(int x, int y, SDL_Rect snakeRect[], int nbrCorpSnake){
        int test=MIN0,i;

        for (i=MIN0;i<nbrCorpSnake;i++){
                if ((snakeRect -> x == x) && (snakeRect -> y == y))
                        test=MIN1;
        }

        return test;
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:recupere les touche du clavier
	 *__ENTREE:1 SDL_Event 3 pointeur d'entier
	 *__SORTIE:
***********************************************************************************/
void toucheJoueur(SDL_Event event,int *repeat,int *directionSnake, int *angleTexture){
        //fps 30ms
        switch(event.type){
                case SDL_QUIT:
                        *repeat =MIN1;
                break;
                case SDL_KEYDOWN:
                       switch(event.key.keysym.sym){
                                case SDLK_RIGHT:
                                        if (*directionSnake!=GAUCHE){
                                                *directionSnake=DROITE;
                                                *angleTexture=ANGLEDROIT;
                                        }
                                break;
                                case SDLK_LEFT:
                                        if (*directionSnake!=DROITE){
                                                *directionSnake=GAUCHE;
                                                *angleTexture=ANGLEGAUCHE;
                                        }
                                break;
                                case SDLK_UP:
                                        if (*directionSnake!=BAS){
                                                *directionSnake=HAUT;
                                                *angleTexture=ANGLEHAUT;
                                        }
                                break;
                                case SDLK_DOWN:
                                        if (*directionSnake!=HAUT){
                                                *directionSnake=BAS;
                                                *angleTexture=ANGLEBAS;
                                        }
                                break;
                       }
                break;
        }
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:deplace le snake sur la map
	 *__ENTREE:1 tab de type Pos 2 entier
	 *__SORTIE:
***********************************************************************************/
void deplacementSnake(Pos snake[], int nbrCorpSnake, int directionSnake){
        int j;
        Pos caseSnake[nbrCorpSnake];

        for (j=MIN0;j<nbrCorpSnake;j++){
                caseSnake[j].x=snake[j].x;
                caseSnake[j].y=snake[j].y;

                if (j!=MIN0){
                        snake[j].x=caseSnake[j-MIN1].x;
                        snake[j].y=caseSnake[j-MIN1].y;
                }
                else{
                        switch(directionSnake){
                                case DROITE: //droite
                                        snake[j].x++;
                                break;

                                case GAUCHE: //gauche
                                        snake[j].x--;
                                break;

                                case HAUT: //haut
                                        snake[j].y--;
                                break;

                                case BAS: //bas
                                        snake[j].y++;
                                break;
                        }
                }
        }
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:initialise les valeurs des cases de la map
	 *__ENTREE:1 tab de type Pos, 1 SDL_Rect
	 *__SORTIE:
***********************************************************************************/
void initTab(Pos lignes[], SDL_Rect fondMenu){
        int i;
        //position des cellules et -MIN1 pour ne pas ajouter la derniere cellule
        for (i=MIN0;i<NBRLIGNES-MIN1;i++){
                if (i!=MIN0){
                        lignes[i].x = fondMenu.x+(((float)fondMenu.w / (NBRLIGNES-MIN1))*i);
                        lignes[i].y = fondMenu.y+(((float)fondMenu.h / (NBRLIGNES-MIN1))*i);
                }
                else{
                        lignes[i].x = fondMenu.x;
                        lignes[i].y = fondMenu.y;
                }
        }
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:initialise la valeurs des différents fond
	 *__ENTREE:4 SDL_Rect 2 entier
	 *__SORTIE:
***********************************************************************************/
void initAllRect(SDL_Rect snakeRect[], SDL_Rect *fondMenu, SDL_Rect *pommeRect, SDL_Rect *fondScore, int screenHeight,int screenWidth){
        int i;
        *fondMenu = setRect(((screenHeight / MIN3) + (screenHeight / MIN2)),((screenHeight / MIN3) + (screenHeight / MIN2)),MIN0,MIN0);
        fondMenu -> y = ((screenHeight / MIN2) - (fondMenu -> h / MIN2));
        fondMenu -> x = ((screenWidth / MIN2) - (fondMenu -> w / MIN2));
        *fondScore = setRect(FONTL,FONTH,fondMenu -> x+fondMenu -> w+FONTDECALAGE,fondMenu -> y);

        //taile du snake par carre
        for (i=MIN0;i<NBRLIGNES*NBRLIGNES;i++)
                snakeRect[i] = setRect(((float)fondMenu -> h / (NBRLIGNES)),((float)fondMenu -> w / (NBRLIGNES)),MIN0,MIN0);

        //taille de la pomme
        *pommeRect = setRect(((float)fondMenu -> h / (NBRLIGNES)),((float)fondMenu -> w / (NBRLIGNES)),MIN0,MIN0);
}


/* *************************PROCEDURE*** / ***FONCTION******************************
	 *_____BUT:libere la mémoire
	 *__ENTREE:1 type Game
	 *__SORTIE:
***********************************************************************************/
void freeAll(Game *jeu){
        int i;
         /***********************************************************************************************************
        --------------------------------Libere les mémoires avant la fin du programme
        ***********************************************************************************************************/
        Mix_FreeMusic(jeu -> musique);
        for (i=MIN0;i<NBRSON;i++)
                Mix_FreeChunk(jeu -> son[i]);
        Mix_CloseAudio();
        Mix_Quit();
        TTF_Quit();
        for (i=MIN0;i<NBRTEXTURE;i++)
                SDL_DestroyTexture(jeu -> texture[i]);
        SDL_DestroyRenderer(jeu -> renderer);
        SDL_DestroyWindow(jeu -> screen);
        free(jeu);
        SDL_Quit();
}


/*
        // On récupère le nombre de modes d'affichage pour l'écran 0
        nbrModeScreen = SDL_GetNumDisplayModes(0);

        if ( nbrModeScreen < 0 ){
                fprintf(stdout,"Echec lors de la recuperation du nombre de modes (%s)\n",SDL_GetError());
                return -2;
        }
        fprintf(stdout,"Vous avez %d mode(s) d'affichage\n",nbrModeScreen);

        // Affichage des différents modes
        for ( i = 0 ; i < nbrModeScreen ; i++ ) {
            if (SDL_GetDisplayMode(0,i,&displayMode)) {
                fprintf(stdout,"Echec lors de la recuperation du mode d'affichage (%s)\n",SDL_GetError());
                return -3;
            }
            fprintf(stdout,"Mode %d : %dx%dx%d\n",i+1,displayMode.w,displayMode.h,displayMode.refresh_rate);
        }*/
