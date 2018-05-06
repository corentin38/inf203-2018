#ifndef __TD11_H__
#define __TD11_H__

#include "variables.h"

/* pour aider a la mise au point des programmes - affichage des
 * variables d'un ensemble de variables */
void afficher_ensemble_variables(variables *ens);

/* cherche a reconnaitre une affectation de variable dans la ligne donnee.
 * Si c'est le cas, affecte la variable a la valeur donnee et modifie la ligne donnee.
 * Renvoie 1 en cas d'affectation trouvee, 0 sinon. */
int trouver_et_appliquer_affectation_variable(variables *ens, char *ligne);

/* copie la ligne originale dans la ligne expansee en remplacant les $NOM par la valeur
 * de la variable NOM */
void appliquer_expansion_variables(variables *ens, char *ligne_originale, char *ligne_expansee);

/* remplit l'ensemble de variables avec les variables automatiques correspondantes aux
 * arguments passes */
void affecter_variables_automatiques(variables *ens, int argc, char *argv[]);

#endif
