char lignes_lues[NOMBRE_MAX_LIGNES][TAILLE_MAX_LIGNE];
int nombre_ligne_lues;
int position_courante;
FILE *fichier;

void init_historique (FILE *f) {
	nombre_ligne_lues = 0;
	position_courante = 0;
	fichier = f;
}

int lire_ligne (char *ligne) {
	int ret = 1;
	char buffer[TAILLE_MAX_LIGNE];
	if (position_courante < nombre_ligne_lues) {
		strcpy (ligne, lignes_lues[position_courante]);
	} else {
		if (nombre_ligne_lues > NOMBRE_MAX_LIGNES - 1) {
			debug ("Taille max historique atteinte\n");
			ligne[0] = '\0';
			return 0;
		}
		ret = lire_ligne_fichier (fichier, buffer);
		strcpy (ligne, buffer);
		strcpy (lignes_lues[nombre_ligne_lues], buffer);
		nombre_ligne_lues++;
	}
	position_courante++;
	return ret;
}

void aller_a_la_ligne (int numero) {
	position_courante = numero;
}

int obtenir_numero_ligne () {
	return position_courante;
}
