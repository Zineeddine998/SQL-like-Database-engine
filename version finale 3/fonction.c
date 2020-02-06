#include "fonction.h"
#include <stdio.h>
#include <windows.h>


/*********************************************Table index***************************/
// ouvre un fichier et m-a-j de l'entete
  void
ouvrir (FILE ** f, char *nom, char mode, t_entete * ent)
{

if (mode == 'A' || mode == 'a')
    {

*f = fopen (nom, "rb+");

if (*f == NULL)
	perror ("ouvrir (probleme dans fopen)");

fread (ent, sizeof (t_entete), 1, *f);

}

  else
    {				// mode == 'N' || mode == 'n'
      *f = fopen (nom, "wb+");

if (*f == NULL)
	perror ("ouvrir (probleme dans fopen)");

ent->nb_bloc = 0;

ent->nb_ins = 0;

ent->nb_sup = 0;

fwrite (ent, sizeof (t_entete), 1, *f);

}

}




// ferme le fichier et sauvegarde de l'entete au dCB)but du fichier
  void
fermer (FILE * f, t_entete * ent)
{

fseek (f, 0L, SEEK_SET);

fwrite (ent, sizeof (t_entete), 1, f);

fclose (f);

}




// lecture du bloc de donnees numero i dans la variable buf
  void
lireDir (FILE * f, long i, tbloc * buf)
{

fseek (f, sizeof (t_entete) + (i - 1) * sizeof (tbloc), SEEK_SET);

fread (buf, sizeof (tbloc), 1, f);

}




// ecriture du contenu de buf dans le bloc de donnees
  void
ecrireDir (FILE * f, long i, tbloc * buf)
{

fseek (f, sizeof (t_entete) + (i - 1) * sizeof (tbloc), SEEK_SET);

fwrite (buf, sizeof (tbloc), 1, f);

}




void
liredir_L7OVC (L7OVC * f, long i, Buffer * buf)
{

fseek (f, sizeof (Entete) + (i - 1) * sizeof (Tbloc), SEEK_SET);

fread (buf, sizeof (Tbloc), 1, f);

}






















  //**************************************************************************************************************************//
  void
ouvrir2 (FILE ** f, char *nom, char mode, t_entete2 * ent)
{

if (mode == 'A' || mode == 'a')
    {

*f = fopen (nom, "rb+");

if (*f == NULL)
	perror ("ouvrir (probleme dans fopen)");

fread (ent, sizeof (t_entete2), 1, *f);

}

  else
    {				// mode == 'N' || mode == 'n'
      *f = fopen (nom, "wb+");

if (*f == NULL)
	perror ("ouvrir (probleme dans fopen)");

ent->nb_bloc = 0;

ent->nb_ins = 0;

ent->nb_sup = 0;

fwrite (ent, sizeof (t_entete2), 1, *f);

}

}




// ferme le fichier et sauvegarde de l'entete du fichier
  void
fermer2 (FILE * f, t_entete2 * ent)
{

fseek (f, 0L, SEEK_SET);

fwrite (ent, sizeof (t_entete2), 1, f);

fclose (f);

}




// lecture du bloc i dans la variable buf
  void
lireDir2 (FILE * f, long i, tbloc2 * buf)
{

fseek (f, sizeof (t_entete2) + (i - 1) * sizeof (tbloc2), SEEK_SET);

fread (buf, sizeof (tbloc2), 1, f);

}




// Ecriture du contenu du buffer dans le bloc i
  void
ecrireDir2 (FILE * f, long i, tbloc2 * buf)
{

fseek (f, sizeof (t_entete2) + (i - 1) * sizeof (tbloc2), SEEK_SET);

fwrite (buf, sizeof (tbloc2), 1, f);

}




//*********************************Affeceter entete de la structure l7ovc******************************//

//Mise a jour de l'entete
  void
aff_entete (L7OVC * fichier, int i, int valeur)
{


switch (i)

    {

case 1:

      {

fichier->entete.nbbloc = valeur;	// nombre total de bloc allouC)s dans le fichier
      }
      break;

case 2:

      {

fichier->entete.tete = valeur;	// numero du bloc representatnt la tete du fichier
      }
      break;

case 3:

      {

fichier->entete.queue = valeur;	// numero du bloc representatnt la tete duf icheir
      }
      break;

case 4:

      {

fichier->entete.indice_libre = valeur;	// la postion libre dans le bloc de queue
      }
      break;

case 5:

      {

fichier->entete.nb_car_sup = valeur;	// nombre de caractC(res suprimC) depuis la
	//crC)ation du ficher afin de lancer la rC)organiosation
      }
      break;


};

}



//-------------------------------------permet d'obtenir les elements de l'entete du ficher------------------------------//
  int
entete (L7OVC * fichier, int i)
{


switch (i)

    {

case 1:

      {

return (fichier->entete.nbbloc);

}
      break;

case 2:

      {

return (fichier->entete.tete);

}
      break;

case 3:

      {

return (fichier->entete.queue);

}
      break;

case 4:

      {

return (fichier->entete.indice_libre);

}
      break;

case 5:

      {

return (fichier->entete.nb_car_sup);

}
      break;


};

}



void
liredir (L7OVC * fichier, int i, Buffer * buf)
{


fseek (fichier->fich, (sizeof (Entete) + sizeof (Tbloc) * (i - 1)), SEEK_SET);	// positionnement au debut du bloc numero i
  fread (buf, sizeof (Buffer), 1, fichier->fich);	//lecture d'un bloc de caractC(re correspondant a la taille du bloc dans le buffer
  rewind (fichier->fich);	// repositionnement endebut de fichier

}



