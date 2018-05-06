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
#include "commandes.h"
#include "systeme.h"
#include "interpreteur.h"
#include "lignes.h"

/********* Etats de l'Automate ************/

/* Gestion du if/then/else/fi */
#define NORMAL             0
#define ATTENTE_THEN_VRAI  1
#define ATTENTE_THEN_FAUX  2
#define DANS_THEN          3
#define DANS_ELSE          4
#define ATTENTE_FI         5
#define ATTENTE_ELSE_OU_FI 6
#define ERREUR             7

/* Gestion du while/do/done */
#define ATTENTE_DO_VRAI    8
#define ATTENTE_DO_FAUX    9
#define DANS_DO            10
#define ATTENTE_DONE       11

/********* Entrees de l'Automate *************/

/* Gestion du if/then/else/fi */
#define IF                 0
#define THEN               1
#define ELSE               2
#define FI                 3
#define INSTRUCTION        4
#define IF_VRAI            5
#define IF_FAUX            6

/* Gestion du while/do/done */
#define WHILE              7
#define DO                 8
#define DONE               9
#define WHILE_VRAI         10
#define WHILE_FAUX         11

/********* Sorties de l'Automate (resultat de commandes_internes) ************/
#define NON                0                /* ne pas executer */
#define OUI                1                /* ligne a executer */
#define BOUCLE             2                /* revenir au while */

char *mnemonique[] = { "if", "then", "else", "fi", "while", "do", "done" };
int valeur_mnemonique[] = { IF, THEN, ELSE, FI, WHILE, DO, DONE };
int nombre_mnemoniques = 7;

int decode_entree(char *mot) {
	int mnemo = INSTRUCTION;

	for (int i=0; i<nombre_mnemoniques; i++) {
		if (strcmp (mot, mnemonique[i]) == 0) {
			mnemo = valeur_mnemonique[i];
			break;
		}
	}

    return mnemo;
}

void init_automate_commandes(automate * A) {
    int i, j;

    /* La majorite des transitions vont dans l'etat d'erreur et la sortie est
       majoritairement NON
     */
    for (i = 0; i < NB_MAX_ETATS; i++) {
        for (j = 0; j < NB_MAX_ENTREES; j++) {
            A->transitions[i][j] = ERREUR;
            A->sortie[i][j] = NON;
        }
    }

    A->transitions[NORMAL][INSTRUCTION]             = NORMAL;
    A->transitions[NORMAL][IF_VRAI]                 = ATTENTE_THEN_VRAI;
    A->transitions[NORMAL][IF_FAUX]                 = ATTENTE_THEN_FAUX;
    A->sortie     [NORMAL][INSTRUCTION]             = OUI;

    A->transitions[ATTENTE_THEN_VRAI][THEN]         = DANS_THEN;
    A->sortie     [ATTENTE_THEN_VRAI][THEN]         = OUI;

    A->transitions[DANS_THEN][INSTRUCTION]          = DANS_THEN;
    A->transitions[DANS_THEN][FI]                   = NORMAL;
    A->transitions[DANS_THEN][ELSE]                 = ATTENTE_FI;
    A->sortie     [DANS_THEN][INSTRUCTION]          = OUI;

    A->transitions[ATTENTE_FI][INSTRUCTION]         = ATTENTE_FI;
    A->transitions[ATTENTE_FI][FI]                  = NORMAL;

    A->transitions[ATTENTE_THEN_FAUX][THEN]         = ATTENTE_ELSE_OU_FI;

    A->transitions[ATTENTE_ELSE_OU_FI][INSTRUCTION] = NORMAL;
    A->transitions[ATTENTE_ELSE_OU_FI][FI]          = NORMAL;
    A->transitions[ATTENTE_ELSE_OU_FI][ELSE]        = DANS_ELSE;
    A->sortie     [ATTENTE_ELSE_OU_FI][ELSE]        = OUI;

    A->transitions[DANS_ELSE][INSTRUCTION]          = DANS_ELSE;
    A->transitions[DANS_ELSE][FI]                   = NORMAL;
    A->sortie     [DANS_ELSE][INSTRUCTION]          = OUI;

    A->transitions[NORMAL][WHILE_VRAI] = ATTENTE_DO_VRAI;
    A->transitions[ATTENTE_DO_VRAI][DO] = DANS_DO;
    A->transitions[DANS_DO][INSTRUCTION] = DANS_DO;
    A->transitions[DANS_DO][DONE] = NORMAL;
    A->transitions[NORMAL][WHILE_FAUX] = ATTENTE_DO_FAUX;
    A->transitions[ATTENTE_DO_FAUX][DO] = ATTENTE_DONE;
    A->transitions[ATTENTE_DONE][DONE] = NORMAL;

    A->sortie[ATTENTE_DO_VRAI][DO] = OUI;
    A->sortie[DANS_DO][INSTRUCTION] = OUI;
    A->sortie[DANS_DO][DONE] = BOUCLE;

    A->etat = NORMAL;
    A->nb_etats = 7;
    A->etat_initial = NORMAL;
    A->ligne_boucle = 0;
}

