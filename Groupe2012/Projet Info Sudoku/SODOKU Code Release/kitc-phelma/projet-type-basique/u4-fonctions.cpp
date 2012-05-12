// u4-fonctions.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
#include <stdlib.h>     // exit, rand
#include <stdio.h>
#include <time.h>       // time
#include <string.h>     // strcpy
// Librairie fmod pour le son
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
#include <FL/fl_ask.H>
// Programmes locaux
#include "u1-interface.h"
#include "u4-fonctions.h"

/*
Ces fonctions proviennent de la r�solution de la grille de Sudoku.
Programme t�l�charg� sur internet : cr�� par Rusty Rossel.
*/

//DECLARATIONS NECESSAIRES POUR RESOLUTION SUDOKU
/* Program to solve Su Doko puzzles. */
#include "stdrusty.h"
#include <assert.h>
#include <stdio.h>

#define  _XOPEN_SOURCE_EXTENDED 1
#include <strings.h>


#define FINISHED (1 << 15)

// AJOUT FONCTIONS RESOLUTION SUDOKU
static inline unsigned int hweight16(unsigned int w)
{
        unsigned int res = (w & 0x5555) + ((w >> 1) & 0x5555);
        res = (res & 0x3333) + ((res >> 2) & 0x3333);
        res = (res & 0x0F0F) + ((res >> 4) & 0x0F0F);
        return (res & 0x00FF) + ((res >> 8) & 0x00FF);
}

static unsigned row(u16 puzzle[9][9], unsigned int x, unsigned int y,
		    u16 *value,
		    bool (*fn)(u16 p[9][9], unsigned int, unsigned int, u16 *))
{
	unsigned int i, total = 0;

	for (i = 0; i < 9; i++)
		if (i != x && !(puzzle[y][i] & FINISHED))
			total += fn(puzzle, i, y, value);
	return total;
}

static unsigned column(u16 puzzle[9][9], unsigned int x, unsigned int y,
		       u16 *value,
		       bool (*fn)(u16 p[9][9], unsigned, unsigned, u16 *))
{
	unsigned int i, total = 0;

	for (i = 0; i < 9; i++)
		if (i != y && !(puzzle[i][x] & FINISHED))
			total += fn(puzzle, x, i, value);
	return total;
}

static unsigned box(u16 puzzle[9][9], unsigned int x, unsigned int y,
		    u16 *value,
		    bool (*fn)(u16 p[9][9], unsigned int, unsigned int, u16 *))
{
	unsigned int ix, iy, total = 0;

	/* Integer division gives us the 3x3 box we're in. */
	for (ix = x / 3 * 3; ix < x / 3 * 3 + 3; ix++) {
		for (iy = y / 3 * 3; iy < y / 3 * 3 + 3; iy++) {
			if (puzzle[iy][ix] & FINISHED)
				continue;
			if (ix == x && iy == y)
				continue;
			total += fn(puzzle, ix, iy, value);
		}
	}
	return total;
}

static void eliminate(u16 puzzle[9][9], unsigned int x, unsigned int y);

static bool reduce(u16 puzzle[9][9], unsigned int x, unsigned int y, u16 *val)
{
	puzzle[y][x] &= ~*val;
	assert(puzzle[y][x] != 0);

	if (hweight16(puzzle[y][x]) == 1) {
		printf("Solved %ix%i = %i\n", x+1, y+1, (puzzle[y][x]));
		eliminate(puzzle, x, y);
		return true;
	}
	return false;
}

static void eliminate(u16 puzzle[9][9], unsigned int x, unsigned int y)
{
	assert(puzzle[y][x] != 0);
	puzzle[y][x] |= FINISHED;

	row(puzzle, x, y, &puzzle[y][x], reduce);
	column(puzzle, x, y, &puzzle[y][x], reduce);
	box(puzzle, x, y, &puzzle[y][x], reduce);
}