void
ecriredir (L7OVC * fichier, int i, Buffer * buf)
{


fseek (fichier->fich, sizeof (Entete) + sizeof (Tbloc) * (i - 1), SEEK_SET);	// positionnement au debut du bloc numero i
  fwrite (buf, sizeof (Buffer), 1, fichier->fich);	//ecriture du contenu du buffer dans le bloc numero i du fichier

}





//******************************************corps des focntions manipulation du fichier **********************************************************//
//---------------------------------------------------------permet d'ouvrir le fichier-----------------------------------------//
  L7OVC * ouvrir_L7OVC (char nom_physique[], char mode)
{


L7OVC * fichier = malloc (sizeof (L7OVC));	// allocation  de la structure
  Buffer buf;

if ((mode == 'A') || (mode == 'a'))	// mode ancien
    {

fichier->fich = fopen (nom_physique, "rb+");	// ouverture du fichier en mode binaire lecture et ecriture
      fread (&(fichier->entete), sizeof (Entete), 1, fichier->fich);	// chargement de l'entete enregistrC)e en debut de fichier
    }

  else

    {

if ((mode == 'N') || (mode == 'n'))	// mode nouveau
	{

fichier->fich = fopen (nom_physique, "wb+");	// ouverture du fichier en mode binaire  ecriture
	  aff_entete (fichier, 1, 0);	// mise a zeo du nombre de bloc si entete(fichier,1)=0 alors le fichier est vide
	  aff_entete (fichier, 2, 1);	// mettre tete au premier bloc
	  aff_entete (fichier, 3, 1);	// de meme pour la queue puisque au debut tete est queue sont confondues
	  aff_entete (fichier, 4, 0);	// le premier caractC(re du ficheir correspond a laposition libre puisqu'il est nouveau
	  aff_entete (fichier, 5, 0);	// aucun caractC(re n'a encore C)tC) supprimC)
	  fwrite (&(fichier->entete), sizeof (Entete), 1, fichier->fich);	// enregistrement de l'entete dans le fichier
	  buf.suivant = -1;	// le suivant du premier bloc a NULL
	  sprintf (buf.tab, "%s", "");	// initialisation du buffer a chaine vide
	  ecriredir (fichier, 1, &buf);	// ecriture du premier bloc dans le fichier


}

      else			// format d'ouverture incorrecte
	{

printf ("format d'ouverture impossible");

}

}

return (fichier);		// renvoyer la structure crC)C)e
}



void
fermer_L7OVC (L7OVC * fichier)	// procedure de fermeture du fichier
{

rewind (fichier->fich);	// repositionnement du curseur en debut de fichier
  fwrite (&(fichier->entete), sizeof (Entete), 1, fichier->fich);	// sauvegarde de la derniC(re version de l'entete de la strucuture L7OVC
  //dans le fichier
  rewind (fichier->fich);	// repositionnement du curseur en debut de fichier
  fclose (fichier->fich);	// fermeture du fichier

}


//***************************************************************************************************************************************//

//-------------------------------------permet d'allouer un nouveau bloc dans le ficiher et de maettre a jour les caractC)ristiques des bloc eet de l'entete touchC)s------------------------------//
  void
alloc_bloc (L7OVC * fichier)
{


Buffer * buf = malloc (sizeof (Buffer));	// allocation du Buffer
  liredir (fichier, entete (fichier, 3), buf);	// lecture du bloc correspondant a la queue
  buf->suivant = entete (fichier, 1) + 1;	// mise a jour dui suvant de la queue au bloc correspondant a la nouvelle queue
  ecriredir (fichier, entete (fichier, 3), buf);	// ecriture du bloc de queue dans le fichier
  aff_entete (fichier, 3, entete (fichier, 1) + 1);	// mise a jour du numero du bloc correspondant a la nouvelle queue dan sl'entete
  buf->suivant = -1;		// mise a jour du suivant a nill
  sprintf (buf->tab, "%s", "");
  ecriredir (fichier, entete (fichier, 3), buf);	// ecriture du buffer dans le bloc representatnt la nouvelle queue
  aff_entete (fichier, 1, entete (fichier, 1) + 1);	// vider la chaine du buffer
  // incrC)mentation du nombre de bloc allouC)s
}




//*********************************focntion de manipulation des chaines****************************************************************//

//----------------------------------- procedure qui transforme un nombre en chaine de caractC(re sur longueur de caractC(re-------------//
  void
turn_to_string (char chaine[], int n, int longueur)
{


int k;

for (k = longueur - 1; k >= 0; k--)	// on commence par le poids faible du nombre qui va etre mi a chaine[longueur-1]
    {

chaine[k] = (n % 10) + '0';	// extraction chiffre par chiffre  grace au mod par 10 et ajout du code ascii du zero afoin d'obtenir le code ascii correspondant au chiffre obtenu
      n = n / 10;		// on passe au chiffre suivant
    }

chaine[longueur] = '\0';	// fin de la chaine construite
}



//----------------------------------- fonction qui permet de construire la chaine correspondant a la forme de l'enregistrememnt-------------//
  void
concat (char chaine[], int cle, char info[])	//           a inserer dans le ficheir a partir de la cle et de l'info
{


char ch_f[100];

turn_to_string (ch_f, cle, 6);	// transformation de la cle en chaine sur 5 positions
  strcat (ch_f, info);		// concatC)nation de cle et info
  turn_to_string (chaine, strlen (info), 3);	// construction du debut de la chaine finale en commenC'ant par la taille de l'info
  strcat (chaine, "f");		// mise a jour du champs effacC)
  strcat (chaine, ch_f);	// constructu=ion de la chaine finale avec l'ordre suivant taille efface cle info
}



