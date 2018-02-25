int main() {
	char chaine[50] ;
	int mon_resultat ;

	printf("un mot (pas plus grand que 50 caractères !) à mesurer ?\n") ;
	scanf("%s", chaine) ;

	mon_resultat=mon_strlen(chaine) ;
	if ( mon_resultat == strlen(chaine) ) {
		printf("longueur du mot ('%s') : %d\n\n", chaine, mon_resultat) ;
	} else {
		printf("non, la longueur de '%s' n'est pas %d\n", chaine, mon_resultat) ;
	}

	char resultat[50];
	mon_strcpy(resultat, "copie simple");
	printf ("mon_strcpy(resultat, \"copie simple\") \t\t resultat = <%s>\n", resultat);
	mon_strcpy(resultat, "");
	printf ("mon_strcpy(resultat, \"\") \t\t\t\t\t resultat = <%s>\n", resultat);

	mon_strcat(resultat, "ajout1");
	printf ("mon_strcat(resultat, \"ajout1\") \t\t\t\t resultat = <%s>\n", resultat);
	mon_strcat(resultat, " ajout2");
	printf ("mon_strcat(resultat, \" ajout2\") \t\t\t resultat = <%s>\n", resultat);
	mon_strcat(resultat, "");
	printf ("mon_strcat(resultat, \"\") \t\t\t\t\t resultat = <%s>\n\n", resultat);

	printf ("mon_strcmp(\"\", \"\") \t\t\t = %d\n", mon_strcmp("", ""));
	printf ("mon_strcmp(\"abc\", \"abc\") \t = %d\n", mon_strcmp("abc", "abc"));
	printf ("mon_strcmp(\"abc\", \"xbc\") \t = %d\n", mon_strcmp("abc", "xbc"));
	printf ("mon_strcmp(\"abc\", \"abC\") \t = %d\n", mon_strcmp("abc", "abC"));
	printf ("mon_strcmp(\"a\", \"abc\") \t\t = %d\n", mon_strcmp("a", "abc"));
	return 0 ;
}
