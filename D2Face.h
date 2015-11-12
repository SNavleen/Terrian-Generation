#ifndef __D2FACE_H__
#define __D2FACE_H__

#include "Vertex.h"
class D2Face{
    public:
        //Constructors
        D2Face();
        D2Face(int point1, int point2, int point3, int point4);

        //Deconstructor
        ~D2Face();

        //Public variables
        int point1, point2, point3, point4;

        //Public function
        /*Face drawEdge(Vertex p1, Vertex p2, Vertex p3, Vertex p4, int meshsize)*/
        void drawEdge(Vertex p1, Vertex p2, Vertex p3, Vertex p4, int meshsize);
        /*Face drawFace(Vertex p1, Vertex p2, Vertex p3, Vertex p4, int meshsize)*/
        void drawFace(Vertex p1, Vertex p2, Vertex p3, Vertex p4, int meshsize);

    private:
        //Private Variables

};

#endif
