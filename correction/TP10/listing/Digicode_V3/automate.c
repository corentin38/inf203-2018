
etat transition [NB_ETATS][NB_ENTREES] = {
	/* entrees ->  0,  1,  2,  3,  4,  5,  6,  7,  8,  9 */
	/* Q0 */     { Q0, Q1, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0 },
	/* Q1 */     { Q0, Q1, Q2, Q0, Q0, Q0, Q0, Q0, Q0, Q0 },
	/* Q2 */     { Q0, Q1, Q0, Q3, Q0, Q0, Q0, Q0, Q0, Q0 },
	/* Q3 */     { Q0, Q1, Q0, Q0, Q4, Q0, Q0, Q0, Q0, Q0 },
	/* Q4 */     { Q0, Q1, Q0, Q0, Q0, Q0, Q0, Q0, Q0, Q0 }
};

void simule_automate() {
	int etat_courant, etat_suivant, entree;
	entree = 0;
	etat_courant = etat_initial();

	while (entree != -1 && !est_final(etat_courant)) {
		entree = lire_entree();
		etat_suivant = transition[etat_courant][entree];

		if (etat_courant == Q3 && entree == 4) {
			printf ("Clic !\n");
		}

		/* Trace de débug, à décommenter seulement si ça plante */
		/* printf("%d - %d -> %d\n", etat_courant, entree, etat_suivant); */

		etat_courant = etat_suivant;
	}
}