/* Take away the possibilities of this square. */
static bool cutdown(u16 puzzle[9][9], unsigned int x, unsigned int y, u16 *val)
{
	if (*val & puzzle[y][x]) {
		*val &= ~puzzle[y][x];
		return true;
	}
	return false;
}

void dump_val(u16 val)
{
	unsigned int i;

	for (i = 0; i < 9; i++)
		if (val & (1 << i))
			printf("%i", i+1);
		else
		{

		}
			//printf(" ");
}

int dump_val2(u16 val)
{
	unsigned int i;

	for (i = 0; i < 9; i++)
		if (val & (1 << i))
		{
            printf("%i", i+1);
			return i+1;
		}

		else
		{

		}
			//printf(" ");
}


// Fonction Dump qui permet de relacher la grille r�solue
static void dump(u16 puzzle[9][9])
{
    int grille [81];

    int i=0;
    int j=0;
    int compteur=0;
    for (i=0;i<81;i++)
    {
        grille[i]=0;
    }
    printf ("\n\n\n1\n\n");
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
            dump_val(puzzle[i][j]);
        }
    }
    printf ("\n\n\n2\n\n");

    // BIDOUILLAGE
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
            grille[j+9*i]= dump_val2(puzzle[i][j]); // On d�pose la valeur de chaque case du tableau � 2 dimension vers un tableau � 1 seule dimension
        }
    }

    // FIN BIDOUILLAGe
    printf ("\n\n\nES CE QUE CA MARCHE?\n\n");


    for (i=0;i<81;i++)
    {
        printf("%d",grille[i]);
    }

    printf ("\n\n\nOUI OU NON\n\n");
    for(i=0;i<81;i++)
    {
        compteur++;
        printf("%d",grille[i]);
        if(compteur==9)
        {
            printf("\n");
            compteur=0;
        }
    }
    printf ("\n\n\n5\n\n");
	unsigned int x, y;

	for (y = 0; y < 9; y++) {
		if (y % 3 == 0)
			printf(" ---------------------------------\n");
		for (x = 0; x < 9; x++) {
			if (x % 3 == 0)
				printf("|");
			else
				printf(".");
			dump_val(puzzle[y][x]);
		}
		printf("|\n");
	}
	printf(" ---------------------------------\n");

	printf ("\n\n\nASSIGNATION DE LA GRILLE DANS GRILLIN\n\n");
    for (i=0;i<81;i++)
	{
        grillin.table[i] = grille [i]; // On �crit la grille dans grillin qui est r�cup�r� par le programme
	}
	printf ("\n\n\nDONE? i dont know\n\n");

}

/* If we have a possibility which no other square has, that's our value */
static bool try_cutdown(u16 puzzle[9][9], unsigned int x, unsigned int y)
{
	u16 val;

	val = puzzle[y][x];
	row(puzzle, x, y, &val, cutdown);
	if (val) {
		printf("Row eliminated %ix%i = %i\n",
		       x+1, y+1, (val));
		goto elim;
	}

	val = puzzle[y][x];
	column(puzzle, x, y, &val, cutdown);
	if (val) {
		printf("Col eliminated %ix%i = %i\n",
		       x+1, y+1, (val));
		goto elim;
	}

	val = puzzle[y][x];
	box(puzzle, x, y, &val, cutdown);
	if (val) {
		printf("Box eliminated %ix%i = %i\n",
		       x+1, y+1, (val));
		goto elim;
	}
	return false;

elim:
	/* Can't have more than one answer. */
	assert(hweight16(val) == 1);
	puzzle[y][x] = val;
	eliminate(puzzle, x, y);
	return true;
}

static bool match(u16 puzzle[9][9], unsigned int x, unsigned int y, u16 *val)
{
	return (puzzle[y][x] == *val);
}

