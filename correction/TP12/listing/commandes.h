/*
Interpr�teur de commandes � but p�dagogique
Copyright (C) 2011-2018 Guillaume Huard
Ce programme est libre, vous pouvez le redistribuer et/ou le modifier selon les
termes de la Licence Publique G�n�rale GNU publi�e par la Free Software
Foundation (version 2 ou bien toute autre version ult�rieure choisie par vous).

Ce programme est distribu� car potentiellement utile, mais SANS AUCUNE
GARANTIE, ni explicite ni implicite, y compris les garanties de
commercialisation ou d'adaptation dans un but sp�cifique. Reportez-vous � la
Licence Publique G�n�rale GNU pour plus de d�tails.

Vous devez avoir re�u une copie de la Licence Publique G�n�rale GNU en m�me
temps que ce programme ; si ce n'est pas le cas, �crivez � la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307,
�tats-Unis.

Contact: Guillaume.Huard@imag.fr
	 B�timent IMAG
	 700 avenue centrale, domaine universitaire
	 38401 Saint Martin d'H�res
*/

#ifndef __COMMANDES_H__
#define __COMMANDES_H__

#define NB_MAX_ETATS   128
#define NB_MAX_ENTREES 128

typedef struct {
	int etat;
	int nb_etats;
	int etat_initial;
	int transitions[NB_MAX_ETATS][NB_MAX_ENTREES];
	int sortie[NB_MAX_ETATS][NB_MAX_ENTREES];
	int ligne_boucle;
} automate;

void init_automate_commandes (automate *A);
int analyse_commande_interne (automate *A, char *ligne_courante);

#endif /* __COMMANDES_H__ */
