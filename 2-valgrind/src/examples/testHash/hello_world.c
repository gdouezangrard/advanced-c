/* This is a test program 	 */
/* Used in Purifying Hello World */
          
#include <stdio.h>
#include <malloc.h>
          
static char *helloWorld = "Hello, World";

main()
{
   char *mystr = malloc(strlen(helloWorld));
          
   strncpy(mystr, helloWorld, 12);
   printf("%s\n", mystr);
}


