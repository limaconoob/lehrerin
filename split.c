
#include "outils.h"
#include <stdlib.h>

static int		ft_count(char *str, char c)
{
	int			count = 0;
	int			quote = 0;
	while (*str)
	{ while (*str == c)
		{ str += 1; }
		if (*str)
		{ while (*str && (*str != c || quote))
			{ if (*str == '\"')
				{ quote ^= 1; }
				str += 1; }
			count += 1; }}
	return (count); }

static void		get_ttab(char **tab, char *str, char c)
{
	int			count = 0;
	int			quote = 0;
	int			i;
	while (*str)
  { while (*str == c)
		{ str += 1; }
		if (*str)
		{ i = 0;
			while (str[i] && (str[i] != c || quote))
			{ if (str[i] == '\"')
				{ quote ^= 1; }
				i += 1; }
			tab[count++] = SUB(str, 0, i);
			str += i; }}
	tab[count] = (void*)0; }

char			**SPL(char *str, char c)
{ char		**tab;
	if (!str)
  { return ((void*)0); }
	if (!((tab = (char**)malloc(sizeof(char*) * (ft_count(str, c) + 1)))))
  { return ((void*)0); }
	get_ttab(tab, str, c);
	return (tab); }
