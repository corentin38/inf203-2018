int expand (variables *ens, char *nom, char *ligne_expansee) {
	int var_id = trouver_variable (ens, nom);
	int i = 0;
	if (var_id != -1) {
		char *val = valeur_variable (ens, var_id);
		while (val[i] != '\0') {
			ligne_expansee[i] = val[i];
			i++;
		}
	}
	return i;
}

void appliquer_expansion_variables(variables * ens, char *ligne_originale, char *ligne_expansee) {
	int i_o = 0, i_e = 0, i_n = 0;
	char nom[TAILLE_MAX_NOM] = "";
	int expanding = 0;

	while (ligne_originale[i_o] != '\0') {
		if (ligne_originale[i_o] == '$') {
			if (!expanding) {
				expanding = 1;
			}
		} else if (ligne_originale[i_o] == ' ') {
			if (expanding) {
				if (i_n == 0) {
					/* dollar isolé */
					ligne_expansee[i_e] = '$';
					i_e++;
				} else {
					nom[i_n] = '\0';
					i_e += expand (ens, nom, &ligne_expansee[i_e]);
					i_n = 0;
				}
				ligne_expansee[i_e] = ligne_originale[i_o];
				i_e++;
				expanding = 0;
			} else {
				ligne_expansee[i_e] = ligne_originale[i_o];
				i_e++;
			}
		} else {
			if (expanding) {
				nom[i_n] = ligne_originale[i_o];
				i_n++;
			} else {
				ligne_expansee[i_e] = ligne_originale[i_o];
				i_e++;
			}
		}
		i_o++;
	}

	if (expanding) {
		if (i_n == 0) {
			/* dollar isolé */
			ligne_expansee[i_e] = '$';
			i_e++;
		} else {
			nom[i_n] = '\0';
			i_e += expand (ens, nom, &ligne_expansee[i_e]);
			i_n = 0;
		}
	}
	ligne_expansee[i_e] = '\0';
}
