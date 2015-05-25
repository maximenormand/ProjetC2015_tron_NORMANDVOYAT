#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include "graph.h"

/* Les dimensions de la fenêtre */
#define LARGEUR 1020
#define HAUTEUR 600




	
	
/**
 * Fonction qui initialise la SDL et tous les objets SDL qui pourront être utiles
 * @return une structure de type AFFICHAGE contenant des pointeurs vers les objets importants
 */
AFFICHAGE initSDL(){
	AFFICHAGE affich;
		
	/**************** Préparation de la fenêtre **************/
	/* Démarrage de la SDL (ici : chargement de tous les sous systèmes installés) */
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",
				SDL_GetError()); /* Ecriture de l'erreur */
		exit(EXIT_FAILURE); /* On quitte le programme */
	}

	/* Création de la fenêtre de jeu*/
	affich.ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE
			| SDL_DOUBLEBUF); /* Ouverture de la fenêtre LARGEURxHAUTEUR/32bits en mémoire vidéo, double buffering activé */
	if (!affich.ecran) {
		fprintf(stderr, "Impossible de charger le mode vidéo : %s\n",
				SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
/* Ajout d'un titre à la fenêtre */
	SDL_WM_SetCaption("TRON", NULL);

	/******************* Préparation de la moto **********/
	affich.moto = IMG_Load("images/motoorange.jpg"); /* chargement d'une image dans le format png qui contient de la transparence (necessite SDL_image) */
	affich.moto2 = IMG_Load("images/motoorange.jpg");
   
  	 affich.posMoto.x = 30 ; /* position initiale de la moto en haut a gauche pour ce test */
	affich.posMoto.y = 30 ;
   
   affich.posMoto2.x = 960 ; /* position initiale de la moto en bas a droite pour ce test */
	affich.posMoto2.y = 540 ;

	/********** Préparation de l'affichage de texte *******/
	if (TTF_Init() == -1) { /* Le module gérant le texte doit être initialisé */
		fprintf(stderr, "Impossible de charger le module texte : SDL_ttf\n");
		exit(EXIT_FAILURE);
	}

	affich.police = TTF_OpenFont("polices/comic.ttf", 42); /* Charge une police de caractère (de type "true type")*/
	if (!affich.police) { /* le chargement de la police a échoué */
		fprintf(stderr, "Impossible de charger la police de caractère : %s\n",
				SDL_GetError());
		exit(EXIT_FAILURE);
	}


	/******** Préparation à la lecture du son *************/
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
			== -1) {/* Le module gérant le son doit être initialisé */
		fprintf(stderr, "Impossible de charger le module son : SDL_mixer\n");
		exit(EXIT_FAILURE);
	}

	Mix_AllocateChannels(32); /* Allocation de 32 canaux (potentiellement 32 sons simultanés) */
	affich.son = Mix_LoadWAV( "sons/bell.ogg" ); /* Chargement du son retenu */
	if (!affich.son) { /* le chargement du son a échoué */
		fprintf(stderr, "Impossible de charger le son : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	return(affich);
}

/**
 * Fonction qui ferme la SDL et libère les espaces mémoires nécessaires.
 * @param[in] affich La structure comprenant les données d'affichage 
 * @return void
 */
void closeSDL(AFFICHAGE affich){

	SDL_FreeSurface(affich.moto); /* Liberation d'une surface */
	
	TTF_CloseFont(affich.police); /* Fermeture de la police avant TTF_Quit */
	Mix_FreeChunk(affich.son); /* libération d'un son */

	Mix_CloseAudio(); /* Arrêt de SDL_mixer */
	TTF_Quit(); /* Arrêt de SDL_ttf  */
	SDL_Quit(); /* Arrêt de la SDL (libération de la mémoire). */
}


 void creationtrainee1(AFFICHAGE affich,SDL_Rect* pos)
 {
	 
	 
	 SDL_Surface *carretrainee=SDL_CreateRGBSurface(SDL_SWSURFACE,30,30,32,0,0,0,0);
	 SDL_FillRect(carretrainee,NULL,SDL_MapRGB(affich.ecran->format,206,100,100));
	 
	 SDL_BlitSurface(carretrainee,NULL,affich.ecran,pos) ;
	 SDL_Flip(affich.ecran);
	 SDL_FreeSurface(carretrainee);
	

 }

void creationtrainee2(AFFICHAGE affich,SDL_Rect* pos)
 {
	 
	 
	 SDL_Surface *carretrainee=SDL_CreateRGBSurface(SDL_SWSURFACE,30,30,32,0,0,0,0);
	 SDL_FillRect(carretrainee,NULL,SDL_MapRGB(affich.ecran->format,206,100,100));
	 
	 SDL_BlitSurface(carretrainee,NULL,affich.ecran,pos) ;
	 SDL_Flip(affich.ecran);
	 SDL_FreeSurface(carretrainee);
	

 }
