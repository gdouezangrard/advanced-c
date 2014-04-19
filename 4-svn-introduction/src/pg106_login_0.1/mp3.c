#include "mp3.h"


int
repertInit(Mp3Lib * repert)
{
	/* Dans cette implémentation, la liste est vide */
	*repert = NULL;
	return (0);
}


int repertCherche  (Mp3Lib * repert,
		char * titre,
		char *artiste,
		char *album,
		int *annee){
	Mp3List * liste;  /*  Le répertoire courant  */

	for (liste = *repert; liste != NULL; liste = liste->suivant) {
		/*  Si le titre recherché trouvé  */
		if (strcmp(liste->mp3.title, titre) == 0) {
			strcpy(artiste, liste->mp3.artist);
			strcpy(album, liste->mp3.album);
			*annee=liste->mp3.year;
			/*  Titre trouvé  */
			return (0);
		}
	}

	/*  Nom pas trouvé  */
	return (1);
}


int repertAjoute   (Mp3Lib * repert,
		char * titre,
		char * artiste,
		char *album,
		int annee){
	Mp3List * nouveau;  /*  Le répertoire courant   */
	Mp3List * liste;

	if ((nouveau = malloc(sizeof(Mp3List))) == NULL) {
		/*  Si pas possible de créer liste  */
		return (1);
	}

	strncpy(nouveau->mp3.title, titre, REPERT_CHAMP_TAILLE);
	nouveau->mp3.title[REPERT_CHAMP_TAILLE_1] = '\0';
	strncpy(nouveau->mp3.artist, artiste, REPERT_CHAMP_TAILLE);
	nouveau->mp3.artist[REPERT_CHAMP_TAILLE_1] = '\0';
	strncpy(nouveau->mp3.album, album, REPERT_CHAMP_TAILLE);
	nouveau->mp3.album[REPERT_CHAMP_TAILLE_1] = '\0';
	nouveau->mp3.year=annee;

	liste = *repert;            /*  Récupère pointeur sur le premier élément  */
	nouveau->suivant = liste;
	*repert = nouveau;

	/*  Tout s'est bien passé  */
	return (0);
}

int repertSaisie(char* titre, char* artiste, char* album, int* annee)
{
	printf ("Ajout d'un nouveau titre\n");
	printf ("Entrez le titre : ");
	scanf  ("%" xstr(REPERT_CHAMP_TAILLE_1) "s", artiste);
	artiste[REPERT_CHAMP_TAILLE_1] = '\0';
	printf ("Entrez l'artiste : ");
	scanf  ("%" xstr(REPERT_CHAMP_TAILLE_1) "s", titre);
	titre[REPERT_CHAMP_TAILLE_1] = '\0';
	printf ("Entrez l'album : ");
	scanf  ("%" xstr(REPERT_CHAMP_TAILLE_1) "s", album);
	album[REPERT_CHAMP_TAILLE_1] = '\0';
	printf ("Entrez l'annee : ");
	scanf  ("%d", annee);

    return(0);
}

static int ficheAffiche(Mp3Entry* entry){
    printf ("Le titre \"%s\" est de %s (album %s, annee %d).\n",
                entry->title, entry->artist, entry->album,entry->year);
    
    return(0);
}

int repertAffiche(Mp3Lib *repert){
	// a vous d'écrire le code
}