#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#define MAX_SIZE 1024
#define cols 7



const char* res_modifier_autre_champs="resultat_modifier_autre_champs_que_mail.txt";
const char* res_champs_vide="resultat_champs_vide.txt";
const char* res_filtrer_un_champ="resultat_filtrer_un_champ.txt";

typedef struct {
    char nom_p[25];
    char prenom_p[25];
    char ville_p[20];
    char code_postal_p[10];
    char telephone_p[20];
    char mel_p[30];
    char profession_p[30];

}client;

void ecrire_csv_to_txt(const char* file_destination, client* enreg) {
  FILE* fp = fopen(file_destination, "w");
  int i=0;
  if (!fp) {
    printf("Impossible d'ouvrir le fichier : %s\n", file_destination);
    return;
  }
  for (i;i<total_lignes(file_destination);i++){
     fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", enreg[i].nom_p, enreg[i].prenom_p, enreg[i].ville_p, enreg[i].code_postal_p, enreg[i].telephone_p, enreg[i].mel_p, enreg[i].profession_p);
  }



  fclose(fp);
}


client* read_csv_from_annuaire(const char * file_source)
{

        FILE * fp;
        char row[1024];
        int k = 0;
        client * enreg; //pointeur vers une struct client

        int nb_lignes = total_lignes(file_source);

        enreg = (client*)malloc( nb_lignes * sizeof(client));

        if (!enreg)
        {
            printf("La reservation de memoire a echoué !\n");
            exit(0);
        }

        fp = fopen(file_source,"r");
        if (!fp)
        {
            printf("Impossible d'ouvrir le fichier :%s\n",file_source);
            exit(0);
        }




        char * d = ",";//
        char* tab[cols];
        int cpt= 0;
        char * position;
        //Lit le fichier ligne par ligne
        while (fgets(row,1024,fp))
        {

            // Eliminer le retour à la ligne '\n'
            position = strchr(row, '\n');
            if (position != NULL)
            {
                *position = '\0';
            }


            char * temp =row ;

            for (k=0;k<cols;k++)
            {
                tab[k] = temp; // on conserve la chaine
               //Renvoie la longueur de la plus grande sous-chaîne
               //ne contenant aucun des caractères présents dans la liste des charactères en rejet.
                int pos = strcspn( temp, d );

                // on avance la position du pointeur de la quantité pos
                temp+=pos;

                // on coupe la chaine(on oblient le premier item de la ligne dans la tableau)
                // et on avance le pointeur pour conserver le reste de la ligne
                if (*temp!= '\0')
                {
                    *temp='\0';
                    temp++;// pour ne pas perdre le reste de la ligne

                }
            }
            strcpy(enreg[cpt].nom_p,tab[0]);
            strcpy(enreg[cpt].prenom_p,tab[1]);
            strcpy(enreg[cpt].ville_p,tab[2]);
            strcpy(enreg[cpt].code_postal_p,tab[3]);
            strcpy(enreg[cpt].telephone_p,tab[4]);
            strcpy(enreg[cpt].mel_p,tab[5]);
            strcpy(enreg[cpt].profession_p,tab[6]);
            cpt++;

        }

        if (fp) fclose(fp);
        return enreg;


}

int filter_clients_donnees_manquantes(const char *annuaire){

    client *enreg=read_csv_from_annuaire(annuaire);
    int n=total_lignes(annuaire);
    FILE* fp = fopen(res_champs_vide, "w");

    if (!fp) {
        printf("Impossible d'ouvrir le fichier resultat_filtrer_champs_vide\n");
        exit(0);
    }

    for(int i=0;i<n;i++){

        if(strlen(enreg[i].nom_p)==0 || strlen(enreg[i].prenom_p)==0 || strlen(enreg[i].ville_p)==0 || strlen(enreg[i].code_postal_p)==0 ||
           strlen(enreg[i].telephone_p)==0 || strlen(enreg[i].profession_p)==0  )
           {
                fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", enreg[i].nom_p, enreg[i].prenom_p, enreg[i].ville_p, enreg[i].code_postal_p, enreg[i].telephone_p, enreg[i].mel_p, enreg[i].profession_p);
           }

    }
    fclose(fp);

    return 1;
}

