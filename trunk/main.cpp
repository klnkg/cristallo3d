#include "fenetre.h"

/* Les variables globales */
HINSTANCE instance;

int WinMain (HINSTANCE cetteInstance, HINSTANCE precedenteInstance,
LPSTR lignesDeCommande, int modeDAffichage)
{
    HWND fenetrePrincipale;
    MSG message;
    WNDCLASS classeFenetre;

    instance = cetteInstance;

    classeFenetre.style = 0;
    classeFenetre.lpfnWndProc = procedureFenetrePrincipale;
    classeFenetre.cbClsExtra = 0;
    classeFenetre.cbWndExtra = 0;
    classeFenetre.hInstance = NULL;
    classeFenetre.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    classeFenetre.hCursor = LoadCursor(NULL, IDC_ARROW);
    classeFenetre.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    classeFenetre.lpszMenuName =  NULL;
    classeFenetre.lpszClassName = "classeF";

    // On prévoit quand même le cas où ça échoue
    if(!RegisterClass(&classeFenetre)) return FALSE;

    fenetrePrincipale = CreateWindow("classeF", "OpenGL", WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
                                                   NULL, NULL, instance, NULL);

    if (!fenetrePrincipale) return FALSE;


    // Chargement de OpenGL
    Contexte_GL contexte_opengl;
    Rect position;
        position.x = 0;
        position.y = 0;
        position.w = 2*WIDTH/3;
        position.h = HEIGHT;
    init_gl(fenetrePrincipale, instance, &contexte_opengl, position);

    ShowWindow(fenetrePrincipale, modeDAffichage);
    UpdateWindow(fenetrePrincipale);

    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
        update_gl(&contexte_opengl);
    }

    delete_gl(&contexte_opengl);
    DestroyWindow(fenetrePrincipale);

    UnregisterClass("classF",instance);

    return message.wParam;
}
