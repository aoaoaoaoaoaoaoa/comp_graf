#include <GL/freeglut.h>
#include "glu.h"
#include "gl.h"
#include <GL/glu.h> 
#include <math.h>
using namespace std;
struct point{
    double x;
    double y;
	double z;
}a, b, mouse;
bool textureMode = true;
bool lightMode = true;
bool AlphaBlending = false;
int xalfa=1, yalfa=1, zalfa=1;
double rotate_x=20;
double rotate_z=0;
double Zindex = 0;
float light0_diffuse[] = {0.4, 0.7, 0.2};
GLfloat pi     = acos(-1.0);
bool click = false;
void calculateNormal(point p1, point p2, point p3) {
	double u1 = p2.x - p1.x;
	double u2 = p2.y - p1.y;
	double u3 = p2.z - p1.z;

	double v1 = p3.x - p1.x;
	double v2 = p3.y - p1.y;
	double v3 = p3.z - p1.z;

	double normalX = u2 * v3 - u3 * v2;
	double normalY = u3 * v1 - u1 * v3;
	double normalZ = u1 * v2 - u2 * v1;

	double length = sqrt(normalX * normalX + normalY * normalY + normalZ * normalZ);

	normalX /= length;
	normalY /= length;
	normalZ /= length;

	glNormal3d(normalX, normalY, normalZ);
}
void init_light(GLfloat light0pos[]){
    glPushMatrix();
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_NORMALIZE);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
        glLightfv(GL_LIGHT0,GL_POSITION,light0pos);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glPopMatrix();
    
}
void click_exit(unsigned char key, int x, int y){
    switch(key){
        case 27: glutDestroyWindow(glutGetWindow());break;
        case 'w': rotate_x+=1;break;;
        case 's': rotate_x-=1; break;
        case 'd': rotate_z+=1; break;;
        case 'a':rotate_z-=1;break;

    };
}
void click_moise(int button, int type, int x, int y){
    if(button == GLUT_RIGHT_BUTTON ){
        if(zalfa >=2 && yalfa>=2 && xalfa>=2){
            xalfa--;
            yalfa--;
            zalfa--;
        }
        
    }
    else if(button == GLUT_LEFT_BUTTON ){
        xalfa++;
        yalfa++;
        zalfa++;
    }
}
void laba_1(){
	point A,B,C,D,E,F,G,L;
    point A1,B1,C1,D1,E1,F1,G1,L1;
	A.x=0, A.y=9, A.z=0;
	B.x=7, B.y=6, B.z=0;
	C.x=2, C.y=0, C.z=0;
	D.x=5,D.y=-5, D.z=0;
	E.x = 0, E.y = -9, E.z=0;
	F.x= -5, F.y=-7, F.z=0;
	G.x=0, G.y=0, G.z=0;
	L.x=-5, L.y=5, L.z=0;
    A1.x=0, A1.y=9, A1.z=-5;
	B1.x=7, B1.y=6, B1.z=-5;
	C1.x=2, C1.y=0, C1.z=-5;
	D1.x=5,D1.y=-5, D1.z=-5;
	E1.x = 0, E1.y = -9, E1.z=-5;
	F1.x= -5, F1.y=-7, F1.z=-5;
	G1.x=0, G1.y=0, G1.z=-5;
	L1.x=-5, L1.y=5, L1.z=-5;

    float radius = sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2))/2;
    glBegin( GL_TRIANGLE_FAN);
    glColor3f(0.5, 0.5, 0.1);
        for(float i =-acos(((A.x+B.x)/2-A.x)/radius); i <= pi-acos(((A.x+B.x)/2-A.x)/radius); i+=0.001f ) {
            point a, b,c;
            a.x=(B.x+ A.x)/2; a.y=(B.y+ A.y)/2; a.z=0;
            b.x=(B.x+ A.x)/2+cos(  i) *radius;b.y=(B.y+ A.y)/2+sin( i) * radius; b.z=0;
            c.x=(B.x+ A.x)/2+cos(  i+0.001f ) *radius;c.y=(B.y+ A.y)/2+sin( i+0.001f ) * radius; c.z=0;
            calculateNormal(a,b,c);
            glVertex3f((B.x+ A.x)/2+cos( i ) *radius,(B.y+ A.y)/2+sin(i ) * radius,0.0f);

        }
    glEnd();
    glBegin( GL_TRIANGLE_FAN);
    glColor3f(0.5, 0.5, 0.1);
        for(float i =-acos(((A.x+B.x)/2-A.x)/radius); i <= pi-acos(((A.x+B.x)/2-A.x)/radius); i+=0.001f ) {
            point a, b,c;
            a.x=(B.x+ A.x)/2; a.y=(B.y+ A.y)/2; a.z=-5;
            b.x=(B.x+ A.x)/2+cos(  i) *radius;b.y=(B.y+ A.y)/2+sin( i) * radius; b.z=-5;
            c.x=(B.x+ A.x)/2+cos(  i+0.001f ) *radius;c.y=(B.y+ A.y)/2+sin( i+0.001f ) * radius; c.z=-5;
            calculateNormal(a,b,c);
            glVertex3f((B.x+ A.x)/2+cos( i ) *radius,(B.y+ A.y)/2+sin(i ) * radius,-5.0f);
        }
    glEnd();
    glBegin( GL_QUADS);
    glColor3f(0.5, 0.5, 0.1);
        for(float i =-acos(((A.x+B.x)/2-A.x)/radius); i <= pi-acos(((A.x+B.x)/2-A.x)/radius); i+=0.001f ) {
            point a, b,c;
            a.x=(B.x+ A.x)/2+cos( i ) *radius; a.y=(B.y+ A.y)/2+sin(i ) * radius; a.z=0;
            b.x=(B.x+ A.x)/2+cos(  i+0.001f ) *radius;b.y=(B.y+ A.y)/2+sin( i+0.001f ) * radius; b.z=0;
            c.x=(B.x+ A.x)/2+cos(  i+0.001f ) *radius;c.y=(B.y+ A.y)/2+sin( i+0.001f ) * radius; c.z=-5;
            calculateNormal(a,b,c);
            glVertex3f((B.x+ A.x)/2+cos( i ) *radius,(B.y+ A.y)/2+sin(i ) * radius,0.0f);
            glVertex3f((B.x+ A.x)/2+cos( i+0.001f ) *radius,(B.y+ A.y)/2+sin(i+0.001f ) * radius,0.0f);
            glVertex3f((B.x+ A.x)/2+cos( i+0.001f ) *radius,(B.y+ A.y)/2+sin(i+0.001f ) * radius,-5.0f);
            glVertex3f((B.x+ A.x)/2+cos( i ) *radius,(B.y+ A.y)/2+sin(i) * radius,-5.0f);
        }
           
    glEnd();
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 1.0); //пурпурный
        calculateNormal(A,B,C);
        calculateNormal(B,C,G);
        calculateNormal(C,G,L);
        calculateNormal(G,L,A);
        calculateNormal(L,A,B);
		glVertex3d(A.x,A.y,A.z);
		glVertex3d(B.x,B.y,B.z);
		glVertex3d(C.x,C.y,C.z);
		glVertex3d(G.x,G.y,G.z);
		glVertex3d(L.x,L.y,L.z);
	//////////////////////////
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0); //красный
        calculateNormal(A1,B1,C1);
        calculateNormal(B1,C1,G1);
        calculateNormal(C1,G1,L1);
        calculateNormal(G1,L1,A1);
        calculateNormal(L1,A1,B1);
		glVertex3d(A.x,A.y,A.z-5);
		glVertex3d(B.x,B.y,B.z-5);
		glVertex3d(C.x,C.y,C.z-5);
		glVertex3d(G.x,G.y,G.z-5);
		glVertex3d(L.x,L.y,L.z-5);
	glEnd();
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 1.0); //пурпурный
        calculateNormal(G,C,D);
        calculateNormal(C,D,E);
        calculateNormal(D,E,F);
        calculateNormal(E,F,G);
        calculateNormal(F,G,C);
        glVertex3d(G.x,G.y,G.z);
        glVertex3d(C.x,C.y,C.z);
		glVertex3d(D.x,D.y,D.z);
		glVertex3d(E.x,E.y,E.z);
		glVertex3d(F.x,F.y,F.z);

	glEnd();
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0); //красный
        calculateNormal(G1,C1,D1);
        calculateNormal(C1,D1,E1);
        calculateNormal(D1,E1,F1);
        calculateNormal(E1,F1,G1);
        calculateNormal(F1,G1,C1);
        glVertex3d(G.x,G.y,G.z-5);
        glVertex3d(C.x,C.y,C.z-5);
		glVertex3d(D.x,D.y,D.z-5);
		glVertex3d(E.x,E.y,E.z-5);
		glVertex3d(F.x,F.y,F.z-5);

	glEnd();
	glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 1.0); //голубой
        calculateNormal(A,B,B1);
		glVertex3d(A.x,A.y,A.z);
        glVertex3d(B.x,B.y,B.z);
        glVertex3d(B.x,B.y,B.z-5);
		glVertex3d(A.x,A.y,A.z-5);	
	glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.6, 0.4, 0.2);
        calculateNormal(B,C,C1);
		glVertex3d(B.x,B.y,B.z);
        glVertex3d(C.x,C.y,C.z);
        glVertex3d(C.x,C.y,C.z-5);
		glVertex3d(B.x,B.y,B.z-5);	
	glEnd();
    glBegin(GL_QUADS);
		glColor3f(0.6, 0.4, 0.8);
        calculateNormal(C,D,D1);
		glVertex3d(C.x,C.y,C.z);
        glVertex3d(D.x,D.y,D.z);
        glVertex3d(D.x,D.y,D.z-5);
		glVertex3d(C.x,C.y,C.z-5);	
	glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.3, 0.1, 0.2);
        calculateNormal(D,E,E1);
        glVertex3d(D.x,D.y,D.z);
        glVertex3d(E.x,E.y,E.z);
        glVertex3d(E.x,E.y,E.z-5);
		glVertex3d(D.x,D.y,D.z-5);	
	glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.2, 1.0, 0.5);
        calculateNormal(E,F,F1);
        glVertex3d(E.x,E.y,E.z);
        glVertex3d(F.x,F.y,F.z);
        glVertex3d(F.x,F.y,F.z-5);
		glVertex3d(E.x,E.y,E.z-5);	
	glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0); //синий
        calculateNormal(F,G,G1);
        glVertex3d(F.x,F.y,F.z);
        glVertex3d(G.x,G.y,G.z);
        glVertex3d(G.x,G.y,G.z-5);
		glVertex3d(F.x,F.y,F.z-5);	
	glEnd();
    glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 1.0); //синий
        calculateNormal(L,G,G1);
        glVertex3d(L.x,L.y,L.z);
        glVertex3d(G.x,G.y,G.z);
        glVertex3d(G.x,G.y,G.z-5);	
        glVertex3d(L.x,L.y,L.z-5);
	glEnd();
    glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 0.0); //желтый
        calculateNormal(L,A,A1);
        glVertex3d(L.x,L.y,L.z);
        glVertex3d(A.x,A.y,A.z);
        glVertex3d(A.x,A.y,A.z-5);
		glVertex3d(L.x,L.y,L.z-5);	
	glEnd();


}
void ClientToOpenGL(int x, int y, double *ox, double *oy, double *oz){
    int vp[4];
    double mmatrix[16],pmatrix[16];
    float z;
    glGetIntegerv(GL_VIEWPORT,vp);
    y=vp[3]-y-1;
    glGetDoublev(GL_MODELVIEW_MATRIX,mmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX,pmatrix);
    glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&z);
    gluUnProject(x,y,z,mmatrix,pmatrix,vp,ox,oy,oz);
}
void active_move_mause(int x, int y){
    double ox,oy, oz;
    ClientToOpenGL(x,y,&ox,&oy,&oz);
    GLfloat light0pos[]={(float)ox,(float)oy,(float)oz, 0};
    glDisable(GL_LIGHTING);
    //init_light(light0pos);
    glutPostRedisplay();
}

void Reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    glMatrixMode(GL_MODELVIEW);
}
void rotate_camera(){

    glLoadIdentity();
    glOrtho(-xalfa, xalfa, -yalfa, yalfa, -zalfa, zalfa);
    glRotatef(rotate_x,1,0,0);
    glRotatef(rotate_z,0,0,1);
    //glDisable(GL_LIGHTING);
    //init_light();
    glutPostRedisplay();

    
}
double f(double p1, double p2, double p3, double p4, double t)
{
	return p1 * (2*t*t*t-3*t*t+1) + p2 * (t * t * t - 2 * t * t + t) + p3 * (-2 * t * t * t + 3 * t * t) + p4 * (t*t*t-t*t); //посчитанная формула
}
void laba3(){
    //кривая Эрмита (1)
	double P1[] = { 0,0,0 }; //Наши точки
	double P2[] = { 2,4,8 };
	double P3[] = { 6,10,4 };
	double P4[] = {2, 4,-4};
	double P6[] = { 8,14,0 };
	double P[4];
	glBegin(GL_LINE_STRIP); 
	glVertex3dv(P1);
	glVertex3dv(P2);
	
	glEnd();
	glBegin(GL_LINE_STRIP); 
	
	glVertex3dv(P3);
	glVertex3dv(P6);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01)
	{
		P[0] = f(P1[0], P2[0], P3[0], P4[0], t);
		P[1] = f(P1[1], P2[1], P3[1], P4[1], t);
		P[2] = f(P1[2], P2[2], P3[2], P4[2], t);
		P[3] = f(P1[3], P2[3], P3[3], P4[3], t);
		glVertex3dv(P); //Рисуем точку P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(P);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P6);
	glEnd();

	


	//кривая Эрмита (2)
	double P11[] = { 0,0,0 }; //Наши точки
	double P22[] = { 4,2,12 };
	double P33[] = { 10,4,2 };
	double P44[] = { 4, 2,-4 };
	double P66[] = { 14,6,0 };
	double P5[4];
	glBegin(GL_LINE_STRIP); 
	glColor3d(0, 0, 0);
	glVertex3dv(P11);
	glVertex3dv(P22);

	glEnd();
	glBegin(GL_LINE_STRIP); 
	glColor3d(0, 0, 0);
	glVertex3dv(P33);
	glVertex3dv(P66);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01)
	{
		P5[0] = f(P11[0], P22[0], P33[0], P44[0], t);
		P5[1] = f(P11[1], P22[1], P33[1], P44[1], t);
		P5[2] = f(P11[2], P22[2], P33[2], P44[2], t);
		P5[3] = f(P11[3], P22[3], P33[3], P44[3], t);
		glVertex3dv(P5); //Рисуем точку P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(P5);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(P11);
	glVertex3dv(P22);
	glVertex3dv(P33);
	glVertex3dv(P66);
	glEnd();

}
void laba31(){
    //кривая Безье 3 порядка (1)
	double P1[] = { 0,0,0 }; //Наши точки
	double P2[] = { -4,6,7 };
	double P3[] = { 6,10,0 };
	double P4[] = {10, 4,2};
	double P[4];
	glBegin(GL_LINE_STRIP); //построим отрезки P1P2 и P2P3 и P3P4
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01)
	{
		P[0] = f(P1[0], P2[0], P3[0], P4[0], t);
		P[1] = f(P1[1], P2[1], P3[1], P4[1], t);
		P[2] = f(P1[2], P2[2], P3[2], P4[2], t);
		glVertex3dv(P); //Рисуем точку P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(P);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();


	//кривая Безье 3 порядка (2)
	double P11[] = { 0,0,0 }; //Наши точки
	double P22[] = { 10,0,6 };
	double P33[] = { 9,-5,8 };
	double P44[] = { 10, -5,2 };
	double P5[4];
	glBegin(GL_LINE_STRIP); //построим отрезки P1P2 и P2P3 и P3P4
	glColor3d(0, 0, 0);
	glVertex3dv(P11);
	glVertex3dv(P22);
	glVertex3dv(P33);
	glVertex3dv(P44);
	glEnd();
	glLineWidth(3); //ширина линии
	glColor3d(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01)
	{
		P5[0] = f(P11[0], P22[0], P33[0], P44[0], t);
		P5[1] = f(P11[1], P22[1], P33[1], P44[1], t);
		P5[2] = f(P11[2], P22[2], P33[2], P44[2], t);
		glVertex3dv(P5); //Рисуем точку P
	}
	glEnd();
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	//нарисуем все точки
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3dv(P);
	glEnd();
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex3dv(P11);
	glVertex3dv(P22);
	glVertex3dv(P33);
	glVertex3dv(P44);
	glEnd();
}
void draw_axes(){
    glBegin(GL_LINES);
        glColor3f(  0.0,  0.0,  0.0 );
        glVertex3f(  0.0, 0.0, 0.0 );
        glVertex3f(  0.0,  0.0, 10 );
    glEnd();
    // Фиолетовая сторона — Y
    glBegin(GL_LINES);
        glColor3f(  1.0,  0.0,  1.0 );
        glVertex3f( 0.0, 0.0, 0.0);
        glVertex3f( 0.0,  10, 0.0);
    glEnd();
    // Зеленая сторона — X
    glBegin(GL_LINES);
        glColor3f(   0.0,  1.0,  0.0 );
        glVertex3f( 0.0, 0.0,0.0);
        glVertex3f( 10,0.0, 0.0);
    glEnd();

}
void axes(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	rotate_camera();
	draw_axes();
	laba_1();
    //laba3();
    //laba31();
	glFlush();
    glutSwapBuffers(); 

}
void Wheel(int wh,int dir,int x,int y)
{
    if(dir == 1)
    {
        ++Zindex;
    }
    else{
        --Zindex;
    }
    glutPostRedisplay();
}
int main(int argc, char *argv[]){
    //инициаллизация;
    glutInit(&argc, argv); 
    glutInitWindowSize(700, 700); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutCreateWindow("app");
    glEnable(GL_DEPTH_TEST);
    //источник света
    //init_light();
    glClearColor(1.0, 1.0, 1.0, 1.0);/*Заполним экран белым фоном*/
    //вызываю обработчики событий
    glutReshapeFunc(Reshape);
    glutDisplayFunc(axes);
    glutKeyboardFunc(click_exit);
    glutMouseFunc(click_moise);
    glutPassiveMotionFunc(active_move_mause);
    glutMouseWheelFunc(Wheel);

    //цикл
    glutMainLoop(); 
    return 0; 

}