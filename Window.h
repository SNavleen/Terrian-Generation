#ifndef __WINDOW_H__
#define __WINDOW_H__

class Window{
    public:
        //Constructors
        Window(char *view);

        //Deconstructor
        ~Window();

        //Public variables

        //Public function
        /*Window setWidth(int width);*/
        void setWidth(int width);
        /*Window getWidth();*/
        int getWidth();

        /*Window setHeight(int height);*/
        void setHeight(int height);
        /*Window getHeight();*/
        int getHeight();

        /*Window setPosX(int posX);*/
        void setPosX(int posX);
        /*Window getPosX();*/
        int getPosX();

        /*Window setPosY(int posY);*/
        void setPosY(int posY);
        /*Window getPosY();*/
        int getPosY();

        /*Window setDisplay(char *view);*/
        void setDisplay(char *view);
        /*Window viewDisplay();*/
        void viewDisplay();

    private:
        //Private Variables
        int width, height, posX, posY;

        char *view;

};

#endif
