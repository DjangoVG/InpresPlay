#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*-----------------------------------------------------------------------------------*/
/* Auteur : Régis Evrard                                                             */
/* Groupe : 2201                                                                     */
/* Application : LC30_Evrard_Régis.c                                                 */
/* Date de la dernière maj de l'exercice : 30/03/2019                                */
/*-----------------------------------------------------------------------------------*/

#define MAX_JOUEURS 10

struct Date
{
    short jour;
    short mois;
    short annee;
};

struct Joueurs {
	long IdJoueur ;
	char Nom[25] ;
	char Prenom[25] ;
	struct Date DateNaissance;
	char Adresse[50] ;
	char CodePostal[5];
	char Ville[25];
	char Pays[25];
	char Telephone[13];
	char AdMail[65];
};

struct IndexJoueurs
{
    long IdJoueur;
	char Nom [25];
    short pos;
};

void Initialisation_Joueurs(struct IndexJoueurs *,struct Joueurs *);
void Tri_IndexJoueurs (struct IndexJoueurs *, struct IndexJoueurs *, int);
void Ajouter_Joueurs(struct IndexJoueurs *,struct Joueurs *, struct IndexJoueurs *, struct tm *);
void Affichage_Joueurs(struct Joueurs *, struct IndexJoueurs *);
short Recherche_Joueurs(struct IndexJoueurs *, long);
void Modifier_Joueurs(struct IndexJoueurs *, struct Joueurs *, struct IndexJoueurs *, struct tm *);
void Supprimer_Joueurs(struct IndexJoueurs *,struct Joueurs *);
int Verification_iD_Joueur(long iDJoueur, struct IndexJoueurs *);
void BidonnageJoueurs(struct Joueurs *);
void Affichage_Index_Joueurs(struct IndexJoueurs *);

int LireChaine (char *);
void LireMail (char *);
void LireCode (char *);
void LireCodePostal (char *);

int VerifTexte(char *);
int VerifDate(short *, short *, short *);
int VerifLong(long *);
int VerifInt(int *);
int VerifMail (char *, short);
int VerifTel (char *);
int VerifCodePostal (char *);

void ModifChaine (char *);

int main()
{
	struct Joueurs Joueurs[MAX_JOUEURS], *pJoueurs;
	struct IndexJoueurs IndJoueurs[MAX_JOUEURS], *pIndexJoueurs, *pIndexJoueurs2;
	short i, PositionAjout, IdJoueurChoisi;
    int ChoixMenuPrincipal=1,ControleChoix, NombreJoueurs, sortie=1, Controle=1;

	pIndexJoueurs = &IndJoueurs[0];
	pIndexJoueurs2 = &IndJoueurs[0];
    pJoueurs = &Joueurs[0];

    time_t timestamp; /* Structure de la date du jour */
    struct tm * t;
    timestamp = time(NULL);
    t = localtime(&timestamp);
    t->tm_year=t->tm_year+1900;
    t->tm_mon=t->tm_mon+1;

	BidonnageJoueurs(&Joueurs[0]); /* On bidone le tableau de structures */
	Initialisation_Joueurs(&IndJoueurs[0], &Joueurs[0]); /* On initialise l'index */

	do
	{
	    pIndexJoueurs = &IndJoueurs[0];
		for (i=0, NombreJoueurs=0;i<MAX_JOUEURS;i++,pIndexJoueurs++)
		{
			if ((pIndexJoueurs->IdJoueur) != -1)
				NombreJoueurs++;
		}
		pIndexJoueurs = &IndJoueurs[0];
    	pJoueurs = &Joueurs[0];
    	Tri_IndexJoueurs (&IndJoueurs[0], &IndJoueurs[0],  NombreJoueurs);

        if (NombreJoueurs <= MAX_JOUEURS)
        {
	        do
	        {
	            if((ChoixMenuPrincipal<1||ChoixMenuPrincipal>5) || ControleChoix==0)
	            	printf("\nChoix Incorrect // Rechoississez votre choix\n");

	            printf("\n-- Menu principal --\n");
	            printf("--------------------\n\n");
	            printf("Que voulez-vous faire :\n\n");
	            printf("1) Ajouter un Joueur\n");
	            printf("2) Modifier un Joueur\n");
	            printf("3) Supprimer un Joueur\n");
	            printf("4) Afficher tous les Joueurs \n");
	            printf("5) Quitter\n\n");
	            printf("Action : ");

	            ControleChoix = VerifInt(&ChoixMenuPrincipal);
	        } while(( ChoixMenuPrincipal<1 || ChoixMenuPrincipal>5) || ControleChoix==0);

			switch (ChoixMenuPrincipal)
	        {
	        	case 1 : system("cls");
						 for (i = 0, pIndexJoueurs = &IndJoueurs[0], sortie=1;i<MAX_JOUEURS && sortie==1; i++, pIndexJoueurs++)
						 {
						     if(pIndexJoueurs->IdJoueur == -1)
						     {
						         PositionAjout = pIndexJoueurs->pos;
						         sortie = 0;
						     }
						 }
			             Ajouter_Joueurs(&IndJoueurs[PositionAjout],&Joueurs[PositionAjout],pIndexJoueurs2, t);
			             break;
			    case 2 : system("cls");
                         if (NombreJoueurs == 0)
                             printf ("Il n'y a aucun joueur enregistre !!\n");
                         else
                         {
                             Affichage_Joueurs(&Joueurs[0], &IndJoueurs[0]);
                             Modifier_Joueurs(&IndJoueurs[0],&Joueurs[0], &IndJoueurs[0], t);
                         }
			             break;
			    case 3 : system("cls");
                         if (NombreJoueurs == 0)
                             printf ("Il n'y a aucun joueur enregistre !!\n");
                         else
                         {
                             Affichage_Joueurs(&Joueurs[0], &IndJoueurs[0]);
                             Supprimer_Joueurs(&IndJoueurs[0],&Joueurs[0]);
                         }
			             break;
			    case 4 : system("cls");
                         if (NombreJoueurs == 0)
                             printf ("Il n'y a aucun joueur enregistre !!\n");
                         else
                             Affichage_Joueurs(&Joueurs[0], &IndJoueurs[0]);
			             break;
			    case 5 : Controle=0;
			             break;
	        }
        }
        else
		{
			do
	        {
	            if((ChoixMenuPrincipal<1||ChoixMenuPrincipal>4)||ControleChoix==0)
	            	printf("\nChoix Incorrect // Rechoississez votre choix\n");

	            printf("\n-- Menu principal --\n");
	            printf("--------------------\n\n");
	            printf("Que voulez-vous faire :\n\n");
	            printf("1) Modifier un Joueur\n");
	            printf("2) Supprimer un Joueur\n");
	            printf("3) Afficher tous les Joueurs \n");
	            printf("4) Quitter\n\n");
	            printf("Action : ");

	            ControleChoix = VerifInt(&ChoixMenuPrincipal);
	        } while(( ChoixMenuPrincipal<1 || ChoixMenuPrincipal>4) || ControleChoix==0);

	        switch (ChoixMenuPrincipal)
	        {
			    case 1 : system("cls");
                         if (NombreJoueurs == 0)
                             printf ("Il n'y a aucun joueur enregistre !!\n");
                         else
                         {
                             Affichage_Joueurs(&Joueurs[0], &IndJoueurs[0]);
                             Modifier_Joueurs(&IndJoueurs[0],&Joueurs[0], &IndJoueurs[0], t);
                         }
			             break;
			    case 2 : system("cls");
                         if (NombreJoueurs == 0)
                             printf ("Il n'y a aucun joueur enregistre !!\n");
                         else
                         {
                             Affichage_Joueurs(&Joueurs[0], &IndJoueurs[0]);
                             Supprimer_Joueurs(&IndJoueurs[0],&Joueurs[0]);
                         }
			             break;
			    case 3 : system("cls");
                         if (NombreJoueurs == 0)
                             printf ("Il n'y a aucun joueur enregistre !!\n");
                         else
                             Affichage_Joueurs(&Joueurs[0], &IndJoueurs[0]);
			             break;
			    case 4 : Controle=0;
			             break;
	        }
		}
	} while (Controle==1);

    return 0;
}

