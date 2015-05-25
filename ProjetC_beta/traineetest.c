#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

/* Les dimensions de la fenêtre */
#define LARGEUR 1020
#define HAUTEUR 600

/* Le pas de déplacement de la moto */
#define PAS 30

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
} AFFICHAGE;

/* definition de la mémoire de la trainée */

int nbdep=0;


	
	
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
	affich.moto2 = IMG_Load("images/motobleue.jpg");
   
  	 affich.posMoto.x = 0 ; /* position initiale de la moto en haut a gauche pour ce test */
	affich.posMoto.y = 0 ;
   
   affich.posMoto2.x = 990 ; /* position initiale de la moto en bas a droite pour ce test */
	affich.posMoto2.y = 570 ;

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


 void creationtrainee(AFFICHAGE affich,SDL_Rect* pos)
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
	 SDL_FillRect(carretrainee,NULL,SDL_MapRGB(affich.ecran->format,306,100,100));
	 
	 SDL_BlitSurface(carretrainee,NULL,affich.ecran,pos) ;
	 SDL_Flip(affich.ecran);
	 SDL_FreeSurface(carretrainee);
	

 }
 

/**
 * Fonction qui attend un événement clavier ou souris et effectue les opérations conséquentes
 * @param[in] aff La structure comprenant les données d'affichage
 * @return code de retour suivant :
 * 0 : un événement à été traité, on continue (réaffichage et retour ici)
 * 1 : une demande d'interruption à été reçue, on doit arrêter le programme
 */
 
 
int ecouteUtilisateur(AFFICHAGE *aff,int **matrice) {
	int continuer = 1;
	
	SDL_Event event; /* Structure de la SDL qui recevra l'événement */

	while (continuer) {
		
		/* Gestion des événements clavier et souris */
		if (SDL_PollEvent(&event)) { /* un événement clavier ou souris a-t'il eu lieu ? */
			switch (event.type) {
			case SDL_QUIT: /* un clic souris sur le bouton de fermeture de la fenêtre a eu lieu -> on quitte le programme */
				return 1;
				break;
			case SDL_KEYDOWN: /* c'est un événement clavier qui a eu lieu */
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
					return 1;
				case SDLK_RIGHT: /* Appui sur la touche droite -> déplacement à droite*/
					/*jouer un son */
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto.x + aff->moto->w <= aff->ecran->w - PAS)/* mais seulement si cela reste dans le tableau */
						creationtrainee(*aff,&(aff->posMoto));
						aff->posMoto.x += PAS;
						nbdep++;
						matrice[aff->posMoto.y/PAS][aff->posMoto.x/PAS]=1;
						
						
						

					return 0;
				case SDLK_LEFT: /* Appui sur la touche gauche -> déplacement à gauche*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto.x >= PAS)/* mais seulement si cela reste dans le tableau */
						creationtrainee(*aff,&(aff->posMoto));
						aff->posMoto.x -= PAS;
						nbdep++;
						matrice[aff->posMoto.y/PAS][aff->posMoto.x/PAS]=1;

					return 0;
				case SDLK_UP: /* Appui sur la touche haut -> déplacement en haut*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto.y >= PAS)/* mais seulement si cela reste dans le tableau*/
						creationtrainee(*aff,&(aff->posMoto));
						aff->posMoto.y -= PAS;
						nbdep++;
						matrice[aff->posMoto.y/PAS][aff->posMoto.x/PAS]=1;
					return 0;
				case SDLK_DOWN: /* Appui sur la touche bas -> déplacement en bas*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto.y + aff->moto->h <= aff->ecran->h - PAS) /* mais seulement si cela reste dans le tableau */
						creationtrainee(*aff,&(aff->posMoto));
						aff->posMoto.y += PAS;
						nbdep++;
						matrice[aff->posMoto.y/PAS][aff->posMoto.x/PAS]=1;

					return 0;
               
            case SDLK_d: /* Appui sur la touche droite -> déplacement à droite*/
					/*jouer un son */
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto2.x + aff->moto2->w <= aff->ecran->w - PAS)/* mais seulement si cela reste dans le tableau */
						creationtrainee2(*aff,&(aff->posMoto2));
						aff->posMoto2.x += PAS;
						nbdep++;
						matrice[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]=1;
						
						
						

					return 0;
				case SDLK_q: /* Appui sur la touche gauche -> déplacement à gauche*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto2.x >= PAS)/* mais seulement si cela reste dans le tableau */
						creationtrainee2(*aff,&(aff->posMoto2));
						aff->posMoto2.x -= PAS;
						nbdep++;
						matrice[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]=1;

					return 0;
				case SDLK_z: /* Appui sur la touche haut -> déplacement en haut*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto2.y >= PAS)/* mais seulement si cela reste dans le tableau*/
						creationtrainee2(*aff,&(aff->posMoto2));
						aff->posMoto2.y -= PAS;
						nbdep++;
						matrice[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]=1;
					return 0;
				case SDLK_s: /* Appui sur la touche bas -> déplacement en bas*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto2.y + aff->moto2->h <= aff->ecran->h - PAS) /* mais seulement si cela reste dans le tableau */
						creationtrainee2(*aff,&(aff->posMoto2));
						aff->posMoto2.y += PAS;
						nbdep++;
						matrice[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]=1;

				default:
					;
				}
				
				break;
			
        	}
		}
	}
	return 0; /* Cette ligne n'est jamais atteinte */
}


