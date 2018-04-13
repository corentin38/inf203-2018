main : main.o automate.o
	clang -o main main.o automate.o

main.o : main.c automate.h
	clang -Wall -Werror -g -c main.c

automate.o : automate.c automate.h
	clang -Wall -Werror -g -c automate.c

clean :
	rm *.o main
