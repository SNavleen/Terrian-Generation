#ifndef __DRAWMESH_H__
#define __DRAWMESH_H__

class DrawMesh{
    public:
        //Constructors
        DrawMesh();

        //Deconstructor
        ~DrawMesh();

        //Public variables

        //Public function
        /*DrawMesh setMeshSize(int meshsize);*/
        void setMeshSize(int meshsize);

        /*DrawMesh setAllVertex();*/
        void setAllVertex();
        /*DrawMesh setAllFace();*/
        void setAllFace();
        /*DrawMesh resetVertex();*/
        void resetVertex();
        /*DrawMesh resetFace();*/
        void resetFace();

        /*DrawMesh heightFault();*/
        void heightFault();
        /*DrawMesh circleAlgorithm();*/
        void circleAlgorithm();
        /*DrawMesh heightMap();*/
        void heightMap();
        /*DrawMesh midPoint();*/
        void midPoint();
        /*DrawMesh drawTerrain(int wireFrame);*/
        void drawTerrain(int wireFrame);
        /*DrawMesh draw2DTerrain(int wireFrame);*/
        void draw2DTerrain(int wireFrame);

    private:
        /*DrawMesh grayScale();*/
        void grayScale();

        //Private Variables
        int meshsize;
        float maxHeight, minHeight;

};

#endif