int selectionne_alternative(char *ligne_commande, int valeur_vrai, int valeur_faux) {
    /*
       Dans le cas d'une structure conditionnelle, il faut tout de suite
       executer le reste de la ligne pour recuperer le resultat du test.
     */
    int resultat_test = executer_ligne_commande(ligne_commande);
    debug("Resultat du test : ");
    if (resultat_test) {
        debug("FAUX\n");
        return valeur_faux;
    } else {
        debug("VRAI\n");
        return valeur_vrai;
    }
}

void extrait_premier_mot(char *ligne_courante, char *premier_mot) {
    int i = 0;
    int j = 0;
    // On saute les espaces
    while (isspace(ligne_courante[i]))
        i++;
    // On copie le premier mot
    while (!isspace(ligne_courante[i]) && (ligne_courante[i] != '\0')) {
	    premier_mot[j] = ligne_courante[i];
        i++;
        j++;
    }
    premier_mot[j] = '\0';
}

int analyse_commande_interne(automate * A, char *ligne_courante) {
    char bout_de_ligne[TAILLE_MAX_LIGNE];
    int entree;
    int i;
    /*
       Par defaut, on indiquera a la fonction appelante qu'elle doit
       executer la commande, on passera cela a NON si on rencontre une
       commande interne completement resolue ici
     */
    int code_sortie = OUI;

    debug("J'essaie de reconnaitre une commande interne\n");
    /*
       On extrait d'abord le premier mot de la ligne pour voir si c'est un
       mnemonique de commande interne
     */
    extrait_premier_mot(ligne_courante, bout_de_ligne);
    entree = decode_entree(bout_de_ligne);

    if (entree != INSTRUCTION) {
        /*
           Si on a reconnu un mnemonique, on l'affiche (debug)
         */
        debug("Commande interne reconnue : %s\n", bout_de_ligne);
        /*
           Pour pouvoir exécuter ce qui suit le mot clé, la ligne courante
           devient ce qui reste apres le premier mot :
           on ecrase simplement le debut de la chaine.
         */
        int len = strlen(bout_de_ligne);
        for (i=len; ligne_courante[i] != '\0'; i++)
            ligne_courante[i-len] = ligne_courante[i];
        ligne_courante[i-len] = '\0';
    }

    /*
       Dans le cas d'une structure conditionnelle, le code de sortie sera
       NON (puisqu'on execute la fin de ligne pour le test).
    */
    if (entree == IF) {
        entree = selectionne_alternative(ligne_courante, IF_VRAI, IF_FAUX);
        code_sortie = NON;
    }

    if (entree == WHILE) {
        entree = selectionne_alternative(ligne_courante, WHILE_VRAI, WHILE_FAUX);
        code_sortie = NON;
        A->ligne_boucle = obtenir_numero_ligne ();
    }

    int etat_suivant = A->transitions[A->etat][entree];
    code_sortie = A->sortie[A->etat][entree];
    A->etat = etat_suivant;

    if (code_sortie == BOUCLE) {
	    aller_a_la_ligne (A->ligne_boucle);
    }

    debug ("Faut-il executer : %d\n", code_sortie);
    return code_sortie;
}