/********************************************************************************************************/
/**INPUT : Prend l'adresse du premiere element de la structure Joueurs.                                **/
/**PROCESS : Initialise la structure Joueurs en mettant des champs vides et en initialisant les id à -1**/
/**OUTPUT : /                                                                                          **/
/********************************************************************************************************/
void BidonnageJoueurs(struct Joueurs *pJoueurs)
{
	short i;

	for(i=0; i<MAX_JOUEURS; i++, pJoueurs++)
	{
		pJoueurs->IdJoueur = -1;
		strcpy(pJoueurs->Nom, "0");
		strcpy(pJoueurs->Prenom, "0");
		pJoueurs->DateNaissance.jour = 0;
		pJoueurs->DateNaissance.mois = 0;
		pJoueurs->DateNaissance.annee = 0;
		strcpy(pJoueurs->Adresse, "0");
		strcpy(pJoueurs->CodePostal, "0");
		strcpy(pJoueurs->Ville, "0");
		strcpy(pJoueurs->Pays, "0");
		strcpy(pJoueurs->Telephone, "0");
		strcpy(pJoueurs->AdMail, "\0");
	}
}

/********************************************************************************************************/
/**INPUT : Prend l'adresse du premiere element de la structure IndexJoueurs , de la structure Joueurs .**/
/**PROCESS : Initialise l'IndexJoueurs en le remplissant des valeurs contenues dans la struct Joueurs. **/
/**OUTPUT : void                                                                                       **/
/********************************************************************************************************/
void Initialisation_Joueurs(struct IndexJoueurs *pIndexJoueurs,struct Joueurs *pJoueurs)
{
	short i;
	for(i=0;i<MAX_JOUEURS;i++, pJoueurs++, pIndexJoueurs++)
	{
	    pIndexJoueurs->IdJoueur = pJoueurs->IdJoueur;
	    strcpy(pIndexJoueurs->Nom,pJoueurs->Nom);
	    pIndexJoueurs->pos = i;
	}
}

/****************************************************************************************************************************************************************************************/
/**INPUT : Prend l'adresse du premiere element de l'IndexJoueurs et le nombre de joueurs actuels.                                                                                      **/
/**PROCESS : on trie l'index Joueur sur les chaines 'Nom' .   																														   **/
/**OUTPUT : /                                                                                                                                                                          **/
/****************************************************************************************************************************************************************************************/
void Tri_IndexJoueurs (struct IndexJoueurs *pIndexJoueurs, struct IndexJoueurs *pIndex, int NombreJoueurs)
{
    short i=10, MaxIdJoueurs, MaxPlace;
    char NomTemporaire[25];

    while (NombreJoueurs>0)
    {
        for( i=NombreJoueurs ; i>1 ;i--, pIndexJoueurs++)
        {
            if(strcmp(pIndexJoueurs->Nom,(pIndexJoueurs+1)->Nom) == 1)
            {
				MaxIdJoueurs = (pIndexJoueurs+1)->IdJoueur;
				(pIndexJoueurs+1)->IdJoueur = pIndexJoueurs->IdJoueur;
				pIndexJoueurs->IdJoueur = MaxIdJoueurs;

				strcpy(NomTemporaire,(pIndexJoueurs+1)->Nom);
				strcpy((pIndexJoueurs+1)->Nom,pIndexJoueurs->Nom);
				strcpy(pIndexJoueurs->Nom,NomTemporaire);

				MaxPlace = (pIndexJoueurs+1)->pos;
				(pIndexJoueurs+1)->pos = pIndexJoueurs->pos;
				pIndexJoueurs->pos = MaxPlace;
            }
        }
    	pIndexJoueurs = pIndex;
    	NombreJoueurs--;
    }
}