/* If not equal, remove these bits. */
static bool reduce_unequal(u16 puzzle[9][9], unsigned x, unsigned y, u16 *val)
{
	if (puzzle[y][x] == *val)
		return false;

	if (!(puzzle[y][x] & *val))
		return false;

	puzzle[y][x] &= ~*val;
	assert(puzzle[y][x] != 0);

	if (hweight16(puzzle[y][x]) == 1) {
		printf("Matches eliminated %ix%i = %i\n",
		       x+1, y+1, (puzzle[y][x]));
		eliminate(puzzle, x, y);
	}
	return true;
}

/* If there are 2 identical pairs, nothing else can be that value.
 * Similarly 3 identical triplets. */
static bool try_matches(u16 puzzle[9][9], unsigned int x, unsigned int y)
{
	unsigned int matches;
	bool progress = false;

	matches = row(puzzle, x, y, &puzzle[y][x], match);
	if (matches+1 == hweight16(puzzle[y][x]))
		progress = row(puzzle, x, y, &puzzle[y][x], reduce_unequal);

	matches = column(puzzle, x, y, &puzzle[y][x], match);
	if (matches+1 == hweight16(puzzle[y][x]))
		progress = column(puzzle, x, y, &puzzle[y][x], reduce_unequal);

	matches = box(puzzle, x, y, &puzzle[y][x], match);
	if (matches+1 == hweight16(puzzle[y][x]))
		progress = box(puzzle, x, y, &puzzle[y][x], reduce_unequal);

	return progress;
}

/*
Fin des fonctions import�es pour la r�solution du Sudoku
*/









// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;

// Initialiser
void InitialiserDonnees()
{
    // On initialise le generateur de nombres aleatoires
    srand(time(NULL));

}




// Fonctions ajout�s au programme

// La fonction trouver carr� renvoi la premiere case du carr� dans lequel est situ� la case que l'on recherche
int TrouveCarre(int NumCase)
    {
        int k = 0, l = 0,  NumCarre = 0;
        int j = 0;

     // Calcul de la ligne et colonne de la case
        NumCase++;

        k = NumCase % 9;        // k : Colonne o� est situ�e la case //Utilisation des modulos
        j = NumCase/9;
            if ( NumCase%9 != 0)
                {
                    l = j+1;
                }
            else {l = j;}       // l : ligne o� est situ�e la case

            //printf(" l = %d",l);


        // Cette structure en if else,  regroupe toute les possibilit�s de carr�, et en fonction des lignes ou des colones renvoi le num�ro du carr�
      //  Calcul du carr� en fonction de �a...
            if (k==1 || k==4 || k==7)  //Si on se situe dans la premi�re colone, la 4 ou la 7
                {
                    if (l==1 || l==4 || l==7  )// Si on se situe dans la premi�re ligne la 4 ou la 7
                        {
                            NumCarre = NumCase; //Dans ce cas la case correspond au d�but du carr�
                        }
                    else if (l==2 || l==5 || l==8 ) // Si on est sur la 2 �me ligne, on retire 9 pour se retrouver au d�but.
                        {
                            NumCarre = NumCase - 9;
                        }
                    else
                        {
                            NumCarre = NumCase - 18;
                        }
                }
            else if (k==2 || k==5 || k==8) // 2 �me colonne
                {
                    if (l==1 || l==4 || l==7  ) //A chaque fois on traite le cas des premi�res lignes, puis des 2nde et des troisi�mes
                        {
                            NumCarre = NumCase - 1;
                        }
                    else if (l==2 || l==5 || l==8 )
                        {
                            NumCarre = NumCase - 10;
                        }
                    else
                        {
                            NumCarre = NumCase - 19;
                        }
                }

            else // 3 �me colonne
                {
                 if (l==1 || l==4 || l==7  )
                        {
                            NumCarre = NumCase - 2;
                        }
                    else if (l==2 || l==5 || l==8 )
                        {
                            NumCarre = NumCase - 11;
                        }
                    else
                        {
                            NumCarre = NumCase - 20;
                        }
                }


        return NumCarre; // Renvoi le nombre du carr� dans lequel se situe la case envoy� en argument
    }




