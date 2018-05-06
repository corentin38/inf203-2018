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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "debug.h"
#include "variables.h"

char * const_empty = "";

void init_variables(variables * ens) {
	ens->nb = 0;
}

int ajouter_variable(variables * ens, char *nom, char *valeur) {
	int index = -1;

	for (int i=0; i<ens->nb; i++) {
		if (strcmp(nom, ens->T[i].nom) == 0) {
			strcpy(ens->T[i].valeur, valeur);
			index = i;
			break;
		}
	}

	if (index == -1) {
		if (ens->nb < (NOMBRE_MAX_VARIABLES - 1)) {
			strcpy(ens->T[ens->nb].nom, nom);
			strcpy(ens->T[ens->nb].valeur, valeur);
			index = ens->nb;
			ens->nb++;
		}
	}

	return index;
}

int nombre_variables(variables * ens) {
	return ens->nb;
}

int trouver_variable(variables * ens, char *nom) {
    int index = -1;

    for (int i=0; i<ens->nb; i++) {
	    if (strcmp (ens->T[i].nom, nom) == 0) {
		    index = i;
		    break;
	    }
    }

    return index;
}

char *nom_variable(variables * ens, int i) {
	char *nom = NULL;

	if (i >= 0 && i < ens->nb) {
		nom = ens->T[i].nom;
	}

	return nom;
}

char *valeur_variable(variables * ens, int i) {
	char *valeur = const_empty;

	if (i >= 0 && i < ens->nb) {
		valeur = ens->T[i].valeur;
	}

	return valeur;
}

void modifier_valeur_variable(variables * ens, int i, char *valeur) {
	strcpy (ens->T[i].valeur, valeur);
}

void afficher_ensemble_variables(variables * ens) {
    for (int i = 0; i < nombre_variables(ens); i++) {
        printf("%s=%s\n", nom_variable(ens, i), valeur_variable(ens, i));
    }
}

int trouver_et_appliquer_affectation_variable(variables * ens, char *ligne) {
	enum { ESP_DEB, NOM, EGAL, VAL, ERR } etat = ESP_DEB;
	int affectation_trouvee = 0;
	char *nom = NULL, *val = NULL;

	int i = 0;
	while (ligne[i] != '\0' && etat != ERR) {
		switch (etat) {

		case ESP_DEB:
			switch (ligne[i]) {
			case '=' : etat = ERR     ; break;
			case ' ' : etat = ESP_DEB ; break;
			default  :
				nom = &ligne[i];
				etat = NOM;
				break;
			}
			break;

		case NOM:
			switch (ligne[i]) {
			case '=' :
				ligne[i] = '\0';
				val = &ligne[i+1];
				etat = EGAL;
				break;
			case ' ' : etat = ERR  ; break;
			default  : etat = NOM  ; break;
			}
			break;

		case EGAL:
			switch (ligne[i]) {
			case '=' : etat = ERR  ; break;
			case ' ' : etat = ERR  ; break;
			default  : etat = VAL  ; break;
			}
			break;

		case VAL:
			switch (ligne[i]) {
			case '=' : etat = ERR  ; break;
			case ' ' : etat = ERR  ; break;
			default  : etat = VAL  ; break;
			}
			break;

		default: break;
		}
		i++;
	}

	if (etat == VAL) {
		ajouter_variable (ens, nom, val);
		affectation_trouvee = 1;
	}

	return affectation_trouvee;
}

int expand (variables *ens, char *nom, char *ligne_expansee) {
	int var_id = trouver_variable (ens, nom);
	int i = 0;
	if (var_id != -1) {
		char *val = valeur_variable (ens, var_id);
		while (val[i] != '\0') {
			ligne_expansee[i] = val[i];
			i++;
		}
	}
	return i;
}

