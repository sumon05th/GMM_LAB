Let r be the rectangular window, whose upper left hand corner is at L(20,-30) and lower right hand corner is at R(90,-100). The coordinates of some the the points are given below-
A(20,-60) 
B(90,-20)
C(0,0)
D(30,-20)
E(50,0) 
F(50,-200) 
G(40,20)
H(140,-160)
I(-200,10) 
J(100,-90)
Write a program to clip the given below line using mid-point subdivision algorithm. The lines are 
AB, CD, EF, GH, IJ

#include <GL/gl.h>
#include <iostream>
#include <cstring>
#include <GL/glut.h>
#include <math.h>
using namespace std;

void display();
float xmin = 20;
float ymin = -100;
float xmax = 90;
float ymax = -30;
float xd1, yd1, xd2, yd2;
float xa, ya, xb, yb, xc, yc, xd, yd, xe, ye, xf, yf, xg, yg, xh, yh, xi, yi, xj, yj;

void init(void)
{

  glClearColor(0.0, 0, 0, 0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-250, 200, -250, 50);
}

int code(float x, float y)
{
  int c = 0;
  if (y > ymax)
    c = 8;
  if (y < ymin)
    c = 4;
  if (x > xmax)
    c = c | 2;
  if (x < xmin)
    c = c | 1;
  return c;
}

void mark_point(int x, int y, int xoffset, int yoffset, char str[])
{
  glColor3f(1.0, 1.0, 1.0);
  int w = glutBitmapLength(GLUT_BITMAP_HELVETICA_10, (unsigned char *)str);
  glRasterPos2f(x + xoffset, y + yoffset);
  int len = strlen(str);
  for (int i = 0; i < len; i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
  }
}

bool isBorderPoint(int px, int py){
	if((py == ymin && px>=xmin && px<=xmax) || py == ymax && px>=xmin && px<=xmax || px == xmin && py>=ymin && py<=ymax || px == xmax && py>=ymin && py<=ymax) {
		return true;
	}
	return false;
}

void draw_original(float xi, float yi, float xf, float yf)
{
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(xi, yi);
  glVertex2i(xf, yf);
  glEnd();
}

void draw_line(float xi, float yi, float xf, float yf)
{
  int c1 = code(xi, yi);
	if(isBorderPoint(xi, yi)) c1 = 0;
  int c2 = code(xf, yf);
	if(isBorderPoint(xf, yf)) c2 = 0;

  // if it's inside draw
  if ((c1 | c2) == 0)
  {
    // line is inside
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    	glVertex2i(xi, yi);
    	glVertex2i(xf, yf);
    glEnd();
  }
  else if ((c1 & c2) != 0)
  {
    // line is outside
    return;
  }
  else if((abs(xi-xf)>1 || abs(yi-yf)>1))
  {
    // line is partially inside
    float xm = (xi + xf) / 2, ym = (yi + yf) / 2;
    draw_line(xi, yi, xm, ym);
    draw_line(xm, ym, xf, yf);
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2.0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(xmin, ymin);
  glVertex2i(xmin, ymax);
  glVertex2i(xmax, ymax);
  glVertex2i(xmax, ymin);
  glEnd();

  // Region Codes
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(-250, ymin);
  glVertex2i(200, ymin);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex2i(-250, ymax);
  glVertex2i(200, ymax);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex2i(xmax, -250);
  glVertex2i(xmax, 50);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex2i(xmin, -250);
  glVertex2i(xmin, 50);
  glEnd();
  mark_point(-250, 50, 10, -10, (char *)"1001");
  mark_point(-250, -30, 10, -10, (char *)"0001");
  mark_point(-250, -100, 10, -10, (char *)"0101");
  mark_point(20, 50, 10, -10, (char *)"1000");
  mark_point(20, -30, 10, -10, (char *)"0000");
  mark_point(20, -100, 10, -10, (char *)"0100");
  mark_point(90, 50, 10, -10, (char *)"1010");
  mark_point(90, -30, 10, -10, (char *)"0010");
  mark_point(90, -100, 10, -10, (char *)"0110");

  // ----------
  //   AB
  cout << "AB: ";
  draw_original(xa, ya, xb, yb);
  draw_line(xa, ya, xb, yb);
  mark_point(xa, ya, -5, -5, (char *)"A(20, -60)");
  mark_point(xb, yb, -5, -5, (char *)"B(90, -20)");
  mark_point(72.5,-30,0,-5,(char *)"(72.5,-30)");
  //   CD
  cout << "CD: ";
  draw_original(xc, yc, xd, yd);
  draw_line(xc, yc, xd, yd);
  mark_point(xc, yc, -5, -5, (char *)"C(0, 0)");
  mark_point(xd, yd, -5, -5, (char *)"D(30, -20)");
  //   EF
  cout << "EF: ";
  draw_original(xe, ye, xf, yf);
  draw_line(xe, ye, xf, yf);
  mark_point(xe, ye, -5, -5, (char *)"E(50, 0)");
  mark_point(xf, yf, -5, -5, (char *)"F(50, -200)");
  mark_point(50,-30,-15,-5,(char *)"(50,-30)");
  mark_point(50,-100,2,-5,(char *)"(50,-100)");
  //   GH
  cout << "GH: ";
  draw_original(xg, yg, xh, yh);
  draw_line(xg, yg, xh, yh);
  mark_point(xg, yg, -5, -5, (char *)"G(40, 20)");
  mark_point(xh, yh, -5, -5, (char *)"H(140, -160)");
  mark_point(67.7,-30,-10,5,(char *)"(67.7,-30)");
  mark_point(90,-70,2,2,(char *)"(90,-70)");
  //   IJ
  cout << "IJ: ";
  draw_original (xi, yi, xj, yj);
  draw_line(xi, yi, xj, yj);
  mark_point(xi, yi, -5, -5, (char *)"I(-200, 10)");
  mark_point(xj, yj, -5, -5, (char *)"J(100, -90)");
  mark_point(20,-63.3,-20,-5,(char *)"(20,-63.3)");
  mark_point(90,-86.67,-20,-5,(char *)"(90,-86.67)");
  glFlush();
}

int main(int argc, char **argv)
{
  xa = 20, ya = -60, xb = 90, yb = -20, xc = 0, yc = 0, xd = 30, yd = -20, xe = 50, ye = 0, xf = 50, yf = -200, xg = 40, yg = 20, xh = 140, yh = -160, xi = -200, yi = 10, xj = 100, yj = -90;
  cout << "------------------------------" << endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Clipping");
  glutDisplayFunc(display);
  init();
  glutMainLoop();
  return 0;
}