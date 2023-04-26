#include<GL/glut.h>

#include<iostream>
#include<string>
#include<math.h>
using namespace std;

void display();
float xmin=-30;
float ymin=10;
float xmax=20;
float ymax=60;
float xd1,yd1,xd2,yd2;
float xa,ya,xb,yb,xc,yc,xd,yd,xe,ye,xf,yf,xg,yg,xh,yh,xi,yi,xj,yj;

void init(void)
{

    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-80,70,-40,110);
}


int code(float x,float y)
{
    int c=0;
    if(y>ymax)c=8;
    if(y<ymin)c=4;
    if(x>xmax)c=c|2;
    if(x<xmin)c=c|1;
    return c;
}

void mark_point(int x,int y,int xoffset, int yoffset, char str[]){
glColor3f(1.0,1.0,1.0);
    int w= glutBitmapLength(GLUT_BITMAP_HELVETICA_10, (unsigned char*)str);
    glRasterPos2f(x+xoffset,y+yoffset);
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str[i]);
}
}

void cohen_Line(float x1,float y1,float x2,float y2)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    while((c1|c2)>0)
    {
        if((c1 & c2)>0)
        {
           cout<<"Completely outisde\n";
  return;
        }

float xi=x1;float yi=y1;
    int c=c1;
    if(c==0)
    {
         c=c2;
         xi=x2;
         yi=y2;
    }
    float x,y;
    if((c & 8)>0)
    {
       y=ymax;
       x=xi+ 1.0/m*(ymax-yi);
    }
    else if((c & 4)>0)
    {
        y=ymin;
        x=xi+1.0/m*(ymin-yi);
    }
    else if((c & 2)>0)
    {
        x=xmax;
        y=yi+m*(xmax-xi);
    }
    else if((c & 1)>0)
    {
        x=xmin;
        y=yi+m*(xmin-xi);
    }

    if(c==c1)
    {
           xd1=x;
           yd1=y;
           c1=code(xd1,yd1);
    }

    if(c==c2)
       {
           xd2=x;
           yd2=y;
           c2=code(xd2,yd2);
       }
}
if((x1==xd1&&y1==yd1)&&(x2==xd2&&y2==yd2)){
cout<<"Fully inside\n";

}else{
cout<<"Partially clipped\n";
cout<<"Line Clipped at :\n";
if(!(x1==xd1&&y1==yd1)){
cout<<"("<<xd1<<","<<yd1<<")"<<endl;
}
if(!(x2==xd2&&y2==yd2)){
cout<<"("<<xd2<<","<<yd2<<")"<<endl;
}
}

}

void draw_line(float xi,float yi,float xf,float yf){
xd1=xi,xd2=xf,yd1=yi,yd2=yf;
cohen_Line(xi,yi,xf,yf);
int c1=code(xi,yi);
    int c2=code(xf,yf);
    if((c1 & c2)>0){
        glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xi,yi);
    glVertex2i(xf,yf);
    glEnd();
    }
    else{
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(xi,yi);
  glVertex2i(xd1,yd1);
  glEnd();
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(xd1,yd1);
  glVertex2i(xd2,yd2);
  glEnd();
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2i(xd2,yd2);
  glVertex2i(xf,yf);
  glEnd();
}
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_LINE_LOOP);
   glVertex2i(xmin,ymin);
   glVertex2i(xmin,ymax);
   glVertex2i(xmax,ymax);
   glVertex2i(xmax,ymin);
   glEnd();
   
   //Region Codes
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_LINE_LOOP);
   glVertex2i(-80,ymin);
   glVertex2i(70,ymin);
   glEnd();
   glBegin(GL_LINE_LOOP);
   glVertex2i(-80,ymax);
   glVertex2i(70,ymax);
   glEnd();
   glBegin(GL_LINE_LOOP);
   glVertex2i(xmax,-40);
   glVertex2i(xmax,110);
   glEnd();
   glBegin(GL_LINE_LOOP);
   glVertex2i(xmin,-40);
   glVertex2i(xmin,110);
   glEnd();
   mark_point(-80,110,5,-5,(char *)"1001");
   mark_point(-80,60,5,-5,(char *)"0001");
   mark_point(-80,10,5,-5,(char *)"0101");
   mark_point(-30,110,5,-5,(char *)"1000");
   mark_point(-30,60,5,-5,(char *)"0000");
   mark_point(-30,10,5,-5,(char *)"0100");
   mark_point(20,110,5,-5,(char *)"1010");
   mark_point(20,60,5,-5,(char *)"0010");
   mark_point(20,10,5,-5,(char *)"0110");
   
   
   // ----------
