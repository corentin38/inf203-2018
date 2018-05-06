all: interpreteur main_test_vars

interpreteur: variables.o lignes.o interpreteur.o systeme.o
	clang -o interpreteur variables.o lignes.o interpreteur.o systeme.o

main_test_vars: variables.o main_test_vars.o
	clang -o main_test_vars variables.o main_test_vars.o

interpreteur.o: interpreteur.c systeme.h lignes.h debug.h variables.h \
  variables_base.h
	clang -Wall -Werror -g -c interpreteur.c

systeme.o: systeme.c systeme.h debug.h
	clang -Wall -Werror -g -c systeme.c

main_test_vars.o: main_test_vars.c variables.h variables_base.h
	clang -Wall -Werror -g -c main_test_vars.c

variables.o: variables.c debug.h variables.h variables_base.h
	clang -Wall -Werror -g -c variables.c

lignes.o: lignes.c lignes.h
	clang -Wall -Werror -g -c lignes.c

clean:
	rm *.o interpreteur main_test_vars
