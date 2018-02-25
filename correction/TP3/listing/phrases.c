#include <stdio.h>
#include <string.h>
#include "generer_entier.c"
#include "bouts_de_phrases.c"

int mon_strlen(char ch[]) {
	...
}

void mon_strcpy(char destination[], char source[]) {
	...
}

void mon_strcat(char destination[], char source[]) {
	...
}

int mon_strcmp(char chaine1[], char chaine2[]) {
	...
}

void faire_phrase(char sujet[], char verbe[], char compl[], char phrase[]) {
	mon_strcat(phrase, sujet);
	mon_strcat(phrase, " ");
	mon_strcat(phrase, verbe);
	mon_strcat(phrase, " ");
	mon_strcat(phrase, compl);
}

int nb_mots(char phrase[]) {
	int i=0, nb=0;
	while (phrase[i] != '\0') {
		if (phrase[i] == ' ') {
			nb++;
		}
		i++;
	}
	return ++nb;
}

int main() {
	long num_sujet = generer_entier(10);
	long num_verbe = generer_entier(10);
	long num_compl = generer_entier(10);

	char Phrase[150]="";

	faire_phrase(sujet[num_sujet], verbe[num_verbe], complement[num_compl], Phrase);

	printf ("phrase (%d) : %s\n", nb_mots(Phrase), Phrase);
	return 0 ;
}
