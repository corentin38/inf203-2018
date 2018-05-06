void affecter_variables_automatiques(variables *ens, int argc, char *argv[]) {
	char buffer[TAILLE_MAX_NOM];
	char buffer_cat[TAILLE_MAX_NOM] = "";
	int i = 0;

	sprintf (buffer, "%d", argc - 1);
	ajouter_variable (ens, "#", buffer);

	while (i < argc) {
		sprintf (buffer, "%d", i);
		ajouter_variable (ens, buffer, argv[i]);
		strcat (buffer_cat, argv[i]);
		if (i < argc - 1) {
			strcat (buffer_cat, " ");
		}
		i++;
	}

	ajouter_variable (ens, "*", buffer_cat);
}
