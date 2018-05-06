char * const_empty = "";

void init_variables(variables * ens) {
	ens->nb = 0;
}

int ajouter_variable(variables * ens, char *nom, char *valeur) {
	int index = -1;

	for (int i=0; i<ens->nb; i++) {
		if (strcmp(nom, ens->T[i].nom) == 0) {
			strcpy(ens->T[i].valeur, valeur);
			index = i;
			break;
		}
	}

	if (index == -1) {
		if (ens->nb < (NOMBRE_MAX_VARIABLES - 1)) {
			strcpy(ens->T[ens->nb].nom, nom);
			strcpy(ens->T[ens->nb].valeur, valeur);
			index = ens->nb;
			ens->nb++;
		}
	}

	return index;
}

int nombre_variables(variables * ens) {
	return ens->nb;
}

int trouver_variable(variables * ens, char *nom) {
	int index = -1;

	for (int i=0; i<ens->nb; i++) {
		if (strcmp (ens->T[i].nom, nom) == 0) {
			index = i;
			break;
		}
	}

	return index;
}

char *nom_variable(variables * ens, int i) {
	char *nom = NULL;

	if (i >= 0 && i < ens->nb) {
		nom = ens->T[i].nom;
	}

	return nom;
}

char *valeur_variable(variables * ens, int i) {
	char *valeur = const_empty;

	if (i >= 0 && i < ens->nb) {
		valeur = ens->T[i].valeur;
	}

	return valeur;
}

void modifier_valeur_variable(variables * ens, int i, char *valeur) {
	strcpy (ens->T[i].valeur, valeur);
}
