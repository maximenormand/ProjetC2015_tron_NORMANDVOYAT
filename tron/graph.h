#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"


/* Une structure contenant les données d'affichage et permettant de facilement les
 * passer en paramètre à une fonction
 */
typedef struct affichage {
	SDL_Surface *ecran, *moto,*moto2;
	/* Les positions des surfaces sont données par des retangles 
	dont les attributs .x et .y définissent le coin en haut à gauche 
	et .h et .w la hauteur et la largeur*/
	SDL_Rect posMoto,posMoto2; 
	/* variable qui contiendra le son à jouer à chaque coup */
	Mix_Chunk *son;
	/* variable qui contiendra la police à utiliser pour l'affichage de texte */
	TTF_Font *police;
	int gagnant;
} AFFICHAGE;

AFFICHAGE initSDL();

void closeSDL(AFFICHAGE affich);

void creationtrainee1(AFFICHAGE affich,SDL_Rect *pos);

void creationtrainee2(AFFICHAGE affich,SDL_Rect *pos);
