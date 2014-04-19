#include "communication.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static int fd_left_read, fd_left_write, fd_right_read, fd_right_write;

int com_init(){
  fd_left_read=open("left_in",O_RDONLY);
  if (fd_left_read==-1) return -1;
  fd_left_write=open("left_out",O_WRONLY|O_CREAT,0600);
  if (fd_left_write==-1) return -1;
  fd_right_read=open("right_in",O_RDONLY);
  if (fd_right_read==-1) return -1;
  fd_right_write=open("right_out",O_WRONLY|O_CREAT,0600);
  if (fd_right_write==-1) return -1;
  return 0;
}

int com_read(int fd,char *buffer, int buffer_size){
  char c;
  int i=0,r;
  while(((r=read(fd,&c,1))==1) && (c!='\n')&&(i<buffer_size)){
    buffer[i]=c;
    i+=1;
  }
  buffer[i]='\0';
  if (c=='\n') return i-1;
  if (r==0) return 0;
  return -1;
}

int com_read_left(char *buffer, int buffer_size){
  return com_read(fd_left_read,buffer,buffer_size);
}

int com_read_right(char *buffer, int buffer_size){
  return com_read(fd_right_read,buffer,buffer_size);
}

int com_write(int fd,char *buffer){
  char c='\n';
  if (write(fd,buffer,strlen(buffer))==-1)
    return -1;
  if (write(fd,&c,1)==-1)
    return -1;
  return 0;
}

int com_write_left(char *buffer){
  return com_write(fd_left_write,buffer);
}

int com_write_right(char *buffer){
  return com_write(fd_right_write,buffer);
}
