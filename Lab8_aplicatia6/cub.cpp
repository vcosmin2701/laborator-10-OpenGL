#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

static int angle = 0;

void myInit()
{

	glEnable(GL_DEPTH_TEST);

	// setari pentru sursa de lumina
	// intensitatea componentei ambientale din sursa 0 este nula
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	// intensitatea componentei difuze din sursa 0 este maxima pentru fiecare componenta de culoare
	GLfloat light_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	// intensitatea componentei speculare din sursa 0 este maxima pentru fiecrae compopnenta de culoare
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	// pozitia sursei de lumina nu este cea implicita
	GLfloat light_position[] = { 1.0, 0.0, 0.0, 0.0 };
	// sursa de lumina pe axa x la infinit
	GLfloat global_ambient[] = { 0.25, 0.25, 0.75, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// lumina ambientala in scena
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);


	glFrontFace(GL_CW); // orientarea implicita a varfurilor in sensul rotirii acelor
	glEnable(GL_LIGHTING); // activare iluminare
	glEnable(GL_LIGHT0); // activare sursa 0

	glEnable(GL_AUTO_NORMAL); // activare calculare normale daca varfurile s-au determinat cu GL_MAP2_VERTEX_3 sau GL_MAP2_VERTEX_4
	glEnable(GL_NORMALIZE); // activare normalizare (vectori unitari) vectori

}

void deseneazaCub()
{
	glBegin(GL_QUAD_STRIP); 
	{
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
	}
	glEnd();
}

void CALLBACK display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat more_ambient[] = { 0.5, 0.5, 0.5, 1.0 };

	glLoadIdentity();

	glMaterialfv(GL_FRONT, GL_AMBIENT, more_ambient);
	glPushMatrix();

	glTranslatef(0.0, 0.0, -4.0);
	glRotatef(angle, 1.0, 1.0, 0.0);

	deseneazaCub();
	glPopMatrix();

	auxSwapBuffers();


}


void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 3.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
}

void CALLBACK IdleFunction()
{
	angle += 1;
	display();
	Sleep(1000/60);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB | AUX_DEPTH);
	auxInitPosition(200, 100, 800, 600);
	auxInitWindow("CUB");
	myInit();
	auxReshapeFunc(myReshape);
	auxIdleFunc(IdleFunction);
	auxMainLoop(display);
	return 0;
}
