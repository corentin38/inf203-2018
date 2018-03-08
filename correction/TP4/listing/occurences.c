#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("USAGE: %s [FICHIER]", argv[0]);
		exit(1);
	}

	char *filename = argv[1];
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Impossible d'ouvrir le fichier %s en lecture\n", filename);
		perror(filename);
		exit(1);
	}

	// 93 = '~' (126) - '!' (33)
	int occurences[93] = {0};
	char c = 0;

	fscanf(file, "%c", &c);
	while (!feof(file)) {
		if (c > '!' && c < '~') {
			occurences[c - '!']++;
		}
		fscanf(file, "%c", &c);
	}

	printf("caractère\tnombre\n");
	for (int i=0; i<93; i++) {
		printf("%c\t\t%d\n", i + '!', occurences[i]);
	}
}
