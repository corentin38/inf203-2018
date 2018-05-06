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
    A->sortie     [NORMAL][IF_VRAI]                 = NON;
    A->sortie     [NORMAL][IF_FAUX]                 = NON;

    A->transitions[ATTENTE_THEN_VRAI][THEN]         = DANS_THEN;
    A->sortie     [ATTENTE_THEN_VRAI][THEN]         = OUI;

    A->transitions[DANS_THEN][INSTRUCTION]          = DANS_THEN;
    A->transitions[DANS_THEN][FI]                   = NORMAL;
    A->transitions[DANS_THEN][ELSE]                 = ATTENTE_FI;
    A->sortie     [DANS_THEN][INSTRUCTION]          = OUI;
    A->sortie     [DANS_THEN][FI]                   = NON;
    A->sortie     [DANS_THEN][ELSE]                 = NON;

    A->transitions[ATTENTE_FI][INSTRUCTION]         = ATTENTE_FI;
    A->transitions[ATTENTE_FI][FI]                  = NORMAL;
    A->sortie     [ATTENTE_FI][INSTRUCTION]         = NON;
    A->sortie     [ATTENTE_FI][FI]                  = NON;

    A->transitions[ATTENTE_THEN_FAUX][THEN]         = ATTENTE_ELSE_OU_FI;
    A->sortie     [ATTENTE_THEN_FAUX][THEN]         = NON;

    A->transitions[ATTENTE_ELSE_OU_FI][INSTRUCTION] = NORMAL;
    A->transitions[ATTENTE_ELSE_OU_FI][FI]          = NORMAL;
    A->transitions[ATTENTE_ELSE_OU_FI][ELSE]        = DANS_ELSE;
    A->sortie     [ATTENTE_ELSE_OU_FI][INSTRUCTION] = NON;
    A->sortie     [ATTENTE_ELSE_OU_FI][FI]          = NON;
    A->sortie     [ATTENTE_ELSE_OU_FI][ELSE]        = OUI;

    A->transitions[DANS_ELSE][INSTRUCTION]          = DANS_ELSE;
    A->transitions[DANS_ELSE][FI]                   = NORMAL;
    A->sortie     [DANS_ELSE][INSTRUCTION]          = OUI;
    A->sortie     [DANS_ELSE][FI]                   = NON;

    /**** etat initial ******************************/
    A->etat = NORMAL;
    A->nb_etats = 7;
    A->etat_initial = NORMAL;
    A->ligne_boucle = 0;
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
           Pour pouvoir executer ce qui suit le mot cle, la ligne courante
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
/*************** A COMPLETER ******************/
    /*
       Si vous arrivez a l'etape du while, il faut commencer
       par un traitement similaire au cas du if : executer le
       reste de la ligne pour recuperer le resultat du test.
       Il faut egalement penser a memoriser la ligne courante
       pour pouvoir y revenir en fin de boucle.
     */
    /*
       Dans tous les cas, calculer code_sortie et changer
       d'etat en fonction de etat_courant et de entree.
     */
/**********************************************/

    int etat_suivant = A->transitions[A->etat][entree];
    code_sortie = A->sortie[A->etat][entree];
    A->etat = etat_suivant;

    /* prise en compte du code de sortie, la fonction doit retourner :
       - 0 si la ligne ne doit pas etre executee (commande interne geree ici)
       - 1 sinon
       Ce sont les valeurs choisies pour NON et OUI
     */
    debug ("Faut-il executer : %d\n", code_sortie);
    return code_sortie;
}
