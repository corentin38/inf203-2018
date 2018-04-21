#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automate.h"

void init_par_defaut(automate *A) {
	int i, j;
	A-> nb_etats = NB_MAX_ETATS;
	A-> etat_initial = 0;

	for (i=0; i<NB_MAX_ETATS; i++) {
		A->etats_finals[i]=0;
	}

	for (i=0; i<NB_MAX_ETATS; i++) {
		for (j=0; j<NB_MAX_ENTREES; j++) {
			A->transitions[i][j]=i;
		}
	}

	for (i=0; i<NB_MAX_ETATS; i++) {
		for (j=0; j<NB_MAX_ENTREES; j++) {
			strcpy(A->sortie[i][j], "entree_invalide");
		}
	}
}

void lecture_automate(automate *A, FILE *f) {
	init_par_defaut(A);

	/* Nombre d'états */
	fscanf (f, "%d", &A->nb_etats);

	int nb_etat_finals = 0;
	fscanf (f, "%d", &nb_etat_finals);

	for (int i=0; i<nb_etat_finals; i++) {
		int etat_final = 0;
		fscanf (f, "%d", &etat_final);
		A->etats_finals[etat_final] = 1;
	}

	int nb_transitions = 0;
	fscanf (f, "%d", &nb_transitions);

	for (int i=0; i<nb_transitions; i++) {
		int etat, etat_suivant;
		char entree;
		fscanf (f, "%d %c %d", &etat, &entree, &etat_suivant);
		A->transitions[etat][(int)entree] = etat_suivant;
		A->sortie[etat][(int)entree][0] = '\0';
	}

	int nb_sorties = 0;
	fscanf (f, "%d", &nb_sorties);

	for (int i=0; i<nb_sorties; i++) {
		int etat;
		char entree;
		fscanf (f, "%d %c ", &etat, &entree);

		int i = 0;
		char cc;
		char sortie[LG_MAX_SORTIE];
		fscanf (f, "%c", &cc);
		while (!feof(f) && cc != '\n') {
			sortie[i] = cc;
			fscanf (f, "%c", &cc);
			i++;
		}
		sortie[i] = '\0';
		strcpy (A->sortie[etat][(int)entree], sortie);
	}
}

void lire_entree(int *s) {
	char c;
	scanf("\n%c", &c);
	*s=(int)c;
}

void ecrire_sortie(char message[]) {
	printf("%s\n", message);
}

void simule_automate(automate *A) {
	printf ("taille automate : %d\n", sizeof(automate));


	int etat_courant, etat_suivant;
	int symbole_entree= ' ';

	etat_courant = A->etat_initial;
	while (!A->etats_finals[etat_courant]) {
		/* lire une entree */
		lire_entree (&symbole_entree);
		if (symbole_entree == 'q') {
			break;
		}

		/* calculer l'état suivant */
		etat_suivant = A->transitions[etat_courant][symbole_entree];

		/* ecrire le message de sortie */
		ecrire_sortie (A->sortie[etat_courant][symbole_entree]);

		/* mettre à jour l'état courant */
		etat_courant = etat_suivant;
	}
}
