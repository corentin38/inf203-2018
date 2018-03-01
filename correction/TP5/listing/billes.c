#include <stdio.h>

typedef struct{
	char pseudo[20];
	int nb_billes;
} joueur;

joueur atchoum ={"Atchoum", 42};
joueur dormeur={"Dormeur", 25};
joueur grincheux={"Grincheux", 3};
joueur joyeux={"Joyeux", 100};
joueur prof={"Prof", 2};
joueur simplet={"Simplet", 0};
joueur timide={"Timide", 12};

void afficher_joueur_V1(joueur j) {
	printf("%s a %d billes\n", j.pseudo, j.nb_billes);
}

void afficher_joueur_V2(joueur *pj) {
	printf("%s a %d billes\n", pj->pseudo, pj->nb_billes);
}

void lire_joueur(joueur *pj) {
	printf ("pseudo: ");
	scanf ("%s", pj->pseudo);
	printf ("nb billes: ");
	scanf ("%d", &pj->nb_billes);
}

void transferer_V2(joueur *pj1, joueur *pj2) {
	strcpy(pj2->pseudo, pj1->pseudo);
	pj2->nb_billes = pj1->nb_billes;
}

int main() {
	afficher_joueur_V1(atchoum);
	afficher_joueur_V2(&atchoum);
	lire_joueur(&atchoum);
	afficher_joueur_V2(&atchoum);

	printf("\n\n");
	afficher_joueur_V2(&timide);
	afficher_joueur_V2(&simplet);
	transferer_V2(&simplet, &timide);
	afficher_joueur_V2(&timide);
	afficher_joueur_V2(&simplet);
	return 0;
}
