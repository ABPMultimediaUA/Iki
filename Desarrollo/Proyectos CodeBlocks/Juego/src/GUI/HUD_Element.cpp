#include "GUI/HUD_Element.h"
#include "Fachada/Image.h"
#include "MyEventReceiver.h"

HUD_Element::HUD_Element(int x, int y, Structs::TRectangulo rect, std::string cadena, bool act)
{
    cadena = "resources/Texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    rec = rect;
    imagen = new Image(c, rec);

    posicionX = x;
    posicionY = y;
    color = {255,255,255,255};
    active = act;
}

HUD_Element::~HUD_Element()
{
    delete imagen;
}

void HUD_Element::draw(){
    imagen->draw(posicionX, posicionY);
}

void HUD_Element::cambiarRect(Structs::TRectangulo rect){
    rec = rect;
}

bool HUD_Element::comprobarEncima(){

    if(   (sf::Mouse::getPosition().x > posicionX
       && sf::Mouse::getPosition().x < posicionX + 79)
       && (sf::Mouse::getPosition().y > posicionY
       && sf::Mouse::getPosition().y< posicionY + 79))

        return true;
    else
        return false;
}

void HUD_Element::setActive(bool act){
    active = act;
}

void HUD_Element::setPosition(int x, int y){
    posicionX = x;
    posicionY = y;
}

void HUD_Element::changeColor(Structs::TColor col){
    color = col;
}