// Ce test permet de v�rifier si un m�me chiffre se situe d�ja dans la case ou non // Cette fonction renvoi 0 si le chiffre est d�ja pr�sent, 1 si le chiffre n'est pas pr�sent
int TestCase(grille * grillin, int NumCase, int Nbre, int Increment ) // Si on renvoi 1, on peut assigner, c'est bon
{
    int Preums=0;
    Preums = TrouveCarre(NumCase + 9*Increment);
    Preums --;
    if (Nbre-grillin->table[Preums] == 0 || Nbre-grillin->table[Preums+1]==0 || Nbre-grillin->table[Preums+2]==0 || Nbre-grillin->table[Preums+9]==0 || Nbre-grillin->table[Preums+10]==0 || Nbre-grillin->table[Preums+11]==0 || Nbre-grillin->table[Preums+18]==0 || Nbre-grillin->table[Preums+19]==0 || Nbre-grillin->table[Preums+20]==0)
    { // On balaye les 9 cases
        return 0;
    }
    else
    {
        return 1; //Si tout est ok on renvoi 1
    }
}

// FIN AJOUT DE CAKEM


// Cette fonction permet de V�rifier si le chiffre se situe d�ja dans la colonne
int TestColonne(grille *grillin, int alea1, int Nbre, int Increment) // alea1 = position dans la ligne // Nbre = nombre essay� // Increment = Ligne du tableau
{
    int i,j;

    for(i=Increment;i>0;i--) //On balaye toutes les cases vers le haut
    {
        if (Nbre - grillin->table[alea1 + 9*Increment - 9*i] == 0) // Si le chiffre est d�ja pr�sent on renvoi 0
        {
            return 0;
        }
    }

    for(j=Increment;j<8;j++) // On balaye toutes les cases vers le bas
    {
        if (Nbre - grillin->table[alea1 + 9*Increment + 9*j] == 0) // Si le chiffre est d�ja pr�sent on renvoi 0
        {
            return 0;
        }
    }


    return 1; // Si tout est ok, on renvoi 1 , dans ce cas, on peut assigner ce chiffre, il ne se situe pas d�ja dans la colonne
}



// Cette fonction permet de V�rifier si le chiffre se situe d�ja dans la ligne
int TestLigne(grille *grillin, int alea1, int Nbre, int Increment) // alea1 = position dans la ligne // Nbre = nombre essay� // Increment = Ligne du tableau
{
    int i,j;

    for(i=alea1-1;i>9*Increment-1;i--) //On balaye toutes les cases vers la gauche
    {
        if (Nbre - grillin->table[i] == 0) // Si le chiffre est d�ja pr�sent on renvoi 0
        {
            return 0;
        }
    }

    for(j=alea1+1;j<9*Increment+9;j++) //On balaye toutes les cases vers la droite
    {
        if (Nbre - grillin->table[j] == 0) // Si le chiffre est d�ja pr�sent on renvoi 0
        {
            return 0;
        }
    }


    return 1; // Si tout est ok, on renvoi 1 , dans ce cas, on peut assigner ce chiffre, il ne se situe pas d�ja sur la ligne
}



