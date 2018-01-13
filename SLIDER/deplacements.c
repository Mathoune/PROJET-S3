#include <stdio.h>
#include <stdlib.h>
#include <uvsqgraphics.h>
#include "mes_types.h"
#include "jeu.h"
#include "afficher.h"



/*mur_VerticalG : Test sur toute la ligne si il y a un mur vertical, s'il y en a un prend la valeur de la case à gauche, puis compare
 * laquelle est plus pres du Slider*/
int
mur_verticalG (SLIDER S)	// Retourne la postion à gauche du mur le plus proche à gauche du slider
{
  int a, tmp, n;
  a = tmp = -1;
  for (n = 0; n < S.N; n++)
    {
      if (S.mury[n] == S.y && S.murx[n] == S.x && S.murz[n] == 9)
	return S.x;
      if (S.mury[n] == S.y && S.murx[n] < S.x && S.murz[n] == 9)
	tmp = S.murx[n];
      if (S.mury[n] == S.y && S.murx[n] < S.x && S.murz[n] == 3)
	tmp = S.murx[n] + 1;
      if (tmp > a)
	a = tmp;
    }
  if (a == -1)
    a = 0;
  return a;
}

int
mur_verticalD (SLIDER S)	// Retourne la postion à droite du mur le plus proche à droite du slider
{
  int a, tmp, n;
  a = tmp = S.L + 1;

  for (n = 0; n < S.N; n++)
    {
      if (S.mury[n] == S.y && S.murx[n] == S.x && S.murz[n] == 3)
	return S.x;
      if (S.mury[n] == S.y && S.murx[n] > S.x && S.murz[n] == 9)
	tmp = S.murx[n] - 1;
      if (S.mury[n] == S.y && S.murx[n] > S.x && S.murz[n] == 3)
	tmp = S.murx[n];
      if (tmp < a)
	a = tmp;
    }
  if (a == S.L + 1)
    a = S.L - 1;

  return a;
}

int
mur_horizontalH (SLIDER S)	// Retourne la position du slider au dessus du mur le plus proche de lui
{
  int a, tmp, n;
  a = tmp = S.H + 1;
  for (n = 0; n < S.N; n++)
    {
      if (S.mury[n] == S.y && S.murx[n] == S.x && S.murz[n] == 0)
	return S.y;
      if (S.murx[n] == S.x && S.mury[n] > S.y && S.murz[n] == 0)
	tmp = S.mury[n];
      if (S.murx[n] == S.x && S.mury[n] > S.y && S.murz[n] == 6)
	tmp = S.mury[n] - 1;
      if (tmp < a)
	a = tmp;
    }
  if (a == S.H + 1)
    a = S.H - 1;

  return a;
}

int
mur_horizontalB (SLIDER S)	// retourne la position du slider en dessous du mur le plus proche de lui
{
  int a, tmp, n;
  a = tmp = -2;
  for (n = 0; n < S.N; n++)
    {
      if (S.mury[n] == S.y && S.murx[n] == S.x && S.murz[n] == 6)
	return S.y;
      if (S.murx[n] == S.x && S.mury[n] < S.y && S.murz[n] == 0)
	tmp = S.mury[n] + 1;
      if (S.murx[n] == S.x && S.mury[n] < S.y && S.murz[n] == 6)
	tmp = S.mury[n];
      if (tmp > a)
	a = tmp;
    }
  if (a == -2)
    a = 0;
  return a;
}

SLIDER
avance_droite (SLIDER S)	//Avance le Slider vers la droite
{
  int a, i;
  a = mur_verticalD (S);

  if (S.x < S.sx && a > S.sx && S.y == S.sy)
    {
      a = S.sx;
    }
  S.x = a;
  a = a * Taille_Case + (Demi_Case);
  for (i = S.ps.x; i < a; i += Taille_Case)
    {
      attendre (10);
      effacer_le_slider (S);
      S.ps.x += Taille_Case;
      afficher_le_slider (S);
    }
  return S;
}

SLIDER
avance_gauche (SLIDER S)	//Avance le Slider vers la gauche
{
  int a, i;
  a = mur_verticalG (S);
  if (S.x > S.sx && a < S.sx && S.y == S.sy)
    {
      a = S.sx;
    }
  S.x = a;
  a = a * Taille_Case + (Demi_Case);
  for (i = S.ps.x; i > a; i -= Taille_Case)
    {
      attendre (10);
      effacer_le_slider (S);
      S.ps.x -= Taille_Case;
      afficher_le_slider (S);
    }
  return S;
}

SLIDER
avance_haut (SLIDER S)		//Avance le Slider vers le haut
{
  int a, i;
  a = mur_horizontalH (S);
  if (S.y < S.sy && a > S.sy && S.x == S.sx)
    {
      a = S.sy;
    }
  S.y = a;
  a = a * Taille_Case + (Demi_Case);
  for (i = S.ps.y; i < a; i += Taille_Case)
    {
      attendre (10);
      effacer_le_slider (S);
      S.ps.y += Taille_Case;
      afficher_le_slider (S);
    }

  return S;
}

SLIDER
avance_bas (SLIDER S)		//Avance le Slider vers le bas
{
  int a, i;
  a = mur_horizontalB (S);
  if (S.y > S.sy && a < S.sy && S.x == S.sx)
    {
      a = S.sy;
    }
  S.y = a;
  a = a * Taille_Case + (Demi_Case);
  for (i = S.ps.y; i > a; i -= Taille_Case)
    {
      attendre (10);
      effacer_le_slider (S);
      S.ps.y -= Taille_Case;
      afficher_le_slider (S);
    }
  return S;
}

SLIDER
deplace (int f, SLIDER S)	//Gere tout le deplacement, selon la fleche appuyée
{
  if (f == FLECHE_GAUCHE)
    S = avance_gauche (S);
  if (f == FLECHE_DROITE)
    S = avance_droite (S);
  if (f == FLECHE_HAUTE)
    S = avance_haut (S);
  if (f == FLECHE_BAS)
    S = avance_bas (S);
  return S;
}
