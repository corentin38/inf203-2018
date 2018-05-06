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

    /***************** Rajout pour le while *********************/
    if (entree == WHILE) {
        entree = selectionne_alternative(ligne_courante, WHILE_VRAI, WHILE_FAUX);
        code_sortie = NON;
        A->ligne_boucle = obtenir_numero_ligne ();
    }
    /************************************************************/

    int etat_suivant = A->transitions[A->etat][entree];
    code_sortie = A->sortie[A->etat][entree];
    A->etat = etat_suivant;

    /***************** Rajout pour le while *********************/
    if (code_sortie == BOUCLE) {
	    aller_a_la_ligne (A->ligne_boucle);
    }
    /************************************************************/

    debug ("Faut-il executer : %d\n", code_sortie);
    return code_sortie;
}
