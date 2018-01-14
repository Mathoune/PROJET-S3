#include <stdlib.h>
#include <stdio.h>
#include <uvsqgraphics.h>
#include "mes_types.h"
#include "afficher.h"


SLIDER
ecrire_taille_init (FILE * f, int L, int H, SLIDER S)	//Ecrit la taille de la fenetre dans le fichier & affiche la grille
{
  fprintf (f, "%d %d \n", L, H);
  S.L = L;
  S.H = H;
  initialiser_affichage (S);
  afficher_grille (S);
  return S;
}

SLIDER
ecrire_position_sortie (FILE * f, SLIDER S)	//Ecrit la position de la sortie dans le fichier & l'affiche
{
  int a, fl;
  char c;
  POINT p;
  a = 0;
  fprintf (stderr, "Cliquez pour afficher la sortie \n");
  while (a != EST_CLIC)
    {
      a = wait_key_arrow_clic (&c, &fl, &p);
    }
  S.sx = p.x / Taille_Case;
  S.sy = p.y / Taille_Case;
  afficher_sortie (S);
  fprintf (f, "%d %d \n", S.sx, S.sy);
  return S;
}

SLIDER
ecrire_position_slider (FILE * f, SLIDER S)	//Ecrit la position du Slider dans le fichier & l'affiche
{
  int a, fl;
  char c;
  POINT p;
  a = 0;
  fprintf (stderr, "Cliquez pour afficher le Slider \n");
  while (a != EST_CLIC)
    {
      a = wait_key_arrow_clic (&c, &fl, &p);
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
mur_fichier (FILE * f, int n, SLIDER S)	//Affiche le mur dans le fichier && sur la fenetre
{
  fprintf (f, "%d %d %d\n", S.murx[n], S.mury[n], S.murz[n]);
  afficher_murs (S, n, n);

  return S;
}

SLIDER
tourne (POINT p, int n, int i, SLIDER S)	//Permet d'effacer le mur avant et d'affihcer le nouveau mur
{
  S.murx[n] = p.x / Taille_Case;
  S.mury[n] = p.y / Taille_Case;
  if (i == 0)
    {
      S.murz[n] = 9;
      efface_mur (S, n);
      S.murz[n] = 0;
      afficher_murs (S, n, n);
    }
  if (i == 1)
    {
      S.murz[n] = 0;
      efface_mur (S, n);
      S.murz[n] = 3;
      afficher_murs (S, n, n);
    }
  if (i == 2)
    {
      S.murz[n] = 3;
      efface_mur (S, n);
      S.murz[n] = 6;
      afficher_murs (S, n, n);
    }
  if (i == 3)
    {
      S.murz[n] = 6;
      efface_mur (S, n);
      S.murz[n] = 9;
      afficher_murs (S, n, n);
    }
  return S;
}

SLIDER
mur (SLIDER S, int n, FILE * f)	// Permet de creer un mur
{
  int a, i, fl, m;
  char c;
  POINT p, p1;
  a = i = 0;
  m = n;
  while (n == m)
    {
		  a = wait_key_arrow_clic (&c, &fl, &p);
		  p1 = p;
		  while (a == EST_CLIC && (p1.x / Taille_Case == p.x / Taille_Case)
			 && (p1.y / Taille_Case == p.y / Taille_Case) && i <= 4)
		{
		  S = tourne (p, n, i, S);
		  a = wait_key_arrow_clic (&c, &fl, &p1);
		  i++;
		}
		  if (i <= 4)
		{
		  S = mur_fichier (f, n, S);
		  n++;
		}
		  if (i == 5)
		{
		  efface_mur (S, n);
		  i = 0;
		}

    }
  return S;
}

SLIDER
ecrire_murs (FILE * f, SLIDER S)	//Cree les murs dans la memoire
{
  int n;
  n = 0;
  S.murx = malloc ((S.N) * sizeof (int));
  S.mury = malloc ((S.N) * sizeof (int));
  S.murz = malloc ((S.N) * sizeof (int));

  fprintf (stderr,
	   "Cliquez une fois dans une case, \n puis à chaque clic fait tourner la position du mur \n");
  fprintf (stderr, "Au bout de 6 clics, efface le mur \n");

  while (n < S.N)
    {
      S = mur (S, n, f);
      n++;
    }
  return S;
}

SLIDER
editeur (SLIDER S, int L, int H, char *nom)	//Gere l'edition
{
  FILE *f = NULL;
  int fl;
  char c;
  POINT p;

  f = fopen (nom, "w+");
  S = ecrire_taille_init (f, L, H, S);
  S = ecrire_position_slider (f, S);
  S = ecrire_position_sortie (f, S);
  S = ecrire_nb_murs (f, S);
  S = ecrire_murs (f, S);
  
  fprintf (stderr, "Appuyez sur S pour sauvegarder le niveau");
  wait_key_arrow_clic (&c, &fl, &p);

  if (c == 'S')
    {
      if (fclose (f) != 0)
	  fprintf (stderr, "ERREUR fermeture");
      return S;
      
    }
  else // Si on a pas sauvegarde on recommence le mode edition
    editeur (S, L, H, nom);

  return S;
}
