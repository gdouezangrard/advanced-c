
#ifndef MP3_H_
#define MP3_H_

/****************  Includes  ****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****************  Macros  ****************/


#define REPERT_CHAMP_TAILLE_1 127 /* Taille des champs des fiches */
#define REPERT_CHAMP_TAILLE REPERT_CHAMP_TAILLE_1+1


#define str(x) # x
#define xstr(x) str(x)


/****************  Type definitions  ****************/


typedef struct Mp3Entry_ {
  char artist[REPERT_CHAMP_TAILLE];               /* chanteur ou groupe  */
  char title[REPERT_CHAMP_TAILLE];                /* chanson */
  char album[REPERT_CHAMP_TAILLE];                /* album */
  int year;                      /* l'année */
} Mp3Entry;


typedef struct Mp3List_ {
  struct Mp3List_ * suivant;  /* Pointeur sur l'élément suivant */
  Mp3Entry mp3;              /* le mp3          */
} Mp3List;


typedef Mp3List * Mp3Lib;     /* Définition d'une liste*/


/****************  Static function prototypes  ****************/


int repertInit     (Mp3Lib * repert);
int repertCherche  (Mp3Lib * repert, char * titre, char *artiste, char *album, int *annee);
int repertAjoute   (Mp3Lib * repert, char * titre, char * artiste, char *album,int annee);
// affiche les entrées de la bibliothèque
// retourne le nombre d'entrées affichées
int repertAffiche(Mp3Lib *repert);
int repertSaisie   (char* titre, char* artiste, char* album, int* annee);

#endif /* MP3_H_ */
