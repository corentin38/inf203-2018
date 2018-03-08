#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int i, somme = 0;

	if (argc == 1) {
		printf ("USAGE: ./prog number...\n");
		exit(EXIT_FAILURE);
	}

	for (i=1 ; i<argc ; i++) {
		somme += atoi(argv[i]);

		printf("%s",argv[i]);
		if (i < (argc - 1)) {
			printf(" + ");
		}
	}

	printf(" = %d\n", somme);
	return 0;
}
