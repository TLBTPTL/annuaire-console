#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"


//char annu[]= "annuaire_client.csv";
const char* annuaire = "annuaire_client.csv";


char nom_p[25]= "";
char prenom_p[25]="";
char code_postal_p[10]="";
char ville_p[20]= "";
char telephone_p[20]= "";
char mel_p[30]= "";
char profession_p[30]= "";

//modification mel
char nv_mel_p[30] = "";

// modification autre que mel
char nom_champ[30];
char nv_valeur[30];

//filtrer un champ
char val_chaine[30];

//filtrer en combinant 2 champs
char nom_champ1[25];
char val_chaine1[25];
char  nom_champ2[25];
char val_chaine2[25];




void display_menu()
{
          printf("\n\n\n\n\n");
          printf("            ________________________________________________________________________  \n");
          printf("           |                                                                        | \n");
          printf("           |                                                          Projet C      | \n");
          printf("           |                                                                        | \n");
          printf("           |                                                                        | \n");
          printf("           |          Choisir une option :                                          | \n");
          printf("           |                                                                        | \n");
          printf("           |         1- Ajouter un client                                           | \n");
          printf("           |         2- Modifier un email                                           | \n");
          printf("           |         3- Modifier un autre champ que l'email                         | \n");
          printf("           |         4- Supprimer une ligne client                                  | \n");
          printf("           |         5- Tri des clients par nom                                     | \n");
          printf("           |         6- Afficher les clients avec donnees manquantes                | \n");
          printf("           |         7- Filtrer par champ                                           | \n");
          printf("           |         8- Filtrer en combinant 2 champs                               | \n");
          printf("           |         9- Afficher l'annuaire                                         | \n");
          printf("           |         0- Exit                                                        | \n");
          printf("           |                                                                        | \n");
          printf("           |                                                                        | \n");
          printf("           |________________________________________________________________________| \n");
          printf("                                                                                      \n");
}
void menu()
{

   int c;

    display_menu();



   //=========================================
    FILE *file;
    char  new_file[] = "annuaire_client.csv";


    printf("\nNom de l'annuaire ?:");
    char start_file[50+1];
    scanf( "%[^\n]", start_file);
    fgetc( stdin );

    //printf("fichier saisi : %s\n",start_file);
    //printf("fichier new : %s\n",new_file);


    file = fopen(start_file, "r");
    if (file)
    {
        fclose(file);
        //printf("fichier exists ok : %s\n",start_file);

    }
    else
    {
        printf("Erreur: le fichier %s est introuvable !\n",start_file);
        fprintf(stderr, "Erreur no (%d): %s\n", errno, strerror(errno));
        exit(0);
    }

    if ( strncasecmp( start_file,  new_file, strlen(new_file)) !=0)
    {
            int value = rename(start_file,new_file);
            printf("Value ok: %d\n",value);
            if (value !=0)
            {
                printf("Erreur: fichier %s impossible a renommer !\n",start_file);
                fprintf(stderr, "System error (%d): %s\n", errno, strerror(errno));
                exit(0);
            }
             annuaire =new_file;
             printf("Le fichier %s a ete renomme en fichier %s\n",start_file,annuaire);
    }


    printf("Fichier retenu : %s\n",annuaire);

   //=========================================
   while(1)
   {

        do
        {

            printf("\nChoix [0-9] >> ");
            if (scanf("%d", &c) !=1)
            {
               vider_buffer();

                c = 10;
            }

            switch(c)
            {
                    case 1:
                        printf("\n");
                        saisie_client();
                        printf("\n");


                        break;

                    case 2:
                        printf("\n");
                        saisie_mel_a_modifier();
                        printf("\n");


                        break;

                    case 3:
                        printf("\n");
                        saisie_champ_a_modifier();
                        printf("\n");
                        modifier_autres_que_mel_client(annuaire,mel_p, nom_champ,nv_valeur);

                        break;

                    case 4:
                        printf("\n");
                        saisie_ligne_mel_a_supprimer();
                        printf("\n");


                        break;

                    case 5:
                        printf("\n");

                        printf("\n");
                        break;

                    case 6:
                        printf("\n");
                        filter_clients_donnees_manquantes(annuaire);
                        printf("\n");
                        break;

                    case 7:

                        vider_buffer();
                        printf("\n");
                        printf("\nFiltrer par champ: ");
                        printf("\n- Nom\n- Prenom\n- Code postal\n- Ville\n- Telephone\n- eMail\n- Profession\n");

                        printf("\nSaisir le nom du champ:");
                        scanf("%[^\n]", nom_champ );
                        fgetc(stdin);

                         do {
                            if (nom_champ[0]=='\0')
                            {
                                printf("\nLe nom du champ doit etre valide et non vide!:");
                                scanf( "%[^\n]", nom_champ);
                                fgetc( stdin );
                            }

                         }while ((nom_champ[0]=='\0') &&(nom_champ_in(nom_champ) !=1));


                        printf("\nSaisir le critere pour filtrer: ");
                        scanf("%[^\n]", val_chaine );
                        fgetc(stdin);

                        do {
                            if (val_chaine[0]=='\0')
                            {
                                printf("\nLa valeur du champ ne peut etre vide!:");
                                scanf( "%[^\n]", val_chaine);
                                fgetc( stdin );
                            }

                        }while (val_chaine[0]=='\0');

                        printf("\n");
                        filtrer_un_champ(annuaire,nom_champ, val_chaine);
                        printf("\n");
                        break;

                    case 8:

                       vider_buffer();
                       printf("\n");

                       printf("\nFilter en combinant deux champs:\n");
                       printf("\nChoix parmi : nom/prenom/code_postal/ville/telephone/mel/profession\n");
                       printf("\nSaisir le 1er nom de champ: ");
                       scanf("%[^\n]s",nom_champ1);
                       //supprimer le caractère '\n' restant dans le flux
                       fgetc( stdin );

                        do {
                            if (nom_champ1[0]=='\0')
                            {
                                printf("\nLe nom du champ 1 doit etre valide et non vide!:");
                                scanf( "%[^\n]", nom_champ1);
                                fgetc( stdin );
                            }

                         }while ((nom_champ1[0]=='\0') &&(nom_champ_in(nom_champ1) !=1));



                       printf("\nSaisir la valeur du champ 1: ");
                       scanf("%[^\n]s",val_chaine1);
                       fgetc( stdin );

                       do {
                            if (val_chaine1[0]=='\0')
                            {
                                printf("\nLa valeur du champ 1 ne peut etre vide!:");
                                scanf( "%[^\n]", val_chaine1);
                                fgetc( stdin );
                            }

                         }while (val_chaine1[0]=='\0');


                       printf("\nSaisir le second nom de champ: ");
                       scanf("%[^\n]s",nom_champ2);
                       fgetc( stdin );

                       do {
                            if (nom_champ2[0]=='\0')
                            {
                                printf("\nLe nom du champ 2 doit etre valide et non vide!:");
                                scanf( "%[^\n]", nom_champ2);
                                fgetc( stdin );
                            }

                         }while ( (nom_champ2[0]=='\0') &&(nom_champ_in(nom_champ2) !=1) &&( strncasecmp(nom_champ2, nom_champ1, strlen(nom_champ1)) ==0) );


                       printf("\nSaisir la valeur du champ 2: ");
                       scanf("%[^\n]s",val_chaine2);
                       fgetc( stdin );

                       do {
                            if (val_chaine2[0]=='\0')
                            {
                                printf("\nLa valeur du champ 2 ne peut etre vide!:");
                                scanf( "%[^\n]", val_chaine2);
                                fgetc( stdin );
                            }

                        }while (val_chaine2[0]=='\0');

                       printf("\n");

                       printf("\n");
                       break;

                    case 9:
                        printf("\n");
                        display_enreg(annuaire);
                        break;

                    case 0:
                        printf("\n");
                        printf("Fin du programme !\n\n");
                        exit(0);


                    default:
                        printf("\n");
                        printf("Choisir une option valide !\n");

                        break;
            }

        } while (c > 9 || c < 0);

   }
}
void saisie_ligne_mel_a_supprimer()
{
    vider_buffer();
    printf("\nSaisir le mel pour supprimer la ligne correspondante:");
    scanf("%[^\n]",mel_p);
    fgetc(stdin);
    do {
        if (mel_p[0]=='\0')
        {
            printf("\nLe mel ne peut être vide!:");
            scanf( "%[^\n]", mel_p );
            fgetc( stdin );
        }

    }while ( (mel_p[0]=='\0')&& (is_mail_exist(annuaire,mel_p) !=1) );

}
void saisie_champ_a_modifier()
{
    vider_buffer();
    printf("\nAdresse mail pour modifier un champ:");
    scanf("%[^\n]",mel_p);
    fgetc(stdin);
    do {
        if (mel_p[0]=='\0')
        {
            printf("\nLe mel doit exister dans l'annuaire et ne peut être vide!:");
            scanf( "%[^\n]", mel_p );
            fgetc( stdin );
        }

    }while ( (mel_p[0]=='\0')&& (is_mail_exist(annuaire,mel_p) !=1) );



    printf("\nChamps: nom/prenom/code postal/ville/telephone/profession");
    printf("\nSaisir le champ a modifier:");
    scanf("%[^\n]", nom_champ);
    fgetc(stdin);

    do {
        if (nom_champ[0]=='\0')
        {
            printf("\nLe nom du champ doit etre valide et non vide!:");
            scanf( "%[^\n]", nom_champ);
            fgetc( stdin );
        }

    }while ((nom_champ[0]=='\0')&&(nom_champ_in(nom_champ)) !=1);


    printf("\nSaisir la valeur du champ:");
    scanf("%[^\n]", nv_valeur);
    fgetc(stdin);



}
void saisie_mel_a_modifier()
{
    vider_buffer();
    printf("\nSaisir l'adresse mail a modifier: ");
    scanf( "%[^\n]", mel_p );
    fgetc( stdin );

    do {
        if (mel_p[0]=='\0')
        {
            printf("\nLe mel doit exister dans l'annuaire et ne peut être vide!:");
            scanf( "%[^\n]", mel_p );
            fgetc( stdin );
        }

    }while ( (mel_p[0]=='\0')&& (is_mail_exist(annuaire,mel_p) !=1) );


    printf("\nSaisir la nouvelle adresse mail:");
    scanf( "%[^\n]", nv_mel_p );
    fgetc( stdin );
    do {
        if (nv_mel_p[0]=='\0')
        {
            printf("\nLe nouveau mel ne doit pas exister dans l'annuaire et ne peut être vide!:");
            scanf( "%[^\n]", nv_mel_p );
            fgetc( stdin );
        }

    }while ( (nv_mel_p[0]=='\0')&&(is_mail_exist(annuaire,nv_mel_p)  ==1) );

}

