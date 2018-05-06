int trouver_et_appliquer_affectation_variable(variables * ens, char *ligne) {
	enum { ESP_DEB, NOM, EGAL, VAL, ERR } etat = ESP_DEB;
	int affectation_trouvee = 0;
	char *nom = NULL, *val = NULL;

	int i = 0;
	while (ligne[i] != '\0' && etat != ERR) {
		switch (etat) {

		case ESP_DEB:
			switch (ligne[i]) {
			case '=' : etat = ERR     ; break;
			case ' ' : etat = ESP_DEB ; break;
			default  :
				nom = &ligne[i];
				etat = NOM;
				break;
			}
			break;

		case NOM:
			switch (ligne[i]) {
			case '=' :
				ligne[i] = '\0';
				val = &ligne[i+1];
				etat = EGAL;
				break;
			case ' ' : etat = ERR  ; break;
			default  : etat = NOM  ; break;
			}
			break;

		case EGAL:
			switch (ligne[i]) {
			case '=' : etat = ERR  ; break;
			case ' ' : etat = ERR  ; break;
			default  : etat = VAL  ; break;
			}
			break;

		case VAL:
			switch (ligne[i]) {
			case '=' : etat = ERR  ; break;
			case ' ' : etat = ERR  ; break;
			default  : etat = VAL  ; break;
			}
			break;

		default: break;
		}
		i++;
	}

	if (etat == VAL) {
		ajouter_variable (ens, nom, val);
		affectation_trouvee = 1;
	}

	return affectation_trouvee;
}
