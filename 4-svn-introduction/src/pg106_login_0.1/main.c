#include "mp3.h"


/****************  Main function  ****************/


int
main(int argc, char * argv[])
{
	Mp3Lib repert;                                  /* Le répertoire courant */
	char artiste[REPERT_CHAMP_TAILLE];                                   /* L'artiste courant        */
	char titre[REPERT_CHAMP_TAILLE];                                /* Le titre courant     */
	char album[REPERT_CHAMP_TAILLE];                                /* L'album courant     */
	int annee;

	repertInit(&repert);


	while (1) {                                     /* Récupération du nom */
		printf ("Entrez le titre (+ pour nouveau, . pour quitter) : ");
		scanf  ("%63s", titre);
		titre[63] = '\0';

		if (strcmp (titre, "+") == 0) {                 /* Si phase d'ajout */
			repertSaisie(titre, artiste, album, &annee);

			if (repertAjoute (&repert, artiste, titre,album,annee) != 0) /* Ajout de la nouvelle carte */
				printf ("Désolé, je n'ai pas pu ajouter la fiche.\n");
		}
		else if (strcmp(titre, ".") == 0)              /* Terminaison */
			return (0);
		else {                                        /* Phase de consultation          */
			if (repertCherche (&repert,titre,artiste,album,&annee) != 0) /* Si fiche pas trouvée */
				printf ("Désolé, je ne connais pas le titre \"%s\".\n", titre);
			else                                        /* Si carte trouvée */
				printf ("Le titre \"%s\" est de %s (album %s, annee %d).\n",
						titre, artiste,album,annee);
		}
	}
}