/***************************************************************************************************************************************************************************************/
/**INPUT : Prend l'adresse à la bonne position pour ajouter de l'IndexJoueurs, pointeur sur struct Joueurs, un deuxieme pointeur sur l'indexJoueurs + l'adresse de la structure time. **/
/**PROCESS : Ajout des différents champs sur la structure Joueurs + reemplissage de l'index 														                                  **/
/**OUTPUT : void                                                                                                                                                                      **/
/***************************************************************************************************************************************************************************************/
void Ajouter_Joueurs(struct IndexJoueurs *pIndexJoueurs,struct Joueurs *pJoueurs, struct IndexJoueurs *pIndexJoueurs2, struct tm *t)
{
	int i,verifLong,CodePostal, VerifChaine=1,ControleAge,lg, Controle;
	float VerifJour=0,VerifMois=0,VerifAnnee=0;
	long iDJoueur;

    fflush(stdin);
    do{ /* Verification de l'ID du Joueur */
    	printf("\nEntrez l'iD du Joueur : ");
    	verifLong = VerifLong(&iDJoueur);
    	if(verifLong == 0 || (iDJoueur<1 || iDJoueur>999))
    		printf("\nUn ID valide est un chiffre entre [1->999] !\nRentrez un nouveau ID : ");
    	if(Verification_iD_Joueur(iDJoueur, pIndexJoueurs2) == 0)
            printf("\nCe Joueur/ID existe deja !\nRentrez un nouveau ID : ");
    } while ((verifLong==0)|| (Verification_iD_Joueur(iDJoueur, pIndexJoueurs2) == 0)||( iDJoueur<1 || iDJoueur>999));
    pJoueurs->IdJoueur = iDJoueur; /* On rentre l'id si tout est ok */

	do{
		printf("\nEntrez le nom du Joueur : ");
		fflush(stdin);
		VerifChaine = LireChaine(pJoueurs->Nom);
		if (VerifChaine == 0)
			printf("\nLe nom encode n'est pas valide !\n");
	} while (VerifChaine == 0);
	ModifChaine(pJoueurs->Nom);

	do{
		printf("\nEntrez le prenom du Joueur : ");
		fflush(stdin);
		VerifChaine = LireChaine(pJoueurs->Prenom);
		if (VerifChaine == 0)
			printf("\nLe prenom encode n'est pas valide !\n");
	} while (VerifChaine == 0);
    ModifChaine(pJoueurs->Prenom);

	ControleAge = 1;
    do{
		do{
            fflush(stdin);
			printf("\nEncodez la date de naissance du Joueur <%s %s> dans le format [JJ/MM/AAAA] : ",(pJoueurs->Prenom), (pJoueurs->Nom));
		} while (VerifDate(&pJoueurs->DateNaissance.jour,&pJoueurs->DateNaissance.mois,&pJoueurs->DateNaissance.annee) == 0);

		VerifJour=(t->tm_mday)-(pJoueurs->DateNaissance.jour);
		VerifMois=(t->tm_mon)-(pJoueurs->DateNaissance.mois);
		VerifAnnee=(t->tm_year)-(pJoueurs->DateNaissance.annee);

		if(VerifAnnee<0 || (VerifAnnee==0 && VerifMois<=0 && VerifJour<0) || (VerifAnnee==0 && VerifMois<0))
		{
			printf("\nLe Joueur <%s %s> doit etre ne !\n",(pJoueurs->Prenom), (pJoueurs->Nom));
			ControleAge = 0;
		}
		else
        {
            if(VerifAnnee<12 || (VerifAnnee==12 && VerifJour<0 && VerifMois<=0)|| (VerifAnnee==12 && VerifMois<0))
            {
                printf("\nLe Joueur <%s %s> doit avoir au moins 12 ans pour jouer aux jeux videos !\n",(pJoueurs->Prenom), (pJoueurs->Nom));
                ControleAge = 0;
            }
            else
            {
                ControleAge = 1;
            }
        }
	} while (ControleAge == 0);

	do{
		printf("\nEntrez la rue du Joueur : ");
		fflush(stdin);
		VerifChaine = LireChaine(pJoueurs->Adresse);
		if (VerifChaine == 0)
			printf("\nLa rue encode n'est pas valide !\n");
	} while (VerifChaine == 0);

	do{
		printf("\nEntrez le code postal du Joueur : ");
		fflush(stdin);
		LireCode(pJoueurs->CodePostal);
		VerifChaine = VerifCodePostal(pJoueurs->CodePostal);
		if (VerifChaine == 2)
			printf("\nLe code postal encode n'est pas valide !\n");
	} while (VerifChaine == 2);

	do{
		printf("\nEntrez la ville du Joueur : ");
		fflush(stdin);
		VerifChaine = LireChaine(pJoueurs->Ville);
		if (VerifChaine == 0)
			printf("\nLa ville encode n'est pas valide !\n");
	} while (VerifChaine == 0);

	do{
		printf("\nEntrez le pays du Joueur : ");
		fflush(stdin);
		VerifChaine = LireChaine(pJoueurs->Pays);
		if (VerifChaine == 0)
			printf("\nLe pays encode n'est pas valide !\n");
	} while (VerifChaine == 0);

    do{
		printf("\nEntrez le telephone (de type 04/XXX.XX.XX) du Joueur : ");
		fflush(stdin);
		LireCode(pJoueurs->Telephone);
		VerifChaine = VerifTel(pJoueurs->Telephone);
		if (VerifChaine == 2)
			printf("\nLe telephone encode n'est pas valide !");
	} while (VerifChaine == 2);

	do
	{
		printf ("\nVoulez-vous entrer une adresse mail pour le Joueur ? (Oui : 1 || Non : 0)");
		scanf("%d", &Controle);
		if (Controle == 1)
            do
            {
                printf("\nEntrez l'adresse mail du Joueur : ");
                fflush(stdin);
                LireMail(pJoueurs->AdMail);
                lg = strlen(pJoueurs->AdMail);

                VerifChaine = VerifMail (pJoueurs->AdMail, lg);
                if (VerifChaine == 2)
                    printf ("\n Votre adresse mail entre n'est pas dans bon format !");
            } while (VerifChaine == 2);
        else
        	strcpy(pJoueurs->AdMail, "Non-renseigne");
	} while (Controle != 0 && Controle != 1);


    pIndexJoueurs->IdJoueur = pJoueurs->IdJoueur;
    strcpy((pIndexJoueurs->Nom) , (pJoueurs->Nom));

    system("cls");
    printf("\nLe Joueur <%s %s> a bien ete ajoute !\n",pJoueurs->Prenom, pJoueurs->Nom);
}

