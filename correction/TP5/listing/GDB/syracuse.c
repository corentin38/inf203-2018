#include <stdio.h>
#include <stdlib.h>

int x_suiv(int x) {
int y ;
      	if (x%2 == 0) {
          y = x/2;
		}
      		else {
          y = 3*x + 1;
	}
	return y ;
}

int main(int argc, char *argv[])
{
int x;

  	if (argc != 2) {
      		fprintf(stderr, "Syntaxe %s valeur_initiale (entier) \n", argv[0]) ;
      		exit(1);
  		}
  	x = atoi(argv[1]);

  	while (x!=1) {
		x = x_suiv(x) ;
		}

  	printf ("%d\n",x);
  	return 0;
}