// Cette fonction permet de g�n�rer une grille de Sudoku
void CreationGrille(grille *grillin)
{
    srand(time(NULL)); //Initialisation du g�n�rateur al�atoire
    int alea1=0;
    int i=0;
    int j=0;
    int k=0;
    int compteur=1;
    int Col=-1;
    int Car=-1;
    int sortir=0;
    int infi3=0;
    int infi2=0;

    for (j=0; j<81 ; j++) // On initialise d'abord toutes les case � 0
    {
        grillin->table [j]=0;
    }

    for (i=0; i<9 ; i++) // On balaye toutes les lignes
    {
        for (k=1; k<10 ; k++) //On prend chaque chiffre les uns apr�s les autres de 1  � 9
        {
            alea1 = rand ()%9; // On g�n�re une position al�atoire pour l'assignation de chacun des chiffres
            sortir = 0; // On initialise une variable sortir qui permet de sortir de la boucle do while
            do
            {
                if (grillin->table [alea1 + 9*i] == 0) // Si la case tir� al�atoirement est vide
                {
                    Col = TestColonne(grillin, alea1, k, i); // On teste pour le nombre k si il est d�ja pr�sent dans la colonne
                    Car = TestCase (grillin, alea1, k, i); // On teste pour le nombre k si il est d�ja pr�sent dans la case
                    if (Col==1 && Car==1) // Si il n'est pr�sent ni dans la colonne ni dans la case
                    {
                        grillin->table [alea1 + 9*i] = k; // On assigne
                        sortir=1; // On sort de la do while
                    }
                    else // Sinon
                    {
                        infi3 ++; // On compte pour �viter les boucles infinies
                        alea1 = rand ()%9; // On retire un nombre al�atoire et on recommence les tests
                        if (alea1 ==9) // Ceci est inutile, on l'utilise que si, � la place de reg�n�rer al�atoirement al�a1, on l'incr�mente. Pour ne pas d�passer 9
                        {
                            alea1 = 0;
                        }
                    }
                }
                else // Si la case est d�ja occup�e
                {
                    infi3 ++;
                    alea1 = rand ()%9; // On retire un nombre
                    if (alea1 ==9)
                    {
                        alea1 = 0;
                    }
                }
                if (infi3 >= 80) // Dans le cas ou on est oblig� de tirer plus de 80 nombres al�atoires (ce qui veut dire qu'on est bloqu�s
                {
                    for (j=0; j<9 ; j++) // On remet dans ce cas � 0 toute la ligne en question
                    {
                        grillin->table [j + 9*i] = 0;
                    }
                    sortir = 1; // On sort de la boucle
                    k=0; // On recommence pour r�assigner le chiffre 1 etc...
                    infi2 ++; // On compte combien de fois on doit effacer la ligne que l'on traite parce qu'elle ne fonctionne pas

                    if (infi2 >= 60) // So on doit effacer plus de 60 fois la ligne, c'est que la ligne pr�c�dente n'est pas juste
                    {
                        for (j=0; j<9 ; j++) // Dans ce cas, on efface et on met � 0 les 2 lignes pr�c�dentes
                        {
                            grillin->table [j + 9*i] = 0;
                        }
                        for (j=0; j<9 ; j++) // Ligne pr�c�dente
                        {
                            grillin->table [j + 9*(i-1)] = 0;
                        }
                        sortir = 1; // On sort
                        k=0; // On recommence � assigner � partir de 1
                        i--; // On remonte d'une ligne
                    }
                }
            } while (sortir ==0);

            infi3 =0; // On r�initialise les compteurs de boucle infini
            alea1 = 0;
        }
        k=0;
        infi2 = 0; // On r�initialise les compteurs de boucle infini
    }

    // Affichage de la grille g�n�r�e dans la console
    printf("\n\n\n\n");
    for (j=0; j<81 ; j++)
    {
        printf("%d", grillin->table [j]);
        compteur ++;
        if (compteur==10)
        {
            printf("\n");
            compteur = 1;
        }
    }
}

