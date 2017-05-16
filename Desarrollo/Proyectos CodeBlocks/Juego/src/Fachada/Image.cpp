#include "Fachada/Image.h"
#include "Fachada/GraphicsFacade.h"

Image::Image(const char* cadena, Structs::TRectangulo rec)
{
    //image = GraphicsFacade::getInstance().getDriver()->getTexture(cadena);
    image = new TDraw2D(cadena, sf::Vector2i(rec.X_final, rec.Y_final));
}

Image::~Image()
{
    //dtor
}

void Image::draw(int posicionX, int posicionY){
    //GraphicsFacade::getInstance().draw2DImage(image, position2d<s32>(posicionX, posicionY), rect<s32>(rec.X_inicio, rec.Y_inicio, rec.X_final, rec.Y_final), 0, SColor(color.opacity, color.r, color.g, color.b), true);
    GraphicsFacade::getInstance().getMotor->draw2D(posicionX, posicionY, image);
}
