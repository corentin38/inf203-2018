#include <stdio.h>
#include <stdlib.h>

void cat (char *srcname) {
	FILE *src = fopen(srcname, "r");
	if (src == NULL) {
		printf("%s n'a pas pu être ouvert en lecture\n", srcname);
		perror(srcname);
		exit(1);
	}

	char c;
	fscanf(src, "%c", &c);
	while (!feof(src)) {
		printf("%c", c);
		fscanf(src, "%c", &c);
	}

	fclose (src);
}

int main (int argc, char *argv[]) {
	if (argc < 2) {
		printf("USAGE: ./prog FICHIER\n");
		exit(1);
	}

	for (int i=2; i<argc; i++) {
		cat (argv[i]);
	}

	return 0 ;
}
