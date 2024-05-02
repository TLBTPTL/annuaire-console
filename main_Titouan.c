#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024
#define cols 7



const char* annuaire = "annuaire_client.csv.csv";
const char* res_modifier_autre_champs="resultat_modifier_autre_champs_que_mail.txt";
const char* res_champs_vide="resultat_champs_vide.txt";
const char* res_ajouter_personne="res_ajouter_personne.txt";
const char* res_modifier_mel="res_modifier_mel.txt";
const char* res_trier_nom="res_trier_nom.txt";


typedef struct {
    char nom_p[25];
    char prenom_p[25];
    char ville_p[20];
    char code_postal_p[10];
    char telephone_p[20];
    char mel_p[30];
    char profession_p[30];

}client;




void ecrire_csv_to_txt(const char* file_destination, client* enreg,int ligne) {
  FILE* fp = fopen(file_destination, "r+");
  int i=ligne;
  if (!fp) {
    printf("Impossible d'ouvrir le fichier : %s\n", file_destination);
    return;
  }
  fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", enreg[i].nom_p, enreg[i].prenom_p, enreg[i].ville_p, enreg[i].code_postal_p, enreg[i].telephone_p, enreg[i].mel_p, enreg[i].profession_p);


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

void ajouter_client(const char *annuaire, char nom_p[MAX_SIZE], char prenom_p[MAX_SIZE], char ville_p[MAX_SIZE], char code_postal_p[MAX_SIZE], char telephone_p[MAX_SIZE], char mel_p[MAX_SIZE], char profession_p[MAX_SIZE])
{
    FILE *annu;
    FILE *cible;

    char c;
    const char* file_name="res_ajouter_client.txt";


        //Ouverture du fichier nom_annuaire en lecture
    annu=fopen(annuaire,"r");
    if (!annu)
    {
        printf("\n Ouverture du fichier %s impossible !" ,annuaire);
        exit(0);
    }
        //Ouverture du fichier ajout_client en ajout
    cible=fopen(file_name,"a+");
    if (!cible)
    {
        printf("\n Ouverture du fichier  %s impossible !" ,file_name);
        exit(0);
    }
        // lecture et copie
    while((c = getc(annu)) != EOF)
        putc(c, cible);


    fprintf(cible,"%s,%s,%s,%s,%s,%s,%s\n",nom_p,prenom_p,code_postal_p,ville_p,telephone_p,mel_p,profession_p);
    printf("%s,%s,%s,%s,%s,%s,%s\n",nom_p,prenom_p,code_postal_p,ville_p,telephone_p,mel_p,profession_p);


    if (cible) fclose(cible);
    if (annu) fclose(annu);
    printf("\n............. Fichier de sortie: %s ..............\n ", file_name);
}


void modifier_mel(const char *annuaire, const char *mel_p, const char *nv_mel_p) {//il faut encore respecter les conditions

    client *enreg=read_csv_from_annuaire(annuaire);
    char ligne[420];
    int i=0;

    FILE* fp = fopen(res_champs_vide, "w");
    if (is_mail_exist(annuaire,mel_p)==0){
        printf("Le mail n'existe pas");
        exit(0);
    }
    while (startsWith(enreg[i].mel_p,mel_p)!=0){
    i++;

    }
    strcpy(enreg[i].mel_p,nv_mel_p);
    ecrire_csv_to_txt(res_modifier_mel,enreg,i);
    fclose(fp);
}


void filtrer_par_champs_vide(const char *annuaire){
    client *enreg=read_csv_from_annuaire(annuaire);
    int n=total_lignes(annuaire);
    FILE* fp = fopen(res_champs_vide, "a");
    for(int i=0;i<n;i++){
        if(strlen(enreg[i].nom_p)==0 || strlen(enreg[i].prenom_p)==0 || strlen(enreg[i].ville_p)==0 || strlen(enreg[i].code_postal_p)==0 ||
           strlen(enreg[i].telephone_p)==0 || strlen(enreg[i].profession_p)==0  )
           {
                fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", enreg[i].nom_p, enreg[i].prenom_p, enreg[i].ville_p, enreg[i].code_postal_p, enreg[i].telephone_p, enreg[i].mel_p, enreg[i].profession_p);
           }
    }
    fclose(fp);
}


void modifier_autre_champ(const char *annuaire) {//il faut encore respecter les coditions

  client *enreg=read_csv_from_annuaire(annuaire);
  printf("Saisir le mail \n");
  char mail[50];
  gets(mail);
  int choix;
  char ligne[420];
  int i=0;
  char nv_champs[30];
  if (is_mail_exist(annuaire,mail)==0){
    printf("Le mail n'existe pas");
    exit(0);
  }
  while (startsWith(enreg[i].mel_p,mail)!=0){
    i++;

  }
  printf("Quel champs voulez vous modifier \n");
  printf("1-Nom \n 2-Prenom \n 3-Ville \n 4-Code_postal \n 5-Telephone \n 6-Profession \n");
  scanf("%d",&choix);
  switch (choix) {
    case 1:
        printf("Vous avez sélectionné le champ 'Nom'\n");
        printf("Saisir le nouveau Nom \n");

        scanf("%s",nv_champs);
        fflush(stdin);

        strcpy(enreg[i].nom_p,nv_champs);
        break;
    case 2:
        printf("Vous avez sélectionné le champ 'Prénom'\n");
        printf("Saisir le nouveau prenom \n");

        scanf("%s",nv_champs);
        fflush(stdin);
        strcpy(enreg[i].prenom_p,nv_champs);
        break;
    case 3:
        printf("Vous avez sélectionné le champ 'Ville'\n");
        printf("Saisir la nouvelle ville \n");

        scanf("%s",nv_champs);
        fflush(stdin);
        strcpy(enreg[i].ville_p,nv_champs);
        break;
    case 4:
        printf("Vous avez sélectionné le champ 'Code postal'\n");
        printf("Saisir le nouveau Code postal \n");

        scanf("%s",nv_champs);
        fflush(stdin);
        strcpy(enreg[i].code_postal_p,nv_champs);
        break;
    case 5:
        printf("Vous avez sélectionné le champ 'Téléphone'\n");
        printf("Saisir le nouveau telephone \n");

        scanf("%s",nv_champs);
        fflush(stdin);
        strcpy(enreg[i].telephone_p,nv_champs);
        break;
    case 6:
        printf("Vous avez sélectionné le champ 'Profession'\n");
        printf("Saisir la nouvelle Profession \n");

        scanf("%s",nv_champs);
        fflush(stdin);
        strcpy(enreg[i].profession_p,nv_champs);
        break;
    default:
        printf("Veuillez entrer un nombre compris entre 1 et 6\n");
        break;
    }
    ecrire_csv_to_txt(res_modifier_autre_champs,enreg,i);

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

    char * arr [7] = {"nom","prenom","code_postal","ville","telephone","mel","profession"};

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









int main(){

    char nom[MAX_SIZE]; char prenom[MAX_SIZE]; char ville[MAX_SIZE]; char cp[MAX_SIZE]; char tel[MAX_SIZE]; char mel[MAX_SIZE]; char profession[MAX_SIZE];
    int nombre;
	do{
        printf("*******************************************************\n");
        printf("        Choisir votre option : \n");
        printf("                        1.Ajouter un nouveau client\n");
        printf("                        2.Afficher le contenu de l'annuaire\n");
        printf("                        3.Modifier les donnees d'un client\n");
        printf("                        3.Modifier le mel d'un client\n");
        printf("                        4.Supprimer un client\n");
        printf("                        5.Trier les clients par nom\n");
        printf("                        6.Filtrer les clients ayant des donn\202es manquantes\n");
        printf("                        3.Filtrer une information\n");
        printf("                        3.Filtrer deux informations\n");
        printf("                        6.Quitter le programme\n");

        printf("************************************************************\n");
        printf("\nVotre choix : \n");
        scanf("%d", &nombre);
        fflush(stdin);
        switch(nombre) {
        case 1:
            printf("Entrez le nom : ");
            gets(nom);
            fflush(stdin);
            printf("\nEntrez le prenom : ");
            gets(prenom);
            fflush(stdin);
            printf("\nEntrez la ville de residence : ");
            gets(ville);
            fflush(stdin);
            printf("\nEntrez le code postal : ");
            gets(cp);
            fflush(stdin);
            printf("\nEntrez le num\202ro de t\202l\202phone : ");
            gets(tel);
            fflush(stdin);
            printf("\nEntre le mel : ");
            gets(mel);
            fflush(stdin);
            is_mail_exist(annuaire, mel);
            printf("\nEntrez la profession : ");
            gets(profession);
            fflush(stdin);
            ajouter_client(annuaire, nom, prenom, ville, cp, tel, mel, profession);

            break;
        case 2:
            filtrer_par_champs_vide(annuaire);
            break;
        case 3:
            display_enreg(annuaire);
            modifier_autre_champ(annuaire);
            break;
        case 4:
            printf("Saisir le mail que vous souhaitez modifier \n");
            char mel[50];
            char nv_mel_p[50];
            gets(mel);

            printf("Saisir le nouveau mel \n");
            scanf("%s",nv_mel_p);
            fflush(stdin);

            display_enreg(annuaire);
            modifier_mel(annuaire, mel, nv_mel_p);
            break;
        case 5:
            display_enreg(annuaire);
            trier_par_nom(annuaire);
            break;
        case 6:
            exit(0);
            break;
        }
        printf("\n");
        //system("pause");
    } while(nombre!=5);

    return 0;

}

void trier_par_nom(const char *annuaire){

    int nb_lignes = total_lignes(annuaire); int i;
    client *enreg=read_csv_from_annuaire(annuaire);
    client *echange = (client*)malloc( nb_lignes * sizeof(client));

    FILE* fp = fopen(res_trier_nom, "a");

    for(i=0;i<nb_lignes;i++){
        if( strcmp(enreg[i].nom_p,enreg[i+1].prenom_p)>0)// si c'est >0 cela veut dire que    tab[i]>tab[i+1]
        {
           strcpy(echange,enreg[i].prenom_p);//on stock dans echange la valeur de tab[i]
           strcpy(enreg[i].prenom_p,enreg[i+1].prenom_p);
           strcpy(enreg[i+1].prenom_p,echange);
           printf("test");
        }
    }
    printf(fp, "Voici la liste des noms tri\202s");
    ecrire_csv_to_txt(res_trier_nom ,enreg,i);

    fclose(fp);
}

