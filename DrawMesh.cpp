#include <stdio.h>
#include <stdlib.h>
#include <vector>
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

#include "DrawMesh.h"
#include "Vertex.h"
#include "Face.h"
#include "D2Face.h"
using namespace std;

vector <Vertex> *vertex;
vector <Face> *face;
Face objFace;
D2Face objD2Face;
float **heightmap;

//Constructors
DrawMesh::DrawMesh(){
    vertex = new vector<Vertex>();
    face = new vector<Face>();
}

//Deconstructor
DrawMesh::~DrawMesh(){
}

//Public function

/*DrawMesh setMeshSize(int meshsize);*/
void DrawMesh::setMeshSize(int meshsize){
    this->meshsize = meshsize;
}

/*DrawMesh setAllVertex();*/
void DrawMesh::setAllVertex(){
    int y = 0;
    for(int z = 0; z <= meshsize; z++){
        for(int x = 0; x <= meshsize; x++){
            Vertex v = Vertex(x, y, z);
            vertex->push_back(v);
        }
    }
}
/*DrawMesh setAllFace();*/
void DrawMesh::setAllFace(){
    for(int i = 0; i < meshsize; i++){
        for(int j = 0; j < meshsize; j++){
            int p1 = (j)+(meshsize+1)*i;
            int p2 = (j+1)+(meshsize+1)*i;
            int p3 = (j+meshsize+1)+(meshsize+1)*i;
            int p4 = (j+meshsize+2)+(meshsize+1)*i;
            Face f = Face(p1, p2, p3, p4);
            face->push_back(f);
        }
    }
}

/*DrawMesh resetVertex();*/
void DrawMesh::resetVertex(){
    while (!vertex->empty()){
        vertex->pop_back();
    }
}
/*DrawMesh resetFace();*/
void DrawMesh::resetFace(){
    while (!face->empty()){
        face->pop_back();
    }
}

/*DrawMesh heightFault();*/
void DrawMesh::heightFault(){
    //http://www.lighthouse3d.com/opengl/terrain/index.php?impdetails
    float v = static_cast <float> (rand()),
          a = sin(v),
          b = cos(v),
          d = sqrt(meshsize*meshsize + meshsize*meshsize),
          c = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * d - d/2;

    int x = 0, z = -1;
    for(int i = 0; i < vertex->size(); i++){
        x = i%(meshsize+1);
        if(x == 0){
            z++;
        }
        if(a*(x-meshsize/2)+b*(z-meshsize/2)-c > 0){
            vertex->at(i).posY += 1;
        }else{
            vertex->at(i).posY -= 1;
        }
    }
}
/*DrawMesh circleAlgorithm();*/
//https://github.com/iSimar/TerrainGenerator-OpenGL/blob/master/Assignment%203/terrain.cpp
void DrawMesh::circleAlgorithm(){
    int randX = rand()%meshsize,
        randZ = rand()%meshsize,
        randR = (rand()%30)+10,
        x = 0,
        z = -1;

    float displacement = (rand()%12)+1;
    for(int i = 0; i < vertex->size(); i++){
        x = i%(meshsize+1);
        if(x == 0){
            z++;
        }

        int dx = x - randX,
            dz = z - randZ;
        float distance = sqrtf((dx*dx) + (dz*dz)),
              radius = (distance*2)/randR;
        if(fabs(radius) <= 1.0){
            vertex->at(i).posY += (displacement/2.0) + (cos(radius*3.14)*(displacement/2.0));
        }
    }
}

void DrawMesh::heightMap() {
    int z = 0, x = -1;
    heightmap = new float *[meshsize];
    for(int i = 0; i < vertex->size(); i++){
        z = i%(meshsize+1);
        if(z == 0){
            x++;
            heightmap[x] = new float [meshsize];
        }
        heightmap[x][z] = 0;
    }
}

void DrawMesh::midPoint() {
    heightMap();
    int z = 0, x = -1;
    heightmap = new float *[meshsize];
    for(int i = 0; i < vertex->size()-2; i++){
        z = i%(meshsize+1);
        if(z == 0){
            x++;
            heightmap[x] = new float [meshsize];
        }
        vertex->at(i).posY = (heightmap[z][x] + heightmap[z+1][x] + heightmap[z+2][x] + heightmap[z][x+1] + heightmap[z+2][x+1] + heightmap[z][x+2] + heightmap[z+1][x+2] + heightmap[z+2][x+2])/8;
    }
}

/*DrawMesh grayScale()*/
void DrawMesh::grayScale(){
    float minHeight = 0,
          maxHeight = 0;
    int x = 0, z = -1;

    for(int i = 0; i < vertex->size(); i++){
        x = i%(meshsize+1);
        if(x == 0){
            z++;
        }

        if(vertex->at(i).posY<minHeight){
            minHeight = vertex->at(i).posY;
        }else if(vertex->at(i).posY>maxHeight){
            maxHeight = vertex->at(i).posY;
        }
    }
    this->maxHeight = maxHeight;
    this->minHeight = minHeight;
}

/*DrawMesh drawTerrain();*/
void DrawMesh::drawTerrain(int wireFrame){
    if(wireFrame%3 == 0 || wireFrame%3 == 2){
        grayScale();

        for(int i = 0; i < face->size(); i++){
            float colour = ((vertex->at(face->at(i).point1).posY - minHeight)/(maxHeight-minHeight))+0.2;
            if(maxHeight == 0 && minHeight == 0){
                colour = 0.2;
            }
            glColor3f(colour, colour, colour);
            objFace.drawFace(vertex->at(face->at(i).point1),
                vertex->at(face->at(i).point2),
                vertex->at(face->at(i).point3),
                vertex->at(face->at(i).point4));
        }
    }
    if(wireFrame%3 == 0 || wireFrame%3 == 1){
        glColor3f(1, 1, 1);
        for(int i = 0; i < face->size(); i++){
            objFace.drawEdge(vertex->at(face->at(i).point1),
                vertex->at(face->at(i).point2),
                vertex->at(face->at(i).point3),
                vertex->at(face->at(i).point4));
        }
    }
}
/*DrawMesh draw2DTerrain();*/
void DrawMesh::draw2DTerrain(int wireFrame){
    if(wireFrame%3 == 0 || wireFrame%3 == 2){
        grayScale();

        for(int i = 0; i < face->size(); i++){
            float colour = ((vertex->at(face->at(i).point1).posY - minHeight)/(maxHeight-minHeight))+0.2;
            if(maxHeight == 0 && minHeight == 0){
                colour = 0.2;
            }
            glColor3f(colour, colour, colour);
            objD2Face.drawFace(vertex->at(face->at(i).point1),
                vertex->at(face->at(i).point2),
                vertex->at(face->at(i).point3),
                vertex->at(face->at(i).point4),
                meshsize);
        }
    }
    if(wireFrame%3 == 0 || wireFrame%3 == 1){
        glColor3f(1, 1, 1);
        for(int i = 0; i < face->size(); i++){
        //printf("%f, %f\n", vertex->at(face->at(i).point1).posX-meshsize/2,  vertex->at(face->at(i).point1).posZ-meshsize/2);
            objD2Face.drawEdge(vertex->at(face->at(i).point1),
                vertex->at(face->at(i).point2),
                vertex->at(face->at(i).point3),
                vertex->at(face->at(i).point4),
                meshsize);
        }
    }
    //glTranslatef(-1, -1, 0);
}
