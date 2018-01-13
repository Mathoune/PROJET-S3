#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>		//Permet d'utiliser des fonction pour les dossiers et repertoires
#include <string.h>
#include <uvsqgraphics.h>
#include "mes_types.h"
#include "jeu.h"


#define nb_fichiers 4
/* Dans le mode de lecture de plusieurs fichiers, j'ai une perte de memoire constante de 1173 blocks
 * 
 */

void
lireDossier (char *s, DIR * rep, char *nom[nb_fichiers])	//Permet de lire le nom de chaque fichier dans le dossier
{
  int i = 0;
  struct dirent *ent = NULL;
  while ((ent = readdir (rep))&& i<nb_fichiers)
    {
      if (strcmp (ent->d_name, ".") != 0 && strcmp (ent->d_name, "..") != 0)
	{
	  nom[i] = ent->d_name;
	  printf("nom[%d]= %s \n",i, nom[i]);  
	  i++;	
	  
	}
	

    }
}

DIR *
parcourirDossier (DIR * rep, char *nom[nb_fichiers])
{
  char *chemin = "dir_slider";
  rep = opendir (chemin);

  if (rep == NULL)
    {
      printf ("Le dossier '%s' n'a pas pu etre ouvert", chemin);
      exit (-1);
    }
  lireDossier (chemin, rep, nom);
  return rep;
}

void
ouvrir_dir (SLIDER S, LISTE l)
{
  DIR *rep = NULL;
  char *nom[nb_fichiers];
  int i = 0;
  rep=parcourirDossier (rep, nom);

  while (i != nb_fichiers)	//On recommence le jeu pour chaque fichier
    {
      char chemin[100] = "dir_slider/";
      strcat (chemin, nom[i]);
      partie (S, chemin, l);	//Joue le jeu 
      i++;
    }

  if (closedir(rep) == -1)
    {
      printf ("fermeture dossier impossible");
      exit (-1);
    }
}