//----------------------------------- fonction qui permet de rC)cuperer une chaine de longueur
  // n dans le bloc i  lu dans buffer a partir de la position j-------------//


//----------------------------------- // procedure qui permet d'ecrire n caractC(re du buffer----------------------------------------------//






void
modification_L7OVC (L7OVC * fichier, char *etablissement, char nvetablissment,
		    int *trouv, int *i, int *j)
{
  Buffer buf;

char *chaine = malloc (sizeof (char) * 50);

}


//********************************************fonction de recherche**************************************************************//
//----------------------------------- fonction qui permet de rC)cuperer une chaine de longueur
  // n dans le bloc i  lu dans buffer a partir de la position j-------------//
  void
recuperer_chaine (L7OVC * fichier, int n, int *i, int *j, char chaine[], Buffer * buf)	//
{


int k = 0;

sprintf (chaine, "%s", "");

for (k = 0; k < n; k++)	// boucle de n itC)rations correspondant a la longueur de la chaine
    {				// indice de parcours de la chaine resultata et j celui du tableau
      if ((*j) <= 1024)		// si le kiC(mem caractC(re de la chaine correspondant au j ime car du buffer  est toujour dans le bloc i
	{			// le caractC(re 99 correspond a la fin de la chaine dans le tableau
	  chaine[k] = buf->tab[(*j)];	// recuperation du caractC(re dans la position k de la chaine
	  (*j)++;		// deplacement d'une position dans le buffer
	}

      else			// si le k iC(eme caractC(re a recuperer sort du buffer
	{

(*i) = buf->suivant;	// on passe au suivant du bloc i dans la liste
	  liredir (fichier, (*i), buf);	// lecture
	  chaine[k] = buf->tab[0];	// recuperation du premier caractC(re du tableau de carractC(re correspondant au ka iC(me car de la chaine
	  (*j) = 1;		//positionnement eu second caractC(re dans le nouveau buffer
	}

}

chaine[k] = '\0';		// fin de la chaine obtenue
}









void
recuperer_chaine2 (L7OVC * fichier, int n, int *i, int *j, char *ch, Buffer * buf)	//
{


int k = 0;

char chan[1512] = "";

strcpy (chan, "");

for (k = 0; k < n; k++)	// boucle de n itC)rations correspondant a la longueur de la chaine
    {				// indice de parcours de la chaine resultata et j celui du tableau
      if ((*j) <= 1024)		// si le kiC(mem caractC(re de la chaine correspondant au j ime car du buffer  est toujour dans le bloc i
	{			// le caractC(re 99 correspond a la fin de la chaine dans le tableau
	  chan[k] = buf->tab[(*j)];

	    //printf("/////////////////////////////////////////////////////%s",buf->tab[(*j)]);  // recuperation du caractC(re dans la position k de la chaine
	    (*j)++;		// deplacement d'une position dans le buffer
	}

      else			// si le k iC(eme caractC(re a recuperer sort du buffer
	{

	    //(*i)=buf->suivant;
	    (*i)++;		// on passe au suivant du bloc i dans la liste
	  liredir (fichier, (*i), buf);	// lecture
	  chan[k] = buf->tab[0];	// recuperation du premier caractC(re du tableau de carractC(re correspondant au ka iC(me car de la chaine
	  (*j) = 1;		//positionnement eu second caractC(re dans le nouveau buffer
	}

}

chan[strlen (chan)] = '\0';

ch = &chan[0];		// fin de la chaine obtenue
}





void
suppression_logique_L7OVC2 (L7OVC * fichier1, int *i, int *j)
{

Buffer buf;

int cpt = 0;

char c = 'O';

char chaine[2048] = "";

    //char chaine2[2048]="";

liredir (fichier1, i, &buf);

printf ("\n1)");

int k = 0;

recuperer_chaine (fichier1, 150, i, j, chaine, &buf);

printf ("\n2)");

while (k != strlen (chaine) - 1)

    {				//printf("\n3)");
      if ((chaine[k] == '#'))

	{
	  printf ("\n4)");

	    //chaine[k+1]=c;
	    //printf("\n/////////////////%s",chaine[k+1]);
	}

k++;

}

chaine[strlen (chaine)] = '\0';

printf ("\n5)");

    //char * ch = &chaine[0];
    ecrire_chaine (fichier1, 150, i, j, chaine, &cpt, &buf);

printf ("\n6)");


}





void
suppression_logique_L7OVC3 (L7OVC * fichier1, int *i, int *j)
{

Buffer buf;

int cpt = 0;

char c = 'O';

char chaine[2048] = "";

    //char chaine2[2048]="";

liredir (fichier1, i, &buf);

printf ("\n1)");

int k = 0;

recuperer_chaine (fichier1, 150, i, j, chaine, &buf);

    //printf("Le enregistrement donee est      :%s",chaine);

printf ("\n5)");

    //char * ch = &chaine[0];
    //ecrire_chaine2()
    //char ch[120]="elhadi adel";
    //ch[strlen(ch)]='\n';
    ecrire_chaine2 (fichier1, 150, i, j, chaine, &cpt, &buf);

ecriredir (fichier1, i, &buf);

printf ("\n6)");


}
















void

