#include <stdio.h>

#include "lignes.h"

Hitorique histo;

void test_simple () {
	FILE *f = fopen ("utest_histo.txt", "r");
	char devnull[TAILLE_MAX_LIGNE];
	int ret = 1;

	histo_ptr = &histo;
	init_historique (histo_ptr, f);

	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	ret = lire_ligne (histo_ptr, devnull);

	if (ret == 1) {
		printf ("[FAIL] 7 lignes lues et pas à la fin du fichier !\n");
	}

	fclose (f);
}

int main () {

	test_simple ();

	return 0;
}
