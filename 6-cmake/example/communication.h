#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define MAX_BUF_SIZE 1024

int com_init();
int com_read_left(char *buffer, int buffer_size);
int com_read_right(char *buffer, int buffer_size);
int com_write_left(char *buffer);
int com_write_right(char *buffer);

#endif
