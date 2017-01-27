
#include "lehrerin.h"
#include "outils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

t_trad *tralloc(void)
{ t_trad *tmp;
  tmp = (t_trad*)malloc(sizeof(t_trad));
  BZE(tmp, sizeof(t_trad));
  return (tmp); }

void deltab(char **tab)
{ int m = 0;
  while (tab[m])
  { free(tab[m]);
    m += 1; }
  free(tab); }

t_trad *get_time(t_trad *tmp, char *tab, int index)
{ int secds;
  int cents;
  if (LEN(tab) != 5)                                   //Temps mal formatté
  { ((*tmp).chrono)[index] = 0;
    return (tmp); }
  secds = atoi(tab);
  cents = atoi(tab + 3);
  if (secds < 0 || secds > 99 || cents < 0 || cents > 99) //Temps mal formatté
  { ((*tmp).chrono)[index] = 0;
    return (tmp); }
  ((*tmp).chrono)[index] = ((time_t)secds << 8) + (time_t)cents;
  return (tmp); }

t_trad *basic(t_trad **trad, char **tab)
{ t_trad *tmp;
  tmp = *trad;
  while (tmp)
  { if (!NCMP(tab[0], (*tmp).origine, LEN(tab[0])))
    { return ((void*)0); }
    tmp = (*tmp).next; }
  tmp = tralloc();
  (*tmp).origine = tab[0];
  *((*tmp).traduit) = tab[1];
  return (get_time(tmp, tab[2], 0)); }

t_trad *gettrad(t_trad *tmp, char **tab)
{ int i;
  if (!NCMP(tab[0], (*tmp).origine, LEN(tab[0])))
  { i = 0;
    while (((*tmp).traduit)[i] && i < 5)
    { if (!NCMP(tab[1], ((*tmp).traduit)[i], LEN(tab[1])))
      { (*tmp).flag |= Doublon;
        break; }
      i += 1; }
    if (!((*tmp).traduit)[i] && i < 5)
    { ((*tmp).traduit)[i] = tab[1];
      tmp = get_time(tmp, tab[2], i); }
    else if (i == 5)
    { (*tmp).flag |= TropDeSynonymes; }}
  return (tmp); }

int main(int argc, char **argv)
{ char *line[1];
  t_trad *trad[1];
  t_trad *tmp;
  char **tab;
  int i;
  *trad = (void*)0;
  int fd = open("./wortschatz.txt", O_RDONLY);
  while (GNL(fd, line) > 0)
  { tab = SPL(*line, ' ');
    if (!tab)                                             //Aucune donnée sur cette ligne
    { DEL((void**)line);
      continue; }
    else if (TLN(tab) != 3)                               //Donnée mal formattée (trop de champs)
    { DEL((void**)line);
      deltab(tab);
      continue; }
    if (*trad)
    { tmp = *trad;
      while ((*tmp).next)
      { tmp = gettrad(tmp, tab);
        tmp = (*tmp).next; }
      tmp = gettrad(tmp, tab);
      (*tmp).next = basic(trad, tab); }
    else
    { tmp = basic(trad, tab);
      *trad = tmp; }
    free(tab);
    DEL((void**)line); }
  close(fd);

  tmp = *trad;
  while (tmp)
  { printf("HI::{%s, ", (*tmp).origine);
    i = 0;
    while (((*tmp).traduit)[i] && i < 5)
    { printf("%s ", ((*tmp).traduit)[i]);
      printf("(%lu, %lu), ", ((*tmp).chrono)[i] >> 8, ((*tmp).chrono)[i] & 0xFF);
      i += 1; }
    printf("}\n");
    tmp = (*tmp).next; }
  return (0);

  TINI();
  while (GNL(1, line) > 0)
  { if (**line == 'q')
    { break; }
    else
    { printf("HI!\n"); }
    DEL((void**)line); }
  TEND((void*)0); }
