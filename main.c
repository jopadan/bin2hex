#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include "bin2hex.h"

int main(int argc, char** argv)
{
	struct stat sb;
	FILE* file = NULL;
	uint8_t* src = NULL;
	char* dst = NULL;
	size_t size = 0;
	size_t ret = 0;

	/* print usage if the only argument is the executables name */
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s [FILE]\nConvert FILE to hexadecimal stdout string output.\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* read file size */
	lstat(argv[1], &sb);
	size = sb.st_size;

	/* open filename argument */
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Could not open filename: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	/* allocate memory of file size bytes + '\0' */
	src = calloc(size, 1);
	dst = calloc(size * 2 + 1, 1);

        /* store binary file in src */
	ret = fread(src, 1, size, file);
	if (ret == 0 || ret < size)
	{
		fprintf(stderr, "Error reading file \"%s\": %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}

	// convert size bytes in src to hexadecimal dst string
	dst = bin2hex(dst, src, size);
	if (dst == NULL)
	{
		fprintf(stderr, "Could not convert %lu number of bytes to hexadecimal string: %s\n", size, strerror(errno));
		if(src) free(src);
		exit(EXIT_FAILURE);
	}

	/* print hexadecimal dst string to stdout */
	printf("%s\n", dst);

	/* free storage */
	if(src) free(src);
	if(dst) free(dst);

	exit(EXIT_SUCCESS);
}
