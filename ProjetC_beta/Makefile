# Donner le nom du compilateur C
CC=gcc

# Options de chemin de headers
HPATH=-I/usr/include/SDL

CFLAGS=-g -Wall -std=c99 -pedantic -ansi $(HPATH)


# Les librairies nécessaires à l'édition de lien 
# avec les librairies SDL (cf http://www.libsdl.org/)
# SDL        --> fonctionnalites de base
# SDL_mixer  --> pour la gestion du son
# SDL_ttf    --> pour la gestion du texte (polices True Type)
# SDL_image  --> pour la gestion des images
LIBS=-lSDL -lSDL_mixer -lSDL_ttf -lSDL_image

NOM_EXECUTABLE=TRAINEETEST
# Les règles de compilations

all: $(NOM_EXECUTABLE)

$(NOM_EXECUTABLE) : traineetest.o
	$(CC) $(CFLAGS) -o $(NOM_EXECUTABLE) traineetest.o $(LIBS)

traineetest.o: traineetest.c
	$(CC) $(CFLAGS) -c traineetest.c


clean:
	\rm -f *.o TRAINEETEST