ecrire_chaine (L7OVC * fichier, int n, int *i, int *j, char chaine[],
	       int *cpt, Buffer * buf)
{


int k = 0;

(*cpt) = 0;			// nombre de bloc ajoutC)s
  for (k = 0; k < n; k++)	// k pourn le deplacement dans la chaine
    {

if ((*j) <= 1024)	//si je suis toujours dans le bloc consernC)
	{

buf->tab[*j] = chaine[k];	// affectation des caractC(res de la chaine dans le buffer un a un
	  (*j)++;

	    //printf("\n %d                    ",*j) ;
	    //printf(" %d",k) ;                            // deplacement da,s le buffer
	}

      else			// si la chaine a inserer depasse le buffer
	{

ecriredir (fichier, *i, &buf);	// ecriture du precedent buffer dans le fichier
	  alloc_bloc (fichier);	// alocation d'un nouveau bloc afin de recevoir le reste de la chaine
	  buf->tab[1] = chaine[k];	// ecrtiture du kiem caractC(re de la chaine dans la position 0
	  (*j) = 2;		// passage a la position 1
	  (*i) = entete (fichier, 3);	// deplacement dans les bloc du ficher
	  (*cpt)++;		// incrementation du nombre de bloc alloues
	}

}

buf->tab[*j] = '\0';		// fin de la chaine

}




void
ecrire_chaine2 (L7OVC * fichier, int n, int *i, int *j, char chaine[],
		int *cpt, Buffer * buf)
{


int k = 0;

char prec;

(*cpt) = 0;			// nombre de bloc ajoutC)s
  for (k = 0; k < n; k++)	// k pourn le deplacement dans la chaine
    {

if ((*j) <= 1024)	//si je suis toujours dans le bloc consernC)
	{
	  char *ch = &ch[k];

printf ("\n%c", chaine[k]);

if ((prec == 65) && (chaine[k + 1] == 65))
	    {

printf ("tbedlet");

buf->tab[*j] = 'O';


}
	  else
	    {

buf->tab[*j] = '*';

prec = chaine[k];

}			// affectation des caractC(res de la chaine dans le buffer un a un
	  (*j)++;

	    //printf("\n %d                    ",*j) ;
	    //printf(" %d",k) ;                            // deplacement da,s le buffer
	}

      else			// si la chaine a inserer depasse le buffer
	{

ecriredir (fichier, *i, &buf);	// ecriture du precedent buffer dans le fichier
	  alloc_bloc (fichier);	// alocation d'un nouveau bloc afin de recevoir le reste de la chaine
	  buf->tab[1] = chaine[k];	// ecrtiture du kiem caractC(re de la chaine dans la position 0
	  (*j) = 2;		// passage a la position 1
	  (*i) = entete (fichier, 3);	// deplacement dans les bloc du ficher
	  (*cpt)++;		// incrementation du nombre de bloc alloues
	}

}

buf->tab[*j] = '\0';		// fin de la chaine

}

























//********************************************fonction de recherche**************************************************************//
  void
recherche_L7OVC (L7OVC * fichier, int cle, int *trouv, int *i, int *j)
{

Buffer buf;

char *ch1 = malloc (sizeof (char) * 3);	// chaine pour recevoir la taille de l'info
  char *ch2 = malloc (sizeof (char));	// chaine pour recevoir le champ 1effacC)
  char *ch3 = malloc (sizeof (char) * 6);	// chaine pour recevoir la cle
  char *chaine = malloc (sizeof (char) * 50);	//chaine pour recevoir l'info'
  int stop = 0;			// booleen pour l'arret de la recherche
  int bloc, pos;

(*trouv) = 0;		// initialisdation de trouv a 0
  (*i) = entete (fichier, 2);	// positionnement au bloc entete pour une recherche sequentielle
  (*j) = 0;			// premiC(re position
  if (entete (fichier, 1) != 0)	// si le fichier nest pas vide
    {


liredir (fichier, *i, &buf);	// lecture du premier bloc afin d'entammer le parcours


while ((stop == 0) && ((*trouv) == 0))	// tant qu'on pas trouvC) ou qu'on est pas a la fin du ficher
	{

bloc = (*i);		// sauvegarde du bloc a partir duquel on a commencC) l'extraction de l'enregistrement
	  pos = (*j);		//sauvegarde de la position
	  recuperer_chaine (fichier, 3, i, j, ch1, &buf);	// recuperation des champs
	  recuperer_chaine (fichier, 1, i, j, ch2, &buf);

recuperer_chaine (fichier, 6, i, j, ch3, &buf);

recuperer_chaine (fichier, atoi (ch1), i, j, chaine, &buf);	// longueur de l'info est le nombre equivalent a ch1
	  int resultat = strcmp (ch2, "f");

int comp = atoi (ch3);


if ((comp == cle) && (resultat == 0))	// si l'info n'est pas effacC) logiquement et que la cle correspond
	    {


(*trouv) = 1;	// arret de la recherche
	    }

	  else

	    {

if (((*i) == entete (fichier, 3)) && ((*j) == entete (fichier, 4)))	// si on est a la fin du fichier on arrete
		{

stop = 1;

}

}

}

(*i) = bloc;		// renvoi du bloc et de la position aux quels no n a trouvC) l'info si elle existe
      (*j) = pos;

}


}





