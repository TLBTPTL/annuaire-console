#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

int filter_clients_donnees_manquantes(const char * nom_annuaire);
int modifier_autres_que_mel_client(const char* nom_annuaire,const char* mel_p, const char* nom_champ,const char* nv_valeur);
int filtrer_un_champ(const char* nom_annuaire,const char* nom_champ, const char* val_chaine);
#endif // FONCTIONS_H_INCLUDED
