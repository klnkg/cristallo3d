#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

/* Les constantes */
#define WIDTH 800
#define HEIGHT 600

/* Les types */
typedef struct Rect Rect;
struct Rect
{
    int x;
    int y;
    int w;
    int h;
};

typedef struct Contexte_GL Contexte_GL;
struct Contexte_GL
{
    HWND hWnd;
    HDC dc;
    HGLRC rc;
};

typedef struct Fenetre Fenetre;
struct Fenetre
{
    HWND handle;
    MSG message;
    WNDCLASS classe;
    HINSTANCE instance;
};

LRESULT CALLBACK procedureFenetrePrincipale(HWND, UINT, WPARAM, LPARAM);

// Fonctions Windows
int ouvrir_fenetre(Fenetre* fenetre);

// Fonctions OpenGL
int  init_gl(HWND parent, HINSTANCE _instance, Contexte_GL* contexte, Rect position);
int  delete_gl(Contexte_GL* contexte);
void update_gl(Contexte_GL* contexte);

void sample_dessin();


#endif // FENETRE_H_INCLUDED
