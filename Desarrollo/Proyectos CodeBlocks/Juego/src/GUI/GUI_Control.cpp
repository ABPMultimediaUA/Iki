#include "GUI_Control.h"
#include "Fachada/Image.h"

GUI_Control::GUI_Control(int x, int y, std::string cadena, std::string cadena2)
{
    cadena = "resources/texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    image = new Image(c);

    cadena2 = "resources/texturas/"+cadena2+".png";
    const char * c2 = cadena2.c_str();
    image2 = new Image(c2);

    posicionX = x;
    posicionY = y;

    posicionX2 = posicionX + 168;
    posicionY2 = posicionY + 15;

    rec       = {0, 0, 214, 145};
    rec2      = {0, 0, 23 , 23 };
}

GUI_Control::~GUI_Control()
{
    delete image;
    delete image2;
}

void GUI_Control::draw(){
    Structs::TColor color = {255, 255, 255, 255};
    image->draw(posicionX, posicionY, rec, color);
    image2->draw(posicionX2, posicionY2, rec2, color);
}

int GUI_Control::comprobarmouse(float x, float y){

    if(x > posicionX + 10 && x < posicionX + 200){

        if(y > posicionY+10 && y < posicionY + 41.25){
            estaencima = true;
            posicionY2 = posicionY + 15;
       }else if(y > posicionY+41.25 && y < posicionY + 72.50){
            estaencima = true;
            posicionY2 = posicionY + 42;
            return 1;
       }else if(y > posicionY+72.50 && y < posicionY + 103.75){
            estaencima = true;
            posicionY2 = posicionY + 71;
            return 2;
       }else if(y > posicionY+103.75 && y < posicionY + 135){
            estaencima = true;
            posicionY2 = posicionY + 100;
            return 3;
       }else{
            estaencima = false;
       }

    }else
        estaencima = false;
    return 0;

}
