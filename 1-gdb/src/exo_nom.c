#include <stdio.h>
#include <stdlib.h>

int
main (void) {
  char * s;
  char c;
  unsigned int l, i;

  printf ("Entrer la longueur de votre nom : ");
  scanf ("%d", &l);

  s = (char *) malloc (l * sizeof (char));
  if (! (s = NULL)) {
    printf ("Entrer votre nom : ");
    c = getchar();
    c = getchar();
    i = 0;
    while ((c != '\n') && (i < l - 1)) {
      s[i] = c;
      c = getchar();
      i++;
    }
    s[i] = '\0';

    printf ("Vous vous appelez : %s\n", s);

    free (s);
  }

  return EXIT_SUCCESS;
}