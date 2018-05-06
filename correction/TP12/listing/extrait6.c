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

    /***************** Rajout pour le while *********************/
    A->transitions [NORMAL][WHILE_VRAI]   = ATTENTE_DO_VRAI;
    A->transitions [ATTENTE_DO_VRAI][DO]  = DANS_DO;
    A->transitions [DANS_DO][INSTRUCTION] = DANS_DO;
    A->transitions [DANS_DO][DONE]        = NORMAL;
    A->transitions [NORMAL][WHILE_FAUX]   = ATTENTE_DO_FAUX;
    A->transitions [ATTENTE_DO_FAUX][DO]  = ATTENTE_DONE;
    A->transitions [ATTENTE_DONE][DONE]   = NORMAL;

    A->sortie      [ATTENTE_DO_VRAI][DO]  = OUI;
    A->sortie      [DANS_DO][INSTRUCTION] = OUI;
    A->sortie      [DANS_DO][DONE]        = BOUCLE;
    /************************************************************/

    A->etat = NORMAL;
    A->nb_etats = 7;
    A->etat_initial = NORMAL;
    A->ligne_boucle = 0;
}
