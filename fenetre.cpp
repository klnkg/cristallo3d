#include "fenetre.h"

LRESULT CALLBACK procedureFenetrePrincipale(HWND fenetrePrincipale, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(fenetrePrincipale, message, wParam, lParam);
    }
}

int ouvrir_fenetre(Fenetre* fenetre)
{

    return 0;
}

int  init_gl(HWND parent, HINSTANCE _instance, Contexte_GL* contexte, Rect position)
{
    contexte->hWnd = CreateWindow("STATIC", NULL, WS_CHILD | WS_VISIBLE, position.x, position.y, position.w, position.h, parent, NULL, _instance, NULL);

    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // get the device context (DC)
    contexte->dc = GetDC( contexte->hWnd);

    // set the pixel format for the DC
    ZeroMemory( &pfd, sizeof( pfd ) );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat( contexte->dc, &pfd );
    SetPixelFormat( contexte->dc, iFormat, &pfd );

    // create and enable the render context (RC)
    contexte->rc = wglCreateContext(contexte->dc);
    wglMakeCurrent(contexte->dc, contexte->rc);

    return 0;
}

void update_gl(Contexte_GL* contexte)
{
    SwapBuffers(contexte->dc);
}

int  delete_gl(Contexte_GL* contexte)
{
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext(contexte->rc );
    ReleaseDC(contexte->hWnd, contexte->dc);
    DestroyWindow(contexte->hWnd);

    return 0;
}


void sample_dessin()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
        glColor3ub(0,255,0);    glVertex2d(0,0.75);
        glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
    glEnd();

    glFlush();
}
