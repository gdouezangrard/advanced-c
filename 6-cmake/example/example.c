#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef MOCKDATA
#include "communication_mock_data.h"
#else
#include "communication.h"
#endif


int main(){
  char buffer[MAX_BUF_SIZE];
  int r;
#if defined(MOCKDATA)
  char *excpected_left[]={"hello",NULL};
  char *excpected_right[]={"world",NULL};
  char *send_left[]={"",NULL};
  char *send_right[]={"",NULL};
  com_mockinit(excpected_left,excpected_right,send_left,send_right);
#else
  if (com_init()==-1){
    fprintf(stderr,"error on init!");
    exit(EXIT_FAILURE);
  }
#endif
  while(1){
    com_write_left("hello");
    com_write_right("world");
    r=com_read_left(buffer,MAX_BUF_SIZE);
    if (r<0){
      fprintf(stderr,"failed to read left!");
      exit(EXIT_FAILURE);
    }
    if (r>0){
      printf("%s",buffer);
    }
    printf("\t|\t");
    r=com_read_right(buffer,MAX_BUF_SIZE);
    if (r<0){
      fprintf(stderr,"failed to read right!");
      exit(EXIT_FAILURE);
    }
    if (r>0){
      printf("%s",buffer);
    }    
    printf("\n");
    usleep(2000);
  }
}
