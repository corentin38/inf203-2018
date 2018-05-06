int decode_entree(char *mot) {
	int mnemo = INSTRUCTION;

	for (int i=0; i<nombre_mnemoniques; i++) {
		if (strcmp (mot, mnemonique[i]) == 0) {
			mnemo = valeur_mnemonique[i];
			break;
		}
	}

    return mnemo;
}
