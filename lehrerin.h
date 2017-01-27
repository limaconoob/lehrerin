
#ifndef LEHRERIN_H
  #define LEHRERIN_H

  #include <time.h>

  typedef enum e_error
  { TropDeSynonymes = 0x01,
    TimerFormat = 0x02,
    Doublon = 0x04,
  } t_error;

  typedef struct s_ubersetzen
  { char *origine;
    char *traduit[5]; //Le tableau de 5 pour les synonymes
    time_t chrono[5]; //Un chrono par synonyme
    char flag;
    struct s_ubersetzen *next;
  } t_trad;

  t_trad *extraction(void);

#endif
