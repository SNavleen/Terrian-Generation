#include <stdio.h>
#include <stdlib.h>

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

#include "Vertex.h"

//Constructors
Vertex::Vertex(float posX, float posY, float posZ){
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
}

//Deconstructor
Vertex::~Vertex(){
}

//Public function
