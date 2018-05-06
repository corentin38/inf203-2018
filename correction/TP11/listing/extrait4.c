void appliquer_expansion_variables (variables * ens, char *ligne_originale, char *ligne_expansee) {
	enum { COPY, DOLLAR, EXPAND } etat = COPY;
	char nom[TAILLE_MAX_NOM] = "";

	int i_o = 0, i_e = 0, i_n = 0;
	while (ligne_originale[i_o] != '\0' || etat == EXPAND) {
		switch (etat) {

		case COPY:
			switch (ligne_originale[i_o]) {
			case '$':
				etat = DOLLAR;
				break;
			default:
				ligne_expansee[i_e] = ligne_originale[i_o];
				i_e++;
				etat = COPY;
				break;
			}
			break;

		case DOLLAR:
			if (isalnum(ligne_originale[i_o]) ||
			    ligne_originale[i_o] == '*'   ||
			    ligne_originale[i_o] == '#') {
				nom[0] = ligne_originale[i_o];
				i_n = 1;
				etat = EXPAND;
			} else {
				ligne_expansee[i_e]   = '$';
				ligne_expansee[i_e+1] = ligne_originale[i_o];
				i_e = i_e + 2;
				etat = COPY;
			}
			break;

		case EXPAND:
			if (isalnum(ligne_originale[i_o])) {
				nom[i_n] = ligne_originale[i_o];
				i_n++;
				etat = EXPAND;
			} else {
				nom[i_n] = '\0';
				int var_id = trouver_variable (ens, nom);
				if (var_id != -1) {
					char *val = valeur_variable (ens, var_id);
					int i_v = 0;
					while (val[i_v] != '\0') {
						ligne_expansee[i_e] = val[i_v];
						i_e++;
						i_v++;
					}
				}
				if (ligne_originale[i_o] != '\0') {
					ligne_expansee[i_e] = ligne_originale[i_o];
					i_e++;
				} else {
					i_o--;
				}
				etat = COPY;
			}
			break;

		}
		i_o++;
	}
	ligne_expansee[i_e] = '\0';
}
