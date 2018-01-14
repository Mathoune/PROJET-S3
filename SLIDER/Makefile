NOM=PROJET_IN301

all: slider

#Pour lancer l'executable
test: slider 
	./slider Niveau0.slider

#Pour lancer le mode edition en 10*10
edition: slider
	./slider -c 10 10 NiveauCree.slider

#Pour lancer le mode de lecture complet
dossiercomplet: slider
	./slider dir_slider

# Edition de liens
slider: slider.o lire_ecrire.o afficher.o deplacements.o listes_memo.o editeur.o lire_dossier.o
	gcc slider.o lire_ecrire.o afficher.o deplacements.o listes_memo.o editeur.o lire_dossier.o -o slider -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

# Compilation
slider.o: slider.c mes_types.h lire_ecrire.h afficher.h  listes_memo.h editeur.h deplacements.h
	gcc -c -Wall `sdl-config --cflags` slider.c

lire_dossier.o: lire_dossier.c mes_types.h deplacements.h
	gcc -c -Wall `sdl-config --cflags` lire_dossier.c

lire_ecrire.o: lire_ecrire.c mes_types.h
	gcc -c -Wall `sdl-config --cflags` lire_ecrire.c

afficher.o: afficher.c mes_types.h
	gcc -c -Wall `sdl-config --cflags` afficher.c

listes_memo.o: listes_memo.c mes_types.h afficher.h
	gcc -c -Wall `sdl-config --cflags` listes_memo.c	

deplacements.o: deplacements.c mes_types.h afficher.h
	gcc -c -Wall `sdl-config --cflags` deplacements.c

	
editeur.o: editeur.c mes_types.h afficher.h
	gcc -c -Wall `sdl-config --cflags` editeur.c

#Pour aligner proprement le code
indent:
	indent *.c

#Pour ouvrir tous les fichiers dans Geany
editeur:
	geany Makefile *.c *.h

# Pour creer le zip 
zip:
	zip -r BECHET .

#Pour lancer Valgrind sur un niveau
valgrind: slider
	valgrind ./slider Niveau0.slider

#Pour supprimer les .o et l'executable
clean:
	rm -f *.o
	rm -f slider