void
insertion_L7OVC (L7OVC * fichier, int cle, char *info)
{

int i, j, trouv = 0, cpt;	// declaration des variables
  Buffer buf;

char *cle_ch = malloc ((sizeof (char)) * sizeof (info));	// la chaine qui va contenir l'enregistrement qui va etre inserC)
  recherche_L7OVC (fichier, cle, &trouv, &i, &j);	// recherche de la cle pour eviter les doublons
  if (entete (fichier, 1) == 0)	// si la cle n'a  pas C)tC) trouvC) alors on insere dans le premier bloc
    aff_entete (fichier, 1, 1);

if (trouv == 0)

    {

cpt = 0;

i = entete (fichier, 3);	// positionnelent dans le queue
      j = entete (fichier, 4);	// positionnnement a la position libre dans le bloc de queue
      liredir (fichier, i, &buf);	// lecture du  bloc
      sprintf (cle_ch, "%s", "");

	//concat(cle_ch,cle,info); // creation de l'enregistrement

char ch_f[100];

turn_to_string (ch_f, cle, 6);	// transformation de la cle en chaine sur 5 positions
      strcat (ch_f, info);	// concatC)nation de cle et info
      turn_to_string (cle_ch, strlen (info), 3);	// construction du debut de la chaine finale en commenC'ant par la taille de l'info
      strcat (cle_ch, "f");	// mise a jour du champs effacC)
      strcat (cle_ch, ch_f);





ecrire_chaine (fichier, strlen (cle_ch), &i, &j, cle_ch, &cpt, &buf);	// ecriture de la chaine construite
      ecriredir (fichier, i, &buf);	// ecriture du dernier bloc en cas de chevauchement
      aff_entete (fichier, 3, i);	// mise a jour de la quee
      aff_entete (fichier, 4, j);	// mise a jour de la position libre
    }

  else

    {

printf ("insertion impossible cle deja existante\n");

}

}







void
suppression_logique_L7OVC (L7OVC * fichier, int cle)
{

int i, j, trouv;

Buffer buf;

char *chaine = malloc (sizeof (char) * 3);

recherche_L7OVC (fichier, cle, &trouv, &i, &j);	// recherche de la cle fdans le fichihre
  if (trouv == 1)		// si la cmle a etet trouvee
    {

liredir (fichier, i, &buf);	// lecture du bloc dans lequel on a trouvC) l'info
      recuperer_chaine (fichier, 3, &i, &j, chaine, &buf);	// recuperation de la chaine correpondant a la taille de l'info
      buf.tab[j] = 'v';		// mise du champs efface a vrai
      ecriredir (fichier, i, &buf);	// reecriture du bloc
      aff_entete (fichier, 5, entete (fichier, 5) + atoi (chaine) + 9);	// mise az jour du nombre de caractC(re supprimes
      printf ("\nsuppression logique reussie\n");

}

  else

    {

printf ("\n   suppression impossible clC) inexistante\n");

}

}











//----------------------------------------affichage du bloc----------------------------------------------------//
  void
afficher_bloc (L7OVC * fichier, int i)
{

Buffer buf;

liredir (fichier, i, &buf);	//lecture du ieme bloc
  printf ("le tableau de caractC(res de bloc %d contient\n\n", i);

printf ("%s\n", buf.tab);	//affichage de la chaine de carctC(res contenue
  printf (" le suivant du bloc %d  est %d\n", i, buf.suivant);	// affichage du suivant

}


//------------------------ affichage du ficher----------------------------------------------------------------//
  void
afficher_fichier (L7OVC * fichier, int *i, int *j)
{				//printf("\nthis is it1");
  //int i=entete(fichier,2); // positionnement a la tete du fichier
  // positionnement au premier caractC(re
  int stop = 0;

Buffer buf;

char ch1[2560] = "";		//=malloc(sizeof(char)*3);
  char ch2[2560] = "";		//=malloc(sizeof(char));
  char ch3[2560] = "";		//=malloc(sizeof(char)*6);
  char ch4[2560] = "";		//=malloc(sizeof(char)*100);
  liredir (fichier, *i, &buf);	// lecture du premier bloc

if (entete (fichier, 1) != 0)

    {				// printf("\n  avant linsertion %s",ch1);
      //while(!stop)
      //{    //printf("\nthis is it2");
      printf ("\n      ");

recuperer_chaine (fichier, 250, i, j, ch1, &buf);

	//printf("\n2)%d  %d",*i,*j );
	*j = 1;

	// printf("\nthis is it   :  %s",ch1);
	for (int f = 0; f < 250; f++)
	{

printf ("%c", ch1[f]);

}
printf ("\n      ");
      printf ("\n      ");	// on commence a recuperer les enregistrememnt un a un
      /*recuperer_chaine(fichier,100,i,j,ch2,&buf);
         printf("\nthis is it2   :  %s",ch2);
         recuperer_chaine(fichier,60,i,j,ch3,&buf);
         printf("\nthis is it3   :  %s",ch3);
         recuperer_chaine(fichier,atoi(ch1),i,j,ch4,&buf);
         //printf("\nthis is it4   :  %s",ch4); */

	/*if(strcmp(ch2,"f")==0) //. si l'info n' pas ete supprimC) logiquement
	   {  // printf("\nthis is it4");
	   printf("%s%s%s%s",ch1,ch2,ch3,ch4); //impression de la totalitC) de l'enregistrement

	   } */
	if ((i == entete (fichier, 3)) && (j == entete (fichier, 4)))	// si on est la fin du ficher on arrete
	{

stop = 1;

}

	//system("pause");
	//}
    }

  else

    {

printf ("fichier vide");

}

}



