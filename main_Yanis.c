#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#define N 40
#define chemin "doc.csv"

typedef struct client{
    int num;
    char prenom[N];
    char nom[N];
    char filliere[N];
    int codepostal;

} CLIENT;

int main(){
	int nombre;
	do{
        printf("*******************************************************\n");
        printf("        Choisir votre option : \n");
        printf("                        1.Ajouter un nouvel \202tudiant\n");
        printf("                        2.Afficher le contenu de la promotion\n");
        printf("                        3.Modifier le nom d'un \202tudiant\n");
        printf("                        4.Supprimer un \202tudiant\n");
        printf("                        5.Afficher la liste des \202tudiant\n");
        printf("                        6.Quitter le programme\n");
        printf("************************************************************\n");
        printf("Votre choix : \n");
        scanf("%d", &nombre);
        fflush(stdin);
        switch(nombre) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        }
        printf("\n");
        system("pause");
    } while(nombre!=5);
    return 0;
}


void modifier_mel_client(char nom_annuaire, char mel_p, char nv_mel_p){
    char nouveau_mail[N];
    FILE *file1 = fopen(chemin,"r");
    FILE *file2 = fopen(chemin,"a");
    if (file1 != NULL || file2 != NULL){
        do{

        }
    }

    else{
        exit(0);
    }

    fclose(file);

}
void supprimer_client(char nom_annuaire, char mel_p){



}

void filtrer_combiner_deux_champs(char nom_annuaire, char nom_champs1, char val_chaine1, char nom_champs2, char val_chaine2){


}
