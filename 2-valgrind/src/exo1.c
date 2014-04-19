#include <stdio.h>
#include <stdlib.h>

typedef struct cell liste_t;
struct cell {
  int donnee;
  liste_t *suivante;
};

liste_t *
liste_ajouter (liste_t *l, unsigned int pos, int donnee)
{
  liste_t *c = NULL;

  if (pos == 0) {
    c = malloc (sizeof (liste_t));
    if (c == NULL)
      return NULL;
    c->donnee   = donnee;
    c->suivante = l;
    return (c);
  }
  else {
    l->suivante = liste_ajouter (l->suivante, pos - 1, donnee);
    return (l);
  }
}

void
liste_detruire (liste_t *l) {
  if (l != NULL) {
    liste_detruire (l->suivante);
    free (l);
  }
}

int main ()
{
  liste_t *l, *l2, *l3;;

  l  = liste_ajouter (NULL, 0, 5);
  l2 = liste_ajouter (l, 2, 5);
  l3 = liste_ajouter (l2, 1, 5);

  liste_detruire (l3);

  return (0);
}