/***************************************************************************************************************************************************************************************/
/**INPUT : Prend l'adresse à la bonne position pour ajouter de l'IndexJoueurs, pointeur sur struct Joueurs, un deuxieme pointeur sur l'indexJoueurs + l'adresse de la structure time. **/
/**PROCESS : Modification des différents champs sur la structure Joueurs + update de l'IndexJoueurs	         										                                  **/
/**OUTPUT : void                                                                                                                                                                      **/
/***************************************************************************************************************************************************************************************/
void Modifier_Joueurs(struct IndexJoueurs *pIndexJoueurs, struct Joueurs *pJoueurs,  struct IndexJoueurs *pIndexJoueurs2, struct tm *t)
{
	int i,sortie=1,veriflong, VerifChaine=1,ControleAge,lg, ChoixModif=1, VerifChoix, Boucle=1;
	float VerifJour=0,VerifMois=0,VerifAnnee=0;
	long iDJoueur, IdJoueurChoisi;
	short pos, PositionAjout;

    do
    {
        printf ("\nQuel joueur voulez-vous modifier ? (IdJoueur) : ");
        scanf("%ld", &IdJoueurChoisi);
    } while (IdJoueurChoisi < 1 || IdJoueurChoisi > 999);
    PositionAjout = Recherche_Joueurs(pIndexJoueurs, IdJoueurChoisi);
    if (PositionAjout == -1)
    {
        system("cls");
        printf ("\nCet Id de Joueur n'existe pas !\n");
    }
    else
    {
        pos = (pIndexJoueurs+PositionAjout)->pos;
        pJoueurs += pos;
        printf ("\nVous avez choisi de modifier le Joueur <%s %s>.\n", pJoueurs->Prenom, pJoueurs->Nom);
        do{
            do{
                if((ChoixModif<1||ChoixModif>11) || VerifChoix==0)
                    printf("\nChoix Incorrect\n");

                printf("\n\nQu'est ce que vous voulez modifier ? : ");
                printf("\n1. Id du Joueur");
                printf("\n2. Nom du Joueur");
                printf("\n3. Prenom du Joueur");
                printf("\n4. Date de naissance du Joueur");
                printf("\n5. Adresse du Joueur");
                printf("\n6. Code Postal du Joueur");
                printf("\n7. Ville du Joueur");
                printf("\n8. Pays du Joueur");
                printf("\n9. Telephone du Joueur");
                printf("\n10. Adresse mail du Joueur");
                printf("\n11. Quitter le menu de modification");
                printf("\nvotre choix : ");
                VerifChoix = VerifInt(&ChoixModif);
            } while((ChoixModif<1||ChoixModif>11) || VerifChoix==0);

            switch(ChoixModif)
            {
                case 1 :
                        do{ /* Verification de l'ID du Joueur */
                            printf("\nEntrez l'iD du Joueur : ");
                            veriflong = VerifLong(&iDJoueur);
                            if(veriflong == 0 || (iDJoueur<1 || iDJoueur>999))
                                printf("\nUn ID valide est un chiffre entre [1->999] !\nRentrez un nouveau ID : ");
                            if(Verification_iD_Joueur(iDJoueur, pIndexJoueurs2) == 0)
                                printf("\nCe Joueur/ID existe deja !\nRentrez un nouveau ID : ");
                        } while ((veriflong==0)|| (Verification_iD_Joueur(iDJoueur, pIndexJoueurs2) == 0)||( iDJoueur<1 || iDJoueur>999));
                        pJoueurs->IdJoueur = iDJoueur; /* On rentre l'id si tout est ok */
                        break;

                case 2 :
                        do{
                            printf("\nEntrez le nom du Joueur : ");
                            fflush(stdin);
                            VerifChaine = LireChaine(pJoueurs->Nom);
                            if (VerifChaine == 0)
                                printf("\nLe nom encode n'est pas valide !\n");
                        } while (VerifChaine == 0);
                        ModifChaine(pJoueurs->Nom);
                        break;

                case 3 :
                        do{
                            printf("\nEntrez le prenom du Joueur : ");
                            fflush(stdin);
                            VerifChaine = LireChaine(pJoueurs->Prenom);
                            if (VerifChaine == 0)
                                printf("\nLe prenom encode n'est pas valide !\n");
                        } while (VerifChaine == 0);
                        ModifChaine(pJoueurs->Prenom);
                        break;

                case 4 :
                        ControleAge = 1;
                        do{
                            do{
                                fflush(stdin);
                                printf("\nEncodez la date de naissance du Joueur <%s %s> dans le format [JJ/MM/AAAA] : ",(pJoueurs->Prenom), (pJoueurs->Nom));
                            } while (VerifDate(&pJoueurs->DateNaissance.jour,&pJoueurs->DateNaissance.mois,&pJoueurs->DateNaissance.annee) == 0);

                            VerifJour=(t->tm_mday)-(pJoueurs->DateNaissance.jour);
                            VerifMois=(t->tm_mon)-(pJoueurs->DateNaissance.mois);
                            VerifAnnee=(t->tm_year)-(pJoueurs->DateNaissance.annee);

                            if(VerifAnnee<0 || (VerifAnnee==0 && VerifMois<=0 && VerifJour<0) || (VerifAnnee==0 && VerifMois<0))
                            {
                                printf("\nLe Joueur <%s %s> doit etre ne !\n",(pJoueurs->Prenom), (pJoueurs->Nom));
                                ControleAge = 0;
                            }
                            else
                            {
                                if(VerifAnnee<16 || (VerifAnnee==12 && VerifJour<0 && VerifMois<=0)|| (VerifAnnee==12 && VerifMois<0))
                                {
                                    printf("\nLe Joueur <%s %s> doit avoir au moins 12 ans pour jouer aux jeux videos !\n",(pJoueurs->Prenom), (pJoueurs->Nom));
                                    ControleAge = 0;
                                }
                                else
                                {
                                    ControleAge = 1;
                                }
                            }
                        } while (ControleAge == 0);
                        break;

                case 5 :
                        do{
                            printf("\nEntrez la rue du Joueur : ");
                            fflush(stdin);
                            VerifChaine = LireChaine(pJoueurs->Adresse);
                            if (VerifChaine == 0)
                                printf("\nLa rue encode n'est pas valide !\n");
                        } while (VerifChaine == 0);
                        break;

                case 6 :
                        do{
                            printf("\nEntrez le code postal du Joueur : ");
                            fflush(stdin);
                            LireCode(pJoueurs->CodePostal);
                            VerifChaine = VerifCodePostal(pJoueurs->CodePostal);
                            if (VerifChaine == 2)
                                printf("\nLe code postal encode n'est pas valide !\n");
                        } while (VerifChaine == 2);
                        break;

                case 7 :
                        do{
                            printf("\nEntrez la ville du Joueur : ");
                            fflush(stdin);
                            VerifChaine = LireChaine(pJoueurs->Ville);
                            if (VerifChaine == 0)
                                printf("\nLa ville encode n'est pas valide !\n");
                        } while (VerifChaine == 0);
                        break;
                case 8 :
                        do{
                            printf("\nEntrez le pays du Joueur : ");
                            fflush(stdin);
                            VerifChaine = LireChaine(pJoueurs->Pays);
                            if (VerifChaine == 0)
                                printf("\nLe pays encode n'est pas valide !\n");
                        } while (VerifChaine == 0);
                        break;
                case 9 :
                        do{
                        printf("\nEntrez le telephone (de type 04/XXX.XX.XX) du Joueur : ");
                        fflush(stdin);
                        LireCode(pJoueurs->Telephone);
                        VerifChaine = VerifTel(pJoueurs->Telephone);
                        if (VerifChaine == 2)
                            printf("\nLe telephone encode n'est pas valide !");
                        } while (VerifChaine == 2);
                        break;
                case 10 :
                        do
                        {
                            printf("\nEntrez l'adresse mail du Joueur : ");
                            fflush(stdin);
                            LireMail(pJoueurs->AdMail);
                            lg = strlen(pJoueurs->AdMail);

                            VerifChaine = VerifMail (pJoueurs->AdMail, lg);
                            if (VerifChaine == 2)
                                printf ("\n Votre adresse mail entre n'est pas dans bon format !");
                        } while (VerifChaine == 2);
                        break;
                case 11 :
                        Boucle = 0;
                        break;
            }

            (pIndexJoueurs+PositionAjout)->IdJoueur = pJoueurs->IdJoueur;
            strcpy((pIndexJoueurs+PositionAjout)->Nom, pJoueurs->Nom);
        } while (Boucle == 1);
        system("cls");
        printf("\nLe Joueur <%s %s> a bien ete modifie !\n",(pJoueurs->Prenom), (pJoueurs->Nom));
    }
}

