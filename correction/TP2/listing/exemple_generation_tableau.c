#include <stdio.h>
#include "generer_entier.c"

// affiche a l'écran T[0..nb-1]
void afficher(int T[], int nb) {
	int i;
	printf("[ ");
	for (i = 0; i < nb; i++) {
		printf("%d ", T[i]);
	}
	printf("]\n");
}

void echanger(int Tab[], int i, int j) {
	int tmp;
	tmp = Tab[i];
	Tab[i] = Tab[j];
	Tab[j] = tmp;
}

/* inserer a sa place l’entier val dans la sequence triee Tab[0..nb-1] */
void inserer(int Tab[], int nb, int val) {
	Tab[nb] = val;
	int i = nb;
	while (i > 0 && Tab[i-1] > Tab[i]) {
		echanger(Tab, i - 1, i);
		i--;
	}
}

int main() {
	int Taille = 20;
	int T[Taille];
	int nb = 0, i = 0, valeur = 0;

	for (i = 0; i < Taille; i++) {
		valeur = generer_entier(100);
		inserer(T, i, valeur);
		nb++;
		afficher(T, i);
	}

	return 0;
}
