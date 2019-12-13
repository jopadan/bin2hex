#define _GNU_SOURCE
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	struct stat sb;
	FILE* file = NULL;
	uint8_t* data_file = NULL;
	char* hex = NULL;
	if (argc < 2)
		exit(EXIT_FAILURE);
	lstat(argv[1], &sb);
	file = fopen(argv[1], "r");
	if (file == NULL)
		exit(EXIT_FAILURE);

	data_file = malloc(sb.st_size);
	hex = calloc(sb.st_size * 2 + 4, 1);
	fread(data_file, 1, sb.st_size, file);
	uint8_t * nptr = data_file;
	uint8_t * endptr = data_file + sb.st_size - 1;
	while(nptr != endptr)
	{
		char *hexstr = NULL; 
		int len = asprintf(&hexstr, "%.2x", *nptr++);
		if (len > 0)
		{
			hex = strncat(hex, hexstr, len);
			free(hexstr);
			if(hex == NULL)
			{
				fprintf(stderr, "Error concatenating hexadecimal string output at offset %lu", endptr - nptr );
				exit(EXIT_FAILURE);
			}
		}
		else if(len < 0)
		{
			fprintf(stderr, "Error printing binary data at offset %lu to hexadecimal string", endptr - nptr );
			exit(EXIT_FAILURE);
		}
	}
	printf("%s\n", hex);
	free(data_file);
	free(hex);
	exit(EXIT_SUCCESS);
}
