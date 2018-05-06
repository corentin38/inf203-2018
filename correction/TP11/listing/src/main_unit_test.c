#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "variables.h"
#include "variables_base.h"

#define TAILLE_MAX_LIGNE 1024

#define OK_AFFECTATION_NB 2
#define KO_AFFECTATION_NB 3
#define EXP_NB 4

variables ens;

void test_aff () {
	init_variables (&ens);
	ajouter_variable (&ens, "TOTO", "5");
	ajouter_variable (&ens, "TITI", "12");
	ajouter_variable (&ens, "TATA", "Chantons gaiement !");
	afficher_ensemble_variables (&ens);
	printf ("\n");
}

void antitest_trouver_et_appliquer_affectation_variable (char *testcase) {
	init_variables (&ens);

	char buffer[TAILLE_MAX_NOM] = "";

	strcpy (buffer, testcase);
	trouver_et_appliquer_affectation_variable(&ens, buffer);
	if (ens.nb != 0) {
		printf ("[FAIL] test case <%s> recognized affectation\n", testcase);
	} else {
		printf ("[ OK ] test case <%s> OK\n", testcase);
	}
}

void test_trouver_et_appliquer_affectation_variable(char *testcase) {
	init_variables (&ens);

	char *nom = "TOTO", *val = "5";
	char buffer[TAILLE_MAX_NOM] = "";

	strcpy (buffer, testcase);
	trouver_et_appliquer_affectation_variable(&ens, buffer);

	if (ens.nb != 1 ||
	    strcmp (ens.T[0].nom, nom) != 0 ||
	    strcmp (ens.T[0].valeur, val) != 0) {
		printf ("[FAIL] test case <%s> didn't produce TOTO=5\n", testcase);
	} else {
		printf ("[ OK ] test case <%s> OK\n", testcase);
	}
}

void test_appliquer_expansion_variables (char *testcase, char *expected) {
	init_variables (&ens);
	ajouter_variable (&ens, "TOTO", "5");

	char res[TAILLE_MAX_LIGNE];
	char buffer[TAILLE_MAX_LIGNE];

	strcpy (buffer, testcase);
	appliquer_expansion_variables (&ens, buffer, res);
	if (strcmp (expected, res) != 0) {
		printf ("[FAIL] test case      <%s>\n", testcase);
		printf ("       didn't produce <%s>\n", expected);
		printf ("       but            <%s>\n", res);
	} else {
		printf ("[ OK ] test case <%s> OK\n", testcase);
	}
}

void test_affecter_variables_automatiques () {
	init_variables (&ens);

	int argc = 5;
	char *argv[5] = {
		"/bin/monprog",
		"argument1",
		"argument2",
		"argument3",
		"argument4",
	};

	printf ("Testing with : argc=%d argv=[%s, %s, %s, %s, %s]\n",
	        argc,
	        argv[0],
	        argv[1],
	        argv[2],
	        argv[3],
	        argv[4]);

	affecter_variables_automatiques (&ens, argc, argv);

	int index = -1;

	if ((index = trouver_variable (&ens, "#")) == -1) {
		printf ("[FAIL] $# non définie. Devrait être : 5\n");
	} else {
		printf ("[ OK ] $# = <%s>\n", valeur_variable (&ens, index));
	}

	if ((index = trouver_variable (&ens, "*")) == -1) {
		printf ("[FAIL] $* non définie. Devrait être : </bin/monprog argument1 argument2 argument3 argument4>\n");
	} else {
		printf ("[ OK ] $* = <%s>\n", valeur_variable (&ens, index));
	}

	if ((index = trouver_variable (&ens, "0")) == -1) {
		printf ("[FAIL] $0 non définie. Devrait être : </bin/monprog>\n");
	} else {
		printf ("[ OK ] $0 = <%s>\n", valeur_variable (&ens, index));
	}

	if ((index = trouver_variable (&ens, "1")) == -1) {
		printf ("[FAIL] $1 non définie. Devrait être : <argument1>\n");
	} else {
		printf ("[ OK ] $1 = <%s>\n", valeur_variable (&ens, index));
	}

	if ((index = trouver_variable (&ens, "2")) == -1) {
		printf ("[FAIL] $2 non définie. Devrait être : <argument2>\n");
	} else {
		printf ("[ OK ] $2 = <%s>\n", valeur_variable (&ens, index));
	}

	if ((index = trouver_variable (&ens, "3")) == -1) {
		printf ("[FAIL] $3 non définie. Devrait être : <argument3>\n");
	} else {
		printf ("[ OK ] $3 = <%s>\n", valeur_variable (&ens, index));
	}

	if ((index = trouver_variable (&ens, "4")) == -1) {
		printf ("[FAIL] $4 non définie. Devrait être : <argument4>\n");
	} else {
		printf ("[ OK ] $4 = <%s>\n", valeur_variable (&ens, index));
	}
}

int main() {
	init_variables (&ens);

	test_aff ();

	printf ("\n");

	test_trouver_et_appliquer_affectation_variable ("TOTO=5");
	test_trouver_et_appliquer_affectation_variable ("     TOTO=5");

	printf ("\n");

	antitest_trouver_et_appliquer_affectation_variable ("     TOTO =5");
	antitest_trouver_et_appliquer_affectation_variable ("     TOTO= 5");
	antitest_trouver_et_appliquer_affectation_variable ("     TOTO=5 ");

	printf ("\n");

	test_appliquer_expansion_variables ("$TOTO", "5");
	test_appliquer_expansion_variables ("aeofubaoeu $TOTO aeufbaeub", "aeofubaoeu 5 aeufbaeub");
	test_appliquer_expansion_variables ("aeofubaoeu $TOTO", "aeofubaoeu 5");
	test_appliquer_expansion_variables ("aeofubaoeu $ aefae", "aeofubaoeu $ aefae");

	printf ("\n");

	test_affecter_variables_automatiques ();
	return 0;
}
