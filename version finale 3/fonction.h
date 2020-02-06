#ifndef MODELE_H
#define MODELE_H

#include <stdio.h>

#define MAXTAB 18000
#define max 1024

/*************************************************Declaration des structures************************************************/

/******************************************************Definition de la structure de la table d'index 1***********************/
  typedef struct enreg
{

long cle;			//La cle representant le matricule
  int pos;			//position dans le fichier principal
  int bloc;			//le bloc dans ce fichier
  int region;			//Le parametere de la region afin d'effectuer les traitements liees a ce dernier
  int eff;


} enreg;

typedef struct blc
{

enreg tab[MAXTAB];		// tableau d'enregistremnts (des entiers longs)
  char eff[MAXTAB];		// indicateurs d'effacement logique ('*' effacC) / ' ' non effacC))
  int nb;			// nombre d'enregistrements dans le bloc

} tbloc;



// type du bloc d'entC*te (les caractC)ristiques du fichier)
  typedef struct entete
{

    // nombre de blocs utilisC) par les enreg (c'est aussi le num du dernier bloc)
  long nb_bloc;

    // nombre d'enregistrements dans le fichier
  long nb_ins;

    // nombre d'enregistrements supprimC)s (logiquement) dans le fichier
  long nb_sup;


} t_entete;






/****************************************************Definition de la structure de la table d'index 2********************/

typedef struct enreg2
{

long cle;			//representant le matricule
  int pos;			//La position dans le fichier
  int bloc;

int Etablissement;		//Le parametere de l'etablissment afin d'effectuer les traitements de ce derniers
  int anciente;			//Le parametere de l'anciente
  int eff;

int specialite;		//specialite
} enreg2;

typedef struct blc2
{

enreg2 tab[MAXTAB];		// tableau d'enregistremnts (des entiers longs)
  char eff[MAXTAB];		// indicateurs d'effacement logique ('*' effacC) / ' ' non effacC))
  int nb;			// nombre d'enregistrements dans le bloc
} tbloc2;



// type du bloc d'entC*te (les caractC)ristiques du fichier)
  typedef struct entete2
{

    // nombre de blocs utilisC) par les enreg (c'est aussi le num du dernier bloc)
  long nb_bloc;

    // nombre d'enregistrements dans le fichier
  long nb_ins;

    // nombre d'enregistrements supprimC)s (logiquement) dans le fichier
  long nb_sup;


} t_entete2;





/*********************************************Definition de la structure principale*************************************/

typedef struct Tbloc
{

char tab[max];		// le tableau de caractC(re
  int suivant;			// le numero du bloc suivant dans la liste
} Tbloc;


typedef struct Tbloc Buffer;	// declaration du Buffer
typedef struct maillon
{

int val;

int suivant;

} maillon;


typedef struct Entete	// structure de l'entete du fichier en mC)moire centrale
{

int nbbloc;

int tete;

int queue;

int indice_libre;		// l'indice libre dans le bloc de la queue
  int nb_car_sup;


} Entete;


typedef struct L7OVC
{

FILE * fich;

Entete entete;


} L7OVC;




/**************************************************************La Machine abstraite***********************************************/
// ouvrir un fichier en mode 'N' ou 'A'
// retourne le flux f et l'entC*te ent
void ouvrir (FILE ** f, char *nom, char mode, t_entete * ent);


// fermer le fichier en sauvegardant l'entC*te ent dans le 1er bloc (num 0) du fichier
void fermer (FILE * f, t_entete * ent);


// lecture du bloc de donnC)es num i dans la variable buf
void lireDir (FILE * f, long i, tbloc * buf);


// ecriture du contenu de la variable buf dans le bloc de donnC)es num i
void ecrireDir (FILE * f, long i, tbloc * buf);







/*************************************************************************Les fonctions standards*****************************************/
void aff_entete (L7OVC * fichier, int i, int valeur);	//L'entete de la structure L7ovc (module d'affectation)
int entete (L7OVC * fichier, int i);	////L'entete de la structure L7ovc
void liredir_L7OVC (L7OVC * fichier, long i, Tbloc * buf);	//Lire le bloc i de la structure l7ovc
void ecriredir_L7OVC (L7OVC * fichier, int i, Buffer * buf);	//Ecrire le contenu du buffer dans le bloc i de la structure
L7OVC *ouvrir_L7OVC (char nom_physique[], char mode);	//Ouvrir le fichier l7ovc
void fermer_L7OVC (L7OVC * fichier);	//Fermer le fichier
void alloc_bloc (L7OVC * fichier);	//Creation d'un nouveau bloc afin de l'ajouter a la structure l7ovc


void ecrire_chaine (L7OVC * fichier, int n, int *i, int *j, char chaine[],
		     int *cpt, Buffer * buf);

//void insertion2_L7OVC(L7OVC *fichier, int cle, char *info) ;//inserer l'info dans la posistion j du bloc i
//void suppression_Logique_L7OVC2(L7OVC *fichier, int cle);//Changer le caracter de suppression dans l'enregistrement a la position donnee
void afficher_bloc (L7OVC * fichier, int i);	//Afficher le bloc i
void reordonner_fichier (L7OVC * fichier1, char *nom_physique);

void afficher_entete (L7OVC * fichier);	//Afficher les information de l'entete du fichier l7ovc
void chargement_initial (L7OVC * fichier);	//Module de chargement initial
//void insertion2_L7OVC(L7OVC *fichier,char *cle_ch,int *i,int *j);//Insertion de l'enregistrement donnee per la cle_ch dans la postion donnee i et j





#endif	/*
 */

