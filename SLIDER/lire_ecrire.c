#include <stdio.h>
#include <stdlib.h>
#include "mes_types.h"

SLIDER
lire_taille (FILE * fichier, SLIDER S)	//Lit la taille dans le fichier
{
  fscanf (fichier, "%d %d ", &S.L, &S.H);
  return S;
}

SLIDER
lire_position (FILE * fichier, SLIDER S)	//Lit la position du Slider dans le fichier
{
  fscanf (fichier, "%d %d ", &S.x, &S.y);
  S.ps.x = S.x * Taille_Case + (Taille_Case / 2);
  S.ps.y = S.y * Taille_Case + (Taille_Case / 2);
  return S;
}

SLIDER
lire_sortie (FILE * fichier, SLIDER S)	//Lit la position de la sortie dans le fichier
{
  fscanf (fichier, "%d %d ", &S.sx, &S.sy);
  return S;
}

SLIDER
lire_murs (FILE * fichier, SLIDER S)	//Alloue de la memoire & lit les murs dans le fichier 
{
  fscanf (fichier, "%d ", &S.N);
  S.murx = malloc ((S.N) * sizeof (int));
  S.mury = malloc ((S.N) * sizeof (int));
  S.murz = malloc ((S.N) * sizeof (int));
  printf ("N= %d \n", S.N);
  int n = 0;
  while (n != S.N)
    {
      fscanf (fichier, "%d %d %d", &S.murx[n], &S.mury[n], &S.murz[n]);
      printf ("%d %d %d \n", S.murx[n], S.mury[n], S.murz[n]);
      n++;
    }

  return S;
}



SLIDER
init_slider (char *nom)		// Initialise les valeurs de la structure du SLIDER
{

  FILE *fichier = NULL;
  printf ("nom du fichier = %s \n", nom);
  fichier = fopen (nom, "r");
  if (fichier == NULL)
    {
      printf ("impossible d'ouvrir le fichier");
      exit (0);
    }

  SLIDER S;
  S = lire_taille (fichier, S);
  S = lire_position (fichier, S);
  S = lire_sortie (fichier, S);
  S = lire_murs (fichier, S);
  fclose (fichier);
  return S;
}
