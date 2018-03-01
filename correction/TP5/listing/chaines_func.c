#include <stdio.h>
#include <string.h>
#include "generer_entier.c"
#include "bouts_de_phrases.c"

/* longueur de la chaine passee en parametre */
int mon_strlen(char ch[]) {
	int i=0 ;
	while (ch[i] != '\0') {
		i++;
	}
	return i ;
}

void mon_strcpy(char destination[], char source[]) {
	int i=0;
	while (source[i] != '\0') {
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
}

void mon_strcat(char destination[], char source[]) {
	int i=0, j=0;
	while (destination[i] != '\0') {
		i++;
	}
	while (source[j] != '\0') {
		destination[i+j] = source[j];
		j++;
	}
	destination[i+j] = '\0';
}

int mon_strcmp(char chaine1[], char chaine2[]) {
	int resultat = 0;

	int i=0;
	while (chaine1[i] == chaine2[i] && chaine1[i] != '\0') {
		i++;
	}

	if (chaine1[i] == '\0' && chaine2[i] == '\0') {
		resultat = 0;
	} else {
		if (chaine1[i] < chaine2[i]) {
			resultat = -1;
		} else {
			resultat = 1;
		}
	}

	return resultat;
}
