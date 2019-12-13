#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bin2hex.h"

char* bin2hex(char* dst, uint8_t* src, size_t n)
{
	if( dst == NULL || src == NULL || n == 0)
		return NULL;

	/* make sure dst is large enough for hex strings */
	dst = realloc(dst, n * 2 + 1);

	/* iterate bytes in src */
	for(size_t i = 0; i < n; i++)
	{
		/* 2 char string for hexadecimal byte */
		char* hexstr;

		/* print byte at src[i] as hexadecimal to hexstr */
		int len = asprintf(&hexstr, "%.2x", *(uint8_t*)&src[i]);
		/* append hexstr to dst */
		if (len > 0) dst = strncat(dst, hexstr, len);
		/* free temporary storage for hexadecimal string */
		if(hexstr) free(hexstr);
		/* bail out if there are errors */
		if(dst == NULL | len <= 0)
		{
			fprintf(stderr, "Error concatenating or convert hexadecimal string output at offset %lu\n", i );
			return NULL;
		}
	}

	/* return pointer to hexadecimal string filled destination */
	return dst;
}
