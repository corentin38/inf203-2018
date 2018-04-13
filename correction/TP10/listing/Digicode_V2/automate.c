etat transition (etat Q, int e) {
	etat etat_suivant = Q;

	switch (Q) {
	case Q0:
		switch (e) {
		case 1:  etat_suivant = Q1; break;
		default: etat_suivant = Q0; break;
		}
		break;

	case Q1:
		switch (e) {
		case 1:  etat_suivant = Q1; break;
		case 2:  etat_suivant = Q2; break;
		default: etat_suivant = Q0; break;
		}
		break;

	case Q2:
		switch (e) {
		case 1:  etat_suivant = Q1; break;
		case 3:  etat_suivant = Q3; break;
		default: etat_suivant = Q0; break;
		}
		break;

	case Q3:
		switch (e) {
		case 1:  etat_suivant = Q1; break;
		case 4:
			etat_suivant = Q4;
			printf ("Clic !\n");
			break;
		default: etat_suivant = Q0; break;
		}
		break;

	case Q4:
		switch (e) {
		case 1:  etat_suivant = Q1; break;
		default: etat_suivant = Q0; break;
		}
		break;

	default : break;
	}

	return etat_suivant;
}

void simule_automate() {
	int etat_courant, etat_suivant, entree;
	entree = 0;
	etat_courant = etat_initial();

	while (entree != -1 && !est_final(etat_courant)) {
		entree = lire_entree();
		etat_suivant = transition (etat_courant, entree);

		/* Trace de débug, à décommenter seulement si ça plante */
		/* printf("%d - %d -> %d\n", etat_courant, entree, etat_suivant); */

		etat_courant = etat_suivant;
	}
}
