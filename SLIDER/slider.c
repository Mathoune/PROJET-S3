#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mes_types.h"
#include "lire_ecrire.h"
#include "afficher.h"
#include "listes_memo.h"
#include "jeu.h"
#include "editeur.h"
#include "lire_dossier.h"

int
main (int argc, char *argv[])
{
  printf ("Debut slider\n");

  SLIDER S;
  LISTE l = NULL;
  char *c;
  c = "dir_slider";

  if (argv[1][0] == '-' && argv[1][1] == 'c')	//On verifie si c'est le mode edition
    {
      int L, H;
      L = atoi (argv[2]);	// Convertit les nombres donnés en entiers
      H = atoi (argv[3]);
      S = editeur (S, L, H, argv[4]);	//Initialise le Slider en mode edition
      partie (S, argv[4], l);
    }
  if (strcmp (argv[1], c) == 0)	// On verifie si c'est le mode de lecture du dossier complet
    {
      ouvrir_dir (S, l);
    }

  else				//Sinon on joue une partie classique
    partie (S, argv[1], l);

  exit (0);
}
