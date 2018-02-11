#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include<SDL2\SDL.h>
#include<SDL2\SDL_ttf.h>
#include<SDL2\SDL_mixer.h>
#include<SDL2\SDL_image.h>

//CONSTANTE
#define FPS 30

#define MAXCARACTERE 255

#define FONT "snake.otf"
#define TAILLEFONT 46

#define FONTH 120
#define FONTL 30
#define FONTDECALAGE 50

#define MIN0 0
#define MIN1 1
#define MIN2 2
#define MIN3 3

#define DROITE 1
#define GAUCHE 2
#define HAUT 3
#define BAS 4

#define NON 0
#define OUI 1

#define ANGLEDROIT  0.0
#define ANGLEGAUCHE 180.0
#define ANGLEHAUT -90.0
#define ANGLEBAS 90.0

#define COLORDRAWR 192
#define COLORDRAWG 241
#define COLORDRAWB 140
#define COLORFONT 255

#define IMAGES "fond.png","fond2.png","serpend-rond.png","serpend-tete.png","pomme.png"
#define IMGICONE "snake.png"
#define NBRTEXTURE 5
#define IMGFOND1 0
#define IMGFOND2 1
#define IMGSERPENDROND 2
#define IMGSERPENDTETE 3
#define IMGPOMME 4

#define SONS "mort.wav","deplacement.wav","pomme.wav"
#define MUSIQUE "musique.wav"
#define NBRSON 3
#define SONMORT 0
#define SONDEPLACEMENT 1
#define SONPOMME 2

#define FREQ 22050
#define SAMPLE 4096

#define NOMFENETRE "Snake by Geuks"
#define NBRLIGNES 25

#define DEPARTSNAKE 4

#define SECONDE 300
#define SECONDEMIN 100
#define REDUITSECONDE 50


//structures
typedef struct Game{
        SDL_Window *screen;
        SDL_Renderer *renderer;
        SDL_Texture *texture[NBRTEXTURE];
        Mix_Music *musique;
        Mix_Chunk *son[NBRSON];
}Game;

typedef struct Pos{
        int x;
        int y;
}Pos;

typedef enum EtatJeu{
        rien,gagner,perdu
}EtatJeu;


//PROTOTYPES
int initSDL();
Game *initJeu();
void initTab(Pos lignes[], SDL_Rect fondMenu);
void initAllRect(SDL_Rect snakeRect[], SDL_Rect *fondMenu, SDL_Rect *pommeRect, SDL_Rect *fondScore, int screenHeight,int screenWidth);
SDL_Rect setRect(int,int,int,int);
void setCorpSnake(SDL_Rect [], Pos [], int ,int ,int ,int ,int *);
SDL_Surface *getSurface(char []);
Mix_Music *getMusique(char []);
Mix_Chunk *getSon(char []);
SDL_Texture *getTexture(SDL_Renderer *,char []);
int testPerduCollision(Pos snake[], int nbrCorpSnake);
int testPerduCadre(int x, int y);
int testSnakePomme(SDL_Rect snakeRect, SDL_Rect pommeRect, int nbrCorpSnake);
int testRandPomme(int x, int y, SDL_Rect snakeRect[], int nbrCorpSnake);
void boucleJeu(Game *,int *, Pos [], SDL_Rect *, SDL_Rect *, SDL_Rect, SDL_Rect);
void randPomme(SDL_Rect *pommeRect,Pos lignes[], SDL_Rect snakeRect[], int nbrCorpSnake);
void toucheJoueur(SDL_Event event,int *repeat,int *directionSnake, int *angleTexture);
void deplacementSnake(Pos snake[], int nbrCorpSnake, int directionSnake);
void freeAll(Game *jeu);
