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

#include "Face.h"
#include "Vertex.h"

//Constructors
Face::Face(){
}
Face::Face(int point1, int point2, int point3, int point4){
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
	this->point4 = point4;
}

//Deconstructor
Face::~Face(){
}

//Public function

/*Face getNormalize(Vertex p1)*/
float* Face::getNormalize(Vertex p1){
	float length = sqrt(p1.posX*p1.posX + p1.posY*p1.posY + p1.posZ*p1.posZ);
	float normalize[3] = {p1.posX/length, p1.posY/length, p1.posZ/length};
	return normalize;
}
/*Face drawEdge()*/
void Face::drawEdge(Vertex p1, Vertex p2, Vertex p3, Vertex p4){
	glBegin(GL_LINE_LOOP);
		float *normalize = getNormalize(p1);
		glNormal3f(normalize[0], normalize[1], normalize[2]);
		glVertex3f(p1.posX, p1.posY, p1.posZ);

		normalize = getNormalize(p2);
		glNormal3f(normalize[0], normalize[1], normalize[2]);
		glVertex3f(p2.posX, p2.posY, p2.posZ);

		normalize = getNormalize(p3);
		glNormal3f(normalize[0], normalize[1], normalize[2]);
		glVertex3f(p4.posX, p4.posY, p4.posZ);

		normalize = getNormalize(p4);
		glNormal3f(normalize[0], normalize[1], normalize[2]);
		glVertex3f(p3.posX, p3.posY, p3.posZ);
	glEnd();
}

void Face::drawFace(Vertex p1, Vertex p2, Vertex p3, Vertex p4){
	glBegin(GL_POLYGON);
		glVertex3f(p1.posX, p1.posY, p1.posZ);
		glVertex3f(p2.posX, p2.posY, p2.posZ);
		glVertex3f(p4.posX, p4.posY, p4.posZ);
		glVertex3f(p3.posX, p3.posY, p3.posZ);
	glEnd();
}