void
afficher_fichier3 (int *i, int *j)
{				//printf("\nthis is it1");
  //int i=entete(fichier,2); // positionnement a la tete du fichier
  L7OVC *fichier = ouvrir_L7OVC ('fichier5.bin', 'a');	// positionnement au premier caractC(re
  int stop = 0;

Buffer buf;

char ch1[2560] = "";		//=malloc(sizeof(char)*3);
  char ch2[2560] = "";		//=malloc(sizeof(char));
  char ch3[2560] = "";		//=malloc(sizeof(char)*6);
  char ch4[2560] = "";		//=malloc(sizeof(char)*100);
  liredir (&fichier, *i, &buf);	// lecture du premier bloc

if (entete (fichier, 1) != 0)

    {				// printf("\n  avant linsertion %s",ch1);
      //while(!stop)
      //{    //printf("\nthis is it2");
      printf ("\n      ");

recuperer_chaine (fichier, 150, i, j, ch1, &buf);

	//printf("\n2)%d  %d",*i,*j );
	*j = 1;

	// printf("\nthis is it   :  %s",ch1);
	for (int f = 0; f < 150; f++)
	{

printf ("%c", ch1[f]);

}
printf ("\n      ");
      printf ("\n      ");	// on commence a recuperer les enregistrememnt un a un
      /*recuperer_chaine(fichier,100,i,j,ch2,&buf);
         printf("\nthis is it2   :  %s",ch2);
         recuperer_chaine(fichier,60,i,j,ch3,&buf);
         printf("\nthis is it3   :  %s",ch3);
         recuperer_chaine(fichier,atoi(ch1),i,j,ch4,&buf);
         //printf("\nthis is it4   :  %s",ch4); */

	/*if(strcmp(ch2,"f")==0) //. si l'info n' pas ete supprimC) logiquement
	   {  // printf("\nthis is it4");
	   printf("%s%s%s%s",ch1,ch2,ch3,ch4); //impression de la totalitC) de l'enregistrement

	   } */
	if ((i == entete (fichier, 3)) && (j == entete (fichier, 4)))	// si on est la fin du ficher on arrete
	{

stop = 1;

}

	//system("pause");
	//}
    }

  else

    {

printf ("fichier vide");

}

}










void
afficher_fichier2 (L7OVC * fichier, int *i, int *j)
{				//printf("\nthis is it1");
  //int i=entete(fichier,2); // positionnement a la tete du fichier
  // positionnement au premier caractC(re
  int stop = 0;

Buffer buf;

char ch1[2560] = "";		//=malloc(sizeof(char)*3);
  char ch2[2560] = "";		//=malloc(sizeof(char));
  char ch3[2560] = "";		//=malloc(sizeof(char)*6);
  char ch4[2560] = "";		//=malloc(sizeof(char)*100);
  liredir (fichier, *i, &buf);	// lecture du premier bloc
  printf ("\n");

for (int r = *j; r < *j + 200; r++)

    {

printf ("%c", buf.tab[r]);

}
printf ("\n");






}





//--------------------------------------- insertion dans un fichier--------------------------------------------------//
/*void insertion_L7OVC(L7OVC *fichier, int cle, char *info)
{
    int i,j,trouv=0,cpt; // declaration des variables
    Buffer buf;
    char *cle_ch=malloc((sizeof(char))*sizeof(info)); // la chaine qui va contenir l'enregistrement qui va etre inserC)
    //recherche_L7OVC(fichier,cle,&trouv,&i,&j); // recherche de la cle pour eviter les doublons
    if(entete(fichier,1)==0) // si la cle n'a  pas C)tC) trouvC) alors on insere dans le premier bloc
      aff_entete(fichier,1,1);
    if(trouv==0)
    {
        cpt=0;
        i=entete(fichier,3); // positionnelent dans le queue
        j=entete(fichier,4);  // positionnnement a la position libre dans le bloc de queue
        liredir(fichier,i,&buf); // lecture du  bloc
       sprintf(cle_ch,"%s","");
        //concat(cle_ch,cle,info); // creation de l'enregistrement

    char ch_f[100];
    turn_to_string(ch_f,cle,6);                   // transformation de la cle en chaine sur 5 positions
    strcat(ch_f,info);                            // concatC)nation de cle et info
    turn_to_string(cle_ch,strlen(info),3);        // construction du debut de la chaine finale en commenC'ant par la taille de l'info
    strcat(cle_ch,"f");                           // mise a jour du champs effacC)
    strcat(cle_ch,ch_f);




        ecrire_chaine(fichier,strlen(cle_ch),&i,&j,cle_ch,&cpt,&buf); // ecriture de la chaine construite
        ecriredir(fichier,i,&buf); // ecriture du dernier bloc en cas de chevauchement
        aff_entete(fichier,3,i); // mise a jour de la quee
        aff_entete(fichier,4,j); // mise a jour de la position libre
    }
    else
    {
        printf("insertion impossible cle deja existante\n");
    }
}*/

//----------------------- focntion de suppression lohgique dans le fichier--------------------------------------------//
/*void suppression_logique_L7OVC(L7OVC *fichier, int cle,int bloc,int pos)
{
    int trouv;
    Buffer buf;
   int i = bloc;
   int j =pos;
   int* k=bloc;
   int* gf = pos;
    char *chaine=malloc(sizeof(char)*3);
    //recherche_L7OVC(fichier,cle,&trouv,&i,&j); // recherche de la cle fdans le fichihre
    if(trouv==1)                                // si la cmle a etet trouvee
    {
        liredir(fichier,i,&buf);   // lecture du bloc dans lequel on a trouvC) l'info
            recuperer_chaine(fichier,3,k,gf,&buf); // recuperation de la chaine correpondant a la taille de l'info
        buf.tab[j]='v';          // mise du champs efface a vrai
        ecriredir(fichier,i,&buf);                  // reecriture du bloc
        aff_entete(fichier,5,entete(fichier,5)+atoi(chaine)+9); // mise az jour du nombre de caractC(re supprimes
        printf("\nsuppression logique reussie\n");
    }
    else
    {
        printf("\n   suppression impossible clC) inexistante\n");
    }
}*/