//   AB
cout<<"AB: ";
draw_line(xa,ya,xb,yb);
mark_point(xa,ya,-5,-5,(char *)"A (-40,20)");
mark_point(xb,yb,-5,-5,(char *)"B (-10,70)");
mark_point(-30,36.67,-5,-5,(char *)"(-30,36.67)");
   mark_point(-16,60,-5,-5,(char *)"(-16,60)");
//   CD
cout<<"CD: ";
draw_line(xc,yc,xd,yd);
mark_point(xc,yc,-5,-5,(char *)"C (-10,50)");
mark_point(xd,yd,-5,-5,(char *)"D (30,80)");
mark_point(3.33,60,-5,-5,(char *)"(3.33,60)");
//   BH
cout<<"BH: ";
draw_line(xb,yb,xh,yh);
mark_point(xb,yb,-5,-5,(char *)"B (-10,70)");
mark_point(xh,yh,-5,-5,(char *)"H (30,30)");
mark_point(0,60,-5,-5,(char *)"(0,60)");
   mark_point(20,40,-5,-5,(char *)"(20,40)");
//   EF
cout<<"EF: ";
draw_line(xe,ye,xf,yf);
mark_point(xe,ye,-5,-5,(char *)"E (-20,20)");
mark_point(xf,yf,-5,-5,(char *)"F (-10,20)");
//   IJ
cout<<"IJ: ";
draw_line(xi,yi,xj,yj);
mark_point(xi,yi,-5,-5,(char *)"I (-40,70)");
mark_point(xj,yj,-5,-5,(char *)"J (-20,100)");
//   DF
cout<<"DF: ";
draw_line(xd,yd,xf,yf);
mark_point(xd,yd,-5,-5,(char *)"D (30,80)");
mark_point(xf,yf,-5,-5,(char *)"F (-10,20)");
mark_point(16.67,60,-5,-5,(char *)"(16.67,60)");
//   EH
cout<<"EH: ";
draw_line(xe,ye,xh,yh);
mark_point(xe,ye,-5,-5,(char *)"E (-20,20)");
mark_point(xh,yh,-5,-5,(char *)"H (30,30)");
mark_point(20,30,-5,-5,(char *)"(20,30)");
//   EG
cout<<"EG: ";
draw_line(xe,ye,xg,yg);
mark_point(xe,ye,-5,-5,(char *)"E (-20,20)");
mark_point(xg,yg,-5,-5,(char *)"G (10,-20)");
mark_point(-8,10,-5,-5,(char *)"(-8,10)");
//   DJ
cout<<"DJ: ";
draw_line(xd,yd,xj,yj);
mark_point(xd,yd,-5,-5,(char *)"D (30,80)");
mark_point(xj,yj,-5,-5,(char *)"J (-20,100)");
//   FH
cout<<"FH: ";
draw_line(xf,yf,xh,yh);
mark_point(xf,yf,-5,-5,(char *)"F (-10,20)");
mark_point(xh,yh,-5,-5,(char *)"H (30,30)");
mark_point(20,27.5,-5,-5,(char *)"(20,27.5)");
   glFlush();
}

int main(int argc,char** argv)
{
xa=-40,ya=20,xb=-10,yb=70,xc=-10,yc=50,xd=30,yd=80,xe=-20,ye=30,xf=-10,yf=20,xg=10,yg=-20,xh=30,yh=30,xi=-40,yi=70,xj=-20,yj=100;
    cout<<"The region code of A is "<<code(xa,ya)<<endl;
    cout<<"The region code of B is "<<code(xb,yb)<<endl;
    cout<<"The region code of C is "<<code(xc,yc)<<endl;
    cout<<"The region code of D is "<<code(xd,yd)<<endl;
    cout<<"The region code of E is "<<code(xe,ye)<<endl;
    cout<<"The region code of F is "<<code(xf,yf)<<endl;
    cout<<"The region code of G is "<<code(xg,yg)<<endl;
    cout<<"The region code of H is "<<code(xh,yh)<<endl;
    cout<<"The region code of I is "<<code(xi,yi)<<endl;
    cout<<"The region code of J is "<<code(xj,yj)<<endl;
   
    cout<<"------------------------------"<<endl;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Clipping");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
