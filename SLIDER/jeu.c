#include <stdlib.h>
#include <stdio.h>
#include <uvsqgraphics.h>
#include "mes_types.h"
#include "afficher.h"
#include "deplacements.h"
#include "listes_memo.h"
#include "lire_ecrire.h"

int
sortie (SLIDER S)		//Test si le Slider est dans la sortie
{
  S.sx = S.sx * Taille_Case + Demi_Case;
  S.sy = S.sy * Taille_Case + Demi_Case;
  if (S.ps.x == S.sx && S.ps.y == S.sy)
    return 0;
  return 1;
}


LISTE
bouge (SLIDER S, LISTE l)	//Gere le mouvement du Slider
{
  char c;
  int a, f;
  POINT p;
  l = ajout (l, S);
  while (sortie (S))
    {
      a = wait_key_arrow_clic (&c, &f, &p);
      SDL_EnableKeyRepeat (0, SDL_DEFAULT_REPEAT_INTERVAL);
      S.x = (S.ps.x - Demi_Case) / Taille_Case;
      S.y = (S.ps.y - Demi_Case) / Taille_Case;

      if (a == EST_FLECHE)
	{
	  S = deplace (f, S);
	  l = ajout (l, S);
	}
      if (a == EST_TOUCHE)
	{
	  l = retour (l, S, c);
	  S.ps = l->ps;
	  afficher_le_slider (S);

	}
      S.coups++;
    }
  return l;
}

void
partie (SLIDER S, char *nom, LISTE l)
{
  printf ("nom du fichier %s \n", nom);
  S = init_slider (nom);
  afficher_slider (S);
  l = bouge (S, l);
  finir_affichage (S);
  libere_murs (S);
  libere_liste (l);
  wait_escape ();
}
