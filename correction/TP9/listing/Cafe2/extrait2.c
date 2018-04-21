void simule_automate(automate *A) {
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
