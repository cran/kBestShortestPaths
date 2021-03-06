#include "mystring.h"
#include <cstdlib>

char * my_strcpy(char *pDestination, const char *pSource)
{
	char *pSaveDest = pDestination;

	for(; (*pDestination = *pSource) != 0; ++pSource, ++pDestination);
	return pSaveDest;
}

char *my_strtok_r(char *s, const char *delim, char **last)
{
	char *spanp;
	int c, sc;
	char *tok;


	if (s == NULL && (s = *last) == NULL)
		return (NULL);

	/*
	 *    * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 *       */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {           /* no non-delimiter characters */
		*last = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 *    * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 *       * Note that delim must have one NUL; we stop if we see that, too.
	 *          */
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*last = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}

