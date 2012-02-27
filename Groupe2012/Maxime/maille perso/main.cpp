#include <windows.h>

#define Y_CHAR 15
#define ID_NB_A 2
#define ID_NB_B 3
#define ID_NB_C 4
#define ID_NB_ALPHA 5
#define ID_NB_BETA 6
#define ID_NB_GAMMA 7
#define PM 90
#define ENTETE 0
#define ID_NOMFICHIER 8
#define ID_NOMAUTEUR 9
#define ATOME 163
#define ID_NOMATOME 9
#define ID_SYM 10
#define SYM 255
#define ID_PC 11
#define PC 347
#define ID_ENREG 12
#define OTHER 429
#define ID_AIDE 13
#define ID_NOMMAILE 14

HINSTANCE instance;

LRESULT CALLBACK procedureFenetrePrincipale(HWND, UINT, WPARAM, LPARAM);

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

    // On pr�voit quand m�me le cas o� �a �choue
    if(!RegisterClass(&classeFenetre)) return FALSE;

    fenetrePrincipale = CreateWindow("classeF", "Cr�ation personnelle de fichier .cif", WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT, 500, 538,
                                                   NULL, NULL, cetteInstance, NULL);
    if (!fenetrePrincipale) return FALSE;

    ShowWindow(fenetrePrincipale, modeDAffichage);
    UpdateWindow(fenetrePrincipale);


    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    return message.wParam;
}

LRESULT CALLBACK procedureFenetrePrincipale(HWND fenetrePrincipale, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND boutons[20] = {NULL};

    switch (message)
    {
        case WM_CREATE:

               CreateWindow("STATIC", "a :", WS_CHILD | WS_VISIBLE, 15,PM+25, 30, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "b :", WS_CHILD | WS_VISIBLE, 155,PM+25, 30, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "c :", WS_CHILD | WS_VISIBLE, 305,PM+25, 30, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "alpha :", WS_CHILD | WS_VISIBLE, 15,PM+45, 80, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "b�ta :", WS_CHILD | WS_VISIBLE, 155,PM+45, 80, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "gamma :", WS_CHILD | WS_VISIBLE, 305,PM+45, 80, Y_CHAR+5, fenetrePrincipale, NULL, instance, NULL);
                boutons[0] = CreateWindow("BUTTON", "Parametres de Maille", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,PM+5, 475,Y_CHAR*4.5, fenetrePrincipale, NULL, instance, NULL);
                boutons[1] = CreateWindow("EDIT", "5.4533", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_AUTOHSCROLL,35,PM+25, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_A, instance, NULL);
                boutons[2] = CreateWindow("EDIT", "5.4533", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_AUTOHSCROLL,185,PM+25, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_B, instance, NULL);
                boutons[3] = CreateWindow("EDIT", "5.4533", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_AUTOHSCROLL,335,PM+25, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_C, instance, NULL);
                boutons[4] = CreateWindow("EDIT", "90", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,65,PM+45, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_ALPHA, instance, NULL);
                boutons[5] = CreateWindow("EDIT", "90", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,215,PM+45, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_BETA, instance, NULL);
                boutons[6] = CreateWindow("EDIT", "90", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,375,PM+45, 50, Y_CHAR, fenetrePrincipale, (HMENU)ID_NB_GAMMA, instance, NULL);


                boutons[7] = CreateWindow("BUTTON", "Ent�te", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,ENTETE+5, 475,Y_CHAR*5.7, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "Nom du fichier        :", WS_CHILD | WS_VISIBLE, 15,ENTETE+45, 130, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "Nom de l'auteur      :", WS_CHILD | WS_VISIBLE, 15,ENTETE+25, 135, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
               CreateWindow("STATIC", "Formule Chimique  :", WS_CHILD | WS_VISIBLE, 15,ENTETE+65, 130, Y_CHAR, fenetrePrincipale, NULL, instance, NULL);
                boutons[8] = CreateWindow("EDIT", "BiTe.cif", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,185,ENTETE+45, 100, Y_CHAR, fenetrePrincipale, (HMENU)ID_NOMFICHIER, instance, NULL);
                boutons[9] = CreateWindow("EDIT", "M. Dupont", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,185,ENTETE+25, 100, Y_CHAR, fenetrePrincipale, (HMENU)ID_NOMAUTEUR, instance, NULL);
                boutons[10] = CreateWindow("EDIT", "Bi Te", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,185,ENTETE+65, 100, Y_CHAR, fenetrePrincipale, (HMENU)ID_NOMMAILE, instance, NULL);

                boutons[11] = CreateWindow("BUTTON", "Atomes", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,ATOME+5, 475,Y_CHAR*5.8, fenetrePrincipale, NULL, instance, NULL);
                boutons[12] = CreateWindow("EDIT", "Bi 0.00000 0.00000 0.00000\r\nTe 0.50000 0.50000 0.50000", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE| ES_AUTOVSCROLL,10,ATOME+25, 462, Y_CHAR*4, fenetrePrincipale, (HMENU)ID_NOMATOME, instance, NULL);

                boutons[13] = CreateWindow("BUTTON", "Sym�tries (Optionnel)", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,SYM+5, 475,Y_CHAR*5.8, fenetrePrincipale, NULL, instance, NULL);
                boutons[14] = CreateWindow("EDIT", "x,y,z\r\n-x,-y,-z", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE| ES_AUTOVSCROLL,10,SYM+25, 462, Y_CHAR*4, fenetrePrincipale, (HMENU)ID_SYM, instance, NULL);

                boutons[15] = CreateWindow("BUTTON", "Parametres connaisseur (Optionnel)", WS_CHILD | WS_VISIBLE|BS_GROUPBOX, 5,PC+5, 475,Y_CHAR*5.8, fenetrePrincipale, NULL, instance, NULL);
                boutons[16] = CreateWindow("EDIT", "loop_", WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE| ES_AUTOVSCROLL,10,PC+25, 462, Y_CHAR*4, fenetrePrincipale, (HMENU)ID_PC, instance, NULL);
                boutons[17] = CreateWindow("BUTTON", "Enregistrer", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,5,OTHER+25, 233, Y_CHAR*2, fenetrePrincipale, (HMENU)ID_ENREG, instance, NULL);
                boutons[18] = CreateWindow("BUTTON", "Aide", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,5+240,OTHER+25, 233, Y_CHAR*2, fenetrePrincipale, (HMENU)ID_AIDE, instance, NULL);
return 0;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_NB_A: // ON PEUT METTRE TOUT LES CODES

                    break;

                case ID_NB_B:

                    break;

                case ID_NB_C:

                    break;
                case ID_NB_ALPHA:

                    break;
                case ID_NB_BETA:

                    break;
                case ID_NB_GAMMA:

                    break;
                case ID_NOMAUTEUR:

                    break;
                case ID_NOMFICHIER:

                    break;
                case ID_NOMMAILE:

                    break;
                case ID_SYM:

                    break;
                case ID_PC:

                    break;
                case ID_ENREG:
                // LA QUIL FAUT METTRE
                MessageBox(NULL,"fichier .cif cr��","Enregistrement",MB_OK);

                    break;
                case ID_AIDE:
                    HINSTANCE err = ShellExecute(NULL,"open", "aide1.pdf",NULL, "extern2",SW_SHOWNORMAL);
                    if((int)err ==  SE_ERR_NOASSOC)
                    MessageBox(NULL, "Erreur : Adobe Reader n'est pas associ� avec les fichiers pdf", "Aide",MB_OK);
                    break;


            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(fenetrePrincipale, message, wParam, lParam);
    }
}