/**************************************************************************************************************************/
/**INPUT : Prend l'adresse du premiere element de la structure IndexJoueurs  et l'iD du joueur recherché.                **/
/**PROCESS : Parcours l'IndexJoueur et compare l'iD à chercher avec les autres iD.                                       **/
/**OUTPUT : renvoit Position = -1 s'il n'est pas trouvé et renvoi la position dans l'index   				             **/
/**************************************************************************************************************************/
short Recherche_Joueurs(struct IndexJoueurs *pIndexJoueurs, long IdJoueurChoisi)
{
    short check=0, i=0, Position=-1;

	for(i=0; i<MAX_JOUEURS && check != 1; i++, pIndexJoueurs++)
		if(pIndexJoueurs->IdJoueur == IdJoueurChoisi)
        {
			check=1;
			Position = i;
        }
    return Position;
}

/***********************************************************************************************************************************************/
/**INPUT : Prend l'adresse du premiere element de l'IndexJoueurs , de la structure Joueurs.													  **/
/**PROCESS : Parcours la structure Joueurs et affiche tous les elements qui n'ont pas un IdJoueur = -1 .                                      **/
/**OUTPUT : /                                                                                                                                 **/
/***********************************************************************************************************************************************/
void Affichage_Joueurs(struct Joueurs *pJoueurs, struct IndexJoueurs *pIndexJoueurs)
{
    int i;

    printf("\nListe des joueurs : \n");
    printf("------------------\n");

    for(i=0;i<MAX_JOUEURS;i++, pIndexJoueurs++)
    {
        if (pIndexJoueurs->IdJoueur != -1)
        {
            printf("\niD du Joueur : <%ld>",(pJoueurs+(pIndexJoueurs->pos))->IdJoueur);
            printf("\nNom : <%s>",(pJoueurs+(pIndexJoueurs->pos))->Nom);
            printf("\nPrenom : <%s>",(pJoueurs+(pIndexJoueurs->pos))->Prenom);
            printf("\nDate de naissance du Joueur : <%d/%d/%d>",(pJoueurs+(pIndexJoueurs->pos))->DateNaissance.jour,(pJoueurs+(pIndexJoueurs->pos))->DateNaissance.mois,(pJoueurs+(pIndexJoueurs->pos))->DateNaissance.annee);
            printf("\nAdresse : <%s>", (pJoueurs+(pIndexJoueurs->pos))->Adresse);
            printf("\nCodePostal : <%s>", (pJoueurs+(pIndexJoueurs->pos))->CodePostal);
            printf("\nVille : <%s>", (pJoueurs+(pIndexJoueurs->pos))->Ville);
            printf("\nPays : <%s>", (pJoueurs+(pIndexJoueurs->pos))->Pays);
            printf("\nTelephone : <%s>", (pJoueurs+(pIndexJoueurs->pos))->Telephone);
            printf("\nAdresse Mail : <%s>", (pJoueurs+(pIndexJoueurs->pos))->AdMail);
            printf("\n\n");
        }
    }
}

