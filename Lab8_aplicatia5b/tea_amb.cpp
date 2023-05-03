/*
 *  Programul afiseaza trei cesti de ceai, cu aceeasi sursa de lumina
 *  dar cu diferite valori pentru coeficientii de reflexie pentru lumina ambientala
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static int spin = 10;

void CALLBACK moveLight(AUX_EVENTREC* event)
{
	spin = (spin + 20) % 360;
}

void myInit()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0); // pozitia de observare

	glPushMatrix();
	glRotated((GLdouble)spin, 0.0, 1.0, 0.0); // rotatia sursei

	GLfloat position[] = { 0.0, 0.0, 1.5, 1.0 }; // pozitia sursei w=1 pozitionala w=0 directionala
	glLightfv(GL_LIGHT0, GL_POSITION, position); // functie apelata

	// doar dupa ce s-a stabilit matricea de rotatie se deseneaza cubul corespunzand pozitiei sursei
	glTranslated(0.0, 0.0, 1.5);
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 1.0, 1.0);
	auxWireCube(0.5);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	// se deseneaza torul
	auxSolidTeapot(1.0);
	glPopMatrix();
	glFlush();

}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w, 4.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-4.0 * (GLfloat)w / (GLfloat)h, 4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 800, 800);
	auxInitWindow("Iluminarea ambientala pentru materiale cu coeficienti de reflexie diferiti");
	myInit();
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, moveLight);
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
