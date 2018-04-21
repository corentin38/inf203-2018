automate: automate.o main.o
	clang automate.o main.o -o automate

automate.o: automate.c automate.h
	clang -c automate.c

main.o: main.c automate.h
	clang -c main.c
