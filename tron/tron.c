#include "graph.h"

/* Le pas de déplacement de la moto */
#define PAS 30

int nbdep=0;

int test_fin_jeu(AFFICHAGE *aff,int** grille)
{	
	int n;
	
	if (grille[aff->posMoto.y/PAS][aff->posMoto.x/PAS]==1)
	{	n=0;}
	
	else if (grille[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]==1)
	{	n=1;}
	else if (aff->posMoto2.y/PAS== aff->posMoto.y/PAS && aff->posMoto.x/PAS== aff->posMoto2.x/PAS)
	{	n=2;}
	else if (grille[aff->posMoto.y/PAS][aff->posMoto.x/PAS]==1 && grille[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]==1)
	{	n=2;}
	else
	{	n=3;}
	return n;
}




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
						{creationtrainee1(*aff,&(aff->posMoto));
						aff->posMoto.x += PAS;
						nbdep++;
						matrice[aff->posMoto.y/PAS][aff->posMoto.x/PAS]=1;}
				
						
					return 0;
				case SDLK_LEFT: /* Appui sur la touche gauche -> déplacement à gauche*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto.x >= PAS)/* mais seulement si cela reste dans le tableau */
						{creationtrainee1(*aff,&(aff->posMoto));
						aff->posMoto.x -= PAS;
						nbdep++;
						matrice[aff->posMoto.y/PAS][aff->posMoto.x/PAS]=1;}

					return 0;
				case SDLK_UP: /* Appui sur la touche haut -> déplacement en haut*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto.y >= PAS)/* mais seulement si cela reste dans le tableau*/{
						creationtrainee1(*aff,&(aff->posMoto));
						aff->posMoto.y -= PAS;
						nbdep++;
						matrice[aff->posMoto.y/PAS][aff->posMoto.x/PAS]=1;}
					return 0;
				case SDLK_DOWN: /* Appui sur la touche bas -> déplacement en bas*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto.y + aff->moto->h <= aff->ecran->h - PAS) /* mais seulement si cela reste dans le tableau */
						{creationtrainee1(*aff,&(aff->posMoto));
						aff->posMoto.y += PAS;
						nbdep++;
						matrice[aff->posMoto.y/PAS][aff->posMoto.x/PAS]=1;}

					return 0;
               
            			case SDLK_d: /* Appui sur la touche droite -> déplacement à droite*/
					/*jouer un son */
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto2.x + aff->moto2->w <= aff->ecran->w - PAS)/* mais seulement si cela reste dans le tableau */
						{creationtrainee2(*aff,&(aff->posMoto2));
						aff->posMoto2.x += PAS;
						nbdep++;
						matrice[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]=1;}
						
						
						

					return 0;
				case SDLK_q: /* Appui sur la touche gauche -> déplacement à gauche*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto2.x >= PAS)/* mais seulement si cela reste dans le tableau */
						{creationtrainee2(*aff,&(aff->posMoto2));
						aff->posMoto2.x -= PAS;
						nbdep++;
						matrice[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]=1;}

					return 0;
				case SDLK_z: /* Appui sur la touche haut -> déplacement en haut*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto2.y >= PAS)/* mais seulement si cela reste dans le tableau*/
						{creationtrainee2(*aff,&(aff->posMoto2));
						aff->posMoto2.y -= PAS;
						nbdep++;
						matrice[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]=1;}
					return 0;
				case SDLK_s: /* Appui sur la touche bas -> déplacement en bas*/
					if (Mix_PlayChannel( -1, aff->son, 0 ) == -1) {
						return 1;
					}
					if (aff->posMoto2.y + aff->moto2->h <= aff->ecran->h - PAS) /* mais seulement si cela reste dans le tableau */
						{creationtrainee2(*aff,&(aff->posMoto2));
						aff->posMoto2.y += PAS;
						nbdep++;
						matrice[aff->posMoto2.y/PAS][aff->posMoto2.x/PAS]=1;}
					return 0;

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
	int i,l,m,Quitter;
	int n = 3;	/*0 si le joueur 0 gagne,1 si c'est le joueur 1, 2 si le jeu finit sans victoire, 3 si le jeu continue (variable renouvelée à chaque tour)*/
	
	SDL_Surface *gmesgVictoire=NULL;
	SDL_Surface *gmesgAuRevoir=NULL; /* La surface qui contiendra le message d'au revoir */
				
	SDL_Color rouge = { 200, 0, 0 }; /* Couleur rouge codée en RVB */
	SDL_Rect positionMesg = { 0, 0 }; /* position du message de fin */
	
	matrice=malloc(20*sizeof(int*));
		
		if( matrice == NULL )
			{
				 fprintf(stderr,"Allocation impossible");
				 exit(EXIT_FAILURE);
			}


		for(i=0; i<20; i++){
			
			matrice[i]=malloc(34*sizeof(int));
			
			if( matrice[i] == NULL )
				 {
					  fprintf(stderr,"Allocation impossible");
					  exit(EXIT_FAILURE);
				 }
			}

	
		
		for (l=1; l<19; l++){
			for(m=1; m<33; m++){
				matrice[l][m]=0;
			}
		}
		
		
		for (m=0; m<34; m++){
			matrice[0][m]=1;
			matrice[19][m]=1;
		}
		
		for (l=0; l<20; l++){
			matrice[l][0]=1;
			matrice[l][33]=1;
		}
		
		
	Quitter=0; /* une variable que l'on passe à 1 pour quitter */
		
	affich = initSDL();
		
	matrice[affich.posMoto.y/PAS][affich.posMoto.x/PAS]=1;
	
	
	SDL_FillRect(affich.ecran, NULL, SDL_MapRGB(affich.ecran->format,0,0,200));


	/* Boucle d'affichage et d'interaction */
	while (!Quitter && n==3) {

		/*n = test_fin_jeu(&affich,matrice); */
		
		/* On affiche la moto */
		SDL_BlitSurface(affich.moto, NULL, affich.ecran, &(affich.posMoto));
		SDL_BlitSurface(affich.moto2, NULL, affich.ecran, &(affich.posMoto2));

		/* Affichage proprement dit (ce n'est qu'a l'exécution de cette instruction que l'écran change)*/
		SDL_Flip(affich.ecran);

		Quitter = ecouteUtilisateur(&affich,matrice);

	}

	/* Remplissage de la fenetre en noir */
	SDL_FillRect(affich.ecran, NULL, SDL_MapRGB(affich.ecran->format,0,0,0));


	gmesgAuRevoir = TTF_RenderText_Blended(affich.police, "Au revoir", rouge);
	positionMesg.x = affich.ecran->w / 2 ; /* centre l'affichage */
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
