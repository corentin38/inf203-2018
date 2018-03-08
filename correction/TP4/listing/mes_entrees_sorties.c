#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	if (argc != 2) {
		printf("USAGE: ./prog FICHIER\n");
		exit(1);
	}

	char *filename = argv[1];
	FILE *f = fopen(filename, "r") ;
	if (f == NULL) {
		printf("%s n'a pas pu être ouvert en lecture\n", filename) ;
		perror(filename);
		return 1 ;
	}

	char c ;
	fscanf(f, "%c", &c) ;
	while (!feof(f)) {
		printf("%c", c) ;
		fscanf(f, "%c", &c) ;
	}

	fclose(f) ;
	return 0 ;
}
