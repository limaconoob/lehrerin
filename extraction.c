
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

static t_trad *tralloc(void)
{ t_trad *tmp;
  tmp = (t_trad*)malloc(sizeof(t_trad));
  BZE(tmp, sizeof(t_trad));
  return (tmp); }

static void deltab(char **tab)
{ int m = 0;
  while (tab[m])
  { free(tab[m]);
    m += 1; }
  free(tab); }

static t_trad *get_time(t_trad *tmp, char *tab, int index)
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

static t_trad *basic(t_trad **trad, char **tab)
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

static t_trad *gettrad(t_trad *tmp, char **tab)
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

t_trad *extraction(void)
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

//DEBUG
  tmp = *trad;
  while (tmp)
  { printf("HI::{%s", (*tmp).origine);
    i = 0;
    while (((*tmp).traduit)[i] && i < 5)
    { printf(", %s ", ((*tmp).traduit)[i]);
      printf("(%lu, %lu)", ((*tmp).chrono)[i] >> 8, ((*tmp).chrono)[i] & 0xFF);
      i += 1; }
    printf("}\n");
    tmp = (*tmp).next; }
//DEBUG
  return (*trad);
}
