#include <stdio.h>
#include <stdlib.h>
#include "automate.h"


int main() {
	if (lecture_automate("sauvegarde.sav")) {
		printf ("Impossible d'initialiser l'automate\n");
		exit(1);
	}

	simule_automate();
	return 0;
}
