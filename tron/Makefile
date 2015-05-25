# Donner le nom du compilateur C
CC=gcc

# Options de chemin de headers
HPATH=-I/usr/include/SDL

# Options compilation 
#  1) pour debugger laisser la ligne suivante
#  2) pour optimiser commenter la ligne suivante
#     et "decommenter celle d'apres".
CFLAGS=-g -Wall -std=c99 -pedantic -ansi $(HPATH)
#CFLAGS=-O3 -Wall -std=c99 -pedantic -ansi $(HPATH)

# Les librairies nécessaires à l'édition de lien 
# avec les librairies SDL (cf http://www.libsdl.org/)
# SDL        --> fonctionnalites de base
# SDL_mixer  --> pour la gestion du son
# SDL_ttf    --> pour la gestion du texte (polices True Type)
# SDL_image  --> pour la gestion des images
LIBS=-lSDL -lSDL_mixer -lSDL_ttf -lSDL_image

NOM_EXECUTABLE=tron
# Les règles de compilations
all: $(NOM_EXECUTABLE)

$(NOM_EXECUTABLE) : tron.o graph.o
	$(CC) $(CFLAGS) -o $(NOM_EXECUTABLE) tron.o graph.o $(LIBS)

tron.o: tron.c 
	$(CC) $(CFLAGS) -c tron.c

graph.o : graph.h graph.c
	$(CC) $(CFLAGS) -c graph.c

clean:
	\rm -f *.o tron


