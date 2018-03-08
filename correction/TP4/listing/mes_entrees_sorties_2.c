#include <stdio.h>
#include <stdlib.h>

void transfer (FILE *src, FILE *dst) {
	char c;
	fscanf(src, "%c", &c);
	while (!feof(src)) {
		fprintf(dst, "%c", c);
		fscanf(src, "%c", &c);
	}
}

void cat (char *srcname) {
	FILE *src = fopen(srcname, "r");
	if (src == NULL) {
		printf("%s n'a pas pu être ouvert en lecture\n", srcname);
		perror(srcname);
		exit(1);
	}

	transfer (src, stdout);

	fclose (src);
}

void cp (char *srcname, char *dstname) {
	FILE *src = fopen(srcname, "r");
	if (src == NULL) {
		printf("%s n'a pas pu être ouvert en lecture\n", srcname);
		perror(srcname);
		exit(1);
	}

	FILE *dst = fopen(dstname, "w");
	if (dst == NULL) {
		printf("%s n'a pas pu être ouvert en écriture\n", dstname);
		perror(dstname);
		exit(1);
	}

	transfer (src, dst);

	fclose (src);
	fclose (dst);
}

int main (int argc, char *argv[]) {
	if (argc == 1 || argc >= 4) {
		printf("USAGE: ./prog FICH_SRC [FICH_DST]\n");
		return 1;
	}

	if (argc == 2) {
		cat (argv[1]);
	} else {
		cp (argv[1], argv[2]);
	}

	return 0;
}
