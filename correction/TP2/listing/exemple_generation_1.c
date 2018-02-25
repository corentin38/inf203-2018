#include <stdio.h>
#include "generer_entier.c"

int main() {
    int x = generer_entier(100);
    printf("Entier généré : %d\n", x);

    if (x < 42) {
	    printf("Trop petit !\n");
    } else if (x > 42) {
	    printf("Trop grand !\n");
    } else {
	    /* Si x n'est ni < 42 ni > 42, c'est qu'il est égal à 42 ! */
	    printf("Youpie !\n");
    }

    return 0;
}
