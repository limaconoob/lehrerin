#ifndef OUTILS_H
#define OUTILS_H
  #include <termios.h>

  void TINI(void);
  void TEND(struct termios *term);
  int TLN(char **tab);
  int LEN(char *str);
  void BZE(void *ptr, int size);
  int GNL(int fd, char **line);
  int NCMP(void *ptr1, void *ptr2, int size);
  char *SUB(char *str, int start, int len);
  void NCPY(void *ptr1, void *ptr2, int size);
  char **SPL(char *str, char c);
  void DEL(void **data);
  char *DUP(char *str);
#endif
