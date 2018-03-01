/* code2.c */
#include "code2.h"
#include "entrees_sorties_codage.h"

/* fonction traitement2 :
permutation des 5 premiers caracteres de txt
precondition: txt contient au moins 5 caracteres */

void traitement2(char txt[]) {
char c ;
int decalage ;
int i, j ;
	decalage = lire_decalage() ;
	c = txt[0] ;
	j = 0 ;
	for (i=0 ; i<3 ; i++) {
		txt[j] = txt[(j+decalage) % 4] ;
		j = (j+decalage) % 4 ;
	}
	txt[j] = c ;
	
}
