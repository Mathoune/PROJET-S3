NOM=PROJET_IN301

all: slider

#Pour lancer l'executable
run: slider 
	./slider Niveau0.slider
	
edition: slider
	./slider -c 10 10 NiveauCree.slider

dossiercomplet: slider
	valgrind ./slider dir_slider

# Edition de liens
slider: slider.o lire_ecrire.o afficher.o jeu.o deplacements.o listes_memo.o editeur.o lire_dossier.o
	gcc slider.o lire_ecrire.o afficher.o jeu.o deplacements.o listes_memo.o editeur.o lire_dossier.o -o slider -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

# Compilation
slider.o: slider.c mes_types.h lire_ecrire.h afficher.h  listes_memo.h editeur.h
	gcc -c -Wall `sdl-config --cflags` slider.c

# 	
lire_dossier.o: lire_dossier.h mes_types.h jeu.h
	gcc -c -Wall `sdl-config --cflags` lire_dossier.c

# Compilation
lire_ecrire.o: lire_ecrire.c mes_types.h
	gcc -c -Wall `sdl-config --cflags` lire_ecrire.c

# Compilation
afficher.o: afficher.c mes_types.h
	gcc -c -Wall `sdl-config --cflags` afficher.c

# Compilation
listes_memo.o: listes_memo.c mes_types.h afficher.h
	gcc -c -Wall `sdl-config --cflags` listes_memo.c	

# Compilation
deplacements.o: deplacements.c mes_types.h afficher.h
	gcc -c -Wall `sdl-config --cflags` deplacements.c

# Compilation	
jeu.o: jeu.c deplacements.h afficher.h listes_memo.h lire_ecrire.h
	gcc -c -Wall `sdl-config --cflags` jeu.c
	
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
	rm -fr $(NOM)
	rm -f $(NOM).zip
	mkdir $(NOM)
	cp *.c $(NOM)
	cp *.h $(NOM)
	cp Makefile $(NOM)
#	cp -f *.slider $(NOM)
	zip $(NOM).zip $(NOM)/*
#	rm -fr $(NOM)

#Pour lancer Valgrind
valgrind: slider
	valgrind ./slider Niveau0.slider

#Pour supprimer les .o
clean:
	rm -f *.o
	rm -f slider
