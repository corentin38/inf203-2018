int lire_ligne_fichier(FILE * fichier, char *ligne) {
	char cc = 0;
	int i = 0;
	fscanf (fichier, "%c", &cc);
	while (!feof (fichier) && cc != '\n') {
		ligne[i] = cc;
		i++;
		fscanf (fichier, "%c", &cc);
	}
	ligne[i] = '\0';
	return (cc == '\n');
}