/***********************************************************************************************************************************************/
/**INPUT : Prend l'adresse du premiere element de l'IndexJoueurs , de la structure Joueurs.													  **/
/**PROCESS : Demande l'id du joueurs à supprimer et parcours le fichier jusqu'à trouver l'id du joueur puis le supprime                       **/
/**OUTPUT : void                                                                                                                              **/
/***********************************************************************************************************************************************/
void Supprimer_Joueurs(struct IndexJoueurs *pIndexJoueurs,struct Joueurs *pJoueurs)
{
    short IdJoueurChoisi, PositionSupp, pos, ChoixSupp=0;
    do
    {
        do
        {
            printf ("\nQuel joueur voulez-vous supprimer ? (IdJoueur) : ");
            scanf("%hd", &IdJoueurChoisi);
        } while (IdJoueurChoisi < 1 || IdJoueurChoisi > 999);
        PositionSupp = Recherche_Joueurs(pIndexJoueurs, IdJoueurChoisi);
        if (PositionSupp == -1)
            printf ("Cet Id de Joueur n'existe pas !");
        else
        {
            pos = (pIndexJoueurs+PositionSupp)->pos;
            pJoueurs += pos;
            printf ("\nVous avez choisi de supprimer le Joueur <%s %s>, etes-vous sur de vouloir le supprimer ? (Oui : 1 || Non : 0)\n", pJoueurs->Prenom, pJoueurs->Nom);
            scanf ("%hd", &ChoixSupp);

            if (ChoixSupp == 1)
            {
                (pIndexJoueurs+PositionSupp)->IdJoueur = -1;
                strcpy((pIndexJoueurs+PositionSupp)->Nom,"0");
                pJoueurs->IdJoueur = -1;

                system ("cls");
                printf ("Vous avez supprime le Joueur <%s %s>. \n", pJoueurs->Prenom, pJoueurs->Nom);
            }
            else
            {
                ChoixSupp = 1;
                system("cls");
                printf ("\n Vous avez decide de ne pas supprimer ce Joueur !\n");
            }
        }
    } while (ChoixSupp == 0);
}

/***********************************************************************************************************************************************/
/**INPUT : pc : permet de d'ecrire une chaine de caractères à l'aide d'un pointeur															  **/
/**PROCESS : Cette fonction permet de lire une chaine de caractères     													                  **/
/**OUTPUT : Renvoie une variable short qui controle si les caracteres entrés sont correctes                                                   **/
/***********************************************************************************************************************************************/
int LireChaine (char *pc)
{
    char c ;
    int i=0, controle=1 ;

    fflush(stdin) ;
    c=getchar() ;
    while(c != '\n' || i < 2)
    {
        if(((c>='a' && c<='z') || (c>='A' && c<='Z')) || c=='-' || c==' ')
        {
            *pc=c ;
            pc++ ;
            i++ ;
            c=getchar() ;
            if (i > 50)
                controle = 0;
        }
        else
        {
            controle = 0;
            i=2;
            c = '\n';
        }
    }
    *pc='\0' ;

    return controle ;
}

/***********************************************************************************************************************************************/
/**INPUT : pc : permet de d'ecrire une chaine de caractères à l'aide d'un pointeur															  **/
/**PROCESS : Cette fonction permet d'entrer une chaine de caracteres			 											                  **/
/**OUTPUT : void                                                   																			  **/
/***********************************************************************************************************************************************/
void LireMail (char * pc)
{
    char c;
    short i=0;

    fflush(stdin);
    c=getchar();

    while (i<64 && c != '\n')
    {
        *pc=c;
        pc++;
        i++;
        c=getchar();
    }
    *pc='\0';
}

/***********************************************************************************************************************************************/
/**INPUT : pc : permet de d'ecrire une chaine de caractères à l'aide d'un pointeur															  **/
/**PROCESS : Cette fonction permet de rentrer du code 						     											                  **/
/**OUTPUT : void                                                   																			  **/
/***********************************************************************************************************************************************/
void LireCode (char * pc)
{
    char c;
    short i=0;

    fflush(stdin);
    c=getchar();

    while (i<12 && c != '\n')
    {
        *pc=c;
        pc++;
        i++;
        c=getchar();
    }
    *pc='\0';
}

/***********************************************************************************************************************************************/
/**INPUT : Le pointeur sur un champ 																										  **/
/**PROCESS : Modifie les majuscules et les minuscules des prenoms			    											                  **/
/**OUTPUT : void                                                   																			  **/
/***********************************************************************************************************************************************/
void ModifChaine(char *pc)
{
    int i=0;

    fflush (stdin);

    while ((i< 50))
    {
        fflush (stdin);
        if (i==0)
            *pc=toupper(*pc);
        else
        {
            if (*pc == ' ' || *pc == '-')
            {
                pc++;
                *pc = toupper(*pc);
            }
            else
                *pc = tolower(*pc);
        }
        pc++ ;
        i++ ;
    }
}

