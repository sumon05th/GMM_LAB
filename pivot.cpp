
//Make a pivot point ,create pentagon based on a pivot point 
// .Make a pivot element on x and y axis having coordinate (0,0) and then 
// perform rotation ,scaling and translation of pentagon based on the pivot point.
#include <iostream>
#include <GL/glut.h>
using namespace std;
GLfloat px, py, Rotation;
GLfloat ax, ay, bx, by, cx, cy, dx, dy, ex, ey;
void myinit(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
}
void drawPentagon()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(ax, ay);
	glVertex2f(bx, by);
	glVertex2f(dx, dy);
	glVertex2f(cx, cy);
	glVertex2f(ex, ey);
	glEnd();
}
void drawQuadrants()
{
	glPointSize(3.0);
	glColor3f(0.0f, 0.5f, 0.5f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-500.0, 0.0, 0.0);
	glVertex3f(500.0, 0.0, 0.0);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, -500.0, 0.0);
	glVertex3f(0.0, 500.0, 0.0);
	glEnd();
}
void display()
{
	drawQuadrants();
	ax = 10.0, ay = 50.0;
	bx = 30.0, by = 50.0,
		cx = 10.0, cy = 15.0,
		dx = 30.0, dy = 15.0;
	ex = 5.0, ey = 20.0;
	px = -20.0, py = 40.0;
	glColor3f(1.0f, 1.0f, 1.0f);
	drawPentagon();
	GLfloat midX, midY;
	midX = (ax + bx + cx + dx + ex) / 5.0;
	midY = (ay + by + cy + dy + ey) / 5.0;
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(-midX, -midY, 0.0);
	glTranslatef(midX - px, midY - py, 0.0);
//	drawPentagon();
	Rotation = -90;
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(px, py, 0.0f);
	glRotatef(Rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-px, -py, 0.0f);
	drawPentagon();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(px, py, 0.0f);
	glRotatef(-Rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-px, -py, 0.0f);
	glTranslatef(px - midX, py - midY, 0.0);
	glTranslatef(midX, midY, 0.0);
	drawPentagon();
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(500, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Rotation of a pentagon based on pivot points");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
