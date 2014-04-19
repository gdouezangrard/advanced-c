#ifndef COMMUNICATION_MOCK_H
#define COMMUNICATION_MOCK_H
#include "communication.h"

extern int rleft;
extern int rright;
extern int wleft;
extern int wright;

int com_mockinit(char **expected_left,		 
		 char **expected_right,
		 char **send_left,
		 char **send_right);

#endif
