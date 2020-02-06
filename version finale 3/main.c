
#include "fonction.h"
#include <stdio.h>
#include <string.h>
#define MAX_LEN 128
#include "windows.h"

FILE * f = NULL;

FILE * h = NULL;

t_entete ent;

t_entete2 ent2;

tbloc buf;

tbloc2 buf2;
int lecture,ecriture;
int o;



void SetColor(int ForgC);
void info ();			// Affichage de l'entC*te
void rech ();			// Recherche d'un enregistrement :
long dicho (long val, int *trouv, long *i, int *j);	// par dichotomie ou
long seq (long val, int *trouv, long *i, int *j);	// par recherche sC)quentielle
void ins ();			// Insertion par decalages d'un enregistrement
void sup ();			// Suppression logique d'un enregistrement
void parcours ();		// Affichage d'une sequence de blocs contigus (entre a et b)
long seq_index2cle (long val, int *trouv, long *i, int *j);




//*************************************************************************************************************//


char *mois[13] =
  { "", "Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet",
"Aout", "Septembre", "Octobre", "Novembre", "Decembre" };

char *specialite[22] =
  { "Informatique", "Economie", "Architecture", "Medecine", "Pharmacie",
"Chirugie Dentaire", "Mathematiques", "Probabilites", "Electronique", "Mecanique",
"Genie civile", "Phylosophie", "Litterature anglaise", "Litterature francaise",
"Litterature arabe", "Litterature Amazighe", "Geologie", "Biologie", "Droit", "Astronomie",
"Physique", "Chimie" };

