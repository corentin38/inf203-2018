void decouper_ligne (char *ligne, char *ligne_decoupee[]) {
	int car_prec_espace = 1, i = 0, index = 0;

	while (ligne[i] != '\0') {
		if (ligne[i] == ' ' && !car_prec_espace) {
			ligne[i] = '\0';
		}

		if (ligne[i] != ' ' && car_prec_espace) {
			ligne_decoupee[index] = &ligne[i];
			index++;
		}

		car_prec_espace = (ligne[i] == ' ' || ligne[i] == '\0');
		i++;
	}
	ligne_decoupee[index] = NULL;
}
