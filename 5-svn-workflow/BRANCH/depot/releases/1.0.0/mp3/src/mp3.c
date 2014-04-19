#include "mp3.h"

typedef struct Mp3Entry_ {
  char artist[MP3_FIELD_LEN];               
  char title[MP3_FIELD_LEN];                
  char album[MP3_FIELD_LEN];                
  int year;                      
} Mp3Entry;


struct Mp3List_ {
  struct Mp3List_ * next;  /* Pointer do the next cell */
  Mp3Entry mp3;            /* current mp3 data          */
};

typedef struct Mp3List_ Mp3List;

//#define str(x) # x
//#define xstr(x) str(x)

int mp3LibInit(Mp3Lib * library)
{
  /* Initially the list is empty */
  *library = NULL;
  return (0);
}


int mp3LibSearchByTitle  (Mp3Lib * library,
			  char * title,
			  char *artist,
			  char *album,
			  int *year){
  Mp3List * current; 

  for (current = *library; current != NULL; current = current->next) {
    if (strcmp(current->mp3.title, title) == 0) {
      strcpy(artist, current->mp3.artist);
      strcpy(album, current->mp3.album);
      *year=current->mp3.year;
      return (0);
    }
  }
  return (1);
}


int mp3LibAdd   (Mp3Lib * library,
		 char * title,
		 char * artist,
		 char *album,
		 int year){
  Mp3List * novelElement;
  Mp3List * list;

  if ((novelElement = malloc(sizeof(Mp3List))) == NULL) {
    return (1);
  }

  strncpy(novelElement->mp3.title, title, MP3_FIELD_LEN);
  novelElement->mp3.title[MP3_FIELD_LEN-1] = '\0';
  strncpy(novelElement->mp3.artist, artist, MP3_FIELD_LEN);
  novelElement->mp3.artist[MP3_FIELD_LEN-1] = '\0';
  strncpy(novelElement->mp3.album, album, MP3_FIELD_LEN);
  novelElement->mp3.album[MP3_FIELD_LEN-1] = '\0';
  novelElement->mp3.year=year;

  list = *library;
  novelElement->next = list;
  *library = novelElement;
  free(novelElement);
  return (0);
}

int mp3LibPrintMp3(FILE *stream,Mp3Entry *mp3){
  fprintf(stream,"%s = %s = [ %s ] ( %d )\n",mp3->title,mp3->artist,mp3->album,mp3->year);
  return 0;
}

int mp3LibPrint(FILE *stream,Mp3Lib *library){
  Mp3List *current = *library;

  while(current!=NULL){
    if (mp3LibPrintMp3(stream,&(current->mp3))!=0) return 1;
    current=current->next;
  };
  return 0;
}
