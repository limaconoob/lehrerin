
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
typedef struct termios t_term;


void TEND(struct termios *term)
{ static t_term stock[1];
  if (term)
  { *stock = *term; }
  else
#ifdef __linux__ 
  { ioctl(0, 0x5402, stock); }}
#else
  { ioctl(0, 0x80000000 | (116 << 8) | 20 | ((sizeof(t_term) & 0x1FFF) << 16), stock); }}
#endif

void TINI(void)
{ struct termios term;
#ifdef __linux__ 
  ioctl(0, 0x5401, &term);
#else
  ioctl(0, 0x40000000 | (116 << 8) | 19 | ((sizeof(t_term) & 0x1FFF) << 16), &term);
#endif
  TEND(&term);
  term.c_lflag ^= ~(ICANON);
  term.c_lflag ^= ~(ECHO);
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;
#ifdef __linux__ 
  ioctl(0, 0x5402, &term); }
#else
  ioctl(0, 0x80000000 | (116 << 8) | 20 | ((sizeof(t_term) & 0x1FFF) << 16), &term); }
#endif

int TLN(char **tab)
{ int i = 0;
  while (tab[i])
  { i += 1; }
  return (i); }

void DEL(void** data)
{ free(*data);
  *data = (void*)0; }

int LEN(char *str)
{ int i = 0;
  while (*(str + i))
  { i += 1; }
  return (i); }

char *DUP(char *str)
{ int i = 0;
  char *ret;
  if (!((ret = (char*)malloc(LEN(str) + 1))))
  { return ((void*)0); }
  while (*(str + i))
  { ret[i] = *(str + i);
    i += 1; }
  ret[i] = 0;
  return (ret); }

char *SUB(char *str, int start, int len)
{ char *ret;
  int i = 0;
  if (!((ret = (char*)malloc(len + 1))))
  { return ((void*)0); }
  while (i < len)
  { ret[i] = *(str + start + i);
    i += 1; }
  ret[i] = 0;
  return (ret); }

void NCPY(void *ptr1, void *ptr2, int size)
{ while (size)
  { ((unsigned char *)ptr1)[size - 1] = ((unsigned char *)ptr2)[size - 1];
    size -= 1; }}

void BZE(void *ptr, int size)
{ while (size)
  { ((unsigned char *)ptr)[size - 1] = 0;
    size -= 1; }}

int NCMP(void *ptr1, void *ptr2, int size)
{ if (size > 0)
  { int i = 0;
    while (i < size && ((unsigned char*)ptr1)[i] == ((unsigned char*)ptr2)[i])
    { i += 1; }
    if (i != size)
    { return (((unsigned char*)ptr1)[i] - ((unsigned char*)ptr2)[i]); }}
  return (0); }
