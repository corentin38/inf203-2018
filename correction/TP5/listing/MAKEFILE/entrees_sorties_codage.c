#include "entrees_sorties_codage.h"
#include <stdio.h>
#include <string.h>

int lire_choix() {
int ok ;
int choix ;
	ok = 0 ;
	while (! ok) {
		printf("indiquez votre choix (1 ou 2) :\n") ;
		scanf("%d", &choix) ;
		ok = ((choix == 1) || (choix == 2)) ;
	}
	return choix ;
}

void lire_donnee(char txt[]) {
	printf("donnez une chaine de 5 caracteres exactement :\n") ;
	scanf("%s", txt) ;
}

void ecrire_resultat(char txt[]) {
	printf("voici le resultat du codage : ") ;
	printf("%s\n", txt) ;
}

int lire_decalage() {
int dec ;
	printf("donnez un entier :\n") ;
	scanf("%d", &dec) ;
	dec = dec % 4 ;
	return dec ;
}