#if _WIN32
int WinMain(int argc, char *argv[]) {
#else
int main(int argc, char *argv[]) {
#endif
	AFFICHAGE affich ;
	
	/*creation du tableau 50*30 qui va répertorier les positions où la moto est déjà passée*/
	
	int **matrice;
	int i,Quitter;
	
	SDL_Surface *gmesgVictoire=NULL;
	SDL_Surface *gmesgAuRevoir=NULL; /* La surface qui contiendra le message d'au revoir */
				
	SDL_Color rouge = { 200, 0, 0 }; /* Couleur rouge codée en RVB */
	SDL_Rect positionMesg = { 0, 0 }; /* position du message de fin */
	
	matrice = malloc( 34 * sizeof(int*));

		if( matrice == NULL )
		{
			 fprintf(stderr,"Allocation impossible");
			 exit(EXIT_FAILURE);
		}

		for( i = 0 ; i < 34 ; i++ )
		{
			 matrice[i] = calloc (20, sizeof(int));
			 
			 if( matrice[i] == NULL )
			 {
				  fprintf(stderr,"Allocation impossible");
				  exit(EXIT_FAILURE);
			 }
		}	/*chaque case vaudra 1 si la moto est déjà passée dessus, 0 sinon*/
		
		
	Quitter=0; /* une variable que l'on passe à 1 pour quitter */
		
	affich = initSDL();
		
	matrice[affich.posMoto.y/PAS][affich.posMoto.x/PAS]=1;
	
	
	SDL_FillRect(affich.ecran, NULL, SDL_MapRGB(affich.ecran->format,0,0,200));

	/* Boucle d'affichage et d'interaction */
	while (!Quitter) {

		/* Remplissage de la fenetre en bleu (impression d'effacement).*/
		/*Remarques :
		-Le deuxième paramètre de cette fonction est de type SDL_Rect* et indique le rectangle à remplir.
		Mettre NULL à la place permet de remplir tout l'écran.
		-Contrairement à RenderText, cette fonction prend un entier pour la couleur, 
		cet entier est généré par SDL_MapRGB, à qui on donne les valeurs de rouge, vert et bleu de 0 à 255*/
		

		/* On affiche la moto */
		SDL_BlitSurface(affich.moto, NULL, affich.ecran, &(affich.posMoto));
		SDL_BlitSurface(affich.moto2, NULL, affich.ecran, &(affich.posMoto2));

		/* Affichage proprement dit (ce n'est qu'a l'exécution de cette instruction que l'écran change)*/
		SDL_Flip(affich.ecran);
		

		Quitter = ecouteUtilisateur(&affich,matrice);
	}

	/* Remplissage de la fenetre en noir */
	SDL_FillRect(affich.ecran, NULL, SDL_MapRGB(affich.ecran->format,0,0,0));

	gmesgVictoire = TTF_RenderText_Blended(affich.police, "Victoire du joueur", rouge); /* construit la surface contenant le texte */

	positionMesg.x = affich.ecran->w / 2 - gmesgAuRevoir->w / 2; /* centre l'affichage */
	positionMesg.y = affich.ecran->h / 2;

	SDL_BlitSurface(gmesgAuRevoir, NULL, affich.ecran, &positionMesg); /* place la surface "texte" dans la surface ecran*/

	SDL_Flip(affich.ecran); /* affiche effectivement */

	SDL_Delay(3000); /* marque une pause de 3 secondes au moins avant de quitter */

	/* Libération de la mémoire et fin du programme */
	SDL_FreeSurface(gmesgAuRevoir);
	closeSDL(affich);
	
	free(matrice);
	
	
	return EXIT_SUCCESS; /* Fin du programme */
}

