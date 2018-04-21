void lecture_automate(automate *A, FILE *f) {
	init_par_defaut(A);

	/* Nombre d'états */
	fscanf (f, "%d", &A->nb_etats);

	/* États finals */
	int nb_etat_finals = 0;
	fscanf (f, "%d", &nb_etat_finals);

	for (int i=0; i<nb_etat_finals; i++) {
		int etat_final = 0;
		fscanf (f, "%d", &etat_final);
		A->etats_finals[etat_final] = 1;
	}

	/* Transitions */
	int nb_transitions = 0;
	fscanf (f, "%d", &nb_transitions);

	for (int i=0; i<nb_transitions; i++) {
		int etat, etat_suivant;
		char entree;
		fscanf (f, "%d %c %d", &etat, &entree, &etat_suivant);
		A->transitions[etat][(int)entree] = etat_suivant;
		A->sortie[etat][(int)entree][0] = '\0';
	}

	/* Sorties */
	int nb_sorties = 0;
	fscanf (f, "%d", &nb_sorties);

	for (int i=0; i<nb_sorties; i++) {
		int etat;
		char entree;
		fscanf (f, "%d %c ", &etat, &entree);

		/* Une fois l'etat et l'entree passés, on lit tous
		 * les caractères jusqu'à la fin de la ligne */
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