/********************************************************************************************************************************/
/**INPUT :  Prend en parametre l'adresse du mot que l'utilisateur vient d'encoder                                              **/
/**PROCESS : Verifie chaque caractere du mot est une lettre , que le mot ne commence pas par un  espace et qu'il n est pas vide**/
/**OUTPUT : renvoit 1 si le mot est correct et 0 s'il ne l est pas                                                             **/
/********************************************************************************************************************************/
int VerifTexte(char *mot)
{
    int Resultat=1,i=0,Lettre=0,Erreur=0;
    if(mot[0]=='\0')
        Resultat=2;
    else
    {
	    while(mot[i]!='\0' && Erreur ==0)
	    {
	        if((mot[i]<'a' || mot[i]>'z' )&& mot[i]!='é' && mot[i]!='è' && mot[i]!='à')
	        {
	            if(Lettre>0 && ( mot[i]==' ' || mot[i]=='-'|| mot[i]=='.'))
	            	Resultat=1;
	            else
	            {
	                Resultat=0;
	                Erreur=1;
	            }
	        }
	        else
	        {
	            if((mot[i]>='a' && mot[i]<='z') || mot[i]=='é' || mot[i]=='è' || mot[i]=='à')
	                Lettre++;
	            else
	            {
	                Resultat=0;
	                Erreur=1;
	            }
	        }
	        i++;
	    }
    }
    if(Resultat==0)
        printf("\n Mot/Phrase incorrect(e)\nEncodez un(e) mot/phrase correct(e)\n ");
    if(Resultat==2)
    {
        printf("\nVeuillez re-encoder\n ");
        Resultat=0;
    }
    return Resultat;
}

/****************************************************************************************************************************************************/
/**INPUT :  Prend en parametre l'adresse d' l'Id que l'utilisateur vient d'encoder                                                                 **/
/**PROCESS : Verifie que chaque caractere du mot est un chiffre , qu'il n est pas vide puis retransforme en chiffre et le met à l'adresse du numero**/
/**OUTPUT : renvoit 1 si le nombre est correct et 0 s'il ne l est pas                                                                              **/
/****************************************************************************************************************************************************/
int VerifLong(long *numero)
{
    int Resultat = 1,i = 0,Erreur = 0,j = 0;
    float multi = 0.1;
    char Chiffre[10];
    *numero = 0;
    fflush(stdin);
    gets(Chiffre);
    if(Chiffre[0]=='\0')
        Resultat=2;
    else
    {
        while(Chiffre[i]!='\0' && Erreur==0)
        {
            if((Chiffre[i] < '0' && Chiffre[i] > '9')&& Chiffre[0] =='0')
            {
                Erreur=1;
                Resultat=0;
            }
            multi=multi*10;
            i++;
        }
    }

    if(Resultat!=0)
    {
      while(j<i)
      {
        *numero=*numero+((Chiffre[j]-48)*multi);
        multi=multi/10;
        j++;
      }
    }
    if(Resultat==2)
    {
        printf("\nveuillez encoder une valeur\n ");
        Resultat=0;
    }

    return Resultat;
}

/****************************************************************************************************************************************************/
/**INPUT :  Prend en parametre l'adresse du numero que l'utilisateur vient d'encoder                                                               **/
/**PROCESS : Verifie que chaque caractere du mot est un chiffre , qu'il n est pas vide puis retransforme en chiffre et le met à l'adresse du numero**/
/**OUTPUT : renvoit 1 si le nombre est correct et 0 s'il ne l est pas                                                                              **/
/****************************************************************************************************************************************************/
int VerifInt(int *numero)
{
    int Resultat=1,i=0,erreur=0,j=0;
    float Multi=0.1;
    char Chiffre[10];
    *numero=0;
    fflush(stdin);
    gets(Chiffre);
    if(Chiffre[0]=='\0')
        Resultat=2;
    else
        while(Chiffre[i]!='\0' && erreur==0)
        {
            if(Chiffre[i]>='0' && Chiffre[i]<='9');
            else
            {
                erreur=1;
                Resultat=0;
            }
            Multi=Multi*10;
            i++;
        }

    if(Resultat!=0)
      while(j<i)
      {
        *numero=*numero+((Chiffre[j]-48)*Multi);
        Multi=Multi/10;
        j++;
      }
    if(Resultat==2)
    {
        system("cls");
        printf("\nveuillez encoder une valeur\n ");
        Resultat=0;
    }
    return Resultat;
}

/**************************************************************************************************************/
/**INPUT : Prend en parametre l'adresse du jour , mois et annee que l'utilisateur veut encoder               **/
/**PROCESS : Compare si le format de la date est bon , s'il est bon ,verifie sa validité ,si elle est bonne ,**/
/**          transforme la chaine en nombre et copie le nombre dans la valeur de l'adresse jour ,mois,annee. **/
/**OUTPUT : renvoit Resultat =0 si la date est mauvaise et 1 si elle est bonne.                              **/
/**************************************************************************************************************/
int VerifDate(short *jour, short *mois , short *annee)
{
    int Resultat = 1;
    char DateEncode[11];
    *jour = 0; *mois = 0; *annee = 0;

    fflush(stdin);
    LireCode(DateEncode);
    if(DateEncode[0] == '\0')
        Resultat = 2;
    else
    {
        if((DateEncode[0]<'0' || DateEncode[0]>'9')||
           (DateEncode[1]<'0' || DateEncode[1]>'9')||
           (DateEncode[2]!='/')||
           (DateEncode[3]<'0' || DateEncode[3]>'9')||
           (DateEncode[4]<'0' || DateEncode[4]>'9')||
           (DateEncode[5]!='/')||
           (DateEncode[6]<'0' || DateEncode[6]>'2')||
           (DateEncode[7]<'0' || DateEncode[7]>'9')||
           (DateEncode[8]<'0' || DateEncode[8]>'9')||
           (DateEncode[9]<'0' || DateEncode[9]>'9'))
        {
            Resultat = 3;
        }

	    if(Resultat!=2 && Resultat!=3)
	    {
	        *jour=(DateEncode[0]-48)*10+(DateEncode[1]-48)*1;
	        *mois=(DateEncode[3]-48)*10+(DateEncode[4]-48)*1;
	        *annee=(DateEncode[6]-48)*1000+(DateEncode[7]-48)*100+(DateEncode[8]-48)*10+(DateEncode[9]-48)*1;
		    switch(*mois)
		    {
		        case 1:
		        case 3:
		        case 5:
		        case 7:
		        case 8:
		        case 10:
		        case 12:
		            if(*jour>0 && *jour<32)
		                Resultat=1;
		            else
		                Resultat=0;
		            break;
		        case 4:
		        case 6:
		        case 9:
		        case 11:
		            if(*jour>0 && *jour<31)
		                Resultat=1;
		            else
		                Resultat=0;
		            break;
		        case 2:
		            if((*annee%4==0&&*annee%100!=0)||*annee%400==0)
		            {
		                if(*jour>0 &&*jour<30)
		                    Resultat=1;
		                else
		                    Resultat=0;
		            }
		            else
		            {
                        if(*jour>0 && *jour<29)
		                    Resultat=1;
                        else
		                    Resultat=0;
		            }
		            break;
		        default:
		            Resultat=0;
		            break;
		    }
    	}
    }
    if(Resultat==0)
		printf("\nla date n'est pas bonne\n");
    if(Resultat==1)
       if(*annee<1900 || *annee>2100)
            Resultat=0;
    if(Resultat==3)
    {
    	printf("\nle format date n'est pas bon\n");
    	Resultat=0;
    }
    if(Resultat==2)
    {
        printf("\nveuillez encoder une valeur\n ");
        Resultat=0;
    }
    return (Resultat);
}

