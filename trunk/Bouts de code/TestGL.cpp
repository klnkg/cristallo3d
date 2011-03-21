#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "geometrie.h"
#include "TestGL.h"


void dessiner_repere(unsigned int echelle = 1)
{
    glPushMatrix();
    glScalef(echelle,echelle,echelle);
    glBegin(GL_LINES);
    glColor3ub(0,0,255);
        glVertex3i(0,0,0);
        glVertex3i(1,0,0);
    glColor3ub(0,255,0);
        glVertex3i(0,0,0);
        glVertex3i(0,1,0);
    glColor3ub(255,0,0);
        glVertex3i(0,0,0);
        glVertex3i(0,0,1);
    glEnd();
    glPopMatrix();
}


void dessiner_point(Point point, Couleur couleur, double x, double y, double z)
{
    glPushMatrix();
    glBegin(GL_POINTS);
    glTranslated(x,y,z); //à utiliser entre chaque atome/cylindre reliant les atomes
    glColor3ub(couleur.r,couleur.v,couleur.b);
    glVertex3i(point.x,point.y,point.z);
    glEnd();
    glPopMatrix();
}


void dessiner_ligne/*adapter*/(Ligne ligne/*adapter*/, Couleur couleur, double x, double y, double z)
{
    glPushMatrix();
    glBegin(GL_LINES/*adapter le GL*/);
    glTranslated(x,y,z); //à utiliser entre chaque atome/cylindre reliant les atomes
    glColor3ub(couleur.r,couleur.v,couleur.b);
    /*adapter les sommets à la figure géométrique*/
    glVertex3i(ligne.P.x,ligne.P.y,ligne.P.z);
    glVertex3i(ligne.Q.x,ligne.Q.y,ligne.Q.z);
    glEnd();
    glPopMatrix();
}


void dessiner_cylindre(Cylindre cylindre, Couleur couleur, double x, double y, double z)
{
    glPushMatrix();

    GLUquadric* params = gluNewQuadric();
    gluQuadricTexture(params,GL_FALSE);
    /*glBindTexture(GL_TEXTURE_2D,texture);*/
    glTranslated(x,y,z); //à utiliser entre chaque atome/cylindre reliant les atomes
    gluCylinder(params,cylindre.base,cylindre.top,cylindre.height,cylindre.slices, 1);

    gluDeleteQuadric(params);
    glPopMatrix();
}


void dessiner_sphere(Sphere sphere, Couleur couleur, double x, double y, double z)
{
    glPushMatrix();

    GLUquadric* params = gluNewQuadric();
    gluQuadricTexture(params,GL_FALSE);
    /*glBindTexture(GL_TEXTURE_2D,texture);*/
    glTranslated(x,y,z); //à utiliser entre chaque atome/cylindre reliant les atomes
    gluSphere(params,sphere.radius,sphere.slices,sphere.stacks);

    gluDeleteQuadric(params);
    glPopMatrix();
}
