#include<stdio.h>
#include<stdlib.h>

typedef struct _element{
  int value;
  struct _element *next;
} element;

element *new_element(int value){
  element *e=malloc(sizeof(element *));
  e->value=value;
  return e;
}

void append(element **list, element *last){
  if (*list==NULL){
    *list=last;
    return;
  }
  append(&((*list)->next),last);
}
void print(element *e){
  if (e==NULL) {
    printf("\n");
    return;
  }
  printf("%d ",e->value);
  print(e->next);
}

void remove_elements(element **l,int value){
  element *tmp;
  if ((*l)==NULL) return;
  if ((*l)->value==value){
    tmp=*l;
    *l=tmp->next;
    remove_elements(l,value);
  } else remove_elements(&((*l)->next),value);
}

int main(){
  element *list=NULL;
  int i;
  for(i=0;i<1000;i++){
    append(&list,new_element(rand()%10));
  }
  print(list);
  remove_elements(&list,0);
  print(list);
  return EXIT_SUCCESS;
}