/**************************************************************************************************************/
/**INPUT : Prend en parametre un pointeur de char + la longueur d'une chaine 				                 **/
/**PROCESS : Verifie la validité d'une adresse email 														 **/
/**OUTPUT : return 1 ou 2													                                 **/
/**************************************************************************************************************/
int VerifMail (char *pc, short Longueur)
{
    short i=0, j=0;

	if (i==0 && (*pc>='a' && *pc<='z') || (*pc>='A' && *pc<='Z'))
	{
	    pc++;
	    i++;
	}
	else
	    return 2;

	while (*pc != '@' && ((*pc>='0' && *pc<='9') || (*pc>='a' && *pc<='z') || (*pc>='A' && *pc<='Z') || *pc =='-' || *pc == '.' ))
	{
	    if (i>Longueur)
	        return 2;
	    pc++;
	    i++;
	}

	if (*pc == '@')
	{
	    pc++;
	    i++;
	}
	else
	    return 2;

	while (*pc != '.' && ((*pc>=48 && *pc<=57) || (*pc>=97 && *pc<=122) || *pc =='-'))
	{
	    if (i>Longueur)
	        return 2;
	    pc++;
	    i++;
	}

	if (*pc == '.')
	{
	    pc++;
	    i++;
	}
	else
	    return 2;

	while ((j>2 || j<4) && *pc != 0)
	{
	    if (*pc>=97 && *pc<=122)
	    {
	        pc++;
	        j++;
	        i++;
	    }
	    else
	        return 2;
	}
	if (*pc == '\0')
	    return 1;
	else
	    return 2;
}

/**************************************************************************************************************/
/**INPUT : Prend en parametre un pointeur de char							 				                 **/
/**PROCESS : Verifie la validité d'un numéro de téléphone (04/XXX.XX.XXX)									 **/
/**OUTPUT : return 1 ou 2													                                 **/
/**************************************************************************************************************/
int VerifTel (char *pc)
{

    if (*pc == '0' && *(pc+1) == '4') /* 4 premiers chiffres */
        pc+=2;
    else
        return 2;
    if (*pc == '/') /* '/' */
        pc++;
    else
        return 2;
	if ((*pc >= '0' && *pc <= '9') &&  (*(pc+1) >= '0' && *(pc+1) <= '9') &&  (*(pc+2) >= '0' && *(pc+2) <= '9')) /* 3 chiffres suivant la '/' */
		pc+=3;
	else
		return 2;
    if (*pc == '.')
        pc++;
    else
        return 2;
	if ((*pc >= '0' && *pc <= '9') &&  (*(pc+1) >= '0' && *(pc+1) <= '9')) /* 2 chiffres suivant le '.' */
		pc+=2;
	else
		return 2;
    if (*pc == '.')
        pc++;
    else
        return 2;
    if ((*pc >= '0' && *pc <= '9') &&  (*(pc+1) >= '0' && *(pc+1) <= '9')) /* 2 chiffres suivant le '.' */
		pc+=2;
	else
		return 2;
    if (*pc == '\0')
		return 1;
	else
		return 2;
}

/**************************************************************************************************************/
/**INPUT : Prend en parametre un pointeur de char							 				                 **/
/**PROCESS : Verifie la validité d'un code postal (XXXX)													 **/
/**OUTPUT : return 1 ou 2													                                 **/
/**************************************************************************************************************/
int VerifCodePostal (char *pc)
{
    if ((*pc >= '0' && *pc <= '9') && (*(pc+1) >= '0' && *(pc+1) <= '9') && (*(pc+2) >= '0' && *(pc+2) <= '9') && (*(pc+3) >= '0' && *(pc+3) <= '9')) /* 4 premiers chiffres */
        pc+=4;
    else
        return 2;

    if (*pc == '\0')
		return 1;
	else
		return 2;
}

/*****************************************************************************************************************************************************************************/
/**INPUT :  Prend en parametre l' iD que l'utilisateur à encodé , l'adresse du premiere element de la structure index Joueurs 						 						**/
/**PROCESS : Parcours l'index joueurs et compare l'id' encodé avec les id déja encodés                                              					                    **/
/**OUTPUT : renvoit 1 s'il n'a pas trouvé le meme id et 0 s'il l'a trouvé                                                               		                            **/
/*****************************************************************************************************************************************************************************/
int Verification_iD_Joueur(long iDJoueur, struct IndexJoueurs *pIndexJoueurs)
{
	short i, Controle;
	for (i=0,Controle=1; Controle == 1 && i < MAX_JOUEURS; i++, pIndexJoueurs++)
		if(pIndexJoueurs->IdJoueur==iDJoueur)
	    	Controle=0;

    return Controle;
}
