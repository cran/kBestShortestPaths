/*
 * Implemented by Adrin Jalali <adrin.jalali@gmail.com>
 * October 2011
 * Licensed under GPLv3
*/
#include <cstdio>
//#include <cstring>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;
///// string manupulation part

void removeAllCharsFromString(string &str, char c)
{
	for ( ; str.find(c) != string::npos; str = str.replace(str.find(c), 1, "")) ;
}

char * strcpy(char *pDestination, const char *pSource)
{
	char *pSaveDest = pDestination;

	for(; (*pDestination = *pSource) != 0; ++pSource, ++pDestination);
	return pSaveDest;
}

char *strtok_r(char *s, const char *delim, char **last)
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

void replaceAll(string &str, char c1, char c2)
{
	char tmp[2] = {c2, 0};
	for ( ; str.find(c1) != string::npos; str = str.replace(str.find(c1), 1, tmp)) ;
}

//// replaces 0 with 1 and 1 with 0 in input string.
//// that's needed to make input key numbers more sensible.
void inversZeroOne(string &str)
{
	replaceAll(str, '1', '_');
	replaceAll(str, '0', '1');
	replaceAll(str, '_', '0');
}

///// file reading part

////////////// not needed yet //////////////
void readAllProportions(const char *name)
{
}

void readPvals(const char *signs_file_name, 
		const char *pval_file_name, 
		double *pvals, 
		int *s_values, 
		char **signs, 
		int &signs_row_num,
		char **proteins)
{
	FILE *f_p = fopen(pval_file_name, "r");
	FILE *f_s = fopen(signs_file_name, "r");
	char line[2000];
	char *ltmp;
	char *save_ptr;
	ltmp = fgets(line, 2000, f_p);
	if (!ltmp)
		assert(false);
	ltmp = fgets(line, 2000, f_s);
	if (!ltmp)
		assert(false);

	char *tmp;
	strtok_r(line, ",", &save_ptr);
	int protein_it = 0;
	while (1)
	{
		tmp = strtok_r(NULL, ",", &save_ptr);
		if (!tmp)
			break;
		string pr = tmp;
		removeAllCharsFromString(pr, '\n');
		removeAllCharsFromString(pr, '"');
		strcpy(proteins[protein_it], pr.c_str());
		protein_it++;
	}

	int count = 0;

	signs_row_num = 0;
	int s_values_it = 0;
	while (!feof(f_p) && !feof(f_s))
	{
		line[0] = 0;
		ltmp = fgets(line, 2000, f_p);
		if (!line[0])
			break;

		char *tmp;
		tmp = strtok_r(line, ",\n\r", &save_ptr);
		tmp = strtok_r(NULL, ",\n\r", &save_ptr);
		double pvalue = strtod(tmp, NULL);
		pvals[signs_row_num] = pvalue;

		line[0] = 0;
		ltmp = fgets(line, 2000, f_s);
		if (!line[0])
			break;

		tmp = strtok_r(line, ",", &save_ptr);
		string name = tmp;
		removeAllCharsFromString(name, '"');
		strcpy(signs[signs_row_num], name.c_str());

		while (1)
		{
			tmp = strtok_r(NULL, ",", &save_ptr);
			if (!tmp)
				break;
			string vl = tmp;
			removeAllCharsFromString(vl, '\n');
			removeAllCharsFromString(vl, '"');
			s_values[s_values_it] = atoi(vl.c_str());
			s_values_it++;
		}


		signs_row_num++;
		count++;
		/*
		fprintf(stderr, "%s\t%lf\n", tmp, pvalue);
		if (count == 10)
			return;
		*/
	}
	fclose(f_p);
	fclose(f_s);
}
