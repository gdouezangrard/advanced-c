#ifndef MP3_H_
#define MP3_H_

/****************  Includes  ****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****************  Macros  ****************/

#define MP3_FIELD_LEN 128

/****************  Type definitions  ****************/

struct Mp3List_;

typedef struct Mp3List_ * Mp3Lib;     /* Définition d'une liste*/


/****************  Static function prototypes  ****************/


int mp3LibInit(Mp3Lib * library);
int mp3LibSearchByTitle (Mp3Lib * library,char * title,char *artist,char *album,int *year);
int mp3LibAdd (Mp3Lib * library, char * title, char * artist, char *album, int year);
int mp3LibPrint(FILE *stream,Mp3Lib *library);

#endif /* MP3_H_ */
