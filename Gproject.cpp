
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>


float angel = 0;
#define RESL 0.02

GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 5;

GLdouble centerx = 0;
GLdouble centery = 0;
GLdouble centerz = 0;





void DrawSphere()
{
	
	static float pos = 0.0;

	float angle1, angle2;
	float xx, yy, zz, xxp, yyp, zzp;

	glClearColor(0.7f, 0.7f, 0.7f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor3f(0.0, 0.9, 1.0);

	
	glPushMatrix();

   //   glRotatef(angel, 1, 1, 0);
	
	
	for (angle2 = -3.1416 / 2; angle2 <= 3.14162 / 2; angle2 += RESL)
	{
		glBegin(GL_QUAD_STRIP);
		for (angle1 = 0.0; angle1 <= 3.1416 * 2.0 + RESL ; angle1 += RESL)
		{
			yy = sin(angle2);
			xx = cos(angle1) * cos(angle2);
			zz = sin(angle1) * cos(angle2);

			yyp = sin(angle2 + RESL);
			xxp = cos(angle1) * cos(angle2 + RESL);
			zzp = sin(angle1) * cos(angle2 + RESL);

		    glColor3f(zz*zz, xx*xx, 1);
			glVertex3f(xx, yy, zz);
			glVertex3f(xxp, yyp, zzp);
		}

		glEnd();

	}

	glPopMatrix();


}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body

	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}


void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, 0, 1, 0);
	
	//glRotatef(angel, 1, 0, 1);

	glPushMatrix();
	glTranslatef(1, -1, 0);
	DrawSphere();
	glPopMatrix();

	glPushMatrix();
	drawSnowMan();
	glPopMatrix();


	
	glutSwapBuffers();

}

void reshape(int w, int h)
{   
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	gluPerspective(50.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);

}



void myTimer(int val) {


	angel += 1; 


	glutPostRedisplay();
	glutTimerFunc(5, myTimer, 0);

}




void keyboard(unsigned char key, int x, int y) {



	if (key == 'q')
		eyez += 0.1;
	else
	{
		if (key == 'w')
			eyez -= 0.1;
	}
	//glutPostRedisplay();
	//reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	

	}

void SpecialKeys(int key, int x, int y)		
{
	switch (key)
	{
	case GLUT_KEY_LEFT:	eyex += 0.1;
		break;
	case GLUT_KEY_RIGHT:eyex -= 0.1;
		break;
	case GLUT_KEY_UP:	eyey -= 0.1;
		break;
	case GLUT_KEY_DOWN:	eyey += 0.1;
		break;
	}
	//glutPostRedisplay();
	//reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	
	return;
}

	





int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("popsoft");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);
	glutTimerFunc(100, myTimer, 0);
	
	glutMainLoop();


	getchar();

	return 0;



}
