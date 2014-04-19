#include "mp3.h"

#include <stdio.h>

#define GETS_ERROR(v) if (NULL==(v)) { fprintf(stderr,"\nerror on gets (%s,%d)\n",__FILE__,__LINE__); return EXIT_FAILURE; }

/****************  Main function  ****************/


int
main(int argc, char * argv[])
{
	Mp3Lib mp3Library;                           
	char artist[MP3_FIELD_LEN];       
	char title[MP3_FIELD_LEN];         
	char album[MP3_FIELD_LEN];     
	char buffer[MP3_FIELD_LEN];
	int year;

	mp3LibInit(&mp3Library);


	while (1) {
		printf ("Entrez le titre (+ pour nouveau, . pour quitter) : ");
		GETS_ERROR(fgets(buffer,MP3_FIELD_LEN,stdin));
		sscanf(buffer,"%s",title);

		if (strcmp(title,"+")==0) {
			printf ("Ajout d'un nouveau titre\n");
			printf ("Entrez le titre : ");
			GETS_ERROR(fgets(buffer,MP3_FIELD_LEN,stdin));
			sscanf(buffer,"%s",title);
			printf ("Entrez l'artiste : ");
			GETS_ERROR(fgets(buffer,MP3_FIELD_LEN,stdin));
			sscanf(buffer,"%s",artist);
			printf ("Entrez l'album : ");
			GETS_ERROR(fgets(buffer,MP3_FIELD_LEN,stdin));
			sscanf(buffer,"%s",album);
			printf ("Entrez l'annee : ");
			GETS_ERROR(fgets(buffer,MP3_FIELD_LEN,stdin));
			sscanf(buffer,"%d", &year); // or atoi

			if (mp3LibAdd(&mp3Library, title,artist,album,year) != 0)
			  printf ("Désolé, je n'ai pas pu ajouter la fiche.\n");
		}
		else if (strcmp(title, ".") == 0)
		  return (0);
		else if (strcmp(title,">")==0)
		  mp3LibPrint(stderr,&mp3Library);
		else {                           
		  if (mp3LibSearchByTitle (&mp3Library,title,artist,album,&year) != 0) 
		    printf ("Désolé, je ne connais pas le titre \"%s\".\n", title);
		  else                                   
		    printf ("Le titre \"%s\" est de %s (album %s, annee %d).\n",
			    title, artist,album,year);
		}
	}
}
