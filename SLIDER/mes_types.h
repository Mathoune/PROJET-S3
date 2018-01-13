#include <uvsqgraphics.h>
#define Taille_Case 50
#define Demi_Case 25

struct slider {
	int L,H;	// Largeur et hauteur de la grille
	int x,y; 	// Position du slider en nombre de case
	POINT ps;	// Position du slider en coordonnées
	int sx,sy;   // Position sortie
	int N; 		// Nombre de murs
	int *murx; // Position en x des murs
	int *mury; // Position en y des murs
	int *murz; // Direction des murs
};
typedef struct slider SLIDER;


struct element{ // Liste chainée pour sauvegarder la position du slider
  POINT ps;
  struct element *suiv;
};
typedef struct element *LISTE;