char *a[26] =
  { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
"p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };

char *wilaya[49] =
  { "", "Adrar", "Chlef", "Laghouat", "Oum El Bouaghi", "Batna", "Bejaia",
"Biskra", "Bechar", "Blida", "Bouira", "Tamanrasset", "Tebessa", "Tlemcen", "Tiaret",
"Tizi-Ouzou", "Alger", "Djelfa", "Jijel", "Setif", "Saida", "Skikda", "Sidi Bel Abbes",
"Annaba", "Guelma", "Constantine", "Medea", "Mostaganem", "M'sila", "Mascara", "Ouargla",
"Oran", "El Bayadh", "Illizi", "Bordj Bou Arreridj", "Boumerdes", "El Tarf", "Tindouf",
"Tissemsilt", "El Oued", "Khenchela", "Souk Ahras", "Tipaza", "Mila", "Ain Defla", "Naama",
"Ain Temouchent", "Ghardaia", "Relizane" };

char *sexe[2] = { "Masculin", "Feminin" };

char *groupe_Sanguin[8] =
  { "O+", "A+", "B+", "O-", "A-", "AB+", "B-", "AB-" };

char *Grade[6] =
  { "Professeur(e)", "Maitre de conferences rang A",
"Maitre de conferences rang B", "Maitre assistant(e) rang A",
"maitre assistant(e) rang B", "Assistant(e)" };

char *Dernier_Diplome[5] =
  { "Doctorat d'etat", "Doctorat en sciences", "PhD", "HDR", "Magistere" };













char *Etablissement_Univ_est[41] =
  { "", "Centre Universitaire de Barika-Si El Haoues",

"Universite de Bejaia-Abderrahmane Mira", "Universite de Blida 2-Lounici Ali",

"Ecole Superieure des Sciences Appliquees de Tlemcen",
"Centre Universitaire de Mila-Abdelhafid Boussouf",

"Centre Universitaire d Illizi-Cheikh Amoud ben Mokhtar",

"Centre universitaire de Tamanrasset-Amine Elokkal El Hadj Moussa Eg Akhamouk",

"Ecole normale superieure de Constantine-Assia Djebar",
"Ecole Superieure des Technologies Industrielles de Annaba",

"Ecole Superieure de Comptabilite et de Finance de Constantine",
"Ecole Superieure des Sciences de Gestion de Annaba",

"Ecole Superieure des Technologies Industrielles de Annaba",

"Ecole Nationale Superieure de Biotechnologie de Constantine-Tewfik Khaznadar",
"Universite de Batna 2-Mustapha Ben Boulaid",
"Universite de Constantine 3-Salah Boubnider",
"Universite de Constantine 2 - Abdelhamid Mehri",
"Universite de Constantine 1-Freres Mentouri", "Universite de Setif 1-Ferhat Abbas",

"Universite de Setif 2-Mohamed Lamine Debaghine", "Universite des sciences islamiques Emir Abdelkader de Constantine",

"Universite de Ouargla-Kasdi Merbah", "Universite de M sila - Mohamed Boudiaf", "Universite de Biskra-Mohamed Khider",
"Universite 8 Mai 1945 de Guelma",
"Universite du 20 Aout 1955 de Skikda", "Universite de Souk Ahras-Mohammed-Cherif Messaadia",
"Universite d El Oued-Hamma Lakhdar",
"Universite de Oum El Bouaghi-Larbi Ben M hidi", "Universite d El Tarf-Chadli Bendjedid",
"Universite de Bordj Bou Arreridj - Mohamed Bachir El Ibrahimi",
"Universite de Tebessa - Larbi Tebessi",
"Universite d Oran 2-Mohamed Ben Ahmed", "Universite de Bouira-Akli Mohand Oulhadj", "Universite de Ghardaia",
"Universite de Tizi Ouzou-Mouloud Maameri", "Universite de Bejaia-Abderrahmane Mira", "Universite de Boumerdes-M hamed Bougara",
"Ecole Nationale Polytechnique de Constantine-Malek Bennabi", "Ecole normale superieure de Ouargla",
"Ecole normale superieure de setif-Messaoud Zeghar", "Ecole normale superieure d enseignement technologique de Skikda"
};


char *Etablissement_Univ_ouest[37] =
  { "", "Centre universitaire d Aflou",

"Ecole Superieure d Informatique(Sidi Bel Abbes)-08 Mai 1945",

"Ecole Nationale Polytechnique d Oran-Maurice Audin", "Centre universitaire de Tipaza-Abdallah Morsli",

"Centre universitaire de Maghnia",
"Centre universitaire de Tindouf-Ali Kafi",
"Ecole normale superieure de Laghouat-Taleb Abderrahmane",
"Ecole normale superieure de Bechar",

"Ecole Normale Superieure d Oran", "Ecole Normale Superieure de Mostaganem",
"Ecole Superieure des sciences Biologiques d Oran",
"Ecole Superieure Agronomique de Mostaganem",
"Ecole Superieure d Economie d Oran", "Ecole Superieure d Economie d Oran",

"Ecole Superieure en Genie Electrique et Energetique d Oran", "Centre universitaire de Naama-Ahmed Salhi",
"Centre universitaire de Relizane-Ahmed Zabana",
"Centre Universitaire de Ain Temouchent-Belhadj Bouchaib",
"Centre Universitaire de Tissemsilt-Ahmed ben yahia el-wancharissi",
"Universite de Annaba-Badji Mokhtar",
"Universite Medea-Yahia Fares", "Universite de Saida-Tahar Moulay", "Universite de Bechar-Mohamed Tahri",

"Universite Mohamed Boudiaf des sciences et de la technologie-Mohamed Boudiaf d Oran",
"Universite d Oran1-Ahmed Ben Bella",
"Universite de Mostaganem-Abdelhamid Ibn Badis",
"Universite Sidi Bel Abbes-Djillali Liabes", "Universite de Tiaret-Ibn Khaldoun",

"Universite d Adrar-Ahmed Draya", "Universite de Tlemcen-Abou Bekr Belkaid",
"Universite de Mascara-Mustapha Stambouli",
"Universite de Laghouat-Amar Telidji",
"Universite Blida 1-Saad Dahlab", "Universite de Khemis Miliana-Djilali Bounaama",

"Universite de Chlef-Hassiba Benbouali", "Ecole normale superieure de Bou Saada",
"Ecole Superieure de Management de Tlemcen"
};


char *Etablissement_Univ_centre[28] =
  { "", "Ecole nationale superieure d hydraulique-Arbaoui Abdellah",

"Ecole nationale superieure des travaux publics-Francis Jeanson",

"Ecole nationale superieure veterinaire-Rabie Bouchama",

"Ecole Polytechnique d architecture et d Urbanisme-Hocine Ait Ahmed",

"Ecole nationale superieure agronomique-Khalef Abdellah alias Kasdi Merbah",

"Ecole nationale superieure de management", "Ecole Nationale Superieure de Technologie",

"Ecole Superieure des Sciences appliquees d Alger", "Universite d Alger 2-Abou el Kacem Saadallah",

"Ecole Superieure des Sciences de l Aliment et des Industries Agroalimentaires d Alger",

"Ecole nationale superieure des sciences de la mer et de l amenagement du littoral",

"Centre universitaire d El Bayadh-Nour Bachir",
"Ecole normale superieure de Kouba-Mohamed Bachir El Ibrahimi",

"Ecole normale superieure de Bouzareah-Cheikh Mubarak Ben Mohamed Brahimi El Mili",

"Ecole Nationale Polytechnique", "Universite de Khenchela-Abbas Laghrour",

"Universite d Alger 2-Abou el Kacem Saadallah", "Universite d Alger 1-Benyoucef Benkhedda",

"Universite de Djelfa-Ziane Achour", "Universite d Alger 3-Brahim Soltane Chaibout",

"Universite des sciences et de la technologie d Alger, Houari Boumediene",
"Ecole des hautes etudes commerciales",
"Ecole nationale superieure d informatique",

"Ecole nationale superieure en statistique et en economie appliquee",

"Ecole Superieure de Commerce-Mouloud Kacem Nait Belkacem",

"Ecole nationale superieure de journalisme et des sciences de l information",

"Ecole Nationale Superieure des sciences politiques",

"Ecole nationale superieure des mines et de la metallurgie-Amar Laskri"
};





char *Etablissement_Univ[106] =
  { "", "Universite de Bechar-Mohamed Tahri",
"Universite de Mascara-Mustapha Stambouli", "Universite de Saida-Tahar Moulay",
"Universite de Tlemcen-Abou Bekr Belkaid", "Universite d Adrar-Ahmed Draya",
"Universite de Tiaret-Ibn Khaldoun", "Universite Sidi Bel Abbes-Djillali Liabes",
"Universite de Mostaganem-Abdelhamid Ibn Badis", "Universite d Oran1-Ahmed Ben Bella",
"Universite Mohamed Boudiaf des sciences et de la technologie-Mohamed Boudiaf d Oran",
"Universite d Oran 2-Mohamed Ben Ahmed", "Universite de Bouira-Akli Mohand Oulhadj",

"Universite de Djelfa-Ziane Achour", "Universite de Ghardaia",
"Universite de Khemis Miliana-Djilali Bounaama", "Universite Medea-Yahia Fares",
"Universite des sciences et de la technologie d Alger, Houari Boumediene",
"Universite de Bejaia-Abderrahmane Mira", "Universite de Chlef-Hassiba Benbouali",
"Universite de Boumerdes-M hamed Bougara", "Universite de Tizi Ouzou-Mouloud Maameri",
"Universite de Laghouat-Amar Telidji", "Universite Blida 1-Saad Dahlab", "Universite de Blida 2-Lounici Ali",
"Universite d Alger 1-Benyoucef Benkhedda", "Universite d Alger 2-Abou el Kacem Saadallah",

"Universite d Alger 3-Brahim Soltane Chaibout", "Universite de la Formation Continue",
"Universite de la Formation Continue", "Universite de Tebessa - Larbi Tebessi",
"Universite de Bordj Bou Arreridj - Mohamed Bachir El Ibrahimi", "Universite d El Tarf-Chadli Bendjedid",
"Universite de Khenchela-Abbas Laghrour", "Universite de Oum El Bouaghi-Larbi Ben M hidi",
"Universite d El Oued-Hamma Lakhdar", "Universite de Souk Ahras-Mohammed-Cherif Messaadia",
"Universite de Annaba-Badji Mokhtar", "Universite du 20 Aout 1955 de Skikda",
"Universite 8 Mai 1945 de Guelma", "Universite 8 Mai 1945 de Guelma",
"Universite de Biskra-Mohamed Khider",
"Universite de M sila - Mohamed Boudiaf", "Universite de Ouargla-Kasdi Merbah",
"Universite des sciences islamiques Emir Abdelkader de Constantine", "Universite de Setif 1-Ferhat Abbas",
"Universite de Setif 2-Mohamed Lamine Debaghine", "Universite de Constantine 1-Freres Mentouri",
"Universite de Constantine 2 - Abdelhamid Mehri", "Universite de Constantine 3-Salah Boubnider",
"Universite de Batna 2-Mustapha Ben Boulaid",
"Centre Universitaire de Tissemsilt-Ahmed ben yahia el-wancharissi",
"Centre Universitaire de Ain Temouchent-Belhadj Bouchaib", "Centre universitaire de Relizane-Ahmed Zabana",

"Centre universitaire de Naama-Ahmed Salhi", "Centre universitaire d El Bayadh-Nour Bachir",
"Centre universitaire de Tindouf-Ali Kafi", "Centre universitaire de Maghnia",
"Centre universitaire de Tamanrasset-Amine Elokkal El Hadj Moussa Eg Akhamouk",
"Centre universitaire de Tipaza-Abdallah Morsli", "Centre Universitaire d Illizi-Cheikh Amoud ben Mokhtar",
"Centre universitaire d Aflou", "Centre Universitaire de Mila-Abdelhafid Boussouf",
"Centre Universitaire de Barika-Si El Haoues", "Ecole Nationale Polytechnique d Oran-Maurice Audin",
"Ecole Superieure d Informatique(Sidi Bel Abbes)-08 Mai 1945",
"Ecole Superieure des Sciences Appliquees de Tlemcen",
"Ecole Superieure de Management de Tlemcen",
"Ecole Superieure d Economie d Oran", "Ecole Superieure en Genie Electrique et Energetique d Oran",
"Ecole Superieure Agronomique de Mostaganem", "Ecole Superieure des sciences Biologiques d Oran",
"Ecole Nationale Polytechnique", "Ecole nationale superieure d hydraulique-Arbaoui Abdellah",
"Ecole nationale superieure des travaux publics-Francis Jeanson",
"Ecole nationale superieure veterinaire-Rabie Bouchama",
"Ecole Polytechnique d architecture et d Urbanisme-Hocine Ait Ahmed",
"Ecole nationale superieure agronomique-Khalef Abdellah alias Kasdi Merbah",
"Ecole des hautes etudes commerciales",
"Ecole nationale superieure d informatique",
"Ecole nationale superieure en statistique et en economie appliquee",
"Ecole Superieure de Commerce-Mouloud Kacem Nait Belkacem",
"Ecole nationale superieure des sciences de la mer et de l amenagement du littoral",
"Ecole nationale superieure de management", "Ecole Nationale Superieure de Technologie",
"Ecole nationale superieure de journalisme et des sciences de l information",
"Ecole Nationale Superieure des sciences politiques",
"Ecole Superieure des Sciences de l Aliment et des Industries Agroalimentaires d Alger",
"Ecole Superieure des Sciences appliquees d Alger",
"Ecole nationale superieure des mines et de la metallurgie-Amar Laskri",

"Ecole Nationale Polytechnique de Constantine-Malek Bennabi",
"Ecole Nationale Superieure de Biotechnologie de Constantine-Tewfik Khaznadar",
"Ecole Superieure des Sciences de Gestion de Annaba",
"Ecole Superieure des Technologies Industrielles de Annaba",
"Ecole Superieure de Comptabilite et de Finance de Constantine", "Ecole Normale Superieure de Mostaganem",
"Ecole Normale Superieure d Oran", "Ecole normale superieure de Bechar",
"Ecole normale superieure de Bouzareah-Cheikh Mubarak Ben Mohamed Brahimi El Mili",
"Ecole normale superieure de Kouba-Mohamed Bachir El Ibrahimi",
"Ecole normale superieure de Laghouat-Taleb Abderrahmane",
"Ecole normale superieure de Constantine-Assia Djebar",

"Ecole normale superieure d enseignement technologique de Skikda",
"Ecole normale superieure de setif-Messaoud Zeghar", "Ecole normale superieure de Bou Saada",
"Ecole normale superieure de Ouargla"
};




  // retourne aussi le nombre de lecture de blocs effectuCB)s.
  long
dicho56 (long val, int *trouv, long *i, int *j)
{

long bi, bs, cpt;

int stop, inf, sup;

bi = 1;

bs = ent.nb_bloc;

*trouv = 0;

stop = 0;

cpt = 0;			// compteur de lectures physiques
  while (bi <= bs && !*trouv && !stop)
    {

*i = (bi + bs) / 2;	// le milieu entre bi et bs
      lecture++;
      lireDir (f, *i, &buf);
      cpt++;			// lecture du bloc du milieu
      if (val < buf.tab[0].cle)

bs = *i - 1;		// la recherche contiue dans la 1ere moitiCB)
      else

if (val > buf.tab[buf.nb - 1].cle)

bi = *i + 1;		// la recherche contiue dans la 2eme moitiCB)
      else
	{

stop = 1;		// recherche interne dans buf (bloc du milieu)
	  inf = 0;

sup = buf.nb - 1;

while (inf <= sup && !*trouv)
	    {

*j = (inf + sup) / 2;

if (val == buf.tab[*j].cle)
		*trouv = 1;

	      else

if (val < buf.tab[*j].cle)

sup = *j - 1;

	      else

inf = *j + 1;

}			// while interne
	  if (inf > sup)
	    *j = inf;

}

}				// while externe
  if (bi > bs)
    {

*i = bi;

*j = 0;

}


return cpt;


}






void
dicho_L7OVC (long val, int *trouv, int *bloc, int *pos, int choix)
{

long bi, bs;

int stop, inf, sup, i, j;

bi = 1;

bs = ent.nb_bloc;

*trouv = 0;

stop = 0;


j = 1;			// compteur de lectures physiques
  while (bi <= bs && !*trouv && !stop)
    {

i = (bi + bs) / 2;	// le milieu entre bi et bs
lecture++;
      lireDir (f, i, &buf);	// lecture du bloc du milieu
      if (val < buf.tab[0].cle)

bs = i - 1;		// la recherche contiue dans la 1ere moitie
      else

if (val > buf.tab[buf.nb - 1].cle)

bi = i + 1;		// la recherche contiue dans la 2eme moitie
      else
	{

stop = 1;		// recherche interne dans buf (bloc du milieu)
	  inf = 0;

sup = buf.nb - 1;

while (inf <= sup && !*trouv)
	    {

j = (inf + sup) / 2;

if ((val == buf.tab[j].cle) && (buf.eff[j] != '*'))
		{


*trouv = 1;

*bloc = buf.tab[j].bloc;

*pos = buf.tab[j].pos;

if (choix == 1)
		    {

buf.eff[j] = '*';
ecriture++;
ecrireDir (f, i, &buf);

}


}

	      else

if (val < buf.tab[j].cle)

sup = j - 1;

	      else

inf = j + 1;

}			// while interne
	  if (inf > sup)
	    j = inf;

}

}				// while externe
  if (bi > bs)
    {

i = bi;

j = 0;

}


    /* if(var1!=*bloc){
     *trouv=0;
     }*/

}				// dicho





char *
entrez (int *j,int *cle2)
{

char c[2500] = "";

char t[50];

int m;

strcat (c, "#N#");

traitement1 :
printf ("\nEntrez un matricule : ");

scanf ("%d", &m);

char v[256];

char *rr = itoa (m, v, 10);

if (strlen(rr) != 6) {
        SetColor(4);
        printf("\nLE MATRICULE DOIT CONTENIR 6 CHIFRES.");
        SetColor(10);
        goto traitement1;
}

strcat (c, rr);

strcat (c, "#");

printf ("\nEntrez un nom : ");

scanf ("%s", t);

char *kl = &t[0];

strcat (c, kl);

strcpy (t, "");

printf ("\nEntrez un prenom : ");

scanf ("%s", t);

kl = &t[0];

strcat (c, "#");

strcat (c, kl);

strcat (c, "#");

strcpy (v, "");
int r;

printf ("\nEntrez le jour de naissance : ");

scanf ("%d", &m);

rr = itoa (m, v, 10);

strcat (c, rr);

strcat (c, "/");
traitement:
printf ("\nEntrez le mois de naissance : ");

strcpy (t, "");

scanf ("%d", &r);

if (r == 2 && (m == 30 || m == 31)) {
        SetColor(4);
        printf("`\nERREUR! FEVRIER NE CONTIENT PAS LE 30 OU LE 31\n");
        SetColor(10);
goto traitement;}

rr = itoa (r, v, 10);

strcat (c, rr);

strcat (c, "/");

c[strlen (c)] = '\0';

strcpy (v, "");

traitement2:
printf ("Entrez l'annee de naissance : ");

scanf ("%d", &m);


if (m < 1953) { SetColor(4);
        printf("\nERREUR! L'ENSEIGNANT QUE VOUS ETES ENTRAIN D'INSERER NE SERA PAS CAPABLE D'ENSEIGNER... IL DOIT REPOSER.\n");
        SetColor(10);
        goto traitement2;}

rr = itoa (m, v, 10);

strcat (c, rr);

strcat (c, "#");

int anneenaissance = m;

int numwilaya;
strcpy(t,"");

printf ("\nEntrez le numero de la wilaya : ");

scanf ("%d", &numwilaya);

strcpy(t,wilaya[numwilaya]);
kl = &t[0];
strcat (c, kl);
strcat (c, "#");

traitement4:
printf ("\nEntrez le sexe : ");
printf ("\n\t1 - Masculin");
printf ("\n\t2 - Feminin");
printf ("\nChoisissez le num qui convient : ");

int nsex;
scanf ("%d", &nsex);
if (nsex == 1) {strcpy(t,"Masculin");}
else { if (nsex == 2) { strcpy(t,"Feminin");}
        else {
        SetColor(4);
        printf("\nERREUR! LE CHIFFRE N'EXISTE PAS. REESSAYEZ S.V.P.\n");
        SetColor(10);
        goto traitement4;
        }
    }




strcat (c, t);

strcat (c, "#");
strcpy (t, "");
int gpesang;

traitement6:
printf ("\nEntrez le groupe sanguin : ");
printf ("\n\t1 - O+");
printf ("\n\t2 - O-");
printf ("\n\t3 - A+");
printf ("\n\t4 - A-");
printf ("\n\t5 - B+");
printf ("\n\t6 - B-");
printf ("\n\t7 - AB+");
printf ("\n\t8 - AB-");
printf ("\nChoisissez le chiffre qui convient : ");


scanf("%d", &gpesang);

switch (gpesang) {
    case 1: strcpy(t,"O+");break;
    case 2: strcpy(t,"O-");break;
    case 3: strcpy(t,"A+");break;
    case 4: strcpy(t,"A-");break;
    case 5: strcpy(t,"B+");break;
    case 6: strcpy(t,"B-");break;
    case 7: strcpy(t,"AB+");break;
    case 8: strcpy(t,"AB-");break;
    default: {
    SetColor(4);
    printf("\nERREUR! CHOISISSEZ UN CHIFFRE QUI EXISTE S.V.P.");        SetColor(4);
    SetColor(10);
    goto traitement6;
    } break;
}



rr = &t[0];

strcat (c, rr);

strcat (c, "#");

printf ("Entrez le jour de recrutement: ");

scanf ("%d", &m);

rr = itoa (m, v, 10);

strcat (c, rr);

strcat (c, "/");

traitement5:
printf ("Entrez le mois de recrutement : ");

strcpy (t, "");

scanf ("%d", &r);

if (r == 2 && (m == 30 || m == 31)) {
        SetColor(4);
        printf("`\nERREUR! FEVRIER NE CONTIENT PAS LE 30 OU LE 31\n");
        SetColor(10);
goto traitement5;}

rr = itoa (r, v, 10);

strcat (c, rr);

strcat (c, "/");

c[strlen (c)] = '\0';

strcpy (v, "");

traitement7:
printf ("Entrez l'annee de recrutement : ");

scanf ("%d", &m);


if (m < 1980 || m>2020 || m < anneenaissance+25) { SetColor(4);
        printf("\nERREUR! CET ENSEGNANT NE PEUT PAS ENCORE TRAVAILLER... ENTREZ UNE ANNEE VALIDE!\n");
        SetColor(10);
        goto traitement7;
}

rr = itoa (m, v, 10);



strcat (c, rr);

strcat (c, "#");
strcpy (t, "");
int gradee;

traitement8:
printf ("Entrez le grade : ");
printf ("\n\t1 - Professeur(e)");
printf ("\n\t2 - Maitre de conferences rang A");
printf ("\n\t3 - Maitre de conferences rang B");
printf ("\n\t4 - Maitre assistant(e) rang A");
printf ("\n\t5 - Maitre assistant(e) rang B");
printf ("\n\t6 - Assistant(e)");
printf ("\nChoisissez le chiffre qui convient : ");


scanf ("%d",&gradee);
switch (gradee) {
    case 1: strcpy(t,"Professeur(e)");break;
    case 2: strcpy(t,"Maitre de conferences rang A");break;
    case 3: strcpy(t,"Maitre de conferences rang B");break;
    case 4: strcpy(t,"Maitre assistant(e) rang A");break;
    case 5: strcpy(t,"Maitre assistant(e) rang B");break;
    case 6: strcpy(t,"Assistant(e)");
    default: {
    SetColor(4);
    printf("\nERREUR! CHOISISSEZ UN CHIFFRE QUI EXISTE S.V.P.");
    SetColor(10);
    goto traitement8;
    }break;
}


rr = &t[0];

strcat (c, rr);

strcat (c, "#");

afficher_specialite ();

printf("\nChoisissez le chiffre qui convient : ");

strcpy (t, "");
int numspecialite;
*cle2=numspecialite;
scanf("%d", &numspecialite);
strcpy(t,specialite[numspecialite]);
rr = &t[0];

strcat (c, rr);

strcat (c, "#");

int numdiplome;
traitement9 :
printf ("\nEntrez le dernier diplome : ");
printf ("\n\t1 - Doctorat D'Etat");
printf ("\n\t2 - Doctorat en sciences");
        printf ("\n\t3 - PhD");
printf ("\n\t4 - HDR");
printf ("\n\t5 - Magistere");
printf ("\nEntrez le chiffre qui convient : ");
strcpy (t, "");
scanf("%d", &numdiplome);

switch (numdiplome) {
    case 1: strcpy(t,"Doctorat D'Etat");break;
    case 2: strcpy(t,"Doctorat en sciences");break;
    case 3: strcpy(t,"PhD");break;
    case 4: strcpy(t,"HDR");break;
    case 5: strcpy(t,"Magistere");break;
    default:{
        SetColor(4);
        printf("\nERREUR! CHOISISSEZ UN CHIFFRE QUI EXISTE S.V.P.");
        SetColor(10);
        goto traitement9;
    }break;
}

rr = &t[0];

strcat (c, rr);

strcat (c, "#");


int numuniv;


afficher_univ ();
printf("\nEntrez le nombre qui convient : ");
strcpy (t, "");
scanf("%d",&numuniv);
*j=numuniv;
strcpy(t,Etablissement_Univ[numuniv]);
rr = &t[0];
strcat(c,rr);
strcat(c,"#");
strcat (c, "$");
c[strlen (c)] = '\0';



char *h = &c[0];

return h;

}


char *
entr (char *h)
{

char d[1500] = "";

strcat (d, h);

int k = strlen (d);

char v[1500] = "";

char l[50] = "";

char *hh = itoa (k, l, 10);

char *kv = &d[0];

strcat (v, hh);

strcat (v, kv);

char *rp = &v[0];

return rp;

}










void afficher_univ ()
{

int e;

printf ("\n Choissisez la region de travail :    1)est   2) ouest   3)centre");
printf ("\n Entrez le chiffre qui convient : ");
scanf ("%d", &e);


    //printf("\n Choisir l'index correspandant a l'etablisment volu  ");
if (e == 1)
{
for (int i = 0; i < 41; i++)
	{

printf ("\n %d - %s", etablissment_num (Etablissement_Univ_est[i]),
		   Etablissement_Univ_est[i]);
    }
}
  else if (e == 2)
{
for (int i = 0; i < 37; i++)
	{
printf ("\n %d - %s", etablissment_num (Etablissement_Univ_ouest[i]),
		   Etablissement_Univ_ouest[i]);
    }
}
  else
    {
      for (int i = 0; i < 28; i++)
        {
printf ("\n %d - %s",
		   etablissment_num (Etablissement_Univ_centre[i]),
		   Etablissement_Univ_centre[i]);
        }
    }
}


void afficher_specialite ()
{

printf ("\n Choisir la specialite :");

for (int i = 0; i < 22; i++)
    {

printf ("\n %d - %s  ", i, specialite[i]);

}


}



int region (int etablissment)
{

for (int u = 0; u < 41; u++)
    {

if (Etablissement_Univ_est[u] == Etablissement_Univ[etablissment])
	return 0;

}

for (int u = 0; u < 28; u++)
    {

if (Etablissement_Univ_centre[u] == Etablissement_Univ[etablissment])
	return 1;

}

for (int u = 0; u < 37; u++)
    {

if (Etablissement_Univ_ouest[u] == Etablissement_Univ[etablissment])
	return 2;

}


return 45;

}


int etablissment_num (char *etablissment)
{

for (int h = 0; h < 106; h++)
    {

if (Etablissement_Univ[h] == etablissment)
	return h;


    }
}



int specialite_index (char *sp)
{

for (int h = 0; h < 22; h++)
    {

if (specialite[h] == sp)
	return h;

return 2;


}



}



char * nom ()
{
char k[256];

int i;

int t = rand () % 27 + 4;

for (i = 0; i < t; i++)

    {

k[i] = rand () % 26 + 97;

}

k[t] = '\0';

char *d = &k[0];

return d;

}


char * prenom ()
{

char k[256];

int i;

int t = rand () % 27 + 4;

for (i = 0; i < t; i++)

    {

k[i] = rand () % 26 + 97;

}

k[t] = '\0';

char *d = &k[0];

return d;

}


char * grade ()
{

return Grade[rand () % 6];

}


int generer_matricule ()
{

int i;

int j;

boucle:

j = rand () % 9 + 1;

for (i = 0; i < 5; i++)

    {

j = j * 10 + rand () % 10;

}

if (j < 111111)

    {

goto boucle;

}

return j;

}


int
bissextile (int annee)
{

if (annee % 4 == 0 && annee % 100 != 0)

    {

return 0;

}

  else

    {

if (annee % 400 == 0)

	{

return 0;

}

      else
	{

return 1;

}

}

}



int
generer_annee_naissance ()
{

return (rand () % 41 + 1953);

}



int
jour (int a, int k)
{


int c;



if ((k == 1) || (k == 3) || (k == 5) || (k == 7) || (k == 8)
	   || (k == 10) || (k == 12))

    {

c = rand () % 31 + 1;

}

  else

    {

if ((k == 4) || (k == 6) || (k == 9) || (k == 11))

	{

c = rand () % 30 + 1;

}

      else

	{

if (bissextile (a) == 0)

	    {

c = rand () % 29 + 1;

}

	  else

	    {

c = rand () % 28 + 1;

}

}

}

return c;



}




char *
wil ()
{

return (wilaya[rand () % 48 + 1]);

}


int
annee_recrutement ()
{

return rand () % 40 + 1980;

}


int
special ()
{

return rand () % 22;

}



char *
generer_sexe ()
{

return sexe[rand () % 2];

}


char *
generer_groupe_sanguin ()
{

return groupe_Sanguin[rand () % 8];

}


char *
matricule ()
{

int b = generer_matricule ();

char c[256];

char *a = itoa (b, a, 10);

return a;

}


char *
generer_dernier_diplome ()
{

return Dernier_Diplome[rand () % 5];

}





char *
generer_etablissement ()
{

return Etablissement_Univ[rand () % 105 + 1];

}



char *
generer_enreg (int *num, int *num2, int *num3)
{

char c[1500] = "";

char t[50];

int m = generer_matricule ();

int moi = rand () % 12 + 1;

int annee;

bcl:annee = generer_annee_naissance ();

int na = annee_recrutement ();

char nnn[256] = "";

char *nnnn = itoa (na, nnn, 10);

if (na < annee + 23)

    {

goto bcl;

}

int jr = jour (annee, moi);

char jp[256] = "";

char *jj = itoa (jr, jp, 10);

char an[256] = "";

char *ann = itoa (annee, an, 10);

char mt[256] = "";

char *mat = itoa (m, mt, 10);

char *a = nom ();

int i = 0;

strcat (c, mat);


strcat (c, "#");

strcat (c, a);

strcat (c, "#");

strcat (c, prenom ());

strcat (c, "#");

strcat (c, jj);

int mo = rand () % 12 + 1;

jr = jour (na, mo);

char jk[256] = "";

char *jjj = itoa (jr, jk, 10);

strcat (c, "/");

strcat (c, mois[mo]);

strcat (c, "/");

strcat (c, ann);

strcat (c, "#");

strcat (c, wil ());

strcat (c, "#");

strcat (c, generer_sexe ());

strcat (c, "#");

strcat (c, jjj);

strcat (c, "/");

strcat (c, mois[moi]);

strcat (c, "/");

strcat (c, nnnn);

strcat (c, "#");

strcat (c, grade ());

strcat (c, "#");

*num3 = special ();

strcat (c, specialite[*num3]);

strcat (c, "#");

strcat (c, generer_dernier_diplome ());

strcat (c, "#");

strcat (c, generer_etablissement ());

*num = etablissment_num (generer_etablissement ());

*num2 = 2019 - annee_recrutement ();

strcat (c, "$");

while (c[i] != '$')

    {

i++;

}

i++;

c[i] = '\0';



char *fin = &c[0];


return fin;

}


char *
enregistrement (int *num, int *num2, int *num3)
{

char fin[1500] = "";

char *a = generer_enreg (num, num2, num3);

int b = strlen (a);

char k[100];

char *bb = itoa (b, k, 10);

int i = 0;

strcat (fin, bb);

strcat (fin, "#");

strcat (fin, "N");

strcat (fin, "#");

strcat (fin, a);

strcat (fin, "$");

while (fin[i] != '\0')

    {

i++;

}

fin[i] = '\0';

char *l = &fin[0];

return l;

}


char *
recupmat (char *a)
{

char c[256] = "";

    //= enregistrement();
    strcat (c, a);

c[strlen (c)] = '\0';

char d[256] = "";

int j = 0;

int i = 0;

for (i = 6; i < 21; i++)

    {

d[j] = c[i];

j++;

}

d[6] = '\0';

char *t = &d[0];

return t;

}



char *
recup_ch (char *a, int n)
{


char b[256] = "";

char c[256] = "";

strcpy (b, a);

b[strlen (b)] = '\0';

int j = 0;

int k = 0;

while (b[k] != '\0')

    {

if (j == n)

	{

goto tr;

}

if (b[k] == '#')

	{

j++;

}

k++;

}

int s;

tr:s = k;

int p = j;

while (b[s] != '\0')

    {

if (p == n + 1)

	{

goto sort;

}

if (b[s] == '#')

	{

p++;

}

s++;

}

int i;

sort:for (i = k; i < s - 1; i++)

    {

char h = b[i];

char *m = malloc (2 * sizeof (char));

m[0] = h;

m[1] = '\0';

strcat (c, m);

	//o=o+1;
    }
c[strlen (c)] = '\0';

char *l = &c[0];

return l;

}


char *
recup_etablissement (char *a)
{

char b[256] = "";

char c[256] = "";

strcpy (b, a);

b[strlen (b)] = '\0';

int j = 0;

int k = 0;

while (b[k] != '\0')

    {

if (j == 12)

	{

goto sort;

}

if (b[k] == '#')

	{

j++;

}

k++;

}

int i;

sort:for (i = k; i < strlen (b) - 1; i++)

    {

char h = b[i];

char *m = malloc (2 * sizeof (char));

m[0] = h;

m[1] = '\0';

strcat (c, m);

	//o=o+1;
    }
c[strlen (c)] = '\0';

char *l = &c[0];

return l;

}



char *
nom_region (int k)
{

if (k == 0)
    return "Est";

if (k == 1)
    return "Centre";

  else
    return "Ouest";

}


void
print_image (FILE * fptr)
{

char read_string[MAX_LEN];


while (fgets (read_string, sizeof (read_string), fptr) != NULL)

printf ("%s", read_string);

}


int
main ()
{
    SetColor(10);               //Function call to change the text color


char *filename = "image.txt";

FILE * fptr = NULL;


if ((fptr = fopen (filename, "r")) == NULL)

    {

fprintf (stderr, "error opening %s\n", filename);

return 1;

}


print_image (fptr);


fclose (fptr);

printf ("\n");







printf (" \t\t\t%s",

"            @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"           @           ____________________________________________________________________           @\n");

Sleep (100);

printf (" \t\t\t%s",

"          @@@         |                                                                    |         @@@\n");

Sleep (100);

printf (" \t\t\t%s",

"         @@@@@        |                            TP 02                                   |        @@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"        @@@@@@@       |                                                                    |       @@@@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"       @@@@@@@@@      |                                                                    |      @@@@@@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"      @@@@@@@@@@@     |          MANIPULATION DE STRUCTURES DE FICHIERS SIMPLES            |     @@@@@@@@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"     @@@@@@@@@@@@@    |                                                                    |    @@@@@@@@@@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"      @@@@@@@@@@@     |                                                                    |     @@@@@@@@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"       @@@@@@@@@      |                                                                   |      @@@@@@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"        @@@@@@@       |                                                                   |       @@@@@@@\n");

Sleep (100);


printf (" \t\t\t%s",

"         @@@@@        |                                                                    |        @@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"          @@@         |____________________________________________________________________|         @@@\n");

Sleep (100);

printf (" \t\t\t%s",

"           @                                                                                          @\n");

Sleep (100);

printf (" \t\t\t%s",

"            @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

Sleep (100);

printf (" \t\t\t%s",

"                                                                                            \n");

Sleep (100);

printf (" \t\t\t%s",

"                                                                                            \n");

printf (" \t\t\t%s",

"                                                                                            \n");




srand (time (NULL));

int choix, i;

char nom[20], mode[20], temp2[1500];

int temp;

int matricule;

    // char *chaine;
  int annee, jour, mois;

int k, pi, cle, re, se;

int bloc2, pos2;

int num;

int minimum, maximum;

int val;

int status;

int cle1, cle2, cle3;



printf
    ("\n\tCapacite maximale des blocs = %d enregistrements (en considerons la taille minimale pour chaque enregistrement )\t",
     10);

printf ("\n\tTaille d'un bloc = %ld \tTaille entete = %ld\n\n",
	   sizeof (Tbloc) - 4, sizeof (entete));


char etablissment[50];

    // Ouverture du fichier ...
  int nombre;


printf ("\n\t Operation de chargement initial ");

printf
    ("\n\t Veuillez introduire le nombre d'enregistrement que vous voulez inserer  :");

status = scanf ("%d", &nombre);    /**************Boucle utilise pour empecher l'utilisateur de faire passer un caractC(re non-numerique C  la machine*************/

while (status != 1)

    {

while ((temp = getchar ()) != EOF && temp != '\n');

printf ("\n\n\tVeuillez introduire une valeur valide  !  : ");

status = scanf ("%d", &nombre);

}



ouvrir (&f, "fichierindex1.bin", 'N', &ent);

ouvrir (&h, "fichierindex2.bin", 'N', &ent2);

    //charg();
    L7OVC * g = ouvrir_L7OVC ("MESRES.bin", 'n');

    //L7OVC *h= ouvrir_L7OVC("fichier.bin",'n' );
  int tr;

k = 1;

pi = 1;

int num2;

int num3;

enreg moule;



for (int l = 0; l < nombre; l++)
    {

char ch[256] = "";

char *r = enregistrement (&num, &num2, &num3);

	//printf("\n%s",recup_etablissement( enregistrement()));
	//printf("\n%d",num);

strcpy (ch, r);

ch[strlen (ch)] = '\0';

char *chaine = &ch[0];

matricule = atoi (recup_ch (chaine, 2));

enreg moule;

moule.cle = matricule;

moule.bloc = k;

moule.pos = pi;

moule.region = region (num);

moule.eff = 0;



ins (moule);


enreg2 moule2;

moule2.Etablissement = num;

moule2.bloc = k;

moule2.pos = pi;

moule2.cle = matricule;

moule2.anciente = num2;

moule2.eff = 0;

moule2.specialite = num3;


ins2 (moule2);

insertion2_L7OVC (g, chaine, &k, &pi);



 o=pi;
}
afficher_entete (g);



printf ("\n\t Operation reussite ");



char *v;

char *h;


    // Menu principal ...



menu:


printf
  ("\n\n\t---------------------------- M E N U -------------------------------------\n");

Sleep (50);
printf ("\n\t1)  Ajout d'un nouveau enseignant  \n");
printf ("\n\t2) Modification de l etablissment d'un enseignant (suite a une mutation) \n");
printf ("\n\t3) Suppression d'un enseignant par matricule\n");
printf ("\n\t4) Supppression par specialite   \n");
printf("\n\t5) Recherche composee a deux criteres (requete a intervalle) \n");
printf ("\n\t6) Affichage des enseignants par region \n");

printf ("\n\t    Options supplementaires : \n");
printf ("\n\t\t8) Recherche d'un element dans la structure \n");
printf ("\n\t\t9) Afficher l'entete du fichier index\n");
printf ("\n\t\t10)  nombre de lecture/ecriture initial \n");
printf ("\n\t\t11) Affichage de bloc(s) (de la structure table index 2) \n");
printf ("\n\t\t12) Affichage de bloc(s) (de la structure table index 1)\n");
printf ("\n\t\t13) Representation graphique d'un bloc en L7ovc  \n");

















printf ("\n\t0) Quitter le programme\n");

printf ("\n\n\t    Votre choix s'il vous plait : ");



int iChoix;

int temp1;


status = scanf ("%d", &iChoix);	      /**************Boucle utilise pour empecher l'utilisateur de faire passer un caractC(re non-numerique C  la machine*************/

while (status != 1)

    {

while ((temp1 = getchar ()) != EOF && temp1 != '\n');

printf ("\n\n\tVeuillez introduire une valeur valide  !  : ");

status = scanf ("%d", &iChoix);

}

switch (iChoix)
    {

case 9:
      info ();
      break;

case 12:
      parcours (ent);
      break;

	// case 3: ins(); break;
	//case 4: sup_index1(); break;
	//case 5: parcours(ent); break;
	//case 6: reorg(); break;


case 11:

system ("cls");



printf ("%s",
		   "\n--------------------------------------------------------------------------------------------\n");


parcours2 (ent2);

	//sup_index2();
	//parcours2(ent2);

break;

case 7:

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


	//afficher_entete(g);
	printf ("Donnez la cle de recherche ");

scanf ("%d", &cle);

dicho_L7OVC (cle, &tr, &bloc2, &pos2, 0);


if (tr == 1)
	{

printf ("\nLe Bloc  : %d     La position dans le bloc : %d", bloc2,
		   pos2);

int f1 = bloc2;

int f2 = pos2;

	    //afficher_fichier3(&f1,&f2);
	}
      else
	{

SetColor(4);
printf ("\n La cle est non existante vous devez l'inserer a la fin");
SetColor(10);


}


printf ("%s",
		 "\n--------------------------------------------------------------------------------------------\n");



break;

case 8:

system ("cls");

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


	//afficher_entete(g);
	printf ("Donnez la cle de recherche ");



status = scanf ("%d", &cle);

while (status != 1)

	{

while ((temp = getchar ()) != EOF && temp != '\n');
SetColor(4);
printf ("\n\n\tVeuillez introduire une valeur valide  !  : ");
SetColor(10);

status = scanf ("%d", &cle);

}

dicho_L7OVC (cle, &tr, &bloc2, &pos2, 0);


if (tr == 1)
	{

printf ("\nLe Bloc  : %d     La position dans le bloc : %d", bloc2,
		   pos2);

int f1 = bloc2;

int f2 = pos2;

	    //afficher_fichier3(&f1,&f2);
	}
      else
	{
SetColor(4);

printf("\n La cle est non existante vous devez l'inserer a la fin");
SetColor(10);

}


printf ("%s",
		 "\n--------------------------------------------------------------------------------------------\n");


break;

case 10:
    printf("Le nombre de lecture : %d       Le nombre d'ecriture : %d",lecture,ecriture);
    break;

case 13:

system ("cls");

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


printf ("\n Inserez le numero du bloc a representer  :");



status = scanf ("%d", &k);


while (status != 1)

	{

while ((temp = getchar ()) != EOF && temp != '\n');
SetColor(4);

printf ("\n\n\tVeuillez introduire un nombre valide  !  : ");
SetColor(10);

status = scanf ("%d", &nombre);

}
      if (entete (g, 3) < k+1)
	{
SetColor(4);

printf
	    ("\n\t  Le nombre de bloc insere est superieure au nombre de bloc (le dernier bloc est affiche par defaut)\n");
	    SetColor(10);


k = entete (g, 3);

}

int rr = 1;

representation_graphique (g, &k, &rr);


printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


break;


case 3:

system ("cls");


bloc2 = 1;

pos2 = 1;

printf
	("\n\tDonnez le Matricule de l'enseignant que vous voulez supprimer  ");


status = scanf ("%d", &cle);


while (status != 1)

	{

while ((temp = getchar ()) != EOF && temp != '\n');

printf ("\n\n\tVeuillez introduire un nombre valide  !  : ");

status = scanf ("%d", &nombre);

}


dicho_L7OVC (cle, &tr, &bloc2, &pos2, 0);



if (tr == 1)
	{

re = bloc2;

se = pos2;

int re2 = bloc2;

int se2 = pos2;

int r3 = bloc2;

int s3 = pos2;

	    //re = 3;
	    printf ("\n\tOperation de suppression logique :  ");

printf ("\n\tAvant suppression   :\n ");

	    //afficher_enreg(g,re2,se2);
	    printf ("\n");

suppression_Logique_L7OVC2 (g, &re2, &se2,1);



printf ("\n\tMise a jour des tables d'index....  ");

printf ("\n");

sup_index2 (cle);

sup_index1 (cle);


printf ("\n\tApres suppression   :\n ");

printf ("\n\t");

afficher_enreg (g, r3, s3);


}
      else
	{

printf
	    ("\n\t\t La cle est non existante veuillez reessayer avec un matricule valide ");

}

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


break;







case 1:

system ("cls");


printf ("%s",
		 "\n--------------------------------------------------------------------------------------------\n");



int j,u;
h = entrez (&j,&u);

v = entr (h);






matricule = atoi (recup_ch (v, 2));


enreg moule;

moule.cle = matricule;


moule.bloc = entete (g, 3);


moule.pos = entete (g, 4);



moule.region = region (j);


moule.eff = 0;



ins (moule);


enreg2 moule2;


moule2.Etablissement = j;

moule2.bloc = entete (g, 3);

moule2.pos = entete (g, 4);

moule2.cle = matricule;

moule2.anciente = 20;

moule2.eff = 0;

moule2.specialite = u;



ins2 (moule2);

pi=o;
insertion2_L7OVC (g, v, &k, &pi);





	// }

printf ("%s",
		 "\n--------------------------------------------------------------------------------------------\n");



break;




    case 5:

printf ("\n\tDonnez le minimum");



status = scanf ("%d", &minimum);


while (status != 1)

	{

while ((temp = getchar ()) != EOF && temp != '\n');

printf ("\n\n\tVeuillez introduire un nombre valide  !  : ");

status = scanf ("%d", &minimum);

}

printf ("\n\tDonnez le maximum");



status = scanf ("%d", &maximum);


while (status != 1)

	{

while ((temp = getchar ()) != EOF && temp != '\n');

printf ("\n\n\tVeuillez introduire un nombre valide  !  : ");

status = scanf ("%d", &maximum);

}

afficher_univ ();

printf
	("\n Veuillez choisir l'etablissment (choissir l'index correspondant a l'etablissment )   :    ");

scanf ("%d", &cle);

if (maximum < minimum)
	{

cle = minimum;

minimum = maximum;

maximum = cle;

}


recherche_intervalle (ent2, minimum, maximum, cle);

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


break;

	/*case 13:
	   printf("%s","\n--------------------------------------------------------------------------------------------\n");

	   rech2();
	   printf("%s","\n--------------------------------------------------------------------------------------------\n");


	   break; */
    case 6:

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


affichage_region ();

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


break;

case 2:

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


printf ("\n Operation de mutation:  ");

printf ("\n Veuillez saisir le matricule de l'enseignant :  ");

scanf ("%d", &cle);

printf ("\n introduire le nouveau etablissment ");

afficher_univ ();

printf
	("\n  Votre choix (inserer l'index correspondant a l'etablissment voulu  : ");


scanf ("%d", &choix);

	//scanf("\n%d",&choix);
	printf ("\n   ");

mutation (g,ent2, cle, choix);

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");



break;




case 4:

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


printf ("\n Operation de suppression par specialite  ");

afficher_specialite ();

scanf ("\n %d", &choix);

suppression_specialite (g, ent2, choix);

printf ("%s",
	       "\n--------------------------------------------------------------------------------------------\n");


break;

default:			// Cas ou iChoix n'etait ni 1 ni 2
      {

printf ("\n\t!! Option non existante dans le menu !! Veuillez choisir une valeur valide ");	// Avertissement
      }

}

char cq[2];


printf ("\n\n\tVoulez vous continuer ou quitter? (C POUR CONTINUER, Q POUR QUITTER) : ");	// option pour continuer l'utilisation ou quitter le programme
  scanf ("%s", &cq);		// lecture du choix pour contiuer ou sortir .
  if ((_stricmp (cq, "C") == 0 || _stricmp (cq, "c") == 0))
    {
      system ("cls");
      goto menu;
    }				// si le choix est 'C' ou 'c' on se branche C  l'etiquette menu, sinon on quitte le programme.
  else

    {
      printf ("\n\n\t Merci d'avoir utiliser notre programme!\n\n");
      exit (1);
    }

return 0;



    // Fermeture du fichier (sauvegarde de l'entete) ...
    fermer (f, &ent);


return 0;


}				// main







// Chargement initial C  u% ...
  void
charg ()
{

double u;

long i, k, n;

int j;

int num;

int num2;


printf ("Chargment initial du fichier\n");

printf ("Donnez le nombre d'enregistrement C  inserer : ");

scanf (" %ld", &n);

printf ("Donnez le taux de chargement souhaite (entre 0 et 1) : ");

scanf (" %lf", &u);

if (u < 1 / MAXTAB)
    u = 1 / MAXTAB;		// pour avoir au moins un enregistrement par bloc
  if (u > 1)
    u = 1.0;			// maximum = 100%

printf
    ("Remplissage des blocs avec %d enreg (sauf eventuellement le dernier)\n",
     \
(int) (MAXTAB * u));

j = 0;

i = 1;

for (k = 0; k < n; k++)
    {

char ch[256] = "";

int num3;

char *r = enregistrement (&num, &num2, &num3);

strcpy (ch, r);

ch[strlen (ch)] = '\0';

char *chaine = &ch[0];

if (j < MAXTAB * u)
	{

buf.tab[j].cle = atoi (recup_ch (chaine, 2));

buf.eff[j] = ' ';

j++;

}

      else
	{

buf.nb = j;

ecrireDir (f, i, &buf);

i++;

buf.tab[0].cle = atoi (recup_ch (chaine, 2));

buf.eff[0] = ' ';

j = 1;

}

}

    // derniC(re ecriture ...
    buf.nb = j;
ecriture++;
ecrireDir (f, i, &buf);


    // m-a-j de l'entete ...
    ent.nb_bloc = i;

ent.nb_ins = n;


}				// charg





// afficher l'entete du fichier ...
  void
info ()
{

printf ("\n\t\t    -  Informations sur le fichier    \n");

printf ("\t\tNombre de blocs utilises =            %ld\n", ent.nb_bloc);

printf ("\t\tNombre d'enregistrements inseres =    %ld\n", ent.nb_ins);



printf ("\t\tNombre d'enregistrements supprimes =  %ld\n", ent.nb_sup);

printf ("\t\tNombre d'enregistremens maximal dans un bloc =  %ld\n",
	   MAXTAB);

printf ("\t\tFacteur de chargement moyen = %f     (en pourcentage % )\n",
	   \
(ent.nb_bloc ==
	      0 ? 0 : (float) (100 *
			       ((double) ent.nb_ins /
				((ent.nb_bloc) * MAXTAB)))));

}				// info


// recherche d'une valeur dans le fichier:
// utilise soit la recherche dichotomique, soit la recherche sequentielle
  void
rech ()
{

long i, val, cpt;

int trouv, j, choix;


printf ("Recherche 1-dichotomique ou 2-sequentielle ? (1 ou 2) : ");

scanf (" %d", &choix);

printf ("Donnez la valeur cherchee : ");

scanf (" %ld", &val);


if (choix == 1)

cpt = dicho (val, &trouv, &i, &j);

  else

cpt = seq (val, &trouv, &i, &j);


printf ("Resultats de la recherche:\n");

if (trouv && buf.eff[j] == ' ')

printf ("element trouve dans le bloc %ld a la position %d\n", i, j);

  else

printf
      ("element non trouve et devrait etre dans le bloc %ld C  la position %d\n",
       i, j);

printf ("Nombre de lectures physiques effectuees = %ld\n", cpt);


}				// rech










void
dicho_index2 (long val, int *trouv, int *bloc, int *pos, int choix)
{

long bi, bs;

int stop, inf, sup, i, j;

bi = 1;

bs = ent2.nb_bloc;

*trouv = 0;

stop = 0;


j = 1;			// compteur de lectures physiques
  while (bi <= bs && !*trouv && !stop)
    {

i = (bi + bs) / 2;	// le milieu entre bi et bs
lecture++;
      lireDir (f, i, &buf);	// lecture du bloc du milieu
      if (val < buf.tab[0].cle)

bs = i - 1;		// la recherche contiue dans la 1ere moitie
      else

if (val > buf.tab[buf.nb - 1].cle)

bi = i + 1;		// la recherche contiue dans la 2eme moitie
      else
	{

stop = 1;		// recherche interne dans buf (bloc du milieu)
	  inf = 0;

sup = buf.nb - 1;

while (inf <= sup && !*trouv)
	    {

j = (inf + sup) / 2;

if ((val == buf.tab[j].cle) && (buf.eff[j] != '*'))
		{


*trouv = 1;

*bloc = buf.tab[j].bloc;

*pos = buf.tab[j].pos;

if (choix == 1)
		    {

buf.eff[j] = '*';
ecriture++;
ecrireDir (f, i, &buf);

}


}

	      else

if (val < buf.tab[j].cle)

sup = j - 1;

	      else

inf = j + 1;

}			// while interne
	  if (inf > sup)
	    j = inf;

}

}				// while externe
  if (bi > bs)
    {

i = bi;

j = 0;

}


    /* if(var1!=*bloc){
     *trouv=0;
     }*/

}				// dicho



long
dicho (long c, int *trouv, long *i, int *j)
{

int bi, bs, inf, sup;

int stop;

int cpt;

cpt = 0;

stop = 0;

*trouv = 0;

*j = 0;

while (bi <= bs && !*trouv && !stop)
    {

*i = (bi + bs) / 2;	// le milieu entre bi et bs
lecture++;
      lireDir (f, *i, &buf);
      cpt++;

if (c >= buf.tab[0].cle && c <= buf.tab[buf.nb - 1].cle)

	{

inf = 0;

sup = buf.nb - 1;

while (inf <= sup && !*trouv)

	    {

*j = (inf + sup) / 2;

if (c == buf.tab[*j].cle)

		{

*trouv = 1;

}

	      else

		{

if (c < buf.tab[*j].cle)

		    {

sup = *j - 1;

}

		  else
		    {

inf = *j + 1;

}

}

}

if (!*trouv)

	    {

*j = inf;

}

stop = 1;

}

      else
	{

if (c < buf.tab[0].cle)

	    {

bs = *i - 1;

}

	  else
	    {

bi = *i + 1;

}

}

}

if (!*trouv)

    {

*i = bi;

}

return cpt;

}



// recherche sequentielle
// resultats: trouv (booleen), i (num de bloc), j (position dans le bloc)
// retourne aussi le nombre de lecture de blocs effectues.
  long
seq (long val, int *trouv, long *i, int *j)
{

long cpt;

int stop;


*i = 1;

*trouv = 0;

stop = 0;

cpt = 0;			// compteur de lectures physiques
  while (*i <= ent.nb_bloc && !*trouv && !stop)
    {
lecture++;
lireDir (f, *i, &buf);
      cpt++;			// lecture physique
      *j = 0;

while (*j < buf.nb && !stop && !*trouv)
	{

if (val == buf.tab[*j].cle)
	    *trouv = 1;

	  else

if (val < buf.tab[*j].cle)

stop = 1;

	  else

*j = *j + 1;

}			// while interne
      if (!stop && !*trouv)

*i = *i + 1;

}				// while externe

return cpt;


}				// seq


long
seq2 (long val, int *trouv, long *i, int *j)
{

long cpt;

int stop;


*i = 1;

*trouv = 0;

stop = 0;

cpt = 0;			// compteur de lectures physiques
  while (*i <= ent2.nb_bloc && !*trouv && !stop)
    {

lireDir2 (h, *i, &buf2);
      cpt++;			// lecture physique
      *j = 0;

while (*j < buf2.nb && !stop && !*trouv)
	{

if (val == buf2.tab[*j].anciente)
	    *trouv = 1;

	  else

if (val < buf2.tab[*j].anciente)

stop = 1;

	  else

*j = *j + 1;

}			// while interne
      if (!stop && !*trouv)

*i = *i + 1;

}				// while externe

return cpt;


}				// seq




				// seq


long
seq_index2cle (long val, int *trouv, long *i, int *j)
{

long cpt;

int stop;


*i = 1;

*trouv = 0;

stop = 0;

cpt = 0;			// compteur de lectures physiques
  while (*i <= ent2.nb_bloc && !*trouv && !stop)
    {

lireDir2 (h, *i, &buf2);
      cpt++;			// lecture physique
      *j = 0;

while (*j < buf2.nb && !stop && !*trouv)
	{

if (val == buf2.tab[*j].cle)
	    *trouv = 1;

	  else

if (val < buf2.tab[*j].cle)

stop = 1;

	  else

*j = *j + 1;

}			// while interne
      if (!stop && !*trouv)

*i = *i + 1;

}				// while externe

return cpt;


}				// seq





void
rech2 ()
{

long i, val, cpt;

int trouv, j, choix;


printf ("Recherche 1-dichotomique ou 2-sequentielle ? (1 ou 2) : ");

scanf (" %d", &choix);

printf ("Donnez la valeur cherchee : ");

scanf (" %ld", &val);


if (choix == 1)

seq2 (val, &trouv, &i, &j);

  else

seq2 (val, &trouv, &i, &j);


printf ("Resultats de la recherche:\n");

if (trouv && buf2.eff[j] == ' ')

printf ("element trouve dans le bloc %ld C  la position %d\n", i, j);

  else

printf
      ("element non trouve et devrait C*tre dans le bloc %ld C  la position %d\n",
       i, j);

printf ("Nombre de lectures physiques effectuees = %ld\n", cpt);


}				// rech


// Insertion par decalages en reutilisant les emplacements des enreg effaces logiquement
/*void ins(enreg e)
{
   long i, cptR, cptI;
   int trouv, continu, empl_recup, j;
   enreg sauv;


  printf("\nla  cle  dans le  %d",e.cle);
   // recherche de la position (i,j) oC9 inserer l'enregistrement
   cptR = seq( e.cle, &trouv, &i, &j );


   printf("La recherche a coutr %ld lectures physiques.\n", cptR);
   if (trouv && buf.eff[j] == ' ') {
      // si l'enreg existe et n'est pas effacee logiquement, on arrete l'insertion.
      printf("Insertion refuse car la valeur existe deja dans le bloc %ld C  la position %d\n"\
	      , i, j);
      return;
   }

   /*printf("La valeur doit C*tre inserer dans le bloc %ld C  la position %d", i, j);
   printf(" ... "); fflush(stdout);

   cptI = 0;	// compteur de lecture/ecriture dans la phase de decalages

   empl_recup = 0; // indicateur de reutilisation d'un emplacement efface logiquement
		   // lors de l'insertion de la nouvelle valeur

   if ( i > ent.nb_bloc ) {
      // cas particulier d'une insertion en fin de fichier ...
      buf.tab[0] = e;
      buf.eff[0] = ' ';
      buf.nb = 1;
      ecrireDir( f, i, &buf ); cptI++;
      ent.nb_bloc++;
   }
   else {
      // cas general ...
      continu = 1;
      while ( continu ) {	// boucle principale pour les decalages inter-blocs
	while ( continu && j < buf.nb ) {	// decalages intra-bloc ...
	   sauv = buf.tab[j];
	   buf.tab[j] =e;
	   if ( buf.eff[j] == '*' ) {
		continu = 0;
		buf.eff[j] = ' ';
	   }
	   else {
	   	j++;
		e = sauv;
	   }
	}

	if ( j == buf.nb ) 	// ou continu == 1
	   if ( buf.nb < MAXTAB ) {
		buf.nb++;
		buf.tab[j] = e;  buf.eff[j] = ' ';
		ecrireDir( f, i, &buf ); cptI++;
		continu = 0;
	   }
	   else {
		ecrireDir( f, i, &buf ); cptI++;
		//i++;  j = 0;
		if ( i <= ent.nb_bloc ) {
		   lireDir( f, i, &buf ); cptI++;
		}
		else {
      	      	   // on a depasse la fin de fichier, donc on rajoute un nouveau bloc ...
      	      	   buf.tab[0] = sauv;
      	      	   buf.eff[0] = ' ';
      	      	   buf.nb = 1;
      	      	   ecrireDir( f, i, &buf ); cptI++;
     	      	   ent.nb_bloc++;
	      	       continu = 0; // et on s'arrC*te
		}
	   }
	else {
	   // cas oC9 les decalages se sont arrC*tes sur un enreg efface logiquement
	   empl_recup = 1;
	   ent.nb_sup--;	// car on reutilise l'emplacement efface logiquement
	   ecrireDir( f, i, &buf ); cptI++;
	}

      } // fin de la boucle while principale

   } // else (cas general)

   if ( !empl_recup )		// si on n'a pas reutilise un emplacement efface logiq
      ent.nb_ins++; 		// alors on incremente le nombre d'insertions

   printf("\nInsertion terminee. \n");
   printf("\tCout operationel de lecture/ecriture (rech:%ld + decl:%ld) = %ld\n", \
		cptR, cptI, cptR+cptI);

} // ins*/




void
ins2 (enreg2 e)
{

long i, cptR, cptI;

int trouv, continu, empl_recup, j;

enreg2 sauv;



    //val = atoi(recup_ch(enregistrement(),2));


    // recherche de la position (i,j) oC9 inserer l'enregistrement
    cptR = seq2 (e.anciente, &trouv, &i, &j);


printf ("La recherche a coC;te %ld lectures physiques.\n", cptR);

    /*if (!trouv && buf2.eff[j] == ' ') {
       // si l'enreg existe et n'est pas effacee logiquement, on arrete l'insertion.
       printf("Insertion refusee car la valeur existe dejC  dans le bloc %ld C  la position %d\n"\
       , i, j);
       return;
       } */

    /*printf("La valeur doit C*tre inserer dans le bloc %ld C  la position %d", i, j);
       printf(" ... "); fflush(stdout); */

cptI = 0;			// compteur de lecture/ecriture dans la phase de decalages

empl_recup = 0;		// indicateur de reutilisation d'un emplacement efface logiquement
  // lors de l'insertion de la nouvelle valeur

if (i > ent2.nb_bloc)
    {

	// cas particulier d'une insertion en fin de fichier ...
	buf2.tab[0] = e;

buf2.eff[0] = ' ';

buf2.nb = 1;
ecriture++;
ecrireDir2 (h, i, &buf2);
      cptI++;

ent2.nb_bloc++;

}

  else
    {

	// cas general ...
	continu = 1;

while (continu)
	{			// boucle principale pour les decalages inter-blocs
	  while (continu && j < buf2.nb)
	    {			// decalages intra-bloc ...
	      sauv = buf2.tab[j];

buf2.tab[j] = e;

if (buf2.eff[j] == '*')
		{

continu = 0;

buf2.eff[j] = ' ';

}

	      else
		{

j++;

e = sauv;

}

}


if (j == buf2.nb)	// ou continu == 1
	    if (buf2.nb < MAXTAB)
	      {

buf2.nb++;

buf2.tab[j] = e;
		buf2.eff[j] = ' ';
ecriture++;
ecrireDir2 (h, i, &buf2);
		cptI++;

continu = 0;

}

	    else
	      {
ecriture++;

ecrireDir2 (h, i, &buf2);
		cptI++;

		  //i++;  j = 0;
		  if (i <= ent2.nb_bloc)
		  {

lireDir2 (h, i, &buf2);
		    cptI++;

}

		else
		  {

		      // on a depasse la fin de fichier, donc on rajoute un nouveau bloc ...
		      buf2.tab[0] = sauv;

buf2.eff[0] = ' ';

buf2.nb = 1;
ecriture++;

ecrireDir2 (h, i, &buf2);
		    cptI++;

ent2.nb_bloc++;

continu = 0;	// et on s'arrC*te
		  }

}

	  else
	    {

		// cas oC9 les decalages se sont arrC*tes sur un enreg efface logiquement
		empl_recup = 1;

ent2.nb_sup--;	// car on reutilise l'emplacement efface logiquement
ecriture++;
	      ecrireDir (h, i, &buf2);
	      cptI++;

}


}			// fin de la boucle while principale

}				// else (cas general)

if (!empl_recup)		// si on n'a pas reutilise un emplacement efface logiq
    ent2.nb_ins++;		// alors on incremente le nombre d'insertions

printf ("\nInsertion terminee. \n");

printf
    ("\tCoC;t en operations de lecture/ecriture (rech:%ld + decl:%ld) = %ld\n",
     \
cptR, cptI, cptR + cptI);


}				// ins
















void
ins (enreg e)
{

long i, cptR, cptI;

int trouv, continu, empl_recup, j;

enreg sauv;





    // recherche de la position (i,j) oC9 inserer l'enregistrement
    cptR = seq(e.cle, &trouv, &i, &j);


    //printf("La recherche a coC;te %ld lectures physiques.\n", cptR);
    if (trouv && buf.eff[j] == ' ')
    {

	// si l'enreg existe et n'est pas effacee logiquement, on arrete l'insertion.
	// printf("Insertion refusee car la valeur existe dejC  dans le bloc %ld C  la position %d\n"\
	, i, j);

return;

}


    //printf("La valeur doit C*tre inserer dans le bloc %ld C  la position %d", i, j);
    //printf(" ... "); fflush(stdout);

cptI = 0;			// compteur de lecture/ecriture dans la phase de decalages

empl_recup = 0;		// indicateur de reutilisation d'un emplacement efface logiquement
  // lors de l'insertion de la nouvelle valeur

if (i > ent.nb_bloc)
    {

	// cas particulier d'une insertion en fin de fichier ...
	buf.tab[0] = e;

buf.eff[0] = ' ';

buf.nb = 1;
ecriture++;
ecrireDir (f, i, &buf);
      cptI++;

ent.nb_bloc++;

}

  else
    {

	// cas general ...
	continu = 1;

while (continu)
	{			// boucle principale pour les decalages inter-blocs
	  while (continu && j < buf.nb)
	    {			// decalages intra-bloc ...
	      sauv = buf.tab[j];

buf.tab[j] = e;

if (buf.eff[j] == '*')
		{

continu = 0;

buf.eff[j] = ' ';

}

	      else
		{

j++;

e = sauv;

}

}


if (j == buf.nb)	// ou continu == 1
	    if (buf.nb < MAXTAB)
	      {

buf.nb++;

buf.tab[j] = e;
		buf.eff[j] = ' ';
ecriture++;
ecrireDir (f, i, &buf);
		cptI++;

continu = 0;

}

	    else
	      {
ecriture++;

ecrireDir (f, i, &buf);
		cptI++;

		  //i++;  j = 0;
		  if (i <= ent.nb_bloc)
		  {
		      lecture++;

lireDir (f, i, &buf);
		    cptI++;

}

		else
		  {

		      // on a depasse la fin de fichier, donc on rajoute un nouveau bloc ...
		      buf.tab[0] = sauv;

buf.eff[0] = ' ';

buf.nb = 1;
ecriture++;

ecrireDir (f, i, &buf);
		    cptI++;

ent.nb_bloc++;

continu = 0;	// et on s'arrC*te
		  }

}

	  else
	    {

		// cas oC9 les decalages se sont arrC*tes sur un enreg efface logiquement
		empl_recup = 1;

ent.nb_sup--;	// car on reutilise l'emplacement efface logiquement
ecriture++;
	      ecrireDir (f, i, &buf);
	      cptI++;

}


}			// fin de la boucle while principale

}				// else (cas general)

if (!empl_recup)		// si on n'a pas reutilise un emplacement efface logiq
    ent.nb_ins++;		// alors on incremente le nombre d'insertions

    //printf("\nInsertion terminee. \n");
    //printf("\tCoC;t en operations de lecture/ecriture (rech:%ld + decl:%ld) = %ld\n", \
    cptR, cptI, cptR + cptI);


}				// ins













void ins7 (enreg e)
{

long i, cptR, cptI;

int trouv, continu, empl_recup, j;


    /*printf("Insertion d'un enregistrement\n");
       printf("Donnez la valeur C  inserer : ");
       scanf(" %ld", &val); */
    //val = atoi(recup_ch(enregistrement(),2));
    enreg val = e;

enreg sauv;

    // recherche de la position (i,j) oC9 inserer l'enregistrement
    cptR = seq (val.cle, &trouv, &i, &j);


printf ("La recherche a coC;te %ld lectures physiques.\n", cptR);

if (trouv && buf.eff[j] == ' ')
    {

	// si l'enreg existe et n'est pas effacee logiquement, on arrete l'insertion.
	printf
	("Insertion refuse car la valeur existe deja  dans le bloc %ld a  la position %d\n"
	 \
, i, j);

return;

}


printf
    ("La valeur doit etre inserer dans le bloc %ld a la position %d", i,
     j);

printf (" ... ");
  fflush (stdout);


cptI = 0;			// compteur de lecture/ecriture dans la phase de decalages

empl_recup = 0;		// indicateur de reutilisation d'un emplacement efface logiquement
  // lors de l'insertion de la nouvelle valeur

if (i > ent.nb_bloc)
    {

	// cas particulier d'une insertion en fin de fichier ...
	buf.tab[0] = val;

buf.eff[0] = ' ';

buf.nb = 1;
ecriture++;
ecrireDir (f, i, &buf);
      cptI++;

ent.nb_bloc++;

}

  else
    {

	// cas general ...
	continu = 1;

while (continu)
	{			// boucle principale pour les decalages inter-blocs
	  while (continu && j < buf.nb)
	    {			// decalages intra-bloc ...
	      sauv = buf.tab[j];

buf.tab[j] = val;

if (buf.eff[j] == '*')
		{

continu = 0;

buf.eff[j] = ' ';

}

	      else
		{

j++;

val = sauv;

}

}


if (j == buf.nb)	// ou continu == 1
	    if (buf.nb < MAXTAB)
	      {

buf.nb++;

buf.tab[j] = val;
		buf.eff[j] = ' ';
ecriture++;
ecrireDir (f, i, &buf);
		cptI++;

continu = 0;

}

	    else
	      {
ecriture++;

ecrireDir (f, i, &buf);
		cptI++;

		  //i++;  j = 0;
		  if (i <= ent.nb_bloc)
		  {
lecture++;
lireDir (f, i, &buf);
		    cptI++;

}

		else
		  {

		      // on a depasse la fin de fichier, donc on rajoute un nouveau bloc ...
		      buf.tab[0] = val;

buf.eff[0] = ' ';

buf.nb = 1;
ecriture++;
ecrireDir (f, i, &buf);
		    cptI++;

ent.nb_bloc++;

continu = 0;	// et on s'arrC*te
		  }

}

	  else
	    {

		// cas oC9 les decalages se sont arrC*tes sur un enreg efface logiquement
		empl_recup = 1;

ent.nb_sup--;	// car on reutilise l'emplacement efface logiquement
ecriture++;
	      ecrireDir (f, i, &buf);
	      cptI++;

}


}			// fin de la boucle while principale

}				// else (cas general)

if (!empl_recup)		// si on n'a pas reutilise un emplacement efface logiq
    ent.nb_ins++;		// alors on incremente le nombre d'insertions

printf ("\nInsertion termine. \n");

printf
    ("\tCoC;t en operations de lecture/ecriture (rech:%ld + decl:%ld) = %ld\n",
     \
cptR, cptI, cptR + cptI);


}				// ins






// Suppression logique d'un enregistrement
void sup ()
{

long i, val, cptR;

int trouv, continu, j;

printf ("\n Donnez la cle a supprimer     :");

scanf ("%d", &val);


dicho_L7OVC (val, &trouv, &i, &j, 0);


printf ("La recherche a coute %ld lectures physiques.\n", cptR);

if (!trouv || buf.tab[j].eff == 1)
    {

printf ("Suppression refuse car la valeur ,n'existe pas\n");

return;

}


printf
    ("La valeur a supprimer est dans le bloc %ld a la position %d\n", i, j);

lireDir (f, i, &buf);

buf.tab[j].eff = 700;

printf ("%d************", buf.tab[j].eff);	// effacement logique de l'enregistrement
ecriture++;
  ecrireDir (f, i, &buf);


ent.nb_sup++;


printf ("Cout total (rech + sup) = %ld + 1 = %ld op. d'E/S\n", cptR,
	     cptR + 1);


}				// sup





void sup_index1 (int val)
{

long i, cptR;

int trouv, continu, j;


i = 1;

j = 1;

while (i != ent.nb_bloc + 1)
    {

lireDir (f, i, &buf);

for (j = 0; j < buf.nb; j++)
	{

if (buf.tab[j].cle == val)
	    buf.tab[j].eff = 1;


}
ecriture++;
ecrireDir (f, i, &buf);

i++;

}


}				// sup




void sup_index2 (int val)//Supprimer selon lindex de l'anciente
{

long i;

int trouv, continu, j;


i = 1;

j = 1;

while (i != ent2.nb_bloc + 1)
    {
lecture++;
lireDir2 (h, i, &buf2);

for (j = 0; j < buf2.nb; j++)
	{

if (buf2.tab[j].cle == val)
	    buf2.tab[j].eff = 1;


}

ecriture++;
ecrireDir2 (h, i, &buf2);

i++;


}


}				// sup


// Affichage d'une sequence de blocs contigus (entre a et b)
void parcours (t_entete entete)//Affichage de la table index 1
{

long i, a, b;

int j;


printf
    ("\n\tAffichage d'une sequence de bloc(s). ayant des adresses dans [a , b] \n");

printf
    ("\n\tle fichier commence dans le bloc num 1 et se termine dans le bloc num %ld\n",
     ent.nb_bloc);

printf ("\n\tdonnez a : ");

scanf ("\n\t %ld", &a);

printf ("\n\tdonnez b : ");

scanf ("\n\t %ld", &b);

if (entete.nb_bloc < b)
    b = entete.nb_bloc;

for (i = a; i <= b; i++)
    {
lecture++;
lireDir (f, i, &buf);

printf ("\n\t[Bloc Num:%3ld \tNB = %2d \tCapacite max = %2d]\n", i,
	       buf.nb, MAXTAB);

for (j = 0; j < buf.nb; j++)

if (buf.tab[j].eff == 0)
	  {

	      // printf("\n\t%*ld              %*ld                %*ld       %*s  ",5, buf.tab[j].cle,buf.tab[j].bloc,buf.tab[j].pos,nom_region(buf.tab[j].region),buf.tab[j].eff);

printf
	      ("\n\t|%ld       |       %03d        |        %04d   |       %s",
	       buf.tab[j].cle, buf.tab[j].bloc, buf.tab[j].pos,
	       nom_region (buf.tab[j].region), buf.tab[j].eff);



}
	else
	  {

printf
	      ("\n\t|%ld       |       %03d         |       %04d   |       %s   Supprime ",
	       buf.tab[j].cle, buf.tab[j].bloc, buf.tab[j].pos,
	       nom_region (buf.tab[j].region), buf.tab[j].eff);

}
      printf
	("\n--------------------------------------------------------------------------\n");

}

printf ("\n\t Affichage termine");

}




void parcours2 (t_entete2 entete)//Fonction de parcours de la table index 2
{

long i, a, b;

int j;


printf
    ("\n\tAffichage d'une sequence de bloc(s). ayant des adresses dans [a , b] \n");

printf
    ("\n\tle fichier commence dans le bloc num 1 et se termine dans le bloc num %ld\n",
     entete.nb_bloc);

printf ("\n\tdonnez a : ");

scanf ("\n\t %ld", &a);

printf ("\n\tdonnez b : ");

scanf ("\n\t %ld", &b);

printf ("\n\t Anciente      Matricule       Specialite ");


for (i = a; i <= entete.nb_bloc; i++)
    {
lecture++;
lireDir2 (h, i, &buf2);

printf ("\n\t[Bloc Num:%3ld \tNB = %2d \tCapacite max = %2d]\n", i,
	       buf2.nb, MAXTAB);

for (j = 0; j < buf2.nb; j++)

if (buf2.tab[j].eff == 0)

printf ("\n\t|%02d       |       %03d        |       %s",
		   buf2.tab[j].anciente, buf2.tab[j].cle,
		   specialite[buf2.tab[j].specialite]);

	else

printf
	    ("\n\t|%ld        |       %03d        |        %04d   |       %s  Supprime",
	     buf2.tab[j].anciente,
	     Etablissement_Univ[buf2.tab[j].Etablissement], buf2.tab[j].cle,
	     specialite[buf2.tab[j].specialite]);

printf
	("\n-------------------------------------------------------------------------\n");

}


}				// parcours


void recherche_intervalle (t_entete2 entete, int minimum, int maximum,
			    int index)
{

long i;

int j;

int trouv;

int cpt = 0;


seq2 (minimum, &trouv, &i, &j);

while (trouv != 1)
    {

minimum++;

seq2 (minimum, &trouv, &i, &j);


}

lecture++;
lireDir2 (h, i, &buf2);

while (buf2.tab[j].anciente < maximum && (i != entete.nb_bloc + 1))
    {


	//printf("[Bloc Num:%3ld \tNB = %2d \tCapacite max = %2d]\n", i, buf2.nb, MAXTAB);
	for (j = 0; j < buf2.nb; j++)
	{

if ((buf2.eff[j] == ' ') &&
	       (buf2.tab[j].Etablissement == index) &&
	       (buf2.tab[j].anciente < maximum) &&
	       (minimum < buf2.tab[j].anciente))

	    {


printf ("\n\t|      %d      |      %02d      |         %s",
			 buf2.tab[j].cle, buf2.tab[j].anciente,
			 Etablissement_Univ[index]);

cpt++;

}
	  else
	    {

		// printf("\n%ld///%s///%ld///%ld/// ",buf2.tab[j].anciente,Etablissement_Univ[buf2.tab[j].Etablissement],buf2.tab[j].bloc,buf2.tab[j].pos,buf2.tab[j].Etablissement);
		// printf("\n--------------------------------------------------\n");
	    }

}

i++;
lecture++;
lireDir2 (h, i, &buf2);




}



if (cpt == 0)
    printf
      ("\n\t Aucun enseignant rempli les deux criterers de recherche ,essayer avec d'autre parameteres  ");

  else

printf ("\n\tOperation reussite ");

}				// parcours

void affichage_region ()
{

long i = 1;

int j = 1;

int num;

    //strcpy(etablissment,"Universite Medea-Yahia Fares");

    //printf("\n //////  %d  %d ",i,j);
    printf ("\n Donnez la region que vous voulez consulter  :");

printf ("\n");

printf ("\n 1) Est       2)  Centre      3)  Ouest ");

scanf ("%d", &num);

num--;



printf ("\n\n\n");
lecture++;
lireDir (f, i, &buf);

printf (" Matricule   Bloc   Position   Region\n");

while (i != ent.nb_bloc + 1)
    {

printf ("[Bloc Num:%3ld \tNB = %2d \tCapacite max = %2d]\n", i,
	       buf.nb, MAXTAB);
	       printf ("\n\t|    matricule     |     bloc     |    position    |      region "
);
	       printf ("\n\t|                  |              |                |       "
);
	//printf("[Bloc Num:%3ld \tNB = %2d \tCapacite max = %2d]\n", i, buf2.nb, MAXTAB);
	for (j = 0; j < buf.nb; j++)
	{

if ((buf.tab[j].eff == 0) && (buf.tab[j].region == num))

	    {


printf ("\n\t|      %d      |      %02d      |      %04d      |        %s", buf.tab[j].cle,
			 buf.tab[j].bloc, buf.tab[j].pos,
			 nom_region (buf.tab[j].region));

}
	  else
	    {

		// printf("\n%ld///%s///%ld///%ld/// ",buf2.tab[j].anciente,Etablissement_Univ[buf2.tab[j].Etablissement],buf2.tab[j].bloc,buf2.tab[j].pos,buf2.tab[j].Etablissement);
		// printf("\n--------------------------------------------------\n");
	    }

}

printf ("\n--------------------------------------------------\n");

i++;
lecture++;
lireDir (f, i, &buf);


}

}				// parcours




void mutation(L7OVC *g,t_entete2 entete,int cle,int index)//Affecter a lenseignant le nouveau etablissment
{   char c1[200];
     int k1,k2;
   long i=0;
   int j=0;
   int trouv=0;
    while((!trouv) && (i!=entete.nb_bloc+1)){

              i++;
lecture++;
             lireDir2(h, i, &buf2);
             for( j=0; j<buf2.nb; j++){
                    if((buf2.tab[j].cle==cle)&&(buf2.tab[j].eff==0)){
                        buf2.tab[j].Etablissement=index;
                        k1=buf2.tab[j].bloc;
                        k2=buf2.tab[j].pos;

                        afficher_enreg(g,k1,k2);
                        suppression_Logique_L7OVC2(g,&k1,&k2,0);
                        trouv=1;
                        printf("\n");
                         printf("\n");
                          printf("\n");
                           printf("\n");
                            strcpy(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),0));
                                      strcat(c1,"#");
                                      strcat(c1,"N");
                                      strcat(c1,"#");
                                      strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),2));
                                                   strcat(c1,"#");
                                                   strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),3));
                                              strcat(c1,"#");
                                             strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),4));
                                               strcat(c1,"#");
                                                 strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),5));
                                                    strcat(c1,"#");
                                                        strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),6));
                                                               strcat(c1,"#");
                                                                strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),7));
                                                                      strcat(c1,"#");
                                                                 strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),8));
                                                              strcat(c1,"#");
                                                       strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),9));
                                                            strcat(c1,"#");
                                         strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),10));
                                                           strcat(c1,"#");
                                        strcat(c1,recup_ch(recup_enreg(g,buf2.tab[j].bloc,buf2.tab[j].pos),11));
                                             strcat(c1,"#");

                                     strcat(c1,Etablissement_Univ[index]);
                                              strcat(c1,"$");
                                              printf("\n\t%s",c1);
                                          char *c2 = &c1[0];
                                                    insertion2_L7OVC(g,c2,&k1,&k2);



                    }

             }

    }
                printf("\n \nOperation reuissite Le nouveau etablissment devient : %s",Etablissement_Univ[index]);
ecriture++;
                ecrireDir2(h,i,&buf2);
}







void suppression_specialite (L7OVC * fichier, t_entete2 entete, int spe)	//Affecter a lenseignant le nouveau etablissment
{

long i = 0;

int j = 0;

int pos, bloc;

while (i != entete.nb_bloc + 1)
    {


i++;
lecture++;
lireDir2 (h, i, &buf2);

for (j = 0; j < buf2.nb; j++)
	{

if (buf2.tab[j].specialite == spe)
	    {

buf2.tab[j].eff = 1;

sup_index1 (buf2.tab[j].cle);

bloc = buf2.tab[j].bloc;

pos = buf2.tab[j].pos;

printf ("\n\t|       %d        |        %s|", buf2.tab[j].cle,
		       specialite[buf2.tab[j].specialite]);


suppression_Logique_L7OVC2(fichier, &bloc, &pos,0);

}
ecriture++;
ecrireDir2 (h, i, &buf2);


}


}

printf
    ("\n Operation reuissite tout les enseignants de specialite %s  sont supprimes  ",
     specialite[spe]);

    //printf("\n%d************",i);




}