//----------------------------------------affichage du bloc----------------------------------------------------//


//------------------------ affichage du ficher----------------------------------------------------------------//



//------------------------ affichage des informations en chevauchement----------------------------------------------------------------//

//------------------------ recherche de la plus petite valeur superieure a une vleur donnC)e ----------------------------------------------------------------//
//----------- recherche du max du  ficher----------------------------------------------------------------//

//------------------------ reordonner le fichier ficher----------------------------------------------------------------//

//------------------------ suppresiion physique dans un autre ficher----------------------------------------------------------------//


void
insertion2_L7OVC (L7OVC * fichier, char *cle, int *i, int *j)
{

int cpt;			// declaration des variables
  Buffer buf;

    //char *cle_ch=malloc((sizeof(char))*200); // la chaine qui va contenir l'enregistrement qui va etre inserC)
    //recherche_L7OVC(fichier,cle,&trouv,&i,&j); // recherche de la cle pour eviter les doublons
    if (entete (fichier, 1) == 0)	// si la cle n'a  pas C)tC) trouvC) alors on insere dans le premier bloc
    aff_entete (fichier, 1, 1);

cpt = 0;

*i = entete (fichier, 3);	// positionnelent dans la queue
  *j = entete (fichier, 4);	// positionnnement a la position libre dans le bloc de queue
  liredir (fichier, *i, &buf);	// lecture du  bloc
  //sprintf(cle_ch,"%s","");
  //concat(cle_ch,cle,info); // creation de l'enregistrement


int k = 0;

cle[strlen (cle)] = '\0';

    // nombre de bloc ajoutC)s
    for (k = 0; k < strlen (cle) - 1; k++)	// k pourn le deplacement dans la chaine
    {

if ((*j) <= 1024)	//si je suis toujours dans le bloc consernC)
	{

buf.tab[*j] = cle[k];	// affectation des caractC(res de la chaine dans le buffer un a un
	  (*j)++;

	    //printf("\n %d                    ",*j) ;
	    //printf(" %d",k) ;                            // deplacement da,s le buffer
	}

      else			// si la chaine a inserer depasse le buffer
	{

ecriredir (fichier, *i, &buf);	// ecriture du precedent buffer dans le fichier
	  // alocation d'un nouveau bloc afin de recevoir le reste de la chaine

	    //ecriredir(fichier,entete(fichier,3),buf);// ecriture du buffer dans le bloc representatnt la nouvelle queue
	    aff_entete (fichier, 1, entete (fichier, 1) + 1);


sprintf (buf.tab, "%s", "");

buf.tab[1] = cle[k];	// ecrtiture du kiem caractC(re de la chaine dans la position 0
	  (*j) = 2;		// passage a la position 1
	  (*i) = entete (fichier, 3) + 1;	// deplacement dans les bloc du ficher
	  // incrementation du nombre de bloc alloues
	}

}

buf.tab[*j] = '\0';




    // ecrire_chaine(fichier,strlen(cle_ch),i,j,cle_ch,&cpt,&buf); // ecriture de la chaine construite
    ecriredir (fichier, *i, &buf);	// ecriture du dernier bloc en cas de chevauchement
  aff_entete (fichier, 3, *i);	// mise a jour de la quee
  aff_entete (fichier, 4, *j);	// mise a jour de la position libre

}









void
suppression_Logique_L7OVC (L7OVC * fichier, int *i, int *j)
{

int cpt;

int choix;			// declaration des variables
  Buffer buf;


    //char *cle_ch=malloc((sizeof(char))*200); // la chaine qui va contenir l'enregistrement qui va etre inserC)
    //recherche_L7OVC(fichier,cle,&trouv,&i,&j); // recherche de la cle pour eviter les doublons
    if (entete (fichier, 1) == 0)	// si la cle n'a  pas C)tC) trouvC) alors on insere dans le premier bloc
    aff_entete (fichier, 1, 1);

cpt = 0;

	/**i=entete(fichier,3); // positionnelent dans le queue
        *j=entete(fichier,4);  // positionnnement a la position libre dans le bloc de queue*/
    liredir (fichier, *i, &buf);	// lecture du  bloc

int g = *j;

if (*j == 1021 && buf.tab[*j + 4] == 'N')
    buf.tab[1025] = 'O';

if (*j < 1021)
    {

while ((buf.tab[g] != '#') || (buf.tab[g + 2] != '#'))

	{

g++;

}

buf.tab[g + 1] = 'O';

}

if (1021 < *j)
    {

*i++;

liredir (fichier, *i, &buf);

	//*j=(*j)%1025+1;
	g = 0;

while ((buf.tab[g] != '#') || (buf.tab[g + 2] != '#'))

	{

g++;

}

buf.tab[g + 1] = 'O';

}







    //ecrire_chaine(fichier,150,i,j,cle_ch,&cpt,&buf); // ecriture de la chaine construite
    ecriredir (fichier, *i, &buf);	// ecriture du dernier bloc en cas de chevauchement
  //aff_entete(fichier,3,*i); // mise a jour de la quee
  //aff_entete(fichier,4,*j); // mise a jour de la position libr,choix
  //afficher_fichier2(fichier,i,j);

}









