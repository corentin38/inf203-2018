/*
Interpréteur de commandes à but pédagogique
Copyright (C) 2011-2018 Guillaume Huard
Ce programme est libre, vous pouvez le redistribuer et/ou le modifier selon les
termes de la Licence Publique Générale GNU publiée par la Free Software
Foundation (version 2 ou bien toute autre version ultérieure choisie par vous).

Ce programme est distribué car potentiellement utile, mais SANS AUCUNE
GARANTIE, ni explicite ni implicite, y compris les garanties de
commercialisation ou d'adaptation dans un but spécifique. Reportez-vous à la
Licence Publique Générale GNU pour plus de détails.

Vous devez avoir reçu une copie de la Licence Publique Générale GNU en même
temps que ce programme ; si ce n'est pas le cas, écrivez à la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307,
États-Unis.

Contact: Guillaume.Huard@imag.fr
	 Bâtiment IMAG
	 700 avenue centrale, domaine universitaire
	 38401 Saint Martin d'Hères
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lignes.h"

int lire_ligne_fichier(FILE * fichier, char *ligne) {
	char cc = 0;
	int i = 0;

	fscanf (fichier, "%c", &cc);
	while (!feof (fichier) && cc == '\n') {
		fscanf (fichier, "%c", &cc);
	}

	while (!feof (fichier) && cc != '\n') {
		ligne[i] = cc;
		i++;
		fscanf (fichier, "%c", &cc);
	}
	ligne[i] = '\0';

	return !feof (fichier);
}

void decouper_ligne(char *ligne, char *ligne_decoupee[]) {
	int car_prec_espace = 1, i = 0, index = 0;

	while (ligne[i] != '\0') {
		if (ligne[i] == ' ' && !car_prec_espace) {
			ligne[i] = '\0';
		}

		if (ligne[i] != ' ' && car_prec_espace) {
			ligne_decoupee[index] = &ligne[i];
			index++;
		}

		car_prec_espace = (ligne[i] == ' ' || ligne[i] == '\0');
		i++;
	}
	ligne_decoupee[index] = NULL;
}
