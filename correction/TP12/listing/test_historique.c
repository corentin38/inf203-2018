#include <stdio.h>
#include <string.h>

#include "lignes.h"

Historique histo;

void test_simple () {
	FILE *f = fopen ("utest_histo.txt", "r");
	char devnull[TAILLE_MAX_LIGNE];
	int ret = 1;

	Historique *histo_ptr = &histo;
	init_historique (histo_ptr, f);

	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	lire_ligne (histo_ptr, devnull);
	ret = lire_ligne (histo_ptr, devnull);

	if (ret == 1) {
		printf ("[FAIL] 7 lignes lues et pas à la fin du fichier !\n");
	} else {
		printf ("[ OK ] après 7 lectures, fin du fichier\n");
	}

	fclose (f);
}

void test_retour () {
	FILE *f = fopen ("utest_histo.txt", "r");
	char buffer1[TAILLE_MAX_LIGNE];
	char buffer2[TAILLE_MAX_LIGNE];

	Historique *histo_ptr = &histo;
	init_historique (histo_ptr, f);

	lire_ligne (histo_ptr, buffer1);
	aller_a_la_ligne (histo_ptr, 0);
	lire_ligne (histo_ptr, buffer2);

	if (strcmp(buffer1, buffer2) != 0) {
		printf ("[FAIL] ligne 0 lue deux fois et non identique : <%s> != <%s>\n", buffer1, buffer2);
	} else {
		printf ("[ OK ] Deux lectures de la même ligne donnent résultat identiques\n");
	}

	fclose (f);
}

int main () {

	test_simple ();
	test_retour ();

	return 0;
}