// Cette fonction permet de pr�parer la grille pour le jeu ( en fonction de la difficult�
void PreparationGrille(grille * grillin, int Difficulte)
{
    // Nombre de chiffres retir�s
    int NbreChiffresRetires=0;

    // On d�cide du niveau et du nombre de chiffres retir�s par niveau
    switch (Difficulte) {
    case (1) :
        NbreChiffresRetires=34; // On s'arrange pour avoir un chiffre pair (en effet on doit retirer les chiffres de facon sym�trique
        break;
    case (2) :
        NbreChiffresRetires=42;
        break;
    case (3) :
        NbreChiffresRetires=48; // On trouve que c'est un peu beaucoup, souvent les grille difficile le sont trop
        break;
    }


    //Declarations
    int i=0;
    srand(time(NULL));
    int alea=0;
    int compteur=1;
    int j=0;
    int temp=0;
    int doublon=0;


    // On retire le nombre de chiffre indiqu�
    for(i=1; i<(NbreChiffresRetires/2)+1; i++)
    {
        do
        {
            alea = rand ()%81; // On prend une case au hasard dans la grille
            if (grillin->table [alea] != 0) // Si elle est occup�e
            {
                grillin->table [alea] = 0; // alors on supprime le contenu
                grillin->table [80-alea] = 0; // Et on suprrime le contenu de son sym�trique par rapport au centre
                doublon=0; // Dans ce ca on sort de la boucle
            }
            else
            {
                doublon=1; // Si la case est d�ja vide, on recommence
            }

        } while (doublon!=0);


    }


    // La grille est pr�par�e
    printf("\n\nGrille Preparee\n\n");
    for (j=0; j<81 ; j++)
    {
        if (grillin->table [j] == 0)
        {
            printf("."); // On affiche des points si les cases sont vide
            temp++;
        }
        else
        {
            printf("%d", grillin->table [j]); // On affiche la grille pr�par�e pour la v�rifier
        }

        compteur ++; // Compteur de case
        if (compteur==10) // Si on atteint le bout de la ligne, on fait un retour � la ligne (plus de visibilit�)
        {
            printf("\n");
            compteur = 1;
        }

    }
    printf("\n\n\n");


    printf("Nombre de chiffres retires : %d", NbreChiffresRetires);
    printf("\nNombre de chiffres retires pour de vrai: %d\n", temp); // On calcule et affiche le nombre de chiffres effectivement retir�s
}



// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds )
{
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}


grille grillin;
grille GrilleResolue;
grille GrilleTemp;



int PosX;
int PosY;



// Cette fonction permet la r�solution de la grille ligne par ligne // Elle ne fonctionne pas sur des grilles de sudoku complexes // Intelligence artificielle trop complexe � programmer
void ResolutionGrilleLigneParLigne(grille *grillin)
{
    srand(time(NULL));
    int alea1=0;
    int j=0;
    int compteur=1;
    int Once=0;
    int a=0;
    int b=0;
    int c=0;
    int d=0;
    int e=0;
    int f=0;
    int g=0;
    int i=0;
    int k=0;
    int Car=0;
    int Col=0;
    int Ligne=0;

    for(a=0;a<100;a++)
    {
        for(b=0;b<81;b++)
        {
            if (grillin->table [b]!=0)
            {

            }
            else
            {
                for (c=1;c<10;c++)
                {
                    i = b/9;
                    alea1 = b - 9*i;
                    Col = TestColonne(grillin, alea1, c, i);

                    Car = TestCase (grillin, alea1, c, i);

                    Ligne = TestLigne (grillin, alea1, c, i);

                    if (Col == 1 && Car == 1 && Ligne == 1) // On teste si le chiffre est d�ja sur la ligne, colonne ou case et sinon on peut l'assigner
                    {
                        grillin->table [b] = c;
                        Once ++; // On incr�mente un compteur
                    }
                }
                if (Once > 1) // S'il y a plus d'une possibilit� // NOTE : C'est justement ceci qui ne fonctionne pas, le logiciel ne peut pas savoir qu'en fait il ne peut
                { // y avoir qu'une possibilit�, d�s que l'on peut mettre plus d'un chiffre, il ne fait rien. M�me si en r�alit� il n'y a qu'un choix: Probl�me IA
                    grillin->table [b] = 0; // on remet la case � 0
                }
                Once = 0;
            }
        }
    }


    // On affiche la grille
    printf("\n\n\n\n");
    for (j=0; j<81 ; j++)
    {
        printf("%d", grillin->table [j]);
        compteur ++;
        if (compteur==10)
        {
            printf("\n");
            compteur = 1;
        }

    }


}




