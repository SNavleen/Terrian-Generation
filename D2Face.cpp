#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/freeglut.h>
#   include <windows.h>
#endif

#include "D2Face.h"
#include "Vertex.h"

//Constructors
D2Face::D2Face(){
}
D2Face::D2Face(int point1, int point2, int point3, int point4){
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
	this->point4 = point4;
}

//Deconstructor
D2Face::~D2Face(){
}

//Public function

/*D2Face drawEdge()*/
void D2Face::drawEdge(Vertex p1, Vertex p2, Vertex p3, Vertex p4, int meshsize){
	glBegin(GL_LINE_LOOP);
		glVertex2f(p1.posX/(meshsize/2)-1, p1.posZ/(meshsize/2)-1);
		glVertex2f(p2.posX/(meshsize/2)-1, p2.posZ/(meshsize/2)-1);
		glVertex2f(p4.posX/(meshsize/2)-1, p4.posZ/(meshsize/2)-1);
		glVertex2f(p3.posX/(meshsize/2)-1, p3.posZ/(meshsize/2)-1);
	glEnd();
}

void D2Face::drawFace(Vertex p1, Vertex p2, Vertex p3, Vertex p4, int meshsize){
	glBegin(GL_POLYGON);
		glVertex2f(p1.posX/(meshsize/2)-1, p1.posZ/(meshsize/2)-1);
		glVertex2f(p2.posX/(meshsize/2)-1, p2.posZ/(meshsize/2)-1);
		glVertex2f(p4.posX/(meshsize/2)-1, p4.posZ/(meshsize/2)-1);
		glVertex2f(p3.posX/(meshsize/2)-1, p3.posZ/(meshsize/2)-1);
	glEnd();
}
