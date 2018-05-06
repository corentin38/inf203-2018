interpreteur: interpreteur.o systeme.o commandes.o variables.o lignes.o
	clang -o interpreteur interpreteur.o systeme.o commandes.o variables.o lignes.o

systeme.o: systeme.c systeme.h debug.h
	clang -Wall -Werror -g -DDEBUG -c systeme.c

variables.o: variables.c debug.h variables.h variables_base.h
	clang -Wall -Werror -g -DDEBUG -c variables.c

commandes.o: commandes.c debug.h commandes.h systeme.h interpreteur.h \
 lignes.h
	clang -Wall -Werror -g -DDEBUG -c commandes.c

lignes.o: lignes.c lignes.h
	clang -Wall -Werror -g -DDEBUG -c lignes.c

interpreteur.o: interpreteur.c systeme.h lignes.h debug.h variables.h \
 variables_base.h commandes.h
	clang -Wall -Werror -g -DDEBUG -c interpreteur.c

clean:
	rm *.o interpreteur

test: lignes.o test_historique.o
	clang $^ -o $@

test_historique.o: test_historique.c lignes.h
	clang -Wall -Werror -g -DDEBUG -c $^
