codage : codage.o code1.o code2.o entrees_sorties_codage.o
	@echo creation de codage :
	clang -o codage codage.o code1.o code2.o entrees_sorties_codage.o
	@echo -------------------------------

codage.o : codage.c code1.h code2.h entrees_sorties_codage.h
	@echo creation de codage.o :
	clang -Wall -Werror -c  codage.c
	@echo -------------------------------

code1.o : code1.c code1.h
	@echo creation de code1.o :
	clang -Wall -Werror -c  code1.c
	@echo -------------------------------

code2.o : code2.c  code2.h entrees_sorties_codage.h
	@echo creation de code2.o :
	clang -Wall -Werror -c  code2.c
	@echo -------------------------------

entrees_sorties_codage.o: entrees_sorties_codage.c entrees_sorties_codage.h
	@echo creation de entrees_sorties_codage.o :
	clang -Wall -Werror -c  entrees_sorties_codage.c
	@echo -------------------------------