void appliquer_expansion_variables(variables * ens, char *ligne_originale, char *ligne_expansee) {
	int i_o = 0, i_e = 0, i_n = 0;
	char nom[TAILLE_MAX_NOM] = "";
	int expanding = 0;

	while (ligne_originale[i_o] != '\0') {
		if (ligne_originale[i_o] == '$') {
			if (!expanding) {
				expanding = 1;
			}
		} else if (ligne_originale[i_o] == ' ') {
			if (expanding) {
				if (i_n == 0) {
					/* dollar isolé */
					ligne_expansee[i_e] = '$';
					i_e++;
				} else {
					nom[i_n] = '\0';
					i_e += expand (ens, nom, &ligne_expansee[i_e]);
					i_n = 0;
				}
				ligne_expansee[i_e] = ligne_originale[i_o];
				i_e++;
				expanding = 0;
			} else {
				ligne_expansee[i_e] = ligne_originale[i_o];
				i_e++;
			}
		} else {
			if (expanding) {
				nom[i_n] = ligne_originale[i_o];
				i_n++;
			} else {
				ligne_expansee[i_e] = ligne_originale[i_o];
				i_e++;
			}
		}
		i_o++;
	}

	if (expanding) {
		if (i_n == 0) {
			/* dollar isolé */
			ligne_expansee[i_e] = '$';
			i_e++;
		} else {
			nom[i_n] = '\0';
			i_e += expand (ens, nom, &ligne_expansee[i_e]);
			i_n = 0;
		}
	}
	ligne_expansee[i_e] = '\0';
}


void appliquer_expansion_variables2(variables * ens, char *ligne_originale, char *ligne_expansee) {
	enum { COPY, DOLLAR, EXPAND } etat = COPY;
	char nom[TAILLE_MAX_NOM] = "";

	int i_o = 0, i_e = 0, i_n = 0;
	while (ligne_originale[i_o] != '\0' || etat == EXPAND) {
		switch (etat) {

		case COPY:
			switch (ligne_originale[i_o]) {
			case '$':
				etat = DOLLAR;
				break;
			default:
				ligne_expansee[i_e] = ligne_originale[i_o];
				i_e++;
				etat = COPY;
				break;
			}
			break;

		case DOLLAR:
			if (isalnum(ligne_originale[i_o]) ||
			    ligne_originale[i_o] == '*'   ||
			    ligne_originale[i_o] == '#') {
				nom[0] = ligne_originale[i_o];
				i_n = 1;
				etat = EXPAND;
			} else {
				ligne_expansee[i_e]   = '$';
				ligne_expansee[i_e+1] = ligne_originale[i_o];
				i_e = i_e + 2;
				etat = COPY;
			}
			break;

		case EXPAND:
			if (isalnum(ligne_originale[i_o])) {
				nom[i_n] = ligne_originale[i_o];
				i_n++;
				etat = EXPAND;
			} else {
				nom[i_n] = '\0';
				int var_id = trouver_variable (ens, nom);
				if (var_id != -1) {
					char *val = valeur_variable (ens, var_id);
					int i_v = 0;
					while (val[i_v] != '\0') {
						ligne_expansee[i_e] = val[i_v];
						i_e++;
						i_v++;
					}
				}
				if (ligne_originale[i_o] != '\0') {
					ligne_expansee[i_e] = ligne_originale[i_o];
					i_e++;
				} else {
					i_o--;
				}
				etat = COPY;
			}
			break;

		}
		i_o++;
	}
	ligne_expansee[i_e] = '\0';
}

void affecter_variables_automatiques(variables *ens, int argc, char *argv[]) {
	char buffer[TAILLE_MAX_NOM];
	char buffer_cat[TAILLE_MAX_NOM] = "";
	int i = 0;

	sprintf (buffer, "%d", argc - 1);
	ajouter_variable (ens, "#", buffer);

	while (i < argc) {
		sprintf (buffer, "%d", i);
		ajouter_variable (ens, buffer, argv[i]);
		strcat (buffer_cat, argv[i]);
		if (i < argc - 1) {
			strcat (buffer_cat, " ");
		}
		i++;
	}

	ajouter_variable (ens, "*", buffer_cat);
}