int  filtrer_un_champ(const char *annuaire,const char* nom_champ,const char* val_chaine){


        int N=total_lignes(annuaire);
        FILE* filtre=fopen(res_filtrer_un_champ,"w");
        if (!filtre)
        {
            printf("Impossible d'ouvrir le fichier :%s\n",res_filtrer_un_champ);
            exit(0);
        }
        int k;
        if (strlen(val_chaine)==0){
            printf("Val_chaine est vide");
            exit(0);
        }
        client*  enreg;
        enreg= read_csv_from_annuaire(annuaire);




            if (startsWith("Nom", nom_champ ))
            {

                    for (k=0; k<N; k++)
                    {
                        if (startsWith(enreg[k].nom_p, val_chaine ))
                        {
                            printf("%s %s %s %s %s %s %s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);
                            fprintf(filtre,"%s,%s,%s,%s,%s,%s,%s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);

                        }
                    }

            }
            else if (startsWith("Prenom", nom_champ ))
            {

                for (k=0; k<N; k++)
                     {
                        if (startsWith(enreg[k].prenom_p, val_chaine ))
                        {
                            printf("%s %s %s %s %s %s %s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);
                            fprintf(filtre,"%s,%s,%s,%s,%s,%s,%s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);

                        }
                     }
            }
            else if (startsWith("Ville", nom_champ ))
            {
                for (k=0; k<N; k++)
                {
                        if (startsWith(enreg[k].ville_p, val_chaine ))
                        {
                            printf("%s %s %s %s %s %s %s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);
                            fprintf(filtre,"%s,%s,%s,%s,%s,%s,%s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);

                        }
                }

            }


            else if (startsWith("code_postal", nom_champ ))
            {
                for (k=0; k<N; k++)
                {
                     if (startsWith(enreg[k].code_postal_p, val_chaine ))
                        {
                            printf("%s %s %s %s %s %s %s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);
                            fprintf(filtre,"%s,%s,%s,%s,%s,%s,%s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);

                        }

                }


            }

            else if (startsWith("Telephone", nom_champ ))
            {

                for (k=0; k<N; k++)
                {
                        if (startsWith(enreg[k].telephone_p, val_chaine ))
                        {
                            printf("%s %s %s %s %s %s %s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);
                            fprintf(filtre,"%s,%s,%s,%s,%s,%s,%s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);

                        }
                }
            }

            else if (startsWith("Mel", nom_champ ))
            {

                for (k=0; k<N; k++)
                {
                        if (startsWith(enreg[k].mel_p, val_chaine ))
                        {
                            printf("%s %s %s %s %s %s %s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);
                            fprintf(filtre,"%s,%s,%s,%s,%s,%s,%s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);

                        }
                }
            }
            else if (startsWith("Profession", nom_champ ))
            {

                for (k=0; k<N; k++)
                {
                        if (startsWith(enreg[k].profession_p, val_chaine ))
                        {
                            printf("%s %s %s %s %s %s %s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);
                            fprintf(filtre,"%s,%s,%s,%s,%s,%s,%s\n",enreg[k].nom_p,enreg[k].prenom_p,enreg[k].code_postal_p,enreg[k].ville_p,enreg[k].telephone_p,enreg[k].mel_p,enreg[k].profession_p);

                        }
                }
            }

            else
            {
                printf("%s\n","Choix invalide !");
            }


        free(enreg);
        if (filtre) fclose(filtre);
        return 1;
}











void ajouter_client(const char *annuaire)
{

  client *enreg=read_csv_from_annuaire(annuaire);
  printf("Saisir le mail \n");
  char mail[50];
  gets(mail);
  int choix;
  char ligne[420];
  int i=0;
  char nv_champs[30];
  if (is_mail_exist(annuaire,mail)!=0){
    printf("Le mail existe deja");
    exit(0);
  }
  while (startsWith(enreg[i].mel_p,mail)!=0){
    i++;

  }
}

int modifier_autres_que_mel_client(const char *annuaire,const char* mel_p,const char* nom_champ,const char* nv_valeur) {

  client *enreg=read_csv_from_annuaire(annuaire);
  int i=0;
  if (strlen(mel_p)==0){
    printf("Mel_p est vide \n");
  }

  if (is_mail_exist(annuaire,mel_p)==0){
    printf("Le mail n'existe pas");
    exit(0);
  }

  while (strcmp(enreg[i].mel_p,mel_p) != 0) {
    i++;
    }
  if (strcmp(enreg[i].mel_p,mel_p)==0)
            {

                if (startsWith("nom",nom_champ))
                {
                    strcpy(enreg[i].nom_p,nv_valeur);
                }
                else if (startsWith("prenom",nom_champ))
                {
                    strcpy(enreg[i].prenom_p,nv_valeur);
                }
                else if (startsWith("ville",nom_champ))
                {
                    strcpy(enreg[i].ville_p,nv_valeur);
                }
                else if (startsWith("code postal",nom_champ))
                {
                    strcpy(enreg[i].code_postal_p , nv_valeur);
                }
                else if (startsWith("telephone",nom_champ))
                {
                    strcpy(enreg[i].telephone_p,nv_valeur);
                }
                 else if (startsWith("profession",nom_champ))
                {
                    strcpy(enreg[i].profession_p,nv_valeur);
                }

            }


    ecrire_csv_to_txt(res_modifier_autre_champs,enreg);
    return 1;

}

int startsWith( const char * chaine, const char * sub ) {
    return strncasecmp( chaine, sub, strlen(sub )) == 0;
}

void vider_buffer()
{
    int c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}




int search_nom_champ_by_index (const char* item)
{
    int i;

    char * arr [7] = {"nom","prenom","ville","code_postal","telephone","mel","profession"};

    for(  i = 0; i < sizeof(arr)/sizeof(arr[0]); i++ )
    {
        if ( strncasecmp(arr[i], item, strlen(item)) ==0)
        //if(strcmp(strlwr(arr[i]), strlwr(item)) == 0)
        {
            return i;
        }
    }

    return  -1;
}

int total_lignes(const char *nom_annuaire)
{
  char li[MAX_SIZE];

  FILE *fp = fopen(nom_annuaire,"r");
  if (!fp)
  {
        printf("Impossible d'ouvrir le fichier :%s\n",nom_annuaire);
        exit(0);
  }

  int cpt=0;

  if (!fp)
  {
    return 0;
  }

   while(fgets(li, sizeof(li), fp) != NULL)
   {
     cpt++;
   }

  if(fp) fclose(fp);
  return cpt;
}

int is_mail_exist ( const char* nom_annuaire,const char* mel)
{
     int flag =0;
     int k;
     client*  enreg;
     const char * fname =nom_annuaire;

     int nb_lignes = total_lignes(fname);
     if (nb_lignes ==0)
     {
        printf("le fichier %s est vide !\n",fname);
        exit(0);
     }


     enreg= read_csv_from_annuaire(fname);
     if (!enreg)
     {
        printf("%s\n","La reservation de memoire a echouee !");
        return 0;

     }

     for (k=0; k<nb_lignes; k++)
     {
        if (strncasecmp(enreg[k].mel_p,mel,strlen(mel)) ==0)
        {
            flag = 1;
            break;
        }
     }
     if (flag == 1)
     {
        free(enreg);
        return 1;
     }

     free(enreg);
     return 0 ;
}


int display_enreg(const char * nom_annuaire)
{
    int i;
    client*  enreg;
    enreg= read_csv_from_annuaire(nom_annuaire);
    int nb_lignes = total_lignes(nom_annuaire);
    if (nb_lignes ==0)
    {
        printf("le fichier %s est vide !\n",nom_annuaire);
        return 0;
    }

    printf("\n......................................Liste des clients:.....................................................\n\n");
    for(i=0; i<nb_lignes; i++)
    {

        printf ("%s,%s,%s,%s,%s,%s,%s\n", enreg[i].nom_p,enreg[i].prenom_p,enreg[i].code_postal_p,enreg[i].ville_p,enreg[i].telephone_p,enreg[i].mel_p,enreg[i].profession_p);

    }

    free(enreg);
    return 1;
}

int nom_champ_in (const char* item)
{
    int i;
    int flag = 0;

    char * arr [6] = {"nom","prenom","code_postal","ville","telephone","profession"};

    for(  i = 0; i < sizeof(arr)/sizeof(arr[0]); i++ )
    {
        if ( strncasecmp(arr[i], item, strlen(item)) ==0)

        {
            flag = 1;
            break;
        }
    }

    return flag;

}
