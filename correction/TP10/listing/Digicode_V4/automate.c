#include <stdio.h>
#include <string.h>
#include "automate.h"

#define NB_ETATS      5
#define NB_ENTREES    10
#define LG_MAX_SORTIE 128

#define Q0 0
#define Q1 1
#define Q2 2
#define Q3 3
#define Q4 4

typedef int etat;

typedef struct sortie_deverouillage {
	etat etat;
	int entree;
	char message[LG_MAX_SORTIE];
} Sortie_Deverouillage;

etat transition [NB_ETATS][NB_ENTREES] = {
	/* entrees ->  0,  1,  2,  3,  4,  5,  6,  7,  8,  9 */
	/* Q0 */     { Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0 },
	/* Q1 */     { Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0 },
	/* Q2 */     { Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0 },
	/* Q3 */     { Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0 },
	/* Q4 */     { Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0 }
};

Sortie_Deverouillage sortie;

int init_automate (int digit1, int digit2, int digit3, int digit4, char *message) {
	if (digit1 < 0 || digit1 > 9 || digit2 < 0 || digit2 > 9 ||
	    digit3 < 0 || digit3 > 9 || digit4 < 0 || digit4 > 9) {
		return 1;
	}

	transition[Q0][digit1] = Q1;
	transition[Q1][digit1] = Q1;
	transition[Q2][digit1] = Q1;
	transition[Q3][digit1] = Q1;
	transition[Q4][digit1] = Q1;

	transition[Q1][digit2] = Q2;
	transition[Q2][digit3] = Q3;
	transition[Q3][digit4] = Q4;

	strcpy (sortie.message, message);
	sortie.etat = Q3;
	sortie.entree = digit4;

	return 0;
}

int lecture_automate (char *sauvegarde) {
	FILE *f = fopen (sauvegarde, "r");
	if (f == NULL) {
		return 1;
	}

	int digit1;
	fscanf (f, "%d\n", &digit1);

	int digit2;
	fscanf (f, "%d\n", &digit2);

	int digit3;
	fscanf (f, "%d\n", &digit3);

	int digit4;
	fscanf (f, "%d\n", &digit4);

	char message[LG_MAX_SORTIE];
	int i=0;
	char cc;
	fscanf (f, "%c", &cc);
	while (!feof(f) && cc != '\n') {
		message[i] = cc;
		fscanf (f, "%c", &cc);
		i++;
	}
	message[i] = '\0';

	fclose (f);
	return init_automate (digit1, digit2, digit3, digit4, message);
}

etat etat_initial() {
	return Q0;
}

int est_final(etat Q) {
	return Q == Q4;
}

int lire_entree() {
	char c;

	scanf("\n%c", &c);
	while (((c < '0') || (c > '9')) && (c != '-')) {
		printf("entree invalide ! un chiffre entre 0 et 9 (- pour finir) ?\n");
		scanf("\n%c", &c);
	}

	if (c == '-') {
		return -1;
	} else {
		return c-'0';
	}
}

void simule_automate() {
	int etat_courant, etat_suivant, entree;
	entree = 0;
	etat_courant = etat_initial();

	while (entree != -1 && !est_final(etat_courant)) {
		entree = lire_entree();
		etat_suivant = transition[etat_courant][entree];

		if (etat_courant == sortie.etat && entree == sortie.entree) {
			printf ("%s\n", sortie.message);
		}

		/* Trace de débug, à décommenter seulement si ça plante */
		/* printf("%d - %d -> %d\n", etat_courant, entree, etat_suivant); */

		etat_courant = etat_suivant;
	}
}
