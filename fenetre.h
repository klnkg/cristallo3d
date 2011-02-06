#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>


/* -----   Les types ----- */

typedef struct Fenetre Fenetre;
struct Fenetre
{
    HDC hDC;   // Contexte GDI
    HGLRC hRC; // Conexte de rendu permanent
    HWND hWnd; // Handle de la fenetre
    HINSTANCE hInstance;  // Instance de l'application
};

typedef struct Message Message;
struct Message
{
    MSG message; // Reserve a windows

    char	keys[256];			// Touches du clavier
    char	active;		        // Fenetre active ou non
    char	fullscreen;	        // Fenetre en mode plein ecran ou non
    char	screensaver;	    // Ecran de veille declanche
    char	monitorpower;	    // Ecran en mode sauvegarde d'energie
    char    resize;             // Indique si un resize de la fenetre a eu lieu
        GLsizei new_largeur;    // Donne la nouvelle largeur apres resize
        GLsizei new_hauteur;    // Donne la nouvelle largeur apres resize
    char    fermeture;          // Fermeture demandee ou non
};
/*
    char est un booleen, c est-a-dire variable qui prend les valeurs 0 ou 1, soit faux ou vrai.
    ici, un 1 signifie un appui et un 0 signifie un non-appui
*/


/* -----   Les variables globales ----- */
Message* messages;
/*
    Cette variable se doit d'etre en globale car elle est utilisee par la fonction CallBack
*/


/* -----   Les fonctions ----- */

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
/*
    Fonction un peu speciale. Cette fonction est la fonction CallBack. On ne l'appelera pas directement,
    elle est appelee par la fenetre elle-meme automatiquement. Elle recoit les messages (messages ~ evenements)
    Son implementation permet de gerer la structure message
*/

void ouvrir_fenetre(Fenetre* fenetre);  // A FAIRE
void creer_contexte_opengl(Fenetre* fenetre); // A FINIR
void eteindre_fenetre();

void init_messages(Message* message);
void dlt_messages(Message* message);

/*
    Fonction qui initialise les parametres de message par defaut
    Ne realise aucune allocation dynamique
*/


#endif // FENETRE_H_INCLUDED