void saisie_client()
{
        int i, cpt;

        printf("\nCombien de clients a ajouter ?: ");
        scanf("%d", &cpt);
        fgetc( stdin );

        for(i = 1; i <= cpt; i++){
             printf("\nSaisir le nom du client:");
             scanf( "%[^\n]", nom_p );
             fgetc( stdin );   //supprimer  '\n'

             printf("\nSaisir le prenom du client:");
             scanf( "%[^\n]", prenom_p );
             fgetc( stdin );

             printf("\nSaisir le code postal du client:");
             scanf( "%[^\n]", code_postal_p );
             fgetc( stdin );

             printf("\nSaisir la ville du client:");
             scanf( "%[^\n]", ville_p );
             fgetc( stdin );

             printf("\nSaisir le N de telephone du client:");
             scanf( "%[^\n]", telephone_p );
             fgetc( stdin );

             printf("\nSaisir un email du client:");
             scanf( "%[^\n]", mel_p );
             fgetc( stdin );
             do {
                if (mel_p[0]=='\0')
                {
                    printf("\nLe mel ne peut etre vide! Resaisir de nouveau : ");
                    scanf( "%[^\n]", mel_p );
                    fgetc( stdin );
                }

             }while (mel_p[0]=='\0');

             printf("\nSaisir la profession du client:");
             scanf( "%[^\n]", profession_p );
             fgetc( stdin );

        }
}
