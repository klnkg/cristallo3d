#include "fenetre.h"

LRESULT CALLBACK WndProc(HWND	hWnd, UINT	uMsg, WPARAM	wParam,	LPARAM	lParam)
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Le bouton minimise est active
		{
            messages->active = 1;
			return 0;
		}

		case WM_SYSCOMMAND:							// Commande emanent de windows
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Ecran de veille ?
                    messages->screensaver = 1;
				case SC_MONITORPOWER:				// Ecran en mode sauvegarde d'energie ?
                    messages->monitorpower = 1;
                    return 0;
                default : break;                    // Ni l'un ni l'autre, non traite
			}
			break;									// Pas de reel message
		}

		case WM_CLOSE:								// Appui sur la croix
		{
		    messages->fermeture = 1;
			return 0;
		}

		case WM_KEYDOWN:							// Touche pressee
		{
		    messages->keys[wParam] = 1;
			return 0;
		}

		case WM_KEYUP:								// Touche relachee
		{
		    messages->keys[wParam] = 0;
			return 0;
		}

		case WM_SIZE:								// Changement de taille de l'ecran
		{
		    messages->resize = 1;
		    messages->new_largeur = LOWORD(lParam);
		    messages->new_hauteur = HIWORD(lParam);
			return 0;
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void init_messages(Message* message)
{
    message = (Message*)malloc(sizeof(message));

    int i;
    for(i=0; i<256; i++)
        message->keys[i] = 0;
    message->active = 0;
    message->fullscreen = 0;
    message->screensaver = 0;
    message->monitorpower = 0;
    message->resize = 0;
    message->new_largeur = 0;
    message->new_hauteur = 0;
    message->fermeture = 0;
}

void dlt_messages(Message* message)
{
    free(message);
}

void ouvrir_fenetre(Fenetre* fenetre)
{
    // Configuration de la classe fenetre
    WNDCLASS classeFenetre;
        classeFenetre.style = 0;
        classeFenetre.lpfnWndProc = (WNDPROC) WndProc;
        classeFenetre.cbClsExtra = 0; // Inutile
        classeFenetre.cbWndExtra = 0; // Inutile
        classeFenetre.hInstance = NULL;
        classeFenetre.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Icone du programme
        classeFenetre.hCursor = LoadCursor(NULL, IDC_ARROW); // Curseur du programme
        classeFenetre.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE); // Couleur de fond de la fenetre
        classeFenetre.lpszMenuName =  NULL; // Menu associe à notre fenetre
        classeFenetre.lpszClassName = "classeF"; // Nom de la classe
    RegisterClass(&classeFenetre); // Sauvegarde des parametres que l'on vient de rentrer TESTER

    // Ouverture de la fenetre
    HWND main_fenetre = CreateWindow("classeF", "Cristallographie en relief", WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, GetModuleHandle(NULL), NULL); // TESTER

    /*
            On cree les deux parties

    */


    // Affichage de cette fenetre
    ShowWindow(main_fenetre,SW_SHOW);
    UpdateWindow(main_fenetre);

}

void creer_contexte_opengl(Fenetre* fenetre)
{

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,										    // Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

    // On recupere le device context correspondant a la zone
	fenetre->hDC=GetDC(fenetre->hWnd);							    // TESTER
	// On recupere et place le format pixel
	GLuint PixelFormat=ChoosePixelFormat(fenetre->hDC,&pfd);	// TESTER
    SetPixelFormat(fenetre->hDC,PixelFormat,&pfd);		    // TESTER

    // On recupere le contexte de rendu
	fenetre->hRC=wglCreateContext(fenetre->hDC);				        // TESTER

    // On active cette fenetre de rendu
	wglMakeCurrent(fenetre->hDC,fenetre->hRC);                        // TESTER

}

void eteindre_fenetre()
{
    PostQuitMessage(0);
}
