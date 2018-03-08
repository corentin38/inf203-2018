#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void cat_stdin () {
	char buffer[MAX];
	int i = 0;
	scanf("%c", buffer+i++);
	while (!feof(stdin)) {
		if (buffer[i-1] == '\n') {
			buffer[i] = '\0';
			i = 0;
			printf("%s", buffer);
		}

		if (i > 98) {
			buffer[i] = '\0';
			i = 0;
			printf("%s\n", buffer);

			scanf("%c", buffer);
			while (!feof(stdin) && buffer[0] != '\n')
				scanf("%c", buffer);
		}

		scanf("%c", buffer+i++);
	}
}

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
		cat_stdin ();
	} else {
		for (int i=2; i<argc; i++) {
			cat (argv[i]);
		}
	}

	return 0 ;
}
