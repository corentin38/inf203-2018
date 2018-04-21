#include <stdio.h>
#include <stdlib.h>
#include "automate.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf ("USAGE: %s automate.auto\n", argv[0]);
		exit(1);
	}

	char *filename = argv[1];
	FILE *file = fopen (filename, "r");
	if (file == NULL) {
		printf ("Impossible d'ouvrir le fichier automate\n");
		perror (filename);
		exit(1);
	}

	automate A;
	lecture_automate(&A, file);
	simule_automate(&A);

	fclose (file);
	return 0;
}