// Cette fonction permet simplement de compter les cases occup�es
int CompteurCasesOccupees(grille *grillin)
{
    int compteur=0;
    int i=0;

    for(i=0;i<81;i++)
    {
        if(grillin->table [i]==0) // Si la case est vide, on ne fait rien
        {

        }
        else if (grillin->table [i] !=0) // Si la case est occup�e, on incr�mente
        {
            compteur++;
        }
    }
    return compteur; // On renvoi le r�sultat du comptage


}



// Utilitaires

// Joue le fichier son passe en parametre, mp3, etc...
void JouerSon(char * FichierSon)
{
    // Musique de fond
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    result = FMOD_System_GetVersion(system, &version);
    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    result = FMOD_System_CreateSound(system, FichierSon, FMOD_SOFTWARE, 0, &sound);
    result = FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
}



// Cette fonction, d�velopp�e par Rusty Rossel et adapt� par nos soins pour qu'elle s'int�gre � notre programme, permet de r�soudre une grille de sudoku
// Cette fonction est presque instantan�e (algorithme de Mr Rossel tr�s efficace)
// Attention cependant, certaines grilles extremement complexes (les plus difficile connues) ne pourront pas �tre r�solues avec cet algorithme
void ResolutionGrilleMrLinux(grille *grillin)
{
    unsigned int x, y;
	bool progress;
	u16 puzzle[9][9]; // On cr�� la matrice n�c�ssaire � la r�solution par la fonction de Rusty Rossel (r�solution matricielle)
	int i=0,j=0;

	int initial_puzzle[9][9]; // Le puzzle initial correspondra � la grille que nous envoyons � la fonction
	for (i=0;i<9;i++)
	{
	    for (j=0;j<9;j++)
	    {
	        initial_puzzle[i][j]=0; // D'abord on la remet � 0 (s�curit�)
	    }
	}
	printf("\nMise a 0 de initial puzzle\n");
	for (i=0;i<9;i++)
	{
	    for (j=0;j<9;j++)
	    {
	        initial_puzzle[i][j]= grillin->table[j + 9*i]; // Puis on passe d'un tableau � 1 dimension � 2 dimension ( pour la r�solution matricielle
	    }
	}
	printf("\npuzzle initial defini\n");

	for (i=0;i<9;i++)
	{
	    for (j=0;j<9;j++)
	    {
	        printf("%d",initial_puzzle[i][j]); // On affiche la grille
	    }
	}
	printf("\nVerif bon puzzle initial\n");


// Fonction de Rusty Rossel
	/* Blank puzzle. */
	for (x = 0; x < 9; x++)
		for (y = 0; y < 9; y++)
			puzzle[y][x] = (1 << 9) - 1;

	printf("Adding known numbers...\n");
	for (x = 0; x < 9; x++) {
		for (y = 0; y < 9; y++) {
			if (!initial_puzzle[y][x])
				continue;
			puzzle[y][x] = 1 << (initial_puzzle[y][x] - 1);
			printf("We know %ix%i = %i\n", //Les nombres deja connus sont identifi�s
			       x+1, y+1, (puzzle[y][x]));
			eliminate(puzzle, x, y);
		}
	}

	printf("Deriving new numbers...\n"); // Les nouveaux nombres sont calcul�s
	do {
		progress = false;
		for (x = 0; x < 9; x++) {
			for (y = 0; y < 9; y++) {
				if (puzzle[y][x] & FINISHED)
					continue;
				progress |= try_cutdown(puzzle, x, y);
				progress |= try_matches(puzzle, x, y);
			}
		}
	} while(progress);
	dump(puzzle); // Une fois la grille r�solue : on renvoi la grille r�solue
//(voir la fonction dump : modifi� par nos soins pour s'integrer au logiciel et renvoyer tableau � 1 dimension)
}





