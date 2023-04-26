//Let R be the rectangular window whose upper right hand corner is (-30,-30) and lower left hand corner is (-100,-100).
//The co-ordinates of some of the points are given below.
//1) A (-40,-40)
//2) B (-80,-80)
//3) C (-120,-30)
//4) D (-100,-100)
//5) E (-50,0)
//6) F (-50,-120)
//7) G (-20,-50)
//8) H (-140,50)
//9) I (-40,10)
//10)J(-110,-110)
//
//WAP to clip the given below lines using Liang Barsky's line clipping algorithm.
//AB, CD, EF, GH, IJ
#include<stdio.h>
#include<GL/glut.h>
#include <string.h>


using namespace std;
double xmin=-100, ymin=-100, xmax=-30,ymax=-30; 
float pts[10][2];
char* to_string(float val){
	char* s="";
	char str[20];
	sprintf(str,"%.2f",val);
	int n=strlen(str);
	for(int i=0;i<n-1;i++)s+=str[i];
	return s;
}
int cliptest(double p,double q,double *t1,double *t2)
{      
// p is denominator in division and q is numerator                 
// t1 is t entering and t2 is t leaving
    double t=q/p;
    if(p<0.0)   //potentially entry point ,update te          
    {    if(t>*t1) *t1=t;
        if(t>*t2) return(0); 
		//line portion is outside as in line no 2 where t(entering) has become more than t(leaving)
    }
    else if(p>0.0) //potentially leaving point ,update tl
        {
        if(t<*t2) *t2=t;
            if(t<*t1) return(0); //line portion is outside
        }
        else if(p==0.0)
            { if(q<0.0)
                 return(0);//line parallel to edge but outside
            }
            return(1);
}
void mark_point(float x, float y, char* s)
{
	float xoffset=.3,  yoffset=-.3;
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x + xoffset, y + yoffset);
    for (int i = 0; i < strlen(s); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
    }
}
void liangbaraskylineclipanddraw(double x0,double y0,double x1,double y1)
{
	double x2=x0,y2=y0,x3=x1,y3=y0;
    double dx= x1-x0,dy=y1-y0, te=0.0,tl=1.0;
    if(cliptest(-dx,x0-xmin,&te,&tl))// inside test wrt left edge
// t for the left edge is t=(xmin-x0) /dx .... order of numerator is reversed and you get -dx
    if(cliptest(dx,xmax-x0,&te,&tl))// inside test wrt right edge
// t for the right edge is t=(xmax-x0)/dx.... first parameter becomes q and second p then t=q/p
    if(cliptest(-dy,y0-ymin,&te,&tl))// inside test wrt bottom edge
// same story numerator by demoninator to find t
    if(cliptest(dy,ymax-y0,&te,&tl))// inside test wrt top edge
// in one way cohen sutherland and liang barasky are similar
    {
        if(tl<1.0)
        {
            x1=x0+tl*dx;
            y1=y0+tl*dy;
        }
        if(te>0.0)
        {
            x0=x0+te*dx;
            y0=y0+te*dy;
        }
    }

        glColor3f(0.0,0.0,1.0); 
		//draw blue colored clip line
        glBegin(GL_LINES);
        glVertex2d(x0,y0);
        glVertex2f(x1,y1);
        glEnd();

}

void draw_line(int i, int j, char* a, char* b)
{
	float xi=pts[i][0],yi=pts[i][1],xf=pts[j][0],yf=pts[j][1];
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(xi, yi);
        glVertex2i(xf, yf);
    glEnd();
    liangbaraskylineclipanddraw(xi,yi,xf,yf);
	
	mark_point(xi,yi, a);
	mark_point(xf,yf, b);
}

void display()
{
    //draw a blue color window
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
	    glVertex2i(xmin, ymin);
	    glVertex2i(xmin, ymax);
	    glVertex2i(xmax, ymax);
	    glVertex2i(xmax, ymin);
    glEnd();

   	draw_line(0,1,"A(-40,-40)"," B(-80,-80)");
    draw_line(2,3,"C(-120,-30)","D(-100,-100)");
    draw_line(4,5,"E(-50,0)","F(-50,-120)");
    draw_line(6,7,"G(-20,-50)","H(-140,50)");
    draw_line(8,9,"I(-40,10)","J(-110,-110)");
    glFlush();
}
void myinit()
{   
    glClearColor(0.0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 100, -200, 100);
}
int main(int argc, char** argv)
{
	pts[0][0]=-40,pts[0][1]=-40;
	pts[1][0]=-80,pts[1][1]=-80;
	pts[2][0]=-120,pts[2][1]=-30;
	pts[3][0]=-100,pts[3][1]=-100;
	pts[4][0]=-50,pts[4][1]=0;
	pts[5][0]=-50,pts[5][1]=-120;
	pts[6][0]=-20,pts[6][1]=-50;
	pts[7][0]=-140,  pts[7][1]=50;
	pts[8][0]=-40,pts[8][1]=10;
	pts[8][0]=-110,  pts[8][1]=-110;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(0,0);
    glutCreateWindow("liang barsky line clipping algorithm");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}