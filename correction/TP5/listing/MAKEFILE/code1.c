/* code1.c */
#include "code1.h"

/* fonction traitement1 :
decalage des 5 premieres lettres de txt
les caracteres qui ne sont pas des lettres sont remplacees par ?
precondition : txt contient au moins 5 caracteres */

void traitement1(char txt[]) {
int i ;
	for (i=0 ; i<5 ; i++) {
    		if ((txt[i] >= 'a')&&(txt[i] <= 'z')) {
       			txt[i] = 'a' + ((txt[i] - 'a') + 11) % 26 ;
			}
    		else if ((txt[i] >= 'A')&&(txt[i] <= 'Z'))   {
       			txt[i] = 'A' + ((txt[i] - 'A') + 11) % 26 ;
			}
    		else {
			txt[i] = '?' ;
			}
	}
}
