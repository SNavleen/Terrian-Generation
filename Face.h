#ifndef __FACE_H__
#define __FACE_H__

#include "Vertex.h"
class Face{
    public:
        //Constructors
        Face();
        Face(int point1, int point2, int point3, int point4);

        //Deconstructor
        ~Face();

        //Public variables
        int point1, point2, point3, point4;

        //Public function
        /*Face getNormalize(Vertex p1)*/
        float* getNormalize(Vertex p1);
        /*Face drawEdge(Vertex p1, Vertex p2, Vertex p3, Vertex p4)*/
        void drawEdge(Vertex p1, Vertex p2, Vertex p3, Vertex p4);
        /*Face drawFace(Vertex p1, Vertex p2, Vertex p3, Vertex p4)*/
        void drawFace(Vertex p1, Vertex p2, Vertex p3, Vertex p4);

    private:
        //Private Variables

};

#endif
