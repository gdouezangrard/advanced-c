#include "communication_mock_data.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int com_init(){
  assert(0 && "don't use com_init for this mock but com_mockinit instead");
}


int rleft=0;
int rright=0;
int wleft=0;
int wright=0;

static char **expected_left;
static char **expected_right;
static char **send_left;
static char **send_right;

int com_mockinit(char **expected_left_,		 
		 char **expected_right_,
		 char **send_left_,
		 char **send_right_){  
  int rleft=0;
  int rright=0;
  int wleft=0;
  int wright=0;
  
  expected_left=expected_left_;
  expected_right=expected_right_;
  send_left=send_left_;
  send_right=send_right_;
  return 0;
}

int com_read_left(char *buffer, int buffer_size){
  if (send_left[wleft]==NULL) return -1;
  strcpy(buffer,send_left[wleft++]);
  return strlen(buffer);
}

int com_read_right(char *buffer, int buffer_size){
  if (send_right[wright]==NULL) return -1;
  strcpy(buffer,send_right[wright++]);
  return strlen(buffer);
}
int com_write_left(char *buffer){
  if (expected_left[rleft]==NULL) return -1;
  assert(strcmp(expected_left[rleft++],buffer)==0);
  return 0;
}
int com_write_right(char *buffer){
  if (expected_right[rright]==NULL) return -1;
  assert(strcmp(expected_right[rright++],buffer)==0);
  return 0;
}
