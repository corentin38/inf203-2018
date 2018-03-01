#include "code1.h" 
#include "entrees_sorties_codage.h"


int main() {
int choix ; 
char texte[6] ;
  
	choix = lire_choix() ;
	lire_donnee(texte) ;

  	switch (choix) {
     	case 1 : 
		traitement1(texte) ;
		break ;
     	case 2 : 
		traitement2(texte) ;
		break ;
	default :
		break ;
	}
	ecrire_resultat(texte) ;
return 0 ;
}

