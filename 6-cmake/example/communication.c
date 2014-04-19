#include "communication.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static char *Client_Id;
static int From_Fd;
static int To_Fd;

int com_init(){
  Client_Id=getenv("BOGGLE_ID");
  if (Client_Id==NULL) return -1;
  From_Fd=open("boggle_from",O_RDONLY);
  if (From_Fd==-1)
    return -1;
  To_Fd=open("boggle_to",O_WRONLY);
  if (To_Fd==-1)
    return -1;
  return 0;
}

int com_read(char *prefix,char *buffer, int buffer_size){
  static char ibuffer[MAX_BUF_SIZE*2];
  int i=sprintf(ibuffer,"%s %s \n",prefix,Client_Id);
  if (write(To_Fd,ibuffer,i)==-1)
    return -1;
  i=read(From_Fd,ibuffer,MAX_BUF_SIZE*2-1);
  if (i==-1)
    return -1;
  ibuffer[i]='\0';
  i-=1;
  while((i>0) && (isspace(ibuffer[i]))){
    ibuffer[i]='\0';
    i-=1;
  }
  if (i==0) return 0;
  if (i>buffer_size) return -1;
  strcpy(buffer,ibuffer);
  return i;
}

int com_read_left(char *buffer, int buffer_size){
  return com_read("RL",buffer,buffer_size);
}
int com_read_right(char *buffer, int buffer_size){
  return com_read("RR",buffer,buffer_size);
}

int com_write(char *prefix,char *buffer){
  static char ibuffer[MAX_BUF_SIZE*2];
  int i=sprintf(ibuffer,"%s %s %s\n",prefix,Client_Id,buffer);
  if (write(To_Fd,ibuffer,i)==-1)
    return -1;
  return 0;
}

int com_write_left(char *buffer){
  return com_write("WL",buffer);
}
int com_write_right(char *buffer){
  return com_write("WR",buffer);
}