void
afficher_entete (L7OVC * fichier)	// affichage de l'entete
{

printf
    ("\nles ceratcteristiques du fichier sont les suivantes\n--------------------------------------------");

printf ("le nombre total de bloc alloue est   %d\n", entete (fichier, 1));

printf ("l'entete du ficher se trouve au bloc    %d\n",
	   entete (fichier, 2));

printf ("la queue du ficher se trouve au bloc    %d\n",
	   entete (fichier, 3));

printf ("la position libre dans le bloc de queue est    %d\n",
	   entete (fichier, 4));

printf ("le nombre total de caractC(re supprime est    %d\n",
	   entete (fichier, 5));

}


//***************************fonction d'affichage*******************************************************************//



//***********************************fonction de verification de la cle******************************************************//
  int
nb_pos (int a)
{

int cpt = 1;

while ((a / 10) != 0)

    {

a = a / 10;

cpt++;

}

return (cpt);

}


int
cle_correct (int cle)
{

int correct = 0;

if (nb_pos (cle) > 5)


    {

puts ("cle n'est pas correct");

}

return (correct);


}


//*************************************************************************************************************************************//







void
chargement_initial (L7OVC * f)
{

int i, j;

int d;

FILE * g = NULL;

t_entete ent;

ouvrir (g, "tof.bin", 'N', &ent);

charg ();

parcours (g, "tof.bin", 1, 5);

    //chargement_initial_index(g,0.5,5);
    printf ("\n entrez lz nombre enregistrements ");

    //char *chaine;
    //chaine = malloc(sizeof(char)*50000);

scanf ("%d", &d);


    //strcpy(chaine,generer_enreg());
  int k = 0;

    //for (int i=0;i<d;i++)
    while (k < d)

    {

	//const char* g = generer_enreg();
	//strcat(chaine,g);
      char ch[256] = "";

char *r = enregistrement ();

strcpy (ch, r);

ch[strlen (ch)] = '\0';

char *chaine = &ch[0];

	//printf("\n//////////////////////////////////////////////////////%s",recup_ch(r,2));
	//insertion2_L7OVC(f,chaine,&i,&j);


ins ();

parcours (g, "tof.bin", 1, 5);

	/*printf("\n%d         ",atoi(recup_ch(chaine,2)));
	   printf("%d      %d",i,j); */

k++;

}
}





void

representation_graphique (L7OVC * fichier, int *i, int *j)//Afficher les inforamations liees au fichier
{				//printf("\nthis is it1");
  //int i=entete(fichier,2); // positionnement a la tete du fichier
  // positionnement au premier caractC(re
  int stop = 0;

Buffer buf;

printf
    ("\n\tles ceratcteristiques du fichier sont les suivantes\n--------------------------------------------");

printf ("\nle nombre total de bloc alloue est   %d\n", entete (fichier, 1));

printf ("\nl'entete du ficher se trouve au bloc    %d\n",
	   entete (fichier, 2));

printf ("\nla queue du ficher se trouve au bloc    %d\n",
	   entete (fichier, 3));

printf ("\nla position libre dans le bloc de queue est    %d\n",
	   entete (fichier, 4));

printf ("\nle nombre total de caractC(re supprime est    %d\n",
	   entete (fichier, 5));


liredir (fichier, *i, &buf);	// lecture du premier bloc
  printf ("\n\t");

for (int r = 0; r < 1030; r++)

    {

printf ("%c", buf.tab[r]);

}
printf ("\n");



}






















void

suppression_Logique_L7OVC2 (L7OVC * fichier, int *i, int *j,int choix)//changer le caractere de supppression dans l'enregistrement a la position donnee
{


Buffer buf;



    if (entete (fichier, 1) == 0)	// si la cle n'a  pas C)tC) trouvC) alors on insere dans le premier bloc
    aff_entete (fichier, 1, 1);

    liredir (fichier, *i, &buf);	// lecture du  bloc
  int temp = *i + (*j + 3) / max;


if (temp != *i)
    {

*i = buf.suivant;

}


*j = (*j % max + 4) % (max + 1);

   if(choix==1) representation_graphique (fichier, i, j);	//to see the current state of the file (the bloc where the structure starts)
  liredir (fichier, *i, &buf);	// lecture du  bloc
  if (buf.tab[*j] == 'N')
    {

buf.tab[*j] = 'O';

}

  else
    {

printf ("\n L'enregistrement n'existe pas!");

}

ecriredir (fichier, *i, &buf);



}



void
afficher_enreg (L7OVC * fichier, int i, int j)//Afficher l'enregistrement
{


int trouv = 0;

Buffer buf;

liredir (fichier, i, &buf);//recuperer le bloc

char c = buf.tab[j];

while (buf.tab[j] != '$')//refaire le traitement jusqua atteindre le caractere de fin
    {


c = buf.tab[j];

if (j < 1024)
	{

printf ("%c", c);


}
      else
	{

i++;

liredir (fichier, i, &buf);//recuperer le bloc suivant

j = -1;

}

j++;

}

printf ("$");


return;


}




char *
recup_enreg (L7OVC * fichier, int i, int j)//Recuperation de l'enregistrement au bloc i eta la position j
{


int trouv = 0;

Buffer buf;

char c[250];

int k = 0;


liredir (fichier, i, &buf);

while (buf.tab[j] != '$')//tant le caracterere de fin nest pas atteint dans le parcours on continue le traitement
    {


if (j < 1024)
	{


c[k] = buf.tab[j];

k++;


}
      else
	{

i++;

liredir (fichier, i, &buf);//recuperartion du bloc suivant

j = -1;

}

j++;

}


c[k] = '$';

c[k + 1] = '\0';//caractere de fin

char *fin = &c[0];


return fin;


}

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

