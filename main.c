
#include "lehrerin.h"
#include "outils.h"
#include <stdio.h>

int main(int argc, char **argv)
{ char *line[1];
  t_trad *trad[1];
  *trad = extraction();
  TINI();
  while (GNL(1, line) > 0)
  { if (**line == 'q')
    { break; }
    else
    { printf("HI!\n"); }
    DEL((void**)line); }
  TEND((void*)0); }
