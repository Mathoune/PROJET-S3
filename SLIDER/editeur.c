#include <stdlib.h>
#include <stdio.h>
#include <uvsqgraphics.h>
#include "mes_types.h"
#include "afficher.h"


SLIDER
ecrire_taille_init (FILE * f, int L, int H, SLIDER S)	//ecrit la taille de la fenetre dans le fichier & affiche la grille
{
  fprintf (f, "%d %d \n", L, H);
  S.L = L;
  S.H = H;
  initialiser_affichage (S);
  afficher_grille (S);
  return S;
}

SLIDER
ecrire_position_sortie (FILE * f, SLIDER S)	//ecrit la position de la sortie dans le fichier & l'affiche
{
  int a, fl;
  char c;
  POINT p;
  a = 0;
  while (a != EST_CLIC)
    {
      a = wait_key_arrow_clic (&c, &fl, &p);
      SDL_EnableKeyRepeat (0, SDL_DEFAULT_REPEAT_INTERVAL);
    }
  S.sx = p.x / Taille_Case;
  S.sy = p.y / Taille_Case;
  afficher_sortie (S);
  fprintf (f, "%d %d \n", S.sx, S.sy);

  return S;
}

SLIDER
ecrire_position_slider (FILE * f, SLIDER S)	//ecrit la position du Slider dans le fichier & l'affiche
{
  int a, fl;
  char c;
  POINT p;
  a = 0;
  while (a != EST_CLIC)
    {
      a = wait_key_arrow_clic (&c, &fl, &p);
      SDL_EnableKeyRepeat (0, SDL_DEFAULT_REPEAT_INTERVAL);
    }
  S.x = p.x / Taille_Case;
  S.y = p.y / Taille_Case;
  S.ps.x = ((S.x) * Taille_Case) + Demi_Case;
  S.ps.y = ((S.y) * Taille_Case) + Demi_Case;
  afficher_le_slider (S);
  fprintf (f, "%d %d \n", S.x, S.y);
  return S;
}

SLIDER
ecrire_nb_murs (FILE * f, SLIDER S)	//Demande nombre de murs
{
  printf ("indiquez le nombre de murs souhaité : ");
  scanf ("%d", &S.N);
  fprintf (f, "%d\n", S.N);
  return S;
}

SLIDER
place_mur (FILE * f, int fl, POINT p, int n, SLIDER S)	//Affiche le mur dans le fichier && sur la fenetre
{
  S.murx[n] = p.x / Taille_Case;
  S.mury[n] = p.y / Taille_Case;
  if (fl == FLECHE_HAUTE)
    S.murz[n] = 0;
  if (fl == FLECHE_DROITE)
    S.murz[n] = 3;
  if (fl == FLECHE_BAS)
    S.murz[n] = 6;
  if (fl == FLECHE_GAUCHE)
    S.murz[n] = 9;
  fprintf (f, "%d %d %d\n", S.murx[n], S.mury[n], S.murz[n]);
  afficher_murs (S, n, n);

  return S;
}

SLIDER
ecrire_murs (FILE * f, SLIDER S)	//Cree les murs dans la memoire
{

  int a, fl, n;
  char c;
  POINT p;
  a = n = 0;
  S.murx = malloc ((S.N) * sizeof (int));
  S.mury = malloc ((S.N) * sizeof (int));
  S.murz = malloc ((S.N) * sizeof (int));
  printf
    ("Cliquez sur la case dans laquelle vous voulez un mur, puis sur une fleche pour la placer dans la case");

  while (a != EST_CLIC && n != S.N)
    {
      a = wait_key_arrow_clic (&c, &fl, &p);
      while (a != EST_FLECHE)
	{
	  a = wait_key_arrow_clic (&c, &fl, &p);
	  S = place_mur (f, fl, p, n, S);
	}
      n++;
    }
  return S;
}

SLIDER
editeur (SLIDER S, int L, int H, char *nom)	//Gere l'edition
{
  FILE *f = NULL;
  f = fopen (nom, "w+");
  S = ecrire_taille_init (f, L, H, S);
  S = ecrire_position_slider (f, S);
  S = ecrire_position_sortie (f, S);
  S = ecrire_nb_murs (f, S);
  S = ecrire_murs (f, S);
  fclose (f);
  return S;
}
